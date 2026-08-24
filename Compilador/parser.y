%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "cgen.h"
#include "assembler.h"


extern FILE *yyin;
extern int linha;
extern int yylex(void); // Chama o Scanner para pedir o próximo token
extern char *yytext;

/* Variáveis globais da Tabela de Símbolos */
Escopo *escopo_atual = NULL;
Escopo *lista_escopos = NULL;
Escopo *tail_escopos = NULL;

int temp_num_params = 0;
TipoDado temp_tipos_params[MAX_PARAMS];
TipoID temp_cats_params[MAX_PARAMS];

int erro_sintatico = 0;
int erro_semantico = 0;

/* Variável global que guardará a raiz da árvore ao final */
NoArvore * arvoreSintatica = NULL;

char * copiaString(char * s);
void imprimeGraphviz(NoArvore * tree);

void yyerror(const char *s);
%}

%code requires {
    #include "globals.h"
}



// definição do tipo de dado dos valores dos tokens
%union {
    int val;
    char *id;
    struct {
        TipoDado tipo;
        NoArvore *no; 
        int num_args;
        TipoDado tipos[MAX_PARAMS];
        TipoID cats[MAX_PARAMS];    
    } info;
}

// Declaração dos Tokens (Alinhados com scanner.l)
// Tokens Valorados
%token<val> NUM
%token<id>  ID

// Palavras-chave
%token IF
%token ELSE
%token INT
%token RETURN
%token VOID
%token WHILE

// Símbolos Especiais
%token MAIS
%token MENOS
%token VEZES
%token DIVIDIDO
%token MENOR
%token MENOR_IGUAL
%token MAIOR
%token MAIOR_IGUAL
%token IGUAL_IGUAL
%token DIFERENTE
%token ATRIBUICAO
%token PONTO_VIRGULA
%token VIRGULA
%token ABRE_PARENTESE
%token FECHA_PARENTESE
%token ABRE_COLCHETE
%token FECHA_COLCHETE
%token ABRE_CHAVE
%token FECHA_CHAVE

%token ERROR

// Declaração de tipos dos não-terminais (para retorno $$)
// Expressões e Tipos Básicos
%type <info> tipo_especificador expressao simples_expressao soma_expressao termo fator var ativacao


// Comandos e estruturas que agora viram nós da árvore:
// Declarações e Estruturas
%type <info> programa declaracao_lista declaracao

// Declarações de Variáveis e Funções
%type <info> fun_declaracao var_declaracao params param_lista param

// Blocos e Conteúdo Interno
%type <info> composto_decl local_declaracoes statement_lista statement

// Comandos Específicos
%type <info> expressao_decl selecao_decl iteracao_decl retorno_decl

// Operadores (retornam apenas o código int do token)
%type <val> relacional soma mult

// Listas de Argumentos (retornam Nós da árvore)
%type <info> args
%type <info> arg_lista

// Regras de Precedência (Maior prioridade nas últimas declarações)
%nonassoc MENOR // Evitar a < b < c (Error para operadores encadeados)
%nonassoc MENOR_IGUAL
%nonassoc MAIOR
%nonassoc MAIOR_IGUAL
%nonassoc IGUAL_IGUAL
%nonassoc DIFERENTE

%left MAIS MENOS
%left VEZES DIVIDIDO

%right ELSE // Solução Dangling Else

%%
/* Gramática (LOUDEN, 2004, p.494) 
1. programa -> declaração-lista
2. declaração-lista -> declaração-lista declaração | declaração
3. declaração -> var-declaração | fun-declaração
4. var-declaração -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
5. tipo-especificador -> int | void
6. fun-declaração -> tipo-especificador ID( params )composto-decl
7. params -> param-lista | void
8. param-lista -> param-lista,param | param
9. param -> tipo-especificador ID | tipo-especificador ID []
10. composto-decl -> { local-declarações statement-lista }
11. local-declarações -> local-declarações var-declaração | vazio
12. statement-lista -> statement-lista statement | vazio
13. statement -> expressão-decl | composto-decl | seleção-decl  | iteração-decl | retorno-decl
14. expressão-decl -> expressão ; | ;
15. seleção-decl ->if ( expressão ) statement  | if ( expressão ) statement else statement
16. iteração-decl -> while ( expressão ) statement
17. retorno-decl -> return ; | return expressão ;
18. expressão -> var = expressão | simples-expressão
19. var -> ID | ID [ expressão ]
20. simples-expressão -> soma-expressão relacional soma-expressão  | soma-expressão
21. relacional -> <= | < | > | >= | == | !=
22. soma-expressão -> soma-expressão soma termo | termo
23. soma -> + | -
24. termo -> termo mult fator | fator
25. mult -> * | /
26. fator -> ( expressão ) | var | ativação | NUM
27. ativação -> ID ( args )
28. args -> arg-lista | vazio
29. arg-lista -> arg-lista,expressão | expressão
*/

//programa -> declaração-lista
programa: 
        declaracao_lista
        {
          /* Salva a raiz da árvore completa na variável global */
          arvoreSintatica = $1.no;
      }
;

//declaração-lista -> declaração-lista declaração | declaração
declaracao_lista:
                  declaracao_lista declaracao
                  {
                        /* Lógica de Lista Encadeada (Irmãos) */
                        NoArvore * t = $1.no;
                        
                        if (t != NULL) {
                            /* Percorre até encontrar o último irmão da lista atual */
                            while (t->irmao != NULL) {
                                t = t->irmao;
                            }
                            /* Conecta a nova declaração no final da fila */
                            t->irmao = $2.no;
                            
                            /* O retorno ($$) continua sendo o começo da lista ($1) */
                            $$.no = $1.no;
                        } else {
                            /* Caso de borda estranho (lista nula), assume o novo nó */
                            $$.no = $2.no;
                        }
                    }
                | declaracao
                  {
                    /* Regra base: o primeiro nó é a própria declaração */
                    $$.no = $1.no;
                  }
;
                 
