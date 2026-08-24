// Duas passagens:
//   1) identifica labels e seus enderecos de instrucao
//   2) codifica cada instrucao em 32 bits

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "assembler.h"

#define MAX_INSTS   256
#define MAX_LABELS  128
#define MAX_LINE    256

// funct codes (tipo R, opcode = 000000)
#define FUNCT_ADD   0   
#define FUNCT_SUB   1   
#define FUNCT_MUL   2   
#define FUNCT_DIV   3   
#define FUNCT_AND   4   
#define FUNCT_OR    5   
#define FUNCT_NOR   6   
#define FUNCT_JR    7   
#define FUNCT_SLL   8   
#define FUNCT_SLR   9   

// opcodes tipo I
#define OP_R      0     
#define OP_ADDI   1     
#define OP_SUBI   2     
#define OP_ANDI   3     
#define OP_ORI    4    
#define OP_LW     5    
#define OP_SW     6     
#define OP_BEQ    7    
#define OP_BNE    8     
#define OP_BLT    9    
#define OP_BGT   10    
#define OP_BLE   11     
#define OP_BGE   12     
#define OP_IN    13    
#define OP_OUT   14    

// opcodes tipo J
#define OP_J     16     
#define OP_JAL   17    
#define OP_NOP   18  
#define OP_HALT  19    



typedef struct { char name[64]; int addr; } Label;

static Label  labels[MAX_LABELS];
static int    num_labels = 0;

// instrucoes lidas (só texto, sem labels)
static char   inst_text[MAX_INSTS][MAX_LINE];
static int    num_insts = 0;


// remove espacos/tabs/newline do inicio e do fim
static char *trim(char *s) {
    while (*s == ' ' || *s == '\t') s++;
    int len = strlen(s);
    while (len > 0 && (s[len-1]==' '||s[len-1]=='\t'||s[len-1]=='\n'||s[len-1]=='\r'))
        s[--len] = '\0';
    return s;
}

// converte registrador simbolico para numero fisico
static int reg_num(const char *s) {
    while (*s == ' ' || *s == '\t') s++;
    if (strcmp(s,"$zero")==0) return 0;
    if (strcmp(s,"$v0")==0)   return 2;
    if (strcmp(s,"$t0")==0)   return 8;
    if (strcmp(s,"$t1")==0)   return 9;
    if (strcmp(s,"$t2")==0)   return 10;
    if (strcmp(s,"$s0")==0)   return 16;
    if (strcmp(s,"$sp")==0)   return 29;
    if (strcmp(s,"$ra")==0)   return 31;
    // generico: $rN
    if (s[0]=='$' && s[1]=='r') return atoi(s+2);
    fprintf(stderr, "ERRO ASM: registrador desconhecido '%s'\n", s);
    return 0;
}

// busca label e retorna o endereco
static int find_label(const char *name) {
    for (int i = 0; i < num_labels; i++)
        if (strcmp(labels[i].name, name) == 0) return labels[i].addr;
    fprintf(stderr, "ERRO ASM: label '%s' nao encontrado\n", name);
    return 0;
}

// separa "offset($reg)" em offset e numero do registrador
static void parse_mem(const char *s, int *offset, int *rs) {
    char buf[128];
    strcpy(buf, s);
    char *paren = strchr(buf, '(');
    if (!paren) { *offset = 0; *rs = 0; return; }
    *paren = '\0';
    *offset = atoi(trim(buf));
    char *reg_start = paren + 1;
    char *close = strchr(reg_start, ')');
    if (close) *close = '\0';
    *rs = reg_num(trim(reg_start));
}

