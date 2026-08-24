/* util.c - Funções utilitárias */
#include "globals.h"
#include "parser.tab.h"

/* === Funções da AST === */

/* Cria um nó de COMANDO (If, While, Atribuição...) */
NoArvore * novoNoComando(TipoComando tipo) {
    NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
    if (t == NULL) {
        fprintf(stderr, "Erro de memoria na linha %d\n", linha);
    } else {
        for (int i=0; i < MAX_FILHOS; i++) t->filhos[i] = NULL;
        t->irmao = NULL;
        t->tipo_no = NoComando;   // Define como Nó de Comando
        t->tipo.cmd = tipo;      // Guarda qual comando é (If, While...)
        t->linha = linha;
    }
    return t;
}

/* Cria um nó de EXPRESSÃO (Soma, ID, Número...) */
NoArvore * novoNoExpr(TipoExpr tipo) {
    NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
    if (t == NULL) {
        fprintf(stderr, "Erro de memoria na linha %d\n", linha);
    } else {
        for (int i=0; i < MAX_FILHOS; i++) t->filhos[i] = NULL;
        t->irmao = NULL;
        t->tipo_no = NoExpressao; // Define como Nó de Expressão
        t->tipo.expr = tipo;     // Guarda qual expressão é
        t->linha = linha;
        // t->tipoDados será preenchido pelo analisador semântico depois
    }
    return t;
}

char * copiaString(char * s) {
    int n;
    char * t;
    if (s == NULL) return NULL;
    n = strlen(s)+1;
    t = malloc(n);
    if (t == NULL) fprintf(stderr, "Erro de memoria na linha %d\n", linha);
    else strcpy(t,s);
    return t;
}


// Impressão da AST

/* Variável auxiliar para indentação */
static int indentno = 0;
#define INDENT indentno+=4
#define UNINDENT indentno-=4

/* Função auxiliar para imprimir espaços */
static void printSpaces(void) {
    int i;
    for (i=0;i<indentno;i++)
      fprintf(stdout," ");
}

/* A função principal de impressão */
void imprimeArvore(NoArvore * tree) { 
    int i;
    INDENT;
    while (tree != NULL) {
      printSpaces();
      
      if (tree->tipo_no == NoComando) {
        switch (tree->tipo.cmd) {
          case comandoIF:       fprintf(stdout,"If\n"); break;
          case comandoRepeat:   fprintf(stdout,"Repeat (While)\n"); break;
          case comandoAssign:   fprintf(stdout,"Atribuicao\n"); break;
          case comandoReturn:   fprintf(stdout,"Return\n"); break;
          case comandoCompound: fprintf(stdout,"Comando Composto (Bloco)\n"); break;
          default:              fprintf(stdout,"Comando Desconhecido\n"); break;
        }
      }
      else if (tree->tipo_no == NoExpressao) {
        switch (tree->tipo.expr) {
          case OpAritmetica:
            fprintf(stdout,"Op: ");
            // Imprime o caractere do operador (+, -, *, /) ou o código token
            if(tree->atr.op < 256) fprintf(stdout,"%c\n", tree->atr.op);
            else fprintf(stdout,"token <%d>\n", tree->atr.op);
            break;
          case Constante:
            fprintf(stdout,"Constante: %d\n",tree->atr.val);
            break;
          case Identificador:
            fprintf(stdout,"Id: %s\n",tree->atr.nome);
            break;
          case Vetor:
            fprintf(stdout,"Vetor: %s\n",tree->atr.nome);
            break;
          case ChamadaFunc:
            fprintf(stdout,"Chamada de Funcao: %s\n",tree->atr.nome);
            break;
          case TipoEspec:
            fprintf(stdout,"Tipo Declarado\n");
            break;
          default:
            fprintf(stdout,"Exp Node Desconhecido\n");
            break;
        }
      }
      else {
        fprintf(stdout,"Tipo de No Desconhecido\n");
      }

      /* Chama recursivamente para os filhos */
      for (i=0;i<MAX_FILHOS;i++) {
         if (tree->filhos[i] != NULL)
            imprimeArvore(tree->filhos[i]);
      }
      
      /* Avança para o próximo irmão */
      tree = tree->irmao;
    }
    UNINDENT;
}