//declaração -> var-declaração | fun-declaração
declaracao: 
            var_declaracao // declaração de variável
            { 
              $$.no = $1.no;
            }
          | fun_declaracao // declaração de função
            { 
              $$.no = $1.no;
            }
;

//Declaração de Variáveis: var-declaração -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
var_declaracao:
                tipo_especificador ID PONTO_VIRGULA //declaração variável
                {
                  // declarações de variáveis não podem ser do tipo 'void'
                  if ($1.tipo == T_VOID) {
                    fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao pode ser declarada como VOID - LINHA: %d\n", $2, linha);
                    erro_semantico = 1;
                    define_var($2, T_INT, T_VAR, linha); // Fallback
                  } else {
                    define_var($2, $1.tipo, T_VAR, linha);
                  }

                  // Cria o nó da árvore para a declaração de variável
                  // Identificador para representar a declaração da variável
                  NoArvore * t = novoNoExpr(Identificador);
                  t->atr.nome = copiaString($2); // Guarda o nome "x"
                  t->tipoDados = $1.tipo;        // Guarda o tipo T_INT
                  
                  $$.no = t;
                  $$.tipo = $1.tipo;
                }
              | 
                tipo_especificador ID ABRE_COLCHETE NUM FECHA_COLCHETE PONTO_VIRGULA //declaração vetor
                {
                  if ($1.tipo == T_VOID) {
                      fprintf(stderr, "ERRO SEMANTICO: Vetor '%s' nao pode ser declarada como VOID - LINHA: %d\n", $2, linha);
                      erro_semantico = 1;
                      define_var($2, T_INT, T_VETOR, linha); // Fallback
                      {
                          Var *vv = busca_var_escopo(escopo_atual, $2);
                          if (vv) vv->tamanho = $4;
                      }

                  } else {
                      define_var($2, $1.tipo, T_VETOR, linha);
                      {
                          Var *vv = busca_var_escopo(escopo_atual, $2);
                          if (vv) vv->tamanho = $4;
                      }
                  }

                  // AST
                  // Vetor para representar a declaração de array
                  NoArvore * t = novoNoExpr(Vetor);
                  t->atr.nome = copiaString($2); // Guarda o nome "v"
                  t->tipoDados = $1.tipo;        // Guarda o tipo T_INT
                  
                  // Para vetores, guardar o tamanho.
                  // Criar um nó de Constante para o tamanho e colocar como filho[0]
                  NoArvore * tamanho = novoNoExpr(Constante);
                  tamanho->atr.val = $4;       // O valor do NUM
                  tamanho->tipoDados = T_INT;
                  
                  t->filhos[0] = tamanho; // Conecta o tamanho ao vetor

                  t->filhos[2] = tamanho;

                  $$.no = t;
                  $$.tipo = $1.tipo;
                }
;

//Bloco de Tipo: tipo-especificador -> int | void
tipo_especificador:
                  INT 
                  { 
                      // Não cria nó na árvore, apenas retorna a informação de tipo
                      $$.tipo = T_INT; 
                      $$.no = NULL; 
                  }
                | VOID 
                  { 
                      $$.tipo = T_VOID; 
                      $$.no = NULL; 
                  }
;

//Declaração de Funções: fun-declaração -> tipo-especificador ID( params )composto-decl
fun_declaracao:
                tipo_especificador ID ABRE_PARENTESE
                {
                  temp_num_params = 0;
                  // Entrar no escopo da função antes dos parâmetros para registrar corretamente
                  entra_escopo(E_FUNCAO, $2);
                  escopo_atual->aguarda_corpo = 1;
                  escopo_atual->tipo_retorno_esperado = $1.tipo; // Guarda tipo de retorno esperadoo)
                }
                params
                {
                  // Define a função com os parâmetros coletados
                  Escopo *escopo_func = (escopo_atual && escopo_atual->pai) ? escopo_atual->pai : escopo_atual;
                  define_func(escopo_func, $2, $1.tipo, linha, temp_num_params, temp_tipos_params, temp_cats_params);
                }
                FECHA_PARENTESE composto_decl{
                  // Construção da AST da Função
                  // Devido à ação no meio da regra, os índices do Bison mudam:
                  // $1: tipo_especificador
                  // $2: ID
                  // $3: ABRE_PARENTESE
                  // $4: { Ação 1: entra_escopo... }
                  // $5: params
                  // $6: { Ação 2: define_func... }
                  // $7: FECHA_PARENTESE
                  // $8: composto_decl

                  NoArvore * t = novoNoExpr(Identificador); // Função é tratada como ID na árvore
                  t->atr.nome = copiaString($2);
                  t->tipoDados = $1.tipo; // Tipo de retorno da função
                  
                  t->filhos[0] = $5.no;   // Params
                  t->filhos[1] = $8.no;   // Corpo da função (bloco)

                  $$.no = t;
                  $$.tipo = $1.tipo;
                }
;

//params -> param-lista | void
params:
        param_lista 
        { 
        $$.no = $1.no;
        }
      | VOID
        { 
          $$.no = NULL; /* Função sem parâmetros = ponteiro NULL na árvore */
        }
;

// param-lista -> param-lista,param | param
param_lista:
            param_lista VIRGULA param
            {
              /* Lógica de Lista Encadeada (igual à declaration_lista) */
              NoArvore * t = $1.no;
              if (t != NULL) {
                  while (t->irmao != NULL) {
                      t = t->irmao;
                  }
                  t->irmao = $3.no; /* Adiciona o novo parâmetro ao final da lista */
                  $$.no = $1.no;    /* Mantém o início da lista */
              } else {
                  $$.no = $3.no;
              }
            }
          | param
          { 
            $$.no = $1.no; /* Início da lista */
          }
;

