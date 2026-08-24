// Le o vetor de quadruplas e gera assembly
// Todas as variaveis e temporarios ficam na memoria de dados
// registradores $t0, $t1, $t2 sao usados como scratch (load -> compute -> store).
//
// Registradores utilizados:
//   $zero (r0)  - sempre 0
//   $v0   (r2)  - valor de retorno
//   $t0   (r8)  - scratch operando 1
//   $t1   (r9)  - scratch operando 2
//   $t2   (r10) - scratch resultado / auxiliar
//   $s0   (r16) - calculo de endereco (vetores)
//   $sp   (r29) - stack pointer
//   $ra   (r31) - return address
//
// Layout da memoria de dados:
//   0 .. N-1        : globais e vetores
//   pilha 255 -> baixo : frames de funcao
//
// Frame de funcao (a partir de $sp apos prologo):
//   $sp + 0 .. num_temps-1            : temporarios
//   $sp + num_temps .. frame_inner-1  : variaveis locais
//   $sp + frame_inner                 : $ra salvo
//   $sp + frame_inner+1 .. +num_params: argumentos (empilhados pelo caller)
//
//   - PARAM diferido: argumentos sao empilhados so no CALL,
//     evitando corromper offsets entre PARAM e CALL.
//   - Constantes numericas nao sao contadas como locais.
//   - output() simplificado (sem push/pop desnecessario).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "cgen.h"

#define MAX_FUNCS    32
#define MAX_LOCALS   64
#define CG_MAX_PARAMS 32

// informacoes de frame para cada funcao
typedef struct {
    char *name;
    int   num_params;
    char *params[CG_MAX_PARAMS];   /* nomes dos parâmetros              */
    int   param_is_array[CG_MAX_PARAMS]; /* 1 se o param é vetor        */
    int   num_locals;
    char *locals[MAX_LOCALS];      /* nomes das variáveis locais        */
    int   first_temp;              /* menor índice $tN nesta função     */
    int   last_temp;               /* maior índice $tN nesta função     */
    int   num_temps;               /* last - first + 1                  */
    int   frame_inner;             /* num_temps + num_locals            */
    int   quad_start;              /* índice da quádrupla FUNC          */
    int   quad_end;                /* índice da quádrupla END_FUNC      */
} FuncFrame;

// Entrada de variável global
typedef struct {
    char  *name;
    int    addr;      /* endereço na memória de dados   */
    int    size;      /* 1 para escalar, N para vetor   */
    TipoID cat;       /* T_VAR ou T_VETOR               */
} GlobalEntry;

static FuncFrame   funcs[MAX_FUNCS];
static int         num_funcs = 0;

static GlobalEntry globs[128];
static int         num_globs = 0;
static int         next_glob_addr = 0;

// argumentos diferidos do PARAM (empilhados somente no CALL)
static const char *deferred_args[CG_MAX_PARAMS];
static int         deferred_is_arr[CG_MAX_PARAMS];
static int         deferred_count = 0;

extern Escopo *lista_escopos;

// FUNÇÕES AUXILIARES

static int is_temp(const char *s)  { return s && s[0]=='$' && s[1]=='t' && isdigit((unsigned char)s[2]); }
static int temp_idx(const char *s) { return atoi(s+2); }
static int is_dash(const char *s)  { return !s || strcmp(s,"-")==0; }

static int is_number(const char *s) {
    if (!s || *s=='\0') return 0;
    const char *p = s;
    if (*p=='-') p++;
    if (*p=='\0') return 0;
    while (*p) { if (!isdigit((unsigned char)*p)) return 0; p++; }
    return 1;
}

// Devolve 1 se op aritmético 
static int is_arith(const char *op) {
    return strcmp(op,"+")==0||strcmp(op,"-")==0||strcmp(op,"*")==0||strcmp(op,"/")==0;
}

// Devolve 1 se op relacional
static int is_relop(const char *op) {
    return strcmp(op,"<")==0||strcmp(op,"<=")==0||strcmp(op,">")==0||
           strcmp(op,">=")==0||strcmp(op,"==")==0||strcmp(op,"!=")==0;
}