void printNoGraphviz(FILE * output, NoArvore * tree) {
    if (tree == NULL) return;

    // Gera um identificador único para o nó baseado no endereço de memória
    fprintf(output, "node%p [label=\"", (void*)tree);

    // Define o Rótulo do Nó
    if (tree->tipo_no == NoComando) {
        switch (tree->tipo.cmd) {
            case comandoIF:       fprintf(output, "IF"); break;
            case comandoRepeat:   fprintf(output, "WHILE"); break;
            case comandoAssign:   fprintf(output, ":="); break;
            case comandoReturn:   fprintf(output, "RETURN"); break;
            case comandoCompound: fprintf(output, "BLOCO"); break;
            default:              fprintf(output, "CMD"); break;
        }
    } 
    else if (tree->tipo_no == NoExpressao) {
        switch (tree->tipo.expr) {
            case OpAritmetica:
                if (tree->atr.op < 256) fprintf(output, "Op: %c", tree->atr.op);
                else {
                    switch(tree->atr.op) {
                        /* Aritméticos */
                        case MAIS:        fprintf(output, "+"); break;
                        case MENOS:       fprintf(output, "-"); break;
                        case VEZES:       fprintf(output, "*"); break;
                        case DIVIDIDO:    fprintf(output, "/"); break;
                        
                        /* Relacionais */
                        case MENOR:       fprintf(output, "<"); break;
                        case MENOR_IGUAL: fprintf(output, "<="); break;
                        case MAIOR:       fprintf(output, ">"); break;
                        case MAIOR_IGUAL: fprintf(output, ">="); break;
                        case IGUAL_IGUAL: fprintf(output, "=="); break;
                        case DIFERENTE:   fprintf(output, "!="); break;
                        
                        /* Outros */
                        case ATRIBUICAO:  fprintf(output, ":="); break;
                        /* Adicione os códigos do seu parser.tab.h se diferir */
                        default: fprintf(output, "Token<%d>", tree->atr.op);
                    }
                }
                break;
            case Constante:       fprintf(output, "%d", tree->atr.val); break;
            case Identificador:   fprintf(output, "ID: %s", tree->atr.nome); break;
            case Vetor:           fprintf(output, "VET: %s[ ]", tree->atr.nome); break;
            case ChamadaFunc:     fprintf(output, "CALL: %s", tree->atr.nome); break;
            case TipoEspec:       fprintf(output, "TIPO"); break;
            default:              fprintf(output, "EXP"); break;
        }
    }
    
    // Mostra o tipo de dado (INT/VOID) se relevante
    if (tree->tipoDados == T_INT) fprintf(output, "\\n(int)");
    else if (tree->tipoDados == T_VOID) fprintf(output, "\\n(void)");
    
    fprintf(output, "\"];\n");

    // Conecta com os Filhos (linhas sólidas)
    for (int i = 0; i < MAX_FILHOS; i++) {
        if (tree->filhos[i] != NULL) {
            fprintf(output, "node%p -> node%p;\n", (void*)tree, (void*)tree->filhos[i]);
            printNoGraphviz(output, tree->filhos[i]);
        }
    }

    // Conecta com o Irmão (linha pontilhada para indicar sequência)
    if (tree->irmao != NULL) {
        // rank=same força eles a ficarem na mesma altura visual
        fprintf(output, "{ rank=same; node%p -> node%p [style=dashed]; }\n", (void*)tree, (void*)tree->irmao);
        printNoGraphviz(output, tree->irmao);
    }
}