// Definição de Parâmetros de Funções: param -> tipo-especificador ID | tipo-especificador ID []
//(ex: func(int x, int y[]) ) 
param:
      tipo_especificador ID
      {
        if ($1.tipo == T_VOID) { //Categoria Variável
          fprintf(stderr, "ERRO SEMANTICO: Parametro de funcao nao pode ser VOID - LINHA: %d\n", linha);
          erro_semantico = 1;
          // Mesmo com erro, definido como INT para a árvore não quebrar
          $1.tipo = T_INT;
        }
        else {
	        // Acumula informações do parâmetro
          if (temp_num_params < MAX_PARAMS) {
            temp_tipos_params[temp_num_params] = $1.tipo;
            temp_cats_params[temp_num_params] = T_VAR;
            temp_num_params++;
          }
          define_var($2, $1.tipo, T_VAR, linha);
        }

        // AST
        NoArvore * t = novoNoExpr(Identificador);
        t->atr.nome = copiaString($2);
        t->tipoDados = $1.tipo;
        
        $$.no = t;
        $$.tipo = $1.tipo;
      }
    | 
      tipo_especificador ID ABRE_COLCHETE FECHA_COLCHETE //Categoria Vetor
      {
        if ($1.tipo == T_VOID) {
          fprintf(stderr, "ERRO SEMANTICO: Parametro de funcao nao pode ser VOID - LINHA: %d\n", linha);
          erro_semantico = 1;
          $1.tipo = T_INT;
        } else {
	        // Acumula informações do parâmetro (vetor)
          if (temp_num_params < MAX_PARAMS) {
            temp_tipos_params[temp_num_params] = $1.tipo;
            temp_cats_params[temp_num_params] = T_VETOR;
            temp_num_params++;
          }
          define_var($2, $1.tipo, T_VETOR, linha);
        }

        // Parâmetros vetoriais usam nó Vetor, mas sem tamanho (filho[0] fica NULL)
        NoArvore * t = novoNoExpr(Vetor);
        t->atr.nome = copiaString($2);
        t->tipoDados = $1.tipo;

        $$.no = t;
        $$.tipo = $1.tipo;
      }
;

//composto-decl -> { local-declarações statement-lista }
composto_decl:
              ABRE_CHAVE 
              {
                //Verifica se o escopo atual é de uma função recém criada
                if (escopo_atual != NULL && escopo_atual->aguarda_corpo == 1) {
                  escopo_atual->aguarda_corpo = 0; // flag consumida para que os escopos internos sejam criados
                }
                else {
                  //É um bloco comum (if, while, etc)
                  entra_escopo(E_BLOCO, NULL);
                }
              }
              local_declaracoes statement_lista FECHA_CHAVE
              {
                sai_escopo();

                // Construção da AST
                // Cria o nó "Bloco"
                NoArvore * t = novoNoComando(comandoCompound);
                
                // ÍNDICES:
                // $1: {
                // $2: Ação do meio (escopo)
                // $3: local_declaracoes
                // $4: statement_lista
                // $5: }
                
                t->filhos[0] = $3.no; // Variáveis locais ficam no filho 0
                t->filhos[1] = $4.no; // Lista de comandos fica no filho 1
                
                $$.no = t;
              }
;

//local-declarações -> local-declarações var-declaração | vazio
local_declaracoes:
                  local_declaracoes var_declaracao
                  {
                    // Lógica de Lista Encadeada (Irmãos)
                    NoArvore * t = $1.no;
                    if (t != NULL) {
                        while (t->irmao != NULL) t = t->irmao;
                        t->irmao = $2.no;
                        $$.no = $1.no;
                    } else {
                        $$.no = $2.no;
                    }
                  }              
                | /* vazio */
                  {
                    $$.no = NULL; // Regra base: vazio
                  }
;
//statement-lista -> statement-lista statement | vazio
statement_lista:
                statement_lista statement
              {
                // Lógica de Lista Encadeada (Irmãos)
                NoArvore * t = $1.no;
                if (t != NULL) {
                    while (t->irmao != NULL) t = t->irmao;
                    t->irmao = $2.no;
                    $$.no = $1.no;
                } else {
                    $$.no = $2.no;
                }
              }
            | /* vazio */
              { 
                  $$.no = NULL; 
              }
;

//statement -> expressão-decl | composto-decl | seleção-decl  | iteração-decl | retorno-decl
statement:
          expressao_decl { $$.no = $1.no; }
        | composto_decl  { $$.no = $1.no; }
        | selecao_decl   { $$.no = $1.no; }
        | iteracao_decl  { $$.no = $1.no; }
        | retorno_decl   { $$.no = $1.no; }
;

//expressão-decl -> expressão ; | ;
expressao_decl:
                expressao PONTO_VIRGULA
              {
                if ($1.tipo == T_VETOR_INT) {
                    fprintf(stderr, "ERRO SEMANTICO: Uso de vetor sem indice como expressao escalar - LINHA: %d\n", linha);
                    erro_semantico = 1;
                }
                /* Uma expressão usada como comando (ex: x = 10;) */
                $$.no = $1.no;
              }
            | PONTO_VIRGULA
              {
                /* Ponto e vírgula sozinho não gera nó na árvore */
                $$.no = NULL;
              }
;

//seleção-decl ->if ( expressão ) statement  | if ( expressão ) statement else statement
selecao_decl:
              IF ABRE_PARENTESE expressao FECHA_PARENTESE statement %prec MENOR //Solução S/R: MENOR possui precedência menor que ELSE
              {
                if ($3.tipo == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if deve ser inteira, nao VOID - LINHA: %d\n", linha);
                  erro_semantico = 1;
                } else if ($3.tipo == T_VETOR_INT) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if nao pode ser vetor sem indice - LINHA: %d\n", linha);
                  erro_semantico = 1;
                }

                NoArvore * t = novoNoComando(comandoIF);
                
                t->filhos[0] = $3.no; /* A condição (Teste) */
                t->filhos[1] = $5.no; /* O bloco "Então" (Then) */
                t->filhos[2] = NULL;  /* Não tem "Else" */
                
                $$.no = t;
              }
            | IF ABRE_PARENTESE expressao FECHA_PARENTESE statement ELSE statement
            {
              if ($3.tipo == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if deve ser inteira, nao VOID - LINHA: %d\n", linha);
                  erro_semantico = 1;
               } else if ($3.tipo == T_VETOR_INT) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if nao pode ser vetor sem indice - LINHA: %d\n", linha);
                  erro_semantico = 1;
               }

              NoArvore * t = novoNoComando(comandoIF);
              
              t->filhos[0] = $3.no; /* A condição (Teste) */
              t->filhos[1] = $5.no; /* O bloco "Então" (Then) */
              t->filhos[2] = $7.no; /* O bloco "Senão" (Else) */
              
              $$.no = t;
            }