// converte operador aritmetico do CI para mnemonico MIPS
static const char *arith_mips(const char *op) {
    if (strcmp(op,"+")==0) return "ADD";
    if (strcmp(op,"-")==0) return "SUB";
    if (strcmp(op,"*")==0) return "MUL";
    if (strcmp(op,"/")==0) return "DIV";
    return "???";
}

// negacao da comparacao para merge com JZ
// JZ pula quando a condicao e falsa, entao emite branch com condição negada
// ex: CI > + JZ -> BLE (pula se nao maior => menor-ou-igual)
static const char *negate_branch(const char *op) {
    if (strcmp(op,">")==0)  return "BLE";
    if (strcmp(op,"<")==0)  return "BGE";
    if (strcmp(op,">=")==0) return "BLT";
    if (strcmp(op,"<=")==0) return "BGT";
    if (strcmp(op,"==")==0) return "BNE";
    if (strcmp(op,"!=")==0) return "BEQ";
    return "???";
}

// separa "v[$t3]" em name="v" e idx="$t3", retorna 1 se for acesso a vetor
static int parse_arr(const char *s, char *name, char *idx) {
    const char *br = strchr(s,'[');
    if (!br) return 0;
    int len = (int)(br-s);
    strncpy(name,s,len); name[len]='\0';
    const char *end = strchr(br,']');
    len = (int)(end-br-1);
    strncpy(idx,br+1,len); idx[len]='\0';
    return 1;
}

// BUSCA DE VARIÁVEIS (globais, parâmetros, locais)

static GlobalEntry *find_glob(const char *n) {
    for (int i=0;i<num_globs;i++) if (strcmp(globs[i].name,n)==0) return &globs[i];
    return NULL;
}
static int find_param(FuncFrame *f, const char *n) {
    for (int i=0;i<f->num_params;i++) if (strcmp(f->params[i],n)==0) return i;
    return -1;
}
static int find_local(FuncFrame *f, const char *n) {
    for (int i=0;i<f->num_locals;i++) if (strcmp(f->locals[i],n)==0) return i;
    return -1;
}

// consulta tabela de simbolos pra saber se name 'n' é vetor
static int sym_is_array(const char *n) {
    Escopo *e=lista_escopos;
    while(e){Var *v=e->vars;while(v){if(strcmp(v->nome,n)==0&&v->cat==T_VETOR)return 1;v=v->prox;}e=e->prox_all;}
    return 0;
}

// VARREDURA TABELA DE SÍMBOLOS E QUÁDRUPLAS (alocacao)
 
// registra globais e atribui enderecos na memoria de dados
static void scan_globals(void) {
    Escopo *e=lista_escopos;
    while(e){
        Var *v=e->vars;
        while(v){
            if(strcmp(v->escopo,"global")==0 && v->cat!=T_FUNC){
                globs[num_globs].name=v->nome;
                globs[num_globs].cat=v->cat;
                globs[num_globs].addr=next_glob_addr;
                if(v->cat==T_VETOR){
                    int sz=v->tamanho>0?v->tamanho:1;
                    globs[num_globs].size=sz;
                    next_glob_addr+=sz;
                } else {
                    globs[num_globs].size=1;
                    next_glob_addr+=1;
                }
                num_globs++;
            }
            v=v->prox;
        }
        e=e->prox_all;
    }
}

// atualiza o range de temporarios usados pela funcao
static void track_temp(FuncFrame *f, const char *s) {
    if (!is_temp(s)) return;
    int idx=temp_idx(s);
    if (f->first_temp<0||idx<f->first_temp) f->first_temp=idx;
    if (idx>f->last_temp) f->last_temp=idx;
}

// registra variavel local se ainda nao foi registrada e nao for global/param/temp
static void track_local(FuncFrame *f, const char *s) {
    if (!s||is_dash(s)||is_temp(s)||is_number(s)) return;
    if (s[0]=='L'&&isdigit((unsigned char)s[1])) return;
    char base[128];
    const char *br=strchr(s,'[');
    if(br){int n=(int)(br-s);strncpy(base,s,n);base[n]='\0';}
    else strcpy(base,s);
    if (find_glob(base))       return;
    if (find_param(f,base)>=0) return;
    if (find_local(f,base)>=0) return;
    Escopo *e=lista_escopos;
    while(e){Var *v=e->vars;while(v){if(strcmp(v->nome,base)==0&&v->cat==T_FUNC)return;v=v->prox;}e=e->prox_all;}
    f->locals[f->num_locals++]=strdup(base);
}