void imprimeGraphviz(NoArvore * tree) {
    if (tree == NULL) return;
    FILE * fp = fopen("arvore.dot", "w");
    if (fp == NULL) {
        printf("Erro ao criar arquivo arvore.dot\n");
        return;
    }
    
    /* Cabeçalho padrão do Graphviz */
    fprintf(fp, "digraph AST {\n");
    fprintf(fp, "  ordering=out;\n");
    fprintf(fp, "node [shape=box, fontname=\"Arial\"];\n");
    fprintf(fp, "edge [fontname=\"Arial\"];\n");

    /* Chama a recursão */
    printNoGraphviz(fp, tree);

    /* Fecha o arquivo */
    fprintf(fp, "}\n");
    fclose(fp);
    
    printf("\n--> Arquivo 'arvore.dot' gerado com sucesso! <--\n");
}

/* === Geração de Código Intermediário (Quadruplas) === */
/* === Variáveis Globais para Quádruplas === */
Quad *quads = NULL;
int quad_count = 0;
int quad_capacity = 0;
int tmp_count = 0;
int label_count = 0;

/* === Funções para Geração de Código Intermediário === */

/* Copia segura de string */
char *strdup_safe(const char *s){
    if(!s) return NULL;
    char *r = malloc(strlen(s)+1);
    if (r == NULL) {
        fprintf(stderr, "Erro de memoria ao duplicar string\n");
        exit(1);
    }
    strcpy(r,s);
    return r;
}

/* Emite uma nova quádrupla */
void emit(const char *op, const char *a1, const char *a2, const char *res){
    if(quad_count + 1 > quad_capacity){
        quad_capacity = quad_capacity ? quad_capacity * 2 : 256;
        quads = realloc(quads, quad_capacity * sizeof(Quad));
        if (quads == NULL) {
            fprintf(stderr, "Erro de memoria ao realocar quádruplas\n");
            exit(1);
        }
    }
    quads[quad_count].op   = op ? strdup_safe(op) : NULL;
    quads[quad_count].arg1 = a1  ? strdup_safe(a1) : NULL;
    quads[quad_count].arg2 = a2  ? strdup_safe(a2) : NULL;
    quads[quad_count].res  = res ? strdup_safe(res) : NULL;
    quad_count++;
}

/* Limpa todas as quádruplas */
void clear_quads(){
    for(int i=0;i<quad_count;i++){
        free(quads[i].op);
        if(quads[i].arg1) free(quads[i].arg1);
        if(quads[i].arg2) free(quads[i].arg2);
        if(quads[i].res) free(quads[i].res);
    }
    free(quads);
    quads = NULL;
    quad_count = 0;
    quad_capacity = 0;
}

/* Gera um novo temporário */
char *newtemp(){
    char buf[32];
    snprintf(buf,sizeof(buf),"$t%d", tmp_count++);
    return strdup_safe(buf);
}

/* Gera um novo label */
char *newlabel(){
    char buf[32];
    snprintf(buf,sizeof(buf),"L%d", label_count++);
    return strdup_safe(buf);
}

