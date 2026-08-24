/* globals.h - Versão Unificada (AST + Tabela de Símbolos) */
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX_PARAMS 100

// TABELA DE SIMBOLOS

/* Tipos usados na análise semântica */
typedef enum { T_INT, T_VOID, T_VETOR_INT } TipoDado;
typedef enum { T_VAR, T_VETOR, T_FUNC } TipoID;
typedef enum { E_GLOBAL, E_FUNCAO, E_BLOCO } TipoEscopo;

/* Estrutura para Variáveis */
typedef struct Var {
    char *nome;
    TipoDado tipo;
    TipoID cat;
    char *escopo;
    int linha;
    int num_params;                  
    TipoDado tipo_params[MAX_PARAMS];
    TipoID cat_params[MAX_PARAMS];
    int memloc;
    int tamanho;
    struct Var *prox;
} Var;

/* Estrutura para Escopos */
typedef struct Escopo {
    struct Var *vars;      
    struct Var *vars_tail; 
    struct Escopo *pai;    
    struct Escopo *prox_all; 
    char *nome_funcao;     
    int aguarda_corpo;     
    TipoDado tipo_retorno_esperado;
    TipoEscopo tipo_escopo;
} Escopo;

// ÁRVORE SINTÁTICA - AST

// Tipo de nó na árvore
typedef enum { 
    NoComando,
    NoExpressao 
} TipoNo;

// Tipo específico de comando
typedef enum {
    comandoIF,
    comandoRepeat,
    comandoAssign,
    comandoReturn,
    comandoCompound
} TipoComando;

// Tipo específico de expressão
typedef enum { 
    OpAritmetica, /* +, -, *, / */
    Constante,    /* Números */
    Identificador,/* Variáveis */
    ChamadaFunc,  /* Ativação de função */
    TipoEspec,    /* int ou void */
    Vetor         /* Acesso a vetor [] */
} TipoExpr;

#define MAX_FILHOS 3

typedef struct NoArvore {
    struct NoArvore * filhos[MAX_FILHOS]; /* Filhos */
    struct NoArvore * irmao;         /* Irmão (próximo comando) */
    int linha;                     /* Linha no código fonte */
    TipoNo tipo_no;                /* Comando ou Expressão */ 

    union { 
        TipoComando cmd;  /* kind.stmt agora é cmd */
        TipoExpr expr;    /* kind.exp agora é expr */
    } tipo;

    union { 
        int op;         // Token do operador (+, -, *, /)
        int val;        // Valor do número 
        char * nome;    // Nome da variável ou função
    } atr;
    
    /* Atributo extra para guardar o tipo semântico */
    TipoDado tipoDados;
    
} NoArvore;


// VARIAVEIS GLOBAIS E FUNÇÕES

extern int linha; /* Contador de linhas do Scanner */

/* Funções de construção da AST (implementadas em util.c) */
NoArvore * novoNoComando(TipoComando);
NoArvore * novoNoExpr(TipoExpr);
char * copyString(char *);
void imprimeArvore(NoArvore *); 

/* Funções da Tabela de Símbolos */
void define_var(const char *nome, TipoDado tipo, TipoID categoria, int l);
void define_func(Escopo *escopo, const char *nome, TipoDado tipo, int linha, int num_params, TipoDado *tipos_params, TipoID *cats_params);
void entra_escopo(TipoEscopo tipo, const char *nome_func);
void sai_escopo();
Var* busca_var(const char *nome);
Var* busca_var_escopo(Escopo *escopo, const char *nome);

const char* get_tipo_nome(TipoDado tipo);

/* === GERAÇÃO DE CÓDIGO INTERMEDIÁRIO (QUÁDRUPLAS) === */

/* Estrutura de Quádrupla (Código de 3 Endereços) */
typedef struct {
    char *op;      /* Operação: +, -, *, /, :=, LDI, JMP, JZ, CALL, RET, etc */
    char *arg1;    /* Primeiro argumento */
    char *arg2;    /* Segundo argumento (ou NULL) */
    char *res;     /* Resultado */
} Quad;

/* Variáveis globais para gerenciar quádruplas */
extern Quad *quads;
extern int quad_count;
extern int quad_capacity;
extern int tmp_count;
extern int label_count;

/* Funções para geração de código intermediário */
char *strdup_safe(const char *s);
void emit(const char *op, const char *a1, const char *a2, const char *res);
void clear_quads();
char *newtemp();
char *newlabel();
char *generate_quads(NoArvore *node);
void print_quads(FILE *out);
void generate_assembly(FILE *out);

#endif