// varre as quadruplas e monta o FuncFrame de cada funcao
static void scan_functions(void) {
    for (int i=0;i<quad_count;i++){
        if (strcmp(quads[i].op,"FUNC")!=0) continue;
        FuncFrame *f=&funcs[num_funcs++];
        memset(f,0,sizeof(FuncFrame));
        f->name=quads[i].arg1; f->quad_start=i;
        f->first_temp=-1; f->last_temp=-1;
        for (int j=i+1;j<quad_count;j++){
            if(strcmp(quads[j].op,"END_FUNC")==0&&strcmp(quads[j].arg1,f->name)==0){f->quad_end=j;break;}

            // Parâmetros formais
            if(strcmp(quads[j].op,"PARAM_DECL")==0){
                int pi=f->num_params;
                f->params[pi]=quads[j].arg1;
                f->param_is_array[pi]=sym_is_array(quads[j].arg1);
                f->num_params++;
                continue;
            }
            // temporarios e locais nos 3 campos da quadrupla
            track_temp(f,quads[j].arg1); track_temp(f,quads[j].arg2); track_temp(f,quads[j].res);

            // Só rastreia locais em quads que NÃO são FUNC/END_FUNC/CALL/LABEL/JMP/JZ
            if(strcmp(quads[j].op,"CALL")!=0&&strcmp(quads[j].op,"JMP")!=0&&
               strcmp(quads[j].op,"JZ")!=0&&strcmp(quads[j].op,"LABEL")!=0){
                track_local(f,quads[j].arg1); track_local(f,quads[j].arg2); track_local(f,quads[j].res);
            }
        }
        f->num_temps=(f->first_temp>=0)?(f->last_temp-f->first_temp+1):0;
        f->frame_inner=f->num_temps+f->num_locals;
    }
}

static FuncFrame *func_by_name(const char *n) {
    for (int i=0;i<num_funcs;i++) if(strcmp(funcs[i].name,n)==0) return &funcs[i];
    return NULL;
}

// EMISSÃO DE LOAD / STORE

// offsets dentro do frame
static int off_temp (FuncFrame *f,const char *s){return temp_idx(s)-f->first_temp;}
static int off_local(FuncFrame *f,int li)       {return f->num_temps+li;}
static int off_param(FuncFrame *f,int pi)       {return f->frame_inner+f->num_params-pi;}

// emit_load / emit_store recebem 'adj':
// quando $sp foi pre-decrementado pra empilhar argumentos,
// todos os offsets baseados em $sp precisam de + adj.
// pra acessos globais ($zero-based), adj e ignorado.
static void emit_load(FILE *out, const char *operand, FuncFrame *f, const char *dreg, int adj) {
    if (!operand||is_dash(operand)) return;

    // temporario
    if (is_temp(operand)){
        fprintf(out,"    LW %s, %d($sp)\n",dreg,off_temp(f,operand)+adj);
        return;
    }
    // vetor arr[idx]
    char aname[128],aidx[128];
    if (parse_arr(operand,aname,aidx)){
        emit_load(out,aidx,f,"$s0",adj);
        GlobalEntry *g=find_glob(aname);
        if(g){
            fprintf(out,"    ADDI $s0, $s0, %d\n",g->addr);
        } else {
            int pi=find_param(f,aname);
            if(pi>=0){
                fprintf(out,"    LW %s, %d($sp)\n",dreg,off_param(f,pi)+adj);
                fprintf(out,"    ADD $s0, $s0, %s\n",dreg);
            }
        }
        fprintf(out,"    LW %s, 0($s0)\n",dreg);
        return;
    }
    // parametro
    int pi=find_param(f,operand);
    if(pi>=0){fprintf(out,"    LW %s, %d($sp)\n",dreg,off_param(f,pi)+adj);return;}
    // local
    int li=find_local(f,operand);
    if(li>=0){fprintf(out,"    LW %s, %d($sp)\n",dreg,off_local(f,li)+adj);return;}
    // global
    GlobalEntry *g=find_glob(operand);
    if(g){fprintf(out,"    LW %s, %d($zero)\n",dreg,g->addr);return;}

    fprintf(out,"    # ?? load: %s\n",operand);
}