;

//iteração-decl -> while ( expressão ) statement
iteracao_decl:
              WHILE ABRE_PARENTESE expressao FECHA_PARENTESE
              {
                if ($3.tipo == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de while deve ser inteira, nao VOID - LINHA: %d\n", linha);
                  erro_semantico = 1;
                } else if ($3.tipo == T_VETOR_INT) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de while nao pode ser vetor sem indice - LINHA: %d\n", linha);
                  erro_semantico = 1;
                }
              }
              statement
              {
                // Construção da AST do While
                // Devido à ação no meio da regra, os índices do Bison mudam:
                // $1: WHILE
                // $2: ABRE_PARENTESE
                // $3: expressao (Condição)
                // $4: FECHA_PARENTESE
                // $5: { Ação semântica: verificação se é VOID ou Vetor }
                // $6: statement (Corpo do laço)

                /* Cria o nó do laço (usamos comandoRepeat para representar o While) */
                NoArvore * t = novoNoComando(comandoRepeat);
                
                t->filhos[0] = $3.no; /* A condição de parada (Teste) */
                t->filhos[1] = $6.no; /* O corpo do laço (Statement) */
                
                $$.no = t;
              }
;

//retorno-decl -> return ; | return expressão ;
retorno_decl:
              RETURN PONTO_VIRGULA
              {
                // Verifica se a função atual permite return sem valor (deve ser void)
                if (escopo_atual != NULL && escopo_atual->tipo_retorno_esperado != T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Funcao retorna VOID, mas deveria retornar %s - LINHA: %d\n", 
                          get_tipo_nome(escopo_atual->tipo_retorno_esperado), linha);
                  erro_semantico = 1;
                }

                /* Return vazio */
                NoArvore * t = novoNoComando(comandoReturn);
                
                t->filhos[0] = NULL; /* Não retorna nada */
                
                $$.no = t;
              }
            | 
              RETURN expressao PONTO_VIRGULA
              {
                // Verificação de Vetor
                if ($2.tipo == T_VETOR_INT) {
                    fprintf(stderr, "ERRO SEMANTICO: Tentativa de retornar vetor em vez de valor inteiro. LINHA: %d\n", linha);
                    erro_semantico = 1;
                }
                // Verifica se a função atual permite return com valor (não deve ser void)
                if (escopo_atual != NULL && escopo_atual->tipo_retorno_esperado == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Funcao VOID nao pode retornar valor - LINHA: %d\n", linha);
                  erro_semantico = 1;
                }

                /* Return com valor */
                NoArvore * t = novoNoComando(comandoReturn);
                t->filhos[0] = $2.no; /* Retorna o valor da expressão */
                
                $$.no = t;

              }
;

//expressão -> var = expressão | simples-expressão
expressao: 
          var ATRIBUICAO expressao
          {
            // Construção da AST
            // Atribuição é tratada como um comando
            NoArvore * t = novoNoComando(comandoAssign);

            t->filhos[0] = $1.no; /* A variável que recebe (lado esquerdo) */
            t->filhos[1] = $3.no; /* O valor atribuído (lado direito) */

            // Atribuição também "retorna" o valor atribuído (permite x = y = 0)
            t->tipoDados = $1.tipo;

            // Verificação de Compatibilidade
            // Obs: $3 pode ser uma função do tipo 'void'
            if($1.tipo == T_VOID || $3.tipo == T_VOID){
              fprintf(stderr, "ERRO SEMANTICO: Atribuicao invalida envolvendo VOID. LINHA: %d\n", linha);
              erro_semantico = 1;
            }
            else if ($1.tipo == T_VETOR_INT || $3.tipo == T_VETOR_INT){ // exemplo: x = y, onde y é um vetor
              fprintf(stderr, "ERRO SEMANTICO: Vetor nao pode ser usado em atribucao direta. LINHA: %d\n", linha);
              erro_semantico = 1;
            }
            else if ($1.tipo != $3.tipo){
              // Nota: C- possui apenas tipo 'int' e 'void. Essa verificação foi implementada pensando na escalabilidade da linguagem
              fprintf(stderr, "ERRO SEMANTICO: incompatibilidade de tipos na atribuicao. LINHA: %d\n", linha);
              erro_semantico = 1;
            }

            $$.no = t;
            $$.tipo = $1.tipo;  
          }
        | simples_expressao
        { 
          $$.no = $1.no; 
          $$.tipo = $1.tipo; 
        }
;

