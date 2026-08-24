
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 36 "parser.y"

    #include "globals.h"



/* Line 1676 of yacc.c  */
#line 46 "parser.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     IF = 260,
     ELSE = 261,
     INT = 262,
     RETURN = 263,
     VOID = 264,
     WHILE = 265,
     MAIS = 266,
     MENOS = 267,
     VEZES = 268,
     DIVIDIDO = 269,
     MENOR = 270,
     MENOR_IGUAL = 271,
     MAIOR = 272,
     MAIOR_IGUAL = 273,
     IGUAL_IGUAL = 274,
     DIFERENTE = 275,
     ATRIBUICAO = 276,
     PONTO_VIRGULA = 277,
     VIRGULA = 278,
     ABRE_PARENTESE = 279,
     FECHA_PARENTESE = 280,
     ABRE_COLCHETE = 281,
     FECHA_COLCHETE = 282,
     ABRE_CHAVE = 283,
     FECHA_CHAVE = 284,
     ERROR = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 43 "parser.y"

    int val;
    char *id;
    struct {
        TipoDado tipo;
        NoArvore *no; 
        int num_args;
        TipoDado tipos[MAX_PARAMS];
        TipoID cats[MAX_PARAMS];    
    } info;



/* Line 1676 of yacc.c  */
#line 107 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