/* Imprime as quádruplas geradas */
void print_quads(FILE *out){
    fprintf(out, "\n=== CODIGO INTERMEDIARIO (QUADRUPLAS) ===\n");
    for(int i=0;i<quad_count;i++){
        Quad *q = &quads[i];
        fprintf(out, "%3d: (%s, %s, %s, %s)\n",
                i,
                q->op ? q->op : "-",
                q->arg1 ? q->arg1 : "-",
                q->arg2 ? q->arg2 : "-",
                q->res  ? q->res  : "-");
    }
    fprintf(out, "==========================================\n");
}
/* Gera quádruplas a partir da AST; retorna "place" (string) que contém o resultado */
char *generate_quads(NoArvore *node){
    if(!node) return NULL;

    char *t, *t1, *t2;
    char buf[128];
    char *label_true, *label_false, *label_end;

    /* Processa nó atual */
    if (node->tipo_no == NoExpressao) {
        switch(node->tipo.expr) {
            case Constante:
                /* Cria um temporário para a constante e emite LDI (load immediate) */
                snprintf(buf, sizeof(buf), "%d", node->atr.val);
                t = newtemp();
                emit("LDI", buf, "-", t);
                return t;

            case Identificador:
                /* Pode ser: 1) Declaração de função, 2) Declaração de variável, 3) Uso de variável */
                if (node->filhos[1] != NULL) {
                    /* É uma declaração de função (tem corpo no filhos[1]) */
                    emit("FUNC", node->atr.nome, "-", "-");
                    
                    /* Processa parâmetros (filhos[0]) se houver */
                    if (node->filhos[0]) {
                        NoArvore *param = node->filhos[0];
                        while (param) {
                            emit("PARAM_DECL", param->atr.nome, "-", "-");
                            param = param->irmao;
                        }
                    }
                    
                    /* Processa corpo da função */
                    generate_quads(node->filhos[1]);
                    
                    emit("END_FUNC", node->atr.nome, "-", "-");
                    /* Continua para processar irmãos no final da função */
                    break;
                } else if (!node->filhos[0]) {
                    /* Identificador sem filhos */
                    /* Se tem irmão que é declaração de função, então este é declaração de variável */
                    if (node->irmao && node->irmao->tipo_no == NoExpressao && 
                        node->irmao->tipo.expr == Identificador && node->irmao->filhos[1]) {
                        /* É declaração de variável global antes de uma função, continua processando */
                        break;
                    } else {
                        /* Uso em expressão ou declaração final - retorna o nome */
                        return strdup_safe(node->atr.nome);
                    }
                } else {
                    /* Tem filhos mas não é função - retorna nome */
                    return strdup_safe(node->atr.nome);
                }

            case Vetor:
                if (node->filhos[2] != NULL) {
                    /* filhos[2] preenchido = é declaração de vetor — não gera código */
                    break;
                } else if (node->filhos[0]) {
                    /* filhos[2] NULL = é acesso a vetor: v[expr] */
                    t1 = generate_quads(node->filhos[0]); // avalia índice
                    t = newtemp();
                    snprintf(buf, sizeof(buf), "%s[%s]", node->atr.nome, t1);
                    emit("LDV", buf, "-", t);
                    if (t1) free(t1);
                    return t;
                } else {
                    /* Sem filhos = parâmetro vetor (int v[]) — não gera código */
                    break;
                }

            case OpAritmetica:
                /* Operador binário: gerar para filhos, depois emitir operação */
                t1 = generate_quads(node->filhos[0]); // esquerda
                t2 = generate_quads(node->filhos[1]); // direita
                
                /* Converte o token para string */
                char opstr[16];
                switch(node->atr.op) {
                    case MAIS:         strcpy(opstr, "+"); break;
                    case MENOS:        strcpy(opstr, "-"); break;
                    case VEZES:        strcpy(opstr, "*"); break;
                    case DIVIDIDO:     strcpy(opstr, "/"); break;
                    case MENOR:        strcpy(opstr, "<"); break;
                    case MENOR_IGUAL:  strcpy(opstr, "<="); break;
                    case MAIOR:        strcpy(opstr, ">"); break;
                    case MAIOR_IGUAL:  strcpy(opstr, ">="); break;
                    case IGUAL_IGUAL:  strcpy(opstr, "=="); break;
                    case DIFERENTE:    strcpy(opstr, "!="); break;
                    default:           snprintf(opstr, sizeof(opstr), "OP%d", node->atr.op);
                }
                
                t = newtemp();
                emit(opstr, t1, t2, t);
                if (t1) free(t1);
                if (t2) free(t2);
                return t;

            case ChamadaFunc:
                /* Chamada de função: CALL funcao, -, result */
                /* Primeiro gera código para os argumentos */
                if (node->filhos[0]) {
                    NoArvore *arg = node->filhos[0];
                    int arg_count = 0;
                    while (arg) {
                        t1 = generate_quads(arg);
                        snprintf(buf, sizeof(buf), "arg%d", arg_count++);
                        emit("PARAM", t1, "-", "-");
                        if (t1) free(t1);
                        arg = arg->irmao;
                    }
                }
                
                t = newtemp();
                emit("CALL", node->atr.nome, "-", t);

                // Processa irmãos (chamadas de função em sequência)
                if (node->irmao) {
                    generate_quads(node->irmao);
                }
    
                return t;

            case TipoEspec:
                /* Tipo: não gera código */
                return NULL;

            default:
                return NULL;
        }
    }
    else if (node->tipo_no == NoComando) {
        switch(node->tipo.cmd) {
            case comandoAssign:
                /* Atribuição: var = expr */
                /* filho[0] = variável (destino), filho[1] = expressão (origem) */
                if (node->filhos[0] && node->filhos[1]) {
                    t2 = generate_quads(node->filhos[1]); // avalia expressão direita
                    
                    /* Verifica se é vetor ou variável simples */
                    if (node->filhos[0]->tipo.expr == Vetor && node->filhos[0]->filhos[0]) {
                        /* Atribuição em vetor: v[i] = expr */
                        t1 = generate_quads(node->filhos[0]->filhos[0]); // índice
                        snprintf(buf, sizeof(buf), "%s[%s]", node->filhos[0]->atr.nome, t1);
                        emit(":=", t2, "-", buf);
                        if (t1) free(t1);
                    } else {
                        /* Atribuição simples: var = expr */
                        emit(":=", t2, "-", node->filhos[0]->atr.nome);
                    }
                    if (t2) free(t2);
                }
                break;

            case comandoIF:
                /* IF: filho[0] = condição, filho[1] = then, filho[2] = else (opcional) */
                label_false = newlabel();
                label_end = newlabel();
                
                /* Avalia condição */
                if (node->filhos[0]) {
                    t1 = generate_quads(node->filhos[0]);
                    emit("JZ", t1, "-", label_false); // Jump if Zero (false)
                    if (t1) free(t1);
                }
                
                /* Bloco THEN */
                if (node->filhos[1]) {
                    generate_quads(node->filhos[1]);
                }
                
                /* Se há ELSE */
                if (node->filhos[2]) {
                    emit("JMP", "-", "-", label_end);
                    emit("LABEL", "-", "-", label_false);
                    generate_quads(node->filhos[2]);
                    emit("LABEL", "-", "-", label_end);
                } else {
                    emit("LABEL", "-", "-", label_false);
                }
                
                free(label_false);
                free(label_end);
                break;

            case comandoRepeat:
                /* WHILE: filho[0] = condição, filho[1] = corpo */
                label_true = newlabel();
                label_false = newlabel();
                
                emit("LABEL", "-", "-", label_true);
                
                /* Avalia condição */
                if (node->filhos[0]) {
                    t1 = generate_quads(node->filhos[0]);
                    emit("JZ", t1, "-", label_false);
                    if (t1) free(t1);
                }
                
                /* Corpo do loop */
                if (node->filhos[1]) {
                    generate_quads(node->filhos[1]);
                }
                
                emit("JMP", "-", "-", label_true);
                emit("LABEL", "-", "-", label_false);
                
                free(label_true);
                free(label_false);
                break;

            case comandoReturn:
                /* RETURN: filho[0] = expressão (opcional) */
                if (node->filhos[0]) {
                    t1 = generate_quads(node->filhos[0]);
                    emit("RET", t1, "-", "-");
                    if (t1) free(t1);
                } else {
                    emit("RET", "-", "-", "-");
                }
                break;

            case comandoCompound:
                /* Bloco composto: processa filhos */
                for (int i = 0; i < MAX_FILHOS; i++) {
                    if (node->filhos[i]) {
                        generate_quads(node->filhos[i]);
                    }
                }
                break;

            default:
                break;
        }
    }

    /* Processa irmãos (comandos em sequência) */
    if (node->irmao) {
        generate_quads(node->irmao);
    }

    return NULL;
}