// Variáveis (já declaradas): var -> ID | ID [ expressão ]
var:
    ID 
    {
      NoArvore * t = novoNoExpr(Identificador);
      t->atr.nome = copiaString($1); // Copia o nome "x" para o nó

      //Verificação de existência
      Var *v = busca_var($1);
      if (v == NULL){
        fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao declarada. LINHA: %d\n", $1, linha);
        erro_semantico = 1;
        // Fallback para evitar crash
        $$.tipo = T_INT; 
        t->tipoDados = T_INT;
      }
      else {
        //Verifica se a variável é um vetor sem índice ou um inteiro
        if (v->cat == T_VETOR) {
          $$.tipo = T_VETOR_INT; //Retorna tipo especial do ID para barrar a operação
                            //(Nota: O tipo T_VETOR_INT nunca é definido com declare_var(). Ele é um tipo para retorno neste caso especial de verificação de tipo de um inteiro)
          t->tipoDados = T_VETOR_INT;
        } else if (v->cat == T_FUNC) {
          fprintf(stderr, "ERRO SEMANTICO: Identificador de funcao '%s' usado como variavel. LINHA: %d\n", $1, linha);
          erro_semantico = 1;
          $$.tipo = T_INT; // Fallback
        }
        else {
          $$.tipo = T_INT;
          t->tipoDados = T_INT;
        }
      }

      $$.no = t;
    }
  | 
    ID ABRE_COLCHETE expressao FECHA_COLCHETE
    {
      // Construção da AST
      NoArvore * t = novoNoExpr(Vetor);
      t->atr.nome = copiaString($1); // Nome do vetor
      
      t->filhos[0] = $3.no; // O índice (a expressão dentro dos colchetes)

      // Verificações Semânticas
      Var *v = busca_var($1);
      if (v == NULL){
        fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao declarada. LINHA: %d\n", $1, linha);
        erro_semantico = 1;
        $$.tipo = T_INT;
        t->tipoDados = T_INT;
      }
      else{
        //Verificação de categoria (deve ser um vetor)
        if (v->cat != T_VETOR) {
          fprintf(stderr, "ERRO SEMANTICO: '%s' nao e um vetor. LINHA: %d\n", $1, linha);
          erro_semantico = 1;
        }

        //Verificação de índice inteiro
        if ($3.tipo != T_INT) {
           fprintf(stderr, "ERRO SEMANTICO: Indice do vetor '%s' deve ser inteiro. LINHA: %d\n", $1, linha);
           erro_semantico = 1;
        }
      
        // Obs: Aqui é permitido a operação com inteiro (ex: x = y + z[0])
        // Acesso a vetor resulta em INT (v[0] é int)
        $$.tipo = v->tipo; 
        t->tipoDados = v->tipo;
      }

      $$.no = t;
    }
;

//Expressão de Comparação: simples-expressão -> soma-expressão relacional soma-expressão  | soma-expressão
simples_expressao:
                  soma_expressao relacional soma_expressao
                  {
                    // 1. Construção da AST
                    // Tratamos comparação como operação aritmética (gera valor 0 ou 1)
                    NoArvore * t = novoNoExpr(OpAritmetica);
                    
                    t->filhos[0] = $1.no;
                    t->filhos[1] = $3.no;
                    t->atr.op = $2; // O token retornado pela regra 'relacional'

                    if ($1.tipo == T_VOID || $3.tipo == T_VOID) {
                      fprintf(stderr, "ERRO SEMANTICO: Comparacao com VOID. LINHA: %d\n", linha);
                      erro_semantico = 1;
                    }
                    else if ($1.tipo == T_VETOR_INT || $3.tipo == T_VETOR_INT) {
                      fprintf(stderr, "ERRO SEMANTICO: Comparacao com vetores. LINHA: %d\n", linha);
                      erro_semantico = 1;
                    }
                    
                    // O resultado de uma comparação é sempre INT (0 ou 1)
                    t->tipoDados = T_INT;

                    $$.no = t;
                    $$.tipo = T_INT;
                  }
                | soma_expressao
                  {
                    $$.no = $1.no;
                    $$.tipo = $1.tipo;
                  }
;


//relacional -> <= | < | > | >= | == | !=
relacional:
          MENOR_IGUAL { $$ = MENOR_IGUAL; }
        | MENOR       { $$ = MENOR; }
        | MAIOR       { $$ = MAIOR; }
        | MAIOR_IGUAL { $$ = MAIOR_IGUAL; }
        | IGUAL_IGUAL { $$ = IGUAL_IGUAL; }
        | DIFERENTE   { $$ = DIFERENTE; }
;

//soma-expressão -> soma-expressão soma termo | termo
soma_expressao:
                soma_expressao soma termo
                {
                  // Cria o nó da árvore
                  NoArvore * t = novoNoExpr(OpAritmetica);
                  
                  // Conecta os filhos (que vieram de $1 e $3)
                  t->filhos[0] = $1.no; 
                  t->filhos[1] = $3.no;
                  t->atr.op = $2; // Guarda qual foi o operador (+ ou -)

                  // Verificação de Compatibilidade
                  if ($1.tipo == T_VOID || $3.tipo == T_VOID){
                    fprintf(stderr, "ERRO SEMANTICO: Operacao aritmetica com VOID. LINHA: %d\n", linha);
                    erro_semantico = 1;
                    t->tipoDados = T_VOID; // Fallback
                  }
                  else if ($1.tipo == T_VETOR_INT || $3.tipo == T_VETOR_INT) {
                    fprintf(stderr, "ERRO SEMANTICO: Operacao com uso de vetor sem indice. LINHA: %d\n", linha);
                    erro_semantico = 1;
                    t->tipoDados = T_INT; // Fallback
                  }
                  else{
                    t->tipoDados = T_INT; // Nota: C- possui apenas o tipo 'int' para operações (int + int será do tipo int)
                  }
                  
                  // Retorna o pacote completo (AST + Tipo)
                  $$.no = t;
                  $$.tipo = t->tipoDados;
                }
              | termo 
              { 
                  /* Regra base: só repassa o que veio do termo */
                  $$.no = $1.no; 
                  $$.tipo = $1.tipo; 
              }
;

//soma -> + | -
soma: 
      MAIS  { $$ = MAIS; }
    | MENOS { $$ = MENOS; }
;

//termo -> termo mult fator | fator
termo:
      // Verificação de Compatibilidade
      termo mult fator
      {
        // Construção da AST
        NoArvore * t = novoNoExpr(OpAritmetica);
        
        t->filhos[0] = $1.no;
        t->filhos[1] = $3.no;
        t->atr.op = $2; // Guarda * ou /

        // Verificação Semântica
        if ($1.tipo == T_VOID || $3.tipo == T_VOID){
          fprintf(stderr, "ERRO SEMANTICO: Operacao aritmetica com VOID. LINHA: %d\n", linha);
          erro_semantico = 1;
          t->tipoDados = T_VOID;
        }
        else if ($1.tipo == T_VETOR_INT || $3.tipo == T_VETOR_INT){
          fprintf(stderr, "ERRO SEMANTICO: Operacao aritmetica entre vetores. LINHA: %d\n", linha);
          erro_semantico = 1;
          t->tipoDados = T_INT; // Fallback
        }
        else{
          t->tipoDados = T_INT; // Nota: C- possui apenas o tipo 'int' para operações (int * int será do tipo int)
        }

        $$.no = t;
        $$.tipo = t->tipoDados;
      }
    | fator
      {
        $$.no = $1.no;
        $$.tipo = $1.tipo;
      }