// separa uma linha em mnemonico + ate 3 operandos
// retorna o numero de partes (1 = so mnemonico)
static int split_line(const char *line, char parts[4][64]) {
    char buf[MAX_LINE];
    strcpy(buf, line);
    char *p = trim(buf);

    // mnemonico: ate o primeiro espaco
    int i = 0;
    while (*p && *p != ' ' && *p != '\t' && i < 63)
        parts[0][i++] = *p++;
    parts[0][i] = '\0';
    int count = 1;

    while (*p == ' ' || *p == '\t') p++;
    if (*p == '\0') return count;

    // operandos: separados por virgula
    while (*p && count < 4) {
        i = 0;
        while (*p && *p != ',' && i < 63)
            parts[count][i++] = *p++;
        parts[count][i] = '\0';
        // trim do operando
        char *t = parts[count];
        while (*t == ' ' || *t == '\t') memmove(t, t+1, strlen(t));
        int tl = strlen(t);
        while (tl > 0 && (t[tl-1]==' '||t[tl-1]=='\t')) t[--tl] = '\0';
        count++;
        if (*p == ',') p++;
        while (*p == ' ' || *p == '\t') p++;
    }
    return count;
}

// CODIFICAÇÃO BINÁRIA

static uint32_t encode_r(int rs, int rt, int rd, int shamt, int funct) {
    return ((uint32_t)OP_R << 26) | ((rs & 0x1F) << 21) | ((rt & 0x1F) << 16) |
           ((rd & 0x1F) << 11)    | ((shamt & 0x1F) << 6) | (funct & 0x3F);
}

static uint32_t encode_i(int opcode, int rs, int rt, int imm) {
    return ((uint32_t)(opcode & 0x3F) << 26) | ((rs & 0x1F) << 21) |
           ((rt & 0x1F) << 16) | (imm & 0xFFFF);
}

static uint32_t encode_j(int opcode, int target) {
    return ((uint32_t)(opcode & 0x3F) << 26) | (target & 0x3FFFFFF);
}

// imprime 32 bits como string de '0' e '1'
static void fprint_bin(FILE *out, uint32_t val) {
    for (int i = 31; i >= 0; i--)
        fputc((val >> i) & 1 ? '1' : '0', out);
}

// MONTAGEM DE UMA INSTRUÇÃO (PASSAGEM 2)