// armazena 'sreg' em 'target'
static void emit_store(FILE *out, const char *target, FuncFrame *f, const char *sreg, int adj) {
    if (!target||is_dash(target)) return;

    // Temporário
    if (is_temp(target)){
        fprintf(out,"    SW %s, %d($sp)\n",sreg,off_temp(f,target)+adj);
        return;
    }

    // Acesso a vetor arr[$tI]
    char aname[128],aidx[128];
    if (parse_arr(target,aname,aidx)){
        emit_load(out,aidx,f,"$s0",adj);
        GlobalEntry *g=find_glob(aname);
        if(g){
            fprintf(out,"    ADDI $s0, $s0, %d\n",g->addr);
        } else {
            int pi=find_param(f,aname);
            if(pi>=0){
                fprintf(out,"    LW $t1, %d($sp)\n",off_param(f,pi)+adj);
                fprintf(out,"    ADD $s0, $s0, $t1\n");
            }
        }
        fprintf(out,"    SW %s, 0($s0)\n",sreg);
        return;
    }

    // Parâmetro
    int pi=find_param(f,target);
    if(pi>=0){fprintf(out,"    SW %s, %d($sp)\n",sreg,off_param(f,pi)+adj);return;}

    // Local
    int li=find_local(f,target);
    if(li>=0){fprintf(out,"    SW %s, %d($sp)\n",sreg,off_local(f,li)+adj);return;}
    
    // Global escalar
    GlobalEntry *g=find_glob(target);
    if(g){fprintf(out,"    SW %s, %d($zero)\n",sreg,g->addr);return;}

    fprintf(out,"    # ?? store: %s\n",target);
}

// carrega o endereco-base de um vetor (para passagem por referencia)
static void emit_load_addr(FILE *out, const char *name, FuncFrame *f, const char *dreg, int adj) {
    GlobalEntry *g=find_glob(name);
    if(g){fprintf(out,"    ADDI %s, $zero, %d\n",dreg,g->addr);return;}
    int pi=find_param(f,name);
    if(pi>=0){fprintf(out,"    LW %s, %d($sp)\n",dreg,off_param(f,pi)+adj);return;}
    fprintf(out,"    # ?? addr: %s\n",name);
}

// Emite o epílogo de uma função (restaura $sp, $ra e retorna)
static void emit_epilogue(FILE *out, FuncFrame *f) {
    if(f->frame_inner>0) fprintf(out,"    ADDI $sp, $sp, %d\n",f->frame_inner);
    fprintf(out,"    LW $ra, 0($sp)\n");
    fprintf(out,"    ADDI $sp, $sp, 1\n");
    fprintf(out,"    JR $ra\n");
}


// LOOP PRINCIPAL DE GERAÇÃO DE ASSEMBLY 