;

//mult -> * | /
mult:
      VEZES    { $$ = VEZES; }
    | DIVIDIDO { $$ = DIVIDIDO; }
;

//fator -> ( expressão ) | var | ativação | NUM
fator:
      ABRE_PARENTESE expressao FECHA_PARENTESE
      {
        /* Parênteses não geram nó, apenas agrupam a precedência */
        $$.no = $2.no;
        $$.tipo = $2.tipo;
      }
    | var
      {
          /* Var já criou o nó (Identificador ou Vetor) na regra dele */
          $$.no = $1.no;
          $$.tipo = $1.tipo;
      }
    | ativacao
      {
        /* Ativacao já criou o nó (ChamadaFunc) na regra dele */
        $$.no = $1.no;
        $$.tipo = $1.tipo;
      }
    | NUM
      {
          /* Cria nó Folha para número */
          NoArvore * t = novoNoExpr(Constante);
          t->atr.val = $1;       // Guarda o valor (ex: 10)
          t->tipoDados = T_INT;  // Números em C- são sempre inteiros
          
          $$.no = t;
          $$.tipo = T_INT;
      }
;

// Chamada de Funções: ativação -> ID ( args )
ativacao:
          ID ABRE_PARENTESE args FECHA_PARENTESE
          {
            // Construção da AST
            NoArvore * t = novoNoExpr(ChamadaFunc);
            t->atr.nome = copiaString($1);
            t->filhos[0] = $3.no; // A lista de argumentos é o primeiro filho

            // Verificação Semântica (Busca na Tabela)
            Var *v = busca_var($1);

            if (v == NULL){
              fprintf(stderr, "ERRO SEMANTICO: Funcao '%s' nao declarada. LINHA: %d\n", $1, linha);
              erro_semantico = 1;
              // Fallback para não quebrar a árvore
              t->tipoDados = T_INT;
              $$.tipo = T_INT; 
            }     
            // Verificação de Categoria
            else if (v->cat != T_FUNC){
              fprintf(stderr, "ERRO SEMANTICO: '%s' nao e uma funcao. LINHA: %d\n", $1, linha);
              erro_semantico = 1;
              // Fallback
              t->tipoDados = v->tipo;
              $$.tipo = v->tipo;
            }
            else{
              // Sucesso: O tipo do nó é o tipo de retorno da função
              t->tipoDados = v->tipo;
              $$.tipo = v->tipo;

              // Verificação de quantidade de parâmetros
              if (v->num_params != $3.num_args) {
                fprintf(stderr, "ERRO SEMANTICO: Funcao '%s' espera %d parametro(s), mas recebeu %d - LINHA: %d\n", 
                        $1, v->num_params, $3.num_args, linha);
                erro_semantico = 1;
              }
              else {
                // Verificação de tipos e categorias dos parâmetros
                for (int i = 0; i < v->num_params; i++) {
                  // Verifica tipo
                  if (v->tipo_params[i] != $3.tipos[i]) {
                    fprintf(stderr, "ERRO SEMANTICO: Parametro %d de '%s' esperava ser '%s', mas eh '%s' - LINHA: %d\n", 
                            i + 1, $1, get_tipo_nome(v->tipo_params[i]), get_tipo_nome($3.tipos[i]), linha);
                    erro_semantico = 1;
                  }
                  // Verifica se é vetor ou não
                  if (v->cat_params[i] == T_VETOR && $3.cats[i] != T_VETOR) {
                    fprintf(stderr, "ERRO SEMANTICO: Parametro %d de '%s' esperava ser um vetor - LINHA: %d\n", 
                            i + 1, $1, linha);
                    erro_semantico = 1;
                  }
                  else if (v->cat_params[i] == T_VAR && $3.cats[i] == T_VETOR) {
                    fprintf(stderr, "ERRO SEMANTICO: Parametro %d de '%s' esperava ser um valor, nao um vetor - LINHA: %d\n", 
                            i + 1, $1, linha);
                    erro_semantico = 1;
                  }
                }
              }
            $$.no = t;
            }
          }
;

//args -> arg-lista | vazio
args:
    arg_lista
    {
        $$ = $1;
    }
  | /* vazio */
    {
      $$.num_args = 0;
      $$.no = NULL;
    }
;

//Listagem dos argumentos de chamadas de funções: arg-lista -> arg-lista,expressão | expressão
arg_lista:
          arg_lista VIRGULA expressao
          {
            if ($3.tipo == T_VOID){
              fprintf(stderr, "ERRO SEMANTICO: Argumento de funcao nao pode ser VOID. LINHA: %d\n", linha);
              erro_semantico = 1;
            }

            $$ = $1;

            if ($$.num_args < MAX_PARAMS) {
             /* Adaptação: Usamos $3.tipo em vez de $3 */
             $$.tipos[$$.num_args] = ($3.tipo == T_INT || $3.tipo == T_VETOR_INT) ? T_INT : $3.tipo;
             $$.cats[$$.num_args]  = ($3.tipo == T_VETOR_INT) ? T_VETOR : T_VAR;
             $$.num_args++;
          }

            NoArvore * t = $$.no;
            if (t != NULL) {
                while (t->irmao != NULL) {
                    t = t->irmao;
                }
                t->irmao = $3.no; // Adiciona o novo argumento ao final
                $$.no = $1.no;    // Retorna o início da lista
            } else {
                $$.no = $3.no;
            }
          }
      | 
        expressao
        {
          if ($1.tipo == T_VOID) {
              fprintf(stderr, "ERRO SEMANTICO: Argumento de funcao nao pode ser VOID. LINHA: %d\n", linha);
              erro_semantico = 1;
          }

          $$.num_args = 1;
          $$.tipos[0] = ($1.tipo == T_INT || $1.tipo == T_VETOR_INT) ? T_INT : $1.tipo;
          $$.cats[0]  = ($1.tipo == T_VETOR_INT) ? T_VETOR : T_VAR;

          // Regra base: início da lista
          $$.no = $1.no;
        }
