%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "parser.tab.h"

    // Variável global para contagem de linhas
    int linha = 1;

%}

DIGITO  [0-9]
LETRA   [a-zA-Z]

 /* Para lidar com comentários multilinha /* ... */
%x COMENTARIO

%%

 /* PALAVRAS-CHAVE (devem ser listadas antes de ID para garantir prioridade) */
"if"            { return IF; }
"else"          { return ELSE; }
"int"           { return INT; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }

 /* SÍMBOLOS ESPECIAIS */
"\+"             { return MAIS; }
"-"             { return MENOS; }
"\*"             { return VEZES; }
"/"             { return DIVIDIDO; }
"<"             { return MENOR; }
"<="            { return MENOR_IGUAL; }
">"             { return MAIOR; }
">="            { return MAIOR_IGUAL; }
"=="            { return IGUAL_IGUAL; }
"!="            { return DIFERENTE; }
"="             { return ATRIBUICAO; }
";"             { return PONTO_VIRGULA; }
","             { return VIRGULA; }
"("             { return ABRE_PARENTESE; }
")"             { return FECHA_PARENTESE; }
"["             { return ABRE_COLCHETE; }
"]"             { return FECHA_COLCHETE; }
"{"             { return ABRE_CHAVE; }
"}"             { return FECHA_CHAVE; }

 /* NÚMEROS */
{DIGITO}+       {   
                    /* atoi(yytext): Converte a string lida (yytext) para inteiro real.
                       yylval.val: Guarda esse valor na variável de comunicação com o Parser.
                       Sem isso, o Parser saberia que é um número, mas não saberia QUAL número. */
                    yylval.val = (int)atoi(yytext);
                    return NUM;
                }

 /* IDENTIFICADORES */
{LETRA}+        {
                    /* strdup(yytext): Duplica a string lida (yytext) para alocar memória separada.
                       yylval.id: Guarda esse valor na variável de comunicação com o Parser. Envia para a Tabela de Símbolos.
                       Sem isso, o Parser saberia que é um identificador, mas não saberia QUAL identificador. */
                    yylval.id = strdup(yytext);
                    return ID; 
                }

 /* ESPAÇOS EM BRANCO: */
 /* Ignora espaços e tabs */
[ \t]+          { /* ignora */ }

 /* Quebras de linha incrementam o contador de linhas */
\n              { linha++; }

 /* COMENTÁRIOS */
 /* Usa start conditions (%x) para lidar com aninhamento e quebras de linha */
"/*"             { BEGIN(COMENTARIO); }
<COMENTARIO>"*/" { BEGIN(INITIAL); }
<COMENTARIO>\n   { linha++; }
<COMENTARIO>.    { /* ignora conteúdo dentro do comentário */ }

 /* TRATAMENTO DE ERROS (Requisito do PDF) */
 /* '.' casa com qualquer coisa que não casou acima */
. { 
    fprintf(stderr, "ERRO LEXICO: ''%s'' - LINHA: %d\n", yytext, linha); 
    return ERROR;
}

%%