void generate_assembly(FILE *out) {
    // alocação
    num_funcs=0; 
    num_globs=0; 
    next_glob_addr=0;
    scan_globals();
    scan_functions();

    // inicializa $sp no topo da pilha (= 255) e pula pra main
    fprintf(out,"    ADDI $sp, $zero, 255\n");
    fprintf(out,"    J main\n");

    FuncFrame *cf=NULL;
    deferred_count=0;

    for (int i=0;i<quad_count;i++){
        const char *op=quads[i].op, *a1=quads[i].arg1, *a2=quads[i].arg2, *res=quads[i].res;

        // FUNC: prologo (salva $ra e aloca frame)
        if (strcmp(op,"FUNC")==0){
            cf=func_by_name(a1);
            fprintf(out,"\n%s:\n",a1);
            fprintf(out,"    SUBI $sp, $sp, 1\n");
            fprintf(out,"    SW $ra, 0($sp)\n");
            if(cf->frame_inner>0) fprintf(out,"    SUBI $sp, $sp, %d\n",cf->frame_inner);
        }
        // END_FUNC: epilogo  (restaura $sp, $ra e retorna)
        // ou HALT (se for main)
        else if (strcmp(op,"END_FUNC")==0){
            if(strcmp(a1,"main")==0) fprintf(out,"    HALT\n");
            else emit_epilogue(out,cf);
            cf=NULL;
        }
        // PARAM_DECL: so declaracao, nao emite codigo
        else if (strcmp(op,"PARAM_DECL")==0){ /* nada */ }

        // LDI: carrega constante imediata
        else if (strcmp(op,"LDI")==0){
            fprintf(out,"    ADDI $t0, $zero, %s\n",a1);
            emit_store(out,res,cf,"$t0",0);
        }
        // := atribuicao
        else if (strcmp(op,":=")==0){
            emit_load(out,a1,cf,"$t0",0);
            emit_store(out,res,cf,"$t0",0);
        }
        // operacoes aritmeticas (+, -, *, /)
        else if (is_arith(op)){
            emit_load(out,a1,cf,"$t0",0);
            emit_load(out,a2,cf,"$t1",0);
            fprintf(out,"    %s $t2, $t0, $t1\n",arith_mips(op));
            emit_store(out,res,cf,"$t2",0);
        }
        // comparacao: merge com JZ seguinte
        else if (is_relop(op)){
            emit_load(out,a1,cf,"$t0",0);
            emit_load(out,a2,cf,"$t1",0);
            if(i+1<quad_count&&strcmp(quads[i+1].op,"JZ")==0){
                fprintf(out,"    %s $t0, $t1, %s\n",negate_branch(op),quads[i+1].res);
                i++;
            }
        }
        // JZ avulso (quando nao foi consumido no merge)
        else if (strcmp(op,"JZ")==0){
            emit_load(out,a1,cf,"$t0",0);
            fprintf(out,"    BEQ $t0, $zero, %s\n",res);
        }
        // JMP: desvio incondicional
        else if (strcmp(op,"JMP")==0) fprintf(out,"    J %s\n",res);

        // LABEL
        else if (strcmp(op,"LABEL")==0) fprintf(out,"%s:\n",res);

        // PARAM: armazena argumento diferido (so empilha no CALL)
        else if (strcmp(op,"PARAM")==0){
            deferred_args[deferred_count]=a1;
            deferred_is_arr[deferred_count]=sym_is_array(a1);
            deferred_count++;
        }
        // CALL: chamada de funcao
        else if (strcmp(op,"CALL")==0){
            // input() IN
            if(strcmp(a1,"input")==0){
                fprintf(out,"    IN $v0\n");
                emit_store(out,res,cf,"$v0",0);
            }
            else if(strcmp(a1,"output")==0){
                // output: carrega o argumento e emite OUT direto
                emit_load(out,deferred_args[0],cf,"$t0",0);
                fprintf(out,"    OUT $t0\n");
            }
            else {
                // chamada normal: pre-decrementa $sp e empilha argumentos
                int nc=deferred_count;
                if(nc>0) fprintf(out,"    SUBI $sp, $sp, %d\n",nc);
                for(int p=0;p<nc;p++){
                    if(deferred_is_arr[p])
                        emit_load_addr(out,deferred_args[p],cf,"$t0",nc);
                    else
                        emit_load(out,deferred_args[p],cf,"$t0",nc);
                    fprintf(out,"    SW $t0, %d($sp)\n", nc-1-p);
                }
                fprintf(out,"    JAL %s\n",a1);
                // desempilha argumentos
                if(nc>0) fprintf(out,"    ADDI $sp, $sp, %d\n",nc);
                // Salva valor de retorno
                if(!is_dash(res)) emit_store(out,res,cf,"$v0",0);
            }
            deferred_count=0;
        }
        // RET: carrega valor de retorno em $v0 e faz epilogo
        else if (strcmp(op,"RET")==0){
            if(!is_dash(a1)) emit_load(out,a1,cf,"$v0",0);
            if(cf) emit_epilogue(out,cf);
        }
        // LDV: leitura de vetor (tratada via emit_load)
        else if (strcmp(op,"LDV")==0){
            emit_load(out,a1,cf,"$t0",0);
            emit_store(out,res,cf,"$t0",0);
        }
    }
}