;

%%

// CÓDIGO EM C

// Inicializa a tabela com as funções nativas
void inicializar_tabela_simbolos() {
    escopo_atual = NULL;
    lista_escopos = NULL;
    tail_escopos = NULL;

    //Cria escopo global
    entra_escopo(E_GLOBAL, NULL);

    // Função input() - sem parâmetros, retorna int
    define_func(escopo_atual, "input", T_INT, 0, 0, NULL, NULL);
    Var *inp = busca_var("input"); 
    if (inp != NULL) {
        inp->num_params = 0; // Garante explicitamente que é zero
    }
    
    TipoDado output_tipos[] = {T_INT};
    TipoID output_cats[] = {T_VAR};
    define_func(escopo_atual, "output", T_VOID, 0, 1, output_tipos, output_cats);
    
    // Agora recuperamos a variável 'output' para configurar os parâmetros dela
    Var *out = busca_var("output");
    if (out != NULL) {
        out->num_params = 1;            // Avisa que espera 1 argumento
        out->tipo_params[0] = T_INT;    // O argumento é do tipo INT
        out->cat_params[0] = T_VAR;     // O argumento é uma variável escalar (valor simples)
    }
}

const char* get_tipo_nome(TipoDado tipo){
  switch(tipo){
    case T_INT: return "int";
    case T_VOID: return "void";
    default: return "indefinido";
  }
}

const char* get_cat_nome(TipoID cat){
  switch(cat){
    case T_VAR: return "var";
    case T_VETOR: return "vetor";
    case T_FUNC: return "func";
    default: return "indefinido";
  }
}

Var* busca_var(const char *nome){
  Escopo *e = escopo_atual;
    while (e != NULL) {
      Var *v = e->vars;
      while (v != NULL){
        if(strcmp(v->nome, nome) == 0)
          return v;
        v = v->prox;
    }
    e = e->pai;
  }
  return NULL;
}

void entra_escopo(TipoEscopo tipo, const char *nome_func) {
  Escopo *e = (Escopo*)malloc(sizeof(Escopo));
  e->vars = NULL;
  e->vars_tail = NULL;
  e->pai = escopo_atual;
  e->aguarda_corpo = 0;
  e->tipo_escopo = tipo;
  e->tipo_retorno_esperado = T_VOID; // Inicializa (será sobrescrito em funções)
  
  // Define o nome da função atual
  if (tipo == E_GLOBAL) {
    e->nome_funcao = NULL;  // Global não tem função
  } else if (tipo == E_FUNCAO) {
    e->nome_funcao = nome_func ? strdup(nome_func) : NULL;
  } else {  // E_BLOCO
    // Herda o nome da função do escopo pai
    e->nome_funcao = (escopo_atual && escopo_atual->nome_funcao) ? strdup(escopo_atual->nome_funcao) : NULL;
    // Herda o tipo de retorno esperado do escopo pai
    e->tipo_retorno_esperado = escopo_atual ? escopo_atual->tipo_retorno_esperado : T_VOID;
  }
  
  // Adiciona à lista acumulativa (no final)
  e->prox_all = NULL;
  if (lista_escopos == NULL) {
    lista_escopos = e;
  } else {
    tail_escopos->prox_all = e;
  }
  tail_escopos = e;
  
  // Atualiza pilha de escopos
  escopo_atual = e;
}

void sai_escopo(){
  if (escopo_atual == NULL)
    return;
  
  // Ao sair de um escopo, retornar ao anterior
  escopo_atual = escopo_atual->pai;
}

Var* busca_var_escopo(Escopo *escopo, const char *nome){
  if (escopo == NULL)
    return NULL;
  Var *v = escopo->vars;
  while(v != NULL){
    if (strcmp(v->nome, nome) == 0) {
      return v;
    }
    v = v->prox;
  }
  return NULL;
}

void define_func(Escopo *escopo, const char *nome, TipoDado tipo, int linha, int num_params, TipoDado *tipos_params, TipoID *cats_params) {
  if (escopo == NULL){
    fprintf(stderr, "ERRO SEMANTICO: nenhum escopo ativo ao declarar funcao '%s' - LINHA: %d\n", nome, linha);
    erro_semantico = 1;
    return;
  }

  // Verifica duplicação somente no escopo atual
  if (busca_var_escopo(escopo, nome) != NULL){
    fprintf(stderr, "ERRO SEMANTICO: Funcao '%s' ja declarada neste escopo - LINHA: %d\n", nome, linha);
    erro_semantico = 1;
    return;
  }

  Var *v = (Var*)malloc(sizeof(Var));
  v->nome = strdup(nome);
  v->tipo = tipo;
  v->cat = T_FUNC;
  v->linha = linha;
  
  // Armazena informações dos parâmetros
  v->num_params = num_params;
  if (num_params > 0) {
    for (int i = 0; i < num_params; i++) {
      v->tipo_params[i] = tipos_params[i];
      v->cat_params[i] = cats_params[i];
    }
  }
  
  // Define o escopo
  if (escopo->tipo_escopo == E_GLOBAL) {
    v->escopo = strdup("global");
  } else if (escopo->tipo_escopo == E_FUNCAO) {
    v->escopo = escopo->nome_funcao ? strdup(escopo->nome_funcao) : strdup("global");
  } else {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s:bloco", 
             escopo->nome_funcao ? escopo->nome_funcao : "global");
    v->escopo = strdup(buffer);
  }

  // Adiciona à lista
  v->prox = NULL;
  if (escopo->vars == NULL) {
    escopo->vars = v;
  } else {
    escopo->vars_tail->prox = v;
  }
  escopo->vars_tail = v;
}

void define_var(const char *nome, TipoDado tipo, TipoID categoria, int linha) {
  if (escopo_atual == NULL){
    fprintf(stderr, "ERRO SEMANTICO: nenhum escopo ativo ao declarar '%s' - LINHA: %d.\n", nome, linha);
    erro_semantico = 1;
    return;
  }

  // Verifica duplicação somente no escopo atual
  if (busca_var_escopo(escopo_atual, nome) != NULL){
    fprintf(stderr, "ERRO SEMANTICO: variavel '%s' ja declarada neste escopo - LINHA: %d\n", nome, linha);
    erro_semantico = 1;
    return;
  }

  Var *v = (Var*)malloc(sizeof(Var));
  v->nome = strdup(nome);
  v->tipo = tipo;
  v->cat = categoria;
  v->linha = linha;
  v->tamanho = 1;
  
  // Define o escopo (nome da função ou "global")
  if (escopo_atual->tipo_escopo == E_GLOBAL) {
    v->escopo = strdup("global");
  } else if (escopo_atual->tipo_escopo == E_FUNCAO) {
    v->escopo = escopo_atual->nome_funcao ? strdup(escopo_atual->nome_funcao) : strdup("global");
  } else {  // E_BLOCO
    // Formato: "função:bloco" para variáveis em blocos dentro de funções
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s:bloco", 
             escopo_atual->nome_funcao ? escopo_atual->nome_funcao : "global");
    v->escopo = strdup(buffer);
  }

  // Adiciona à lista de variáveis (no final)
  v->prox = NULL;
  if (escopo_atual->vars == NULL) {
    escopo_atual->vars = v;
  } else {
    escopo_atual->vars_tail->prox = v;
  }
  escopo_atual->vars_tail = v;
}

void impressao_tabela() {
  printf("\n==================TABELA DE SIMBOLOS=====================\n");
  printf("LINHA\tNOME\t\tTIPO\tCATEGORIA\tESCOPO\n");
  printf("=========================================================\n");
  
  // Percorre todos os escopos na lista acumulativa
  Escopo *e = lista_escopos;
  while (e != NULL) {
    // Percorre todas as variáveis do escopo
    Var *v = e->vars;
    while (v != NULL) {
      printf("%d\t%-10s\t%s\t%-10s\t%s\n", 
             v->linha, v->nome, get_tipo_nome(v->tipo), 
             get_cat_nome(v->cat), v->escopo);
      v = v->prox;
    }
    e = e->prox_all;
  }
  printf("=========================================================\n\n");
}

void limpar_tabela(){
  Escopo *e = lista_escopos;
  while (e) {
    // Libera todas as variáveis do escopo
    Var *v = e->vars;
    while (v) {
      Var *temp_v = v;
      v = v->prox;
      free(temp_v->nome);
      free(temp_v->escopo);
      free(temp_v);
    }
    
    // Libera o escopo
    Escopo *temp_e = e;
    e = e->prox_all;
    if (temp_e->nome_funcao) free(temp_e->nome_funcao);
    free(temp_e);
  }
  lista_escopos = NULL;
  tail_escopos = NULL;
  escopo_atual = NULL;
}

void valida_main() {
  Var *main_func = busca_var("main");
  
  if (main_func == NULL) {
    fprintf(stderr, "ERRO SEMANTICO: Funcao main() nao declarada\n");
    erro_semantico = 1;
  } else if (main_func->cat != T_FUNC) {
    fprintf(stderr, "ERRO SEMANTICO: 'main' nao e uma funcao\n");
    erro_semantico = 1;
  } else {
    // Verifica tipo de retorno (deve ser int ou void)
    if (main_func->tipo != T_VOID && main_func->tipo != T_INT) {
      fprintf(stderr, "ERRO SEMANTICO: main() deve retornar int ou void, nao %s\n", 
              get_tipo_nome(main_func->tipo));
      erro_semantico = 1;
    }
    
    // Verifica número de parâmetros (deve ser 0)
    if (main_func->num_params != 0) {
      fprintf(stderr, "ERRO SEMANTICO: main() nao deve ter parametros, mas tem %d\n", 
              main_func->num_params);
      erro_semantico = 1;
    }
  }
}

void yyerror(const char *s) {
  erro_sintatico = 1;
  fprintf(stderr, "ERRO SINTATICO: token inesperado '%s' - LINHA: %d\n", yytext, linha);
}

int main(int argc, char **argv) {
  if (argc > 1) {
      yyin = fopen(argv[1], "r");
      if (!yyin) {
          fprintf(stderr, "Erro na abertura do arquivo: '%s'\n", argv[1]);
          return 1;
      }
  } else {
      yyin = stdin; 
  }

    inicializar_tabela_simbolos();
    yyparse();
    impressao_tabela();

    if (!erro_sintatico && !erro_semantico) {
      valida_main();

      printf("\n==================ARVORE SINTATICA (AST)=============\n");

      if (arvoreSintatica != NULL) {
          imprimeGraphviz(arvoreSintatica);

          // GCI
          clear_quads(); // Limpa quádruplas anteriores
          tmp_count = 0; // Reinicia contador de temporários
          label_count = 0; // Reinicia contador de labels
          
          generate_quads(arvoreSintatica); // Gera as quádruplas
          print_quads(stdout); // Imprime as quádruplas

          /* Gera código assembly */
          FILE *fasm = fopen("codigo.asm", "w");
          if (fasm) {
              generate_assembly(fasm);
              fclose(fasm);
              printf("\nArquivo 'codigo.asm' gerado com sucesso\n");
              
              /* Gera código binário (.mif) */
              generate_binary("codigo.asm", "codigo.mif");
          } else {
              fprintf(stderr, "Erro ao criar arquivo de assembly\n");
          }

          clear_quads(); // Libera memória das quádruplas
      } else {
          printf("Arvore vazia.\n");
      }

    }
    
    limpar_tabela();
    return 0;
}