static uint32_t assemble_one(const char *line, int addr) {
    char p[4][64];
    memset(p, 0, sizeof(p));
    int n = split_line(line, p);
    const char *mn = p[0];         /* mnemônico */

    // tipo R: ADD, SUB, MUL, DIV, AND, OR, NOR
    // formato assembly: OP rd, rs, rt
    int funct = -1;
    if (strcmp(mn,"ADD")==0) funct=FUNCT_ADD;
    if (strcmp(mn,"SUB")==0) funct=FUNCT_SUB;
    if (strcmp(mn,"MUL")==0) funct=FUNCT_MUL;
    if (strcmp(mn,"DIV")==0) funct=FUNCT_DIV;
    if (strcmp(mn,"AND")==0) funct=FUNCT_AND;
    if (strcmp(mn,"OR")==0)  funct=FUNCT_OR;
    if (strcmp(mn,"NOR")==0) funct=FUNCT_NOR;
    if (funct >= 0) {
        int rd = reg_num(p[1]);
        int rs = reg_num(p[2]);
        int rt = reg_num(p[3]);
        return encode_r(rs, rt, rd, 0, funct);
    }

    // JR rs
    if (strcmp(mn,"JR")==0) {
        int rs = reg_num(p[1]);
        return encode_r(rs, 0, 0, 0, FUNCT_JR);
    }

    // tipo I aritmetico: ADDI, SUBI, ANDI, ORI
    // formato assembly: OP rt, rs, imm
    int opcode = -1;
    if (strcmp(mn,"ADDI")==0) opcode=OP_ADDI;
    if (strcmp(mn,"SUBI")==0) opcode=OP_SUBI;
    if (strcmp(mn,"ANDI")==0) opcode=OP_ANDI;
    if (strcmp(mn,"ORI")==0)  opcode=OP_ORI;
    if (opcode >= 0) {
        int rt  = reg_num(p[1]);
        int rs  = reg_num(p[2]);
        int imm = atoi(p[3]);
        return encode_i(opcode, rs, rt, imm);
    }

    // LW rt, offset(rs)
    if (strcmp(mn,"LW")==0) {
        int rt = reg_num(p[1]);
        int offset, rs;
        parse_mem(p[2], &offset, &rs);
        return encode_i(OP_LW, rs, rt, offset);
    }

    // SW rt, offset(rs)
    if (strcmp(mn,"SW")==0) {
        int rt = reg_num(p[1]);
        int offset, rs;
        parse_mem(p[2], &offset, &rs);
        return encode_i(OP_SW, rs, rt, offset);
    }

    // Branches: BEQ, BNE, BLT, BGT, BLE, BGE
    // Formato assembly: Bxx rs, rt, label           
    // offset = label_addr - (addr + 1)               
    opcode = -1;
    if (strcmp(mn,"BEQ")==0) opcode=OP_BEQ;
    if (strcmp(mn,"BNE")==0) opcode=OP_BNE;
    if (strcmp(mn,"BLT")==0) opcode=OP_BLT;
    if (strcmp(mn,"BGT")==0) opcode=OP_BGT;
    if (strcmp(mn,"BLE")==0) opcode=OP_BLE;
    if (strcmp(mn,"BGE")==0) opcode=OP_BGE;
    if (opcode >= 0) {
        int rs     = reg_num(p[1]);
        int rt     = reg_num(p[2]);
        int target = find_label(p[3]);
        int offset = target - (addr + 1);
        return encode_i(opcode, rs, rt, offset);
    }

    // J label
    if (strcmp(mn,"J")==0) {
        int target = find_label(p[1]);
        return encode_j(OP_J, target);
    }

    // JAL label
    if (strcmp(mn,"JAL")==0) {
        int target = find_label(p[1]);
        return encode_j(OP_JAL, target);
    }

    // IN rt
    if (strcmp(mn,"IN")==0) {
        int rt = reg_num(p[1]);
        return encode_i(OP_IN, 0, rt, 0);
    }

    // OUT rs
    if (strcmp(mn,"OUT")==0) {
        int rs = reg_num(p[1]);
        return encode_i(OP_OUT, rs, 0, 0);
    }

    // HALT
    if (strcmp(mn,"HALT")==0) return encode_j(OP_HALT, 0);

    // NOP
    if (strcmp(mn,"NOP")==0)  return encode_j(OP_NOP, 0);

    fprintf(stderr, "ERRO ASM: instrucao desconhecida '%s'\n", mn);
    return 0;
}

// FUNÇÃO PRINCIPAL

void generate_binary(const char *asm_file, const char *mif_file) {
    FILE *fin = fopen(asm_file, "r");
    if (!fin) { perror("Erro ao abrir .asm"); return; }

    char line[MAX_LINE];
    num_labels = 0;
    num_insts  = 0;

    // passagem 1: identifica labels e seus enderecos
    int inst_addr = 0;
    while (fgets(line, sizeof(line), fin)) {
        char *t = trim(line);
        if (strlen(t) == 0) continue;               // linha vazia
        if (t[0] == '/' && t[1] == '/') continue;    // comentario

        int len = strlen(t);
        if (t[len - 1] == ':') {
            // É um label
            t[len - 1] = '\0';
            strncpy(labels[num_labels].name, t, 63);
            labels[num_labels].addr = inst_addr;
            num_labels++;
        } else {
            // É uma instrução
            strncpy(inst_text[num_insts], t, MAX_LINE - 1);
            num_insts++;
            inst_addr++;
        }
    }
    fclose(fin);

    // passagem 2: codificar e gravar .mif
    FILE *fout = fopen(mif_file, "w");
    if (!fout) { perror("Erro ao criar .mif"); return; }

    for (int i = 0; i < num_insts; i++) {
        uint32_t encoded = assemble_one(inst_text[i], i);
        fprint_bin(fout, encoded);
        fprintf(fout, " // %d: %s\n", i, inst_text[i]);
    }

    fclose(fout);
    printf("--> Arquivo '%s' gerado com sucesso! (%d instrucoes) <--\n",
           mif_file, num_insts);
}