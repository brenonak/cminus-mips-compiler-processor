
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

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


/* Line 189 of yacc.c  */
#line 109 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 36 "parser.y"

    #include "globals.h"



/* Line 209 of yacc.c  */
#line 139 "parser.tab.c"

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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 200 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 212 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   99

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  106

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    25,
      27,    29,    30,    31,    40,    42,    44,    48,    50,    53,
      58,    59,    65,    68,    69,    72,    73,    75,    77,    79,
      81,    83,    86,    88,    94,   102,   103,   110,   113,   117,
     121,   123,   125,   130,   134,   136,   138,   140,   142,   144,
     146,   148,   152,   154,   156,   158,   162,   164,   166,   168,
     172,   174,   176,   178,   183,   185,   186,   190
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    33,    34,    -1,    34,    -1,
      35,    -1,    37,    -1,    36,     4,    22,    -1,    36,     4,
      26,     3,    27,    22,    -1,     7,    -1,     9,    -1,    -1,
      -1,    36,     4,    24,    38,    40,    39,    25,    43,    -1,
      41,    -1,     9,    -1,    41,    23,    42,    -1,    42,    -1,
      36,     4,    -1,    36,     4,    26,    27,    -1,    -1,    28,
      44,    45,    46,    29,    -1,    45,    35,    -1,    -1,    46,
      47,    -1,    -1,    48,    -1,    43,    -1,    49,    -1,    50,
      -1,    52,    -1,    53,    22,    -1,    22,    -1,     5,    24,
      53,    25,    47,    -1,     5,    24,    53,    25,    47,     6,
      47,    -1,    -1,    10,    24,    53,    25,    51,    47,    -1,
       8,    22,    -1,     8,    53,    22,    -1,    54,    21,    53,
      -1,    55,    -1,     4,    -1,     4,    26,    53,    27,    -1,
      57,    56,    57,    -1,    57,    -1,    16,    -1,    15,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    57,    58,
      59,    -1,    59,    -1,    11,    -1,    12,    -1,    59,    60,
      61,    -1,    61,    -1,    13,    -1,    14,    -1,    24,    53,
      25,    -1,    54,    -1,    62,    -1,     3,    -1,     4,    24,
      63,    25,    -1,    64,    -1,    -1,    64,    23,    53,    -1,
      53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   164,   164,   173,   193,   202,   206,   214,   235,   277,
     283,   293,   301,   292,   332,   336,   344,   358,   367,   394,
     423,   422,   457,   470,   476,   489,   496,   497,   498,   499,
     500,   505,   514,   523,   541,   564,   563,   596,   613,   637,
     668,   677,   711,   752,   777,   787,   788,   789,   790,   791,
     792,   797,   826,   836,   837,   843,   870,   879,   880,   885,
     891,   897,   903,   917,   982,   987,   995,  1023
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "IF", "ELSE", "INT",
  "RETURN", "VOID", "WHILE", "MAIS", "MENOS", "VEZES", "DIVIDIDO", "MENOR",
  "MENOR_IGUAL", "MAIOR", "MAIOR_IGUAL", "IGUAL_IGUAL", "DIFERENTE",
  "ATRIBUICAO", "PONTO_VIRGULA", "VIRGULA", "ABRE_PARENTESE",
  "FECHA_PARENTESE", "ABRE_COLCHETE", "FECHA_COLCHETE", "ABRE_CHAVE",
  "FECHA_CHAVE", "ERROR", "$accept", "programa", "declaracao_lista",
  "declaracao", "var_declaracao", "tipo_especificador", "fun_declaracao",
  "$@1", "$@2", "params", "param_lista", "param", "composto_decl", "$@3",
  "local_declaracoes", "statement_lista", "statement", "expressao_decl",
  "selecao_decl", "iteracao_decl", "$@4", "retorno_decl", "expressao",
  "var", "simples_expressao", "relacional", "soma_expressao", "soma",
  "termo", "mult", "fator", "ativacao", "args", "arg_lista", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    38,    39,    37,    40,    40,    41,    41,    42,    42,
      44,    43,    45,    45,    46,    46,    47,    47,    47,    47,
      47,    48,    48,    49,    49,    51,    50,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    56,    56,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    62,    63,    63,    64,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     0,     0,     8,     1,     1,     3,     1,     2,     4,
       0,     5,     2,     0,     2,     0,     1,     1,     1,     1,
       1,     2,     1,     5,     7,     0,     6,     2,     3,     3,
       1,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     4,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,     0,     7,    11,     0,     0,     0,    10,     0,    12,
      14,    17,     0,    18,     0,     0,     8,     0,     0,    16,
      19,    20,    13,    23,    25,    22,     0,     0,     0,    62,
      41,     0,     0,     0,    32,     0,    21,    27,    24,    26,
      28,    29,    30,     0,    60,    40,    44,    52,    56,    61,
      65,     0,     0,    37,     0,     0,     0,    31,     0,    53,
      54,    46,    45,    47,    48,    49,    50,     0,     0,    57,
      58,     0,    67,     0,    64,     0,     0,    38,     0,    59,
      39,    60,    43,    51,    55,    63,     0,    42,     0,    35,
      66,    33,     0,     0,    36,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    15,    24,    19,
      20,    21,    47,    33,    34,    37,    48,    49,    50,    51,
     102,    52,    53,    54,    55,    77,    56,    78,    57,    81,
      58,    59,    83,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int8 yypact[] =
{
       5,   -94,   -94,     4,     5,   -94,   -94,    20,   -94,   -94,
     -94,    15,   -94,   -94,    37,    43,    24,    33,    62,   -94,
      47,   -94,    49,    46,    48,     5,   -94,    50,    51,   -94,
     -94,   -94,   -94,   -94,     5,   -94,    70,     3,    -5,   -94,
      41,    52,    12,    54,   -94,    -2,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,    53,    59,   -94,    44,    31,   -94,   -94,
      -2,    -2,    -2,   -94,    60,    -2,    56,   -94,    -2,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,    -2,    -2,   -94,
     -94,    -2,   -94,    58,    61,    63,    64,   -94,    66,   -94,
     -94,   -94,    57,    31,   -94,   -94,    -2,   -94,    25,   -94,
     -94,    79,    25,    25,   -94,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,   -94,    82,    65,    23,   -94,   -94,   -94,   -94,
     -94,    67,    68,   -94,   -94,   -94,   -93,   -94,   -94,   -94,
     -94,   -94,   -42,   -35,   -94,   -94,    10,   -94,    16,   -94,
       7,   -94,   -94,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int8 yytable[] =
{
      64,    39,    40,    66,     9,   101,    39,    40,    41,   104,
     105,    42,     1,    43,     2,    39,    40,    12,    82,    85,
      86,    14,    45,    88,    11,    44,    90,    45,    39,    40,
      41,    31,    46,    42,    63,    43,    45,    12,    18,    13,
      16,    14,    91,    91,    79,    80,    91,    44,    18,    45,
       1,    22,    17,    31,   100,    69,    70,    36,   -15,    71,
      72,    73,    74,    75,    76,    60,    23,    61,    69,    70,
      25,    26,    27,    28,    38,    67,    62,    30,    65,    31,
      68,    89,    87,    95,    96,   103,    10,    92,    94,    98,
      97,    99,    29,     0,    93,     0,    32,     0,     0,    35
};

static const yytype_int8 yycheck[] =
{
      42,     3,     4,    45,     0,    98,     3,     4,     5,   102,
     103,     8,     7,    10,     9,     3,     4,    22,    60,    61,
      62,    26,    24,    65,     4,    22,    68,    24,     3,     4,
       5,    28,    29,     8,    22,    10,    24,    22,    15,    24,
       3,    26,    77,    78,    13,    14,    81,    22,    25,    24,
       7,    27,     9,    28,    96,    11,    12,    34,    25,    15,
      16,    17,    18,    19,    20,    24,     4,    26,    11,    12,
      23,    22,    26,    25,     4,    22,    24,    27,    24,    28,
      21,    25,    22,    25,    23,     6,     4,    77,    81,    25,
      27,    25,    25,    -1,    78,    -1,    28,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     9,    32,    33,    34,    35,    36,    37,     0,
      34,     4,    22,    24,    26,    38,     3,     9,    36,    40,
      41,    42,    27,     4,    39,    23,    22,    26,    25,    42,
      27,    28,    43,    44,    45,    35,    36,    46,     4,     3,
       4,     5,     8,    10,    22,    24,    29,    43,    47,    48,
      49,    50,    52,    53,    54,    55,    57,    59,    61,    62,
      24,    26,    24,    22,    53,    24,    53,    22,    21,    11,
      12,    15,    16,    17,    18,    19,    20,    56,    58,    13,
      14,    60,    53,    63,    64,    53,    53,    22,    53,    25,
      53,    54,    57,    59,    61,    25,    23,    27,    25,    25,
      53,    47,    51,     6,    47,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {
          /* Salva a raiz da árvore completa na variável global */
          arvoreSintatica = (yyvsp[(1) - (1)].info).no;
      ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    {
                        /* Lógica de Lista Encadeada (Irmãos) */
                        NoArvore * t = (yyvsp[(1) - (2)].info).no;
                        
                        if (t != NULL) {
                            /* Percorre até encontrar o último irmão da lista atual */
                            while (t->irmao != NULL) {
                                t = t->irmao;
                            }
                            /* Conecta a nova declaração no final da fila */
                            t->irmao = (yyvsp[(2) - (2)].info).no;
                            
                            /* O retorno ($$) continua sendo o começo da lista ($1) */
                            (yyval.info).no = (yyvsp[(1) - (2)].info).no;
                        } else {
                            /* Caso de borda estranho (lista nula), assume o novo nó */
                            (yyval.info).no = (yyvsp[(2) - (2)].info).no;
                        }
                    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    {
                    /* Regra base: o primeiro nó é a própria declaração */
                    (yyval.info).no = (yyvsp[(1) - (1)].info).no;
                  ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    { 
              (yyval.info).no = (yyvsp[(1) - (1)].info).no;
            ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    { 
              (yyval.info).no = (yyvsp[(1) - (1)].info).no;
            ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 215 "parser.y"
    {
                  // declarações de variáveis não podem ser do tipo 'void'
                  if ((yyvsp[(1) - (3)].info).tipo == T_VOID) {
                    fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao pode ser declarada como VOID - LINHA: %d\n", (yyvsp[(2) - (3)].id), linha);
                    erro_semantico = 1;
                    define_var((yyvsp[(2) - (3)].id), T_INT, T_VAR, linha); // Fallback
                  } else {
                    define_var((yyvsp[(2) - (3)].id), (yyvsp[(1) - (3)].info).tipo, T_VAR, linha);
                  }

                  // Cria o nó da árvore para a declaração de variável
                  // Identificador para representar a declaração da variável
                  NoArvore * t = novoNoExpr(Identificador);
                  t->atr.nome = copiaString((yyvsp[(2) - (3)].id)); // Guarda o nome "x"
                  t->tipoDados = (yyvsp[(1) - (3)].info).tipo;        // Guarda o tipo T_INT
                  
                  (yyval.info).no = t;
                  (yyval.info).tipo = (yyvsp[(1) - (3)].info).tipo;
                ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 236 "parser.y"
    {
                  if ((yyvsp[(1) - (6)].info).tipo == T_VOID) {
                      fprintf(stderr, "ERRO SEMANTICO: Vetor '%s' nao pode ser declarada como VOID - LINHA: %d\n", (yyvsp[(2) - (6)].id), linha);
                      erro_semantico = 1;
                      define_var((yyvsp[(2) - (6)].id), T_INT, T_VETOR, linha); // Fallback
                      {
                          Var *vv = busca_var_escopo(escopo_atual, (yyvsp[(2) - (6)].id));
                          if (vv) vv->tamanho = (yyvsp[(4) - (6)].val);
                      }

                  } else {
                      define_var((yyvsp[(2) - (6)].id), (yyvsp[(1) - (6)].info).tipo, T_VETOR, linha);
                      {
                          Var *vv = busca_var_escopo(escopo_atual, (yyvsp[(2) - (6)].id));
                          if (vv) vv->tamanho = (yyvsp[(4) - (6)].val);
                      }
                  }

                  // AST
                  // Vetor para representar a declaração de array
                  NoArvore * t = novoNoExpr(Vetor);
                  t->atr.nome = copiaString((yyvsp[(2) - (6)].id)); // Guarda o nome "v"
                  t->tipoDados = (yyvsp[(1) - (6)].info).tipo;        // Guarda o tipo T_INT
                  
                  // Para vetores, guardar o tamanho.
                  // Criar um nó de Constante para o tamanho e colocar como filho[0]
                  NoArvore * tamanho = novoNoExpr(Constante);
                  tamanho->atr.val = (yyvsp[(4) - (6)].val);       // O valor do NUM
                  tamanho->tipoDados = T_INT;
                  
                  t->filhos[0] = tamanho; // Conecta o tamanho ao vetor

                  t->filhos[2] = tamanho;

                  (yyval.info).no = t;
                  (yyval.info).tipo = (yyvsp[(1) - (6)].info).tipo;
                ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    { 
                      // Não cria nó na árvore, apenas retorna a informação de tipo
                      (yyval.info).tipo = T_INT; 
                      (yyval.info).no = NULL; 
                  ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    { 
                      (yyval.info).tipo = T_VOID; 
                      (yyval.info).no = NULL; 
                  ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 293 "parser.y"
    {
                  temp_num_params = 0;
                  // Entrar no escopo da função antes dos parâmetros para registrar corretamente
                  entra_escopo(E_FUNCAO, (yyvsp[(2) - (3)].id));
                  escopo_atual->aguarda_corpo = 1;
                  escopo_atual->tipo_retorno_esperado = (yyvsp[(1) - (3)].info).tipo; // Guarda tipo de retorno esperadoo)
                ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {
                  // Define a função com os parâmetros coletados
                  Escopo *escopo_func = (escopo_atual && escopo_atual->pai) ? escopo_atual->pai : escopo_atual;
                  define_func(escopo_func, (yyvsp[(2) - (5)].id), (yyvsp[(1) - (5)].info).tipo, linha, temp_num_params, temp_tipos_params, temp_cats_params);
                ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {
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
                  t->atr.nome = copiaString((yyvsp[(2) - (8)].id));
                  t->tipoDados = (yyvsp[(1) - (8)].info).tipo; // Tipo de retorno da função
                  
                  t->filhos[0] = (yyvsp[(5) - (8)].info).no;   // Params
                  t->filhos[1] = (yyvsp[(8) - (8)].info).no;   // Corpo da função (bloco)

                  (yyval.info).no = t;
                  (yyval.info).tipo = (yyvsp[(1) - (8)].info).tipo;
                ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    { 
        (yyval.info).no = (yyvsp[(1) - (1)].info).no;
        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    { 
          (yyval.info).no = NULL; /* Função sem parâmetros = ponteiro NULL na árvore */
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {
              /* Lógica de Lista Encadeada (igual à declaration_lista) */
              NoArvore * t = (yyvsp[(1) - (3)].info).no;
              if (t != NULL) {
                  while (t->irmao != NULL) {
                      t = t->irmao;
                  }
                  t->irmao = (yyvsp[(3) - (3)].info).no; /* Adiciona o novo parâmetro ao final da lista */
                  (yyval.info).no = (yyvsp[(1) - (3)].info).no;    /* Mantém o início da lista */
              } else {
                  (yyval.info).no = (yyvsp[(3) - (3)].info).no;
              }
            ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 359 "parser.y"
    { 
            (yyval.info).no = (yyvsp[(1) - (1)].info).no; /* Início da lista */
          ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {
        if ((yyvsp[(1) - (2)].info).tipo == T_VOID) { //Categoria Variável
          fprintf(stderr, "ERRO SEMANTICO: Parametro de funcao nao pode ser VOID - LINHA: %d\n", linha);
          erro_semantico = 1;
          // Mesmo com erro, definido como INT para a árvore não quebrar
          (yyvsp[(1) - (2)].info).tipo = T_INT;
        }
        else {
	        // Acumula informações do parâmetro
          if (temp_num_params < MAX_PARAMS) {
            temp_tipos_params[temp_num_params] = (yyvsp[(1) - (2)].info).tipo;
            temp_cats_params[temp_num_params] = T_VAR;
            temp_num_params++;
          }
          define_var((yyvsp[(2) - (2)].id), (yyvsp[(1) - (2)].info).tipo, T_VAR, linha);
        }

        // AST
        NoArvore * t = novoNoExpr(Identificador);
        t->atr.nome = copiaString((yyvsp[(2) - (2)].id));
        t->tipoDados = (yyvsp[(1) - (2)].info).tipo;
        
        (yyval.info).no = t;
        (yyval.info).tipo = (yyvsp[(1) - (2)].info).tipo;
      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    {
        if ((yyvsp[(1) - (4)].info).tipo == T_VOID) {
          fprintf(stderr, "ERRO SEMANTICO: Parametro de funcao nao pode ser VOID - LINHA: %d\n", linha);
          erro_semantico = 1;
          (yyvsp[(1) - (4)].info).tipo = T_INT;
        } else {
	        // Acumula informações do parâmetro (vetor)
          if (temp_num_params < MAX_PARAMS) {
            temp_tipos_params[temp_num_params] = (yyvsp[(1) - (4)].info).tipo;
            temp_cats_params[temp_num_params] = T_VETOR;
            temp_num_params++;
          }
          define_var((yyvsp[(2) - (4)].id), (yyvsp[(1) - (4)].info).tipo, T_VETOR, linha);
        }

        // Parâmetros vetoriais usam nó Vetor, mas sem tamanho (filho[0] fica NULL)
        NoArvore * t = novoNoExpr(Vetor);
        t->atr.nome = copiaString((yyvsp[(2) - (4)].id));
        t->tipoDados = (yyvsp[(1) - (4)].info).tipo;

        (yyval.info).no = t;
        (yyval.info).tipo = (yyvsp[(1) - (4)].info).tipo;
      ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {
                //Verifica se o escopo atual é de uma função recém criada
                if (escopo_atual != NULL && escopo_atual->aguarda_corpo == 1) {
                  escopo_atual->aguarda_corpo = 0; // flag consumida para que os escopos internos sejam criados
                }
                else {
                  //É um bloco comum (if, while, etc)
                  entra_escopo(E_BLOCO, NULL);
                }
              ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 434 "parser.y"
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
                
                t->filhos[0] = (yyvsp[(3) - (5)].info).no; // Variáveis locais ficam no filho 0
                t->filhos[1] = (yyvsp[(4) - (5)].info).no; // Lista de comandos fica no filho 1
                
                (yyval.info).no = t;
              ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    {
                    // Lógica de Lista Encadeada (Irmãos)
                    NoArvore * t = (yyvsp[(1) - (2)].info).no;
                    if (t != NULL) {
                        while (t->irmao != NULL) t = t->irmao;
                        t->irmao = (yyvsp[(2) - (2)].info).no;
                        (yyval.info).no = (yyvsp[(1) - (2)].info).no;
                    } else {
                        (yyval.info).no = (yyvsp[(2) - (2)].info).no;
                    }
                  ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {
                    (yyval.info).no = NULL; // Regra base: vazio
                  ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 477 "parser.y"
    {
                // Lógica de Lista Encadeada (Irmãos)
                NoArvore * t = (yyvsp[(1) - (2)].info).no;
                if (t != NULL) {
                    while (t->irmao != NULL) t = t->irmao;
                    t->irmao = (yyvsp[(2) - (2)].info).no;
                    (yyval.info).no = (yyvsp[(1) - (2)].info).no;
                } else {
                    (yyval.info).no = (yyvsp[(2) - (2)].info).no;
                }
              ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 489 "parser.y"
    { 
                  (yyval.info).no = NULL; 
              ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 496 "parser.y"
    { (yyval.info).no = (yyvsp[(1) - (1)].info).no; ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 497 "parser.y"
    { (yyval.info).no = (yyvsp[(1) - (1)].info).no; ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 498 "parser.y"
    { (yyval.info).no = (yyvsp[(1) - (1)].info).no; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 499 "parser.y"
    { (yyval.info).no = (yyvsp[(1) - (1)].info).no; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 500 "parser.y"
    { (yyval.info).no = (yyvsp[(1) - (1)].info).no; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 506 "parser.y"
    {
                if ((yyvsp[(1) - (2)].info).tipo == T_VETOR_INT) {
                    fprintf(stderr, "ERRO SEMANTICO: Uso de vetor sem indice como expressao escalar - LINHA: %d\n", linha);
                    erro_semantico = 1;
                }
                /* Uma expressão usada como comando (ex: x = 10;) */
                (yyval.info).no = (yyvsp[(1) - (2)].info).no;
              ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 515 "parser.y"
    {
                /* Ponto e vírgula sozinho não gera nó na árvore */
                (yyval.info).no = NULL;
              ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 524 "parser.y"
    {
                if ((yyvsp[(3) - (5)].info).tipo == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if deve ser inteira, nao VOID - LINHA: %d\n", linha);
                  erro_semantico = 1;
                } else if ((yyvsp[(3) - (5)].info).tipo == T_VETOR_INT) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if nao pode ser vetor sem indice - LINHA: %d\n", linha);
                  erro_semantico = 1;
                }

                NoArvore * t = novoNoComando(comandoIF);
                
                t->filhos[0] = (yyvsp[(3) - (5)].info).no; /* A condição (Teste) */
                t->filhos[1] = (yyvsp[(5) - (5)].info).no; /* O bloco "Então" (Then) */
                t->filhos[2] = NULL;  /* Não tem "Else" */
                
                (yyval.info).no = t;
              ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 542 "parser.y"
    {
              if ((yyvsp[(3) - (7)].info).tipo == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if deve ser inteira, nao VOID - LINHA: %d\n", linha);
                  erro_semantico = 1;
               } else if ((yyvsp[(3) - (7)].info).tipo == T_VETOR_INT) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de if nao pode ser vetor sem indice - LINHA: %d\n", linha);
                  erro_semantico = 1;
               }

              NoArvore * t = novoNoComando(comandoIF);
              
              t->filhos[0] = (yyvsp[(3) - (7)].info).no; /* A condição (Teste) */
              t->filhos[1] = (yyvsp[(5) - (7)].info).no; /* O bloco "Então" (Then) */
              t->filhos[2] = (yyvsp[(7) - (7)].info).no; /* O bloco "Senão" (Else) */
              
              (yyval.info).no = t;
            ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 564 "parser.y"
    {
                if ((yyvsp[(3) - (4)].info).tipo == T_VOID) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de while deve ser inteira, nao VOID - LINHA: %d\n", linha);
                  erro_semantico = 1;
                } else if ((yyvsp[(3) - (4)].info).tipo == T_VETOR_INT) {
                  fprintf(stderr, "ERRO SEMANTICO: Condicao de while nao pode ser vetor sem indice - LINHA: %d\n", linha);
                  erro_semantico = 1;
                }
              ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 574 "parser.y"
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
                
                t->filhos[0] = (yyvsp[(3) - (6)].info).no; /* A condição de parada (Teste) */
                t->filhos[1] = (yyvsp[(6) - (6)].info).no; /* O corpo do laço (Statement) */
                
                (yyval.info).no = t;
              ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 597 "parser.y"
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
                
                (yyval.info).no = t;
              ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 614 "parser.y"
    {
                // Verificação de Vetor
                if ((yyvsp[(2) - (3)].info).tipo == T_VETOR_INT) {
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
                t->filhos[0] = (yyvsp[(2) - (3)].info).no; /* Retorna o valor da expressão */
                
                (yyval.info).no = t;

              ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 638 "parser.y"
    {
            // Construção da AST
            // Atribuição é tratada como um comando
            NoArvore * t = novoNoComando(comandoAssign);

            t->filhos[0] = (yyvsp[(1) - (3)].info).no; /* A variável que recebe (lado esquerdo) */
            t->filhos[1] = (yyvsp[(3) - (3)].info).no; /* O valor atribuído (lado direito) */

            // Atribuição também "retorna" o valor atribuído (permite x = y = 0)
            t->tipoDados = (yyvsp[(1) - (3)].info).tipo;

            // Verificação de Compatibilidade
            // Obs: $3 pode ser uma função do tipo 'void'
            if((yyvsp[(1) - (3)].info).tipo == T_VOID || (yyvsp[(3) - (3)].info).tipo == T_VOID){
              fprintf(stderr, "ERRO SEMANTICO: Atribuicao invalida envolvendo VOID. LINHA: %d\n", linha);
              erro_semantico = 1;
            }
            else if ((yyvsp[(1) - (3)].info).tipo == T_VETOR_INT || (yyvsp[(3) - (3)].info).tipo == T_VETOR_INT){ // exemplo: x = y, onde y é um vetor
              fprintf(stderr, "ERRO SEMANTICO: Vetor nao pode ser usado em atribucao direta. LINHA: %d\n", linha);
              erro_semantico = 1;
            }
            else if ((yyvsp[(1) - (3)].info).tipo != (yyvsp[(3) - (3)].info).tipo){
              // Nota: C- possui apenas tipo 'int' e 'void. Essa verificação foi implementada pensando na escalabilidade da linguagem
              fprintf(stderr, "ERRO SEMANTICO: incompatibilidade de tipos na atribuicao. LINHA: %d\n", linha);
              erro_semantico = 1;
            }

            (yyval.info).no = t;
            (yyval.info).tipo = (yyvsp[(1) - (3)].info).tipo;  
          ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 669 "parser.y"
    { 
          (yyval.info).no = (yyvsp[(1) - (1)].info).no; 
          (yyval.info).tipo = (yyvsp[(1) - (1)].info).tipo; 
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 678 "parser.y"
    {
      NoArvore * t = novoNoExpr(Identificador);
      t->atr.nome = copiaString((yyvsp[(1) - (1)].id)); // Copia o nome "x" para o nó

      //Verificação de existência
      Var *v = busca_var((yyvsp[(1) - (1)].id));
      if (v == NULL){
        fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao declarada. LINHA: %d\n", (yyvsp[(1) - (1)].id), linha);
        erro_semantico = 1;
        // Fallback para evitar crash
        (yyval.info).tipo = T_INT; 
        t->tipoDados = T_INT;
      }
      else {
        //Verifica se a variável é um vetor sem índice ou um inteiro
        if (v->cat == T_VETOR) {
          (yyval.info).tipo = T_VETOR_INT; //Retorna tipo especial do ID para barrar a operação
                            //(Nota: O tipo T_VETOR_INT nunca é definido com declare_var(). Ele é um tipo para retorno neste caso especial de verificação de tipo de um inteiro)
          t->tipoDados = T_VETOR_INT;
        } else if (v->cat == T_FUNC) {
          fprintf(stderr, "ERRO SEMANTICO: Identificador de funcao '%s' usado como variavel. LINHA: %d\n", (yyvsp[(1) - (1)].id), linha);
          erro_semantico = 1;
          (yyval.info).tipo = T_INT; // Fallback
        }
        else {
          (yyval.info).tipo = T_INT;
          t->tipoDados = T_INT;
        }
      }

      (yyval.info).no = t;
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 712 "parser.y"
    {
      // Construção da AST
      NoArvore * t = novoNoExpr(Vetor);
      t->atr.nome = copiaString((yyvsp[(1) - (4)].id)); // Nome do vetor
      
      t->filhos[0] = (yyvsp[(3) - (4)].info).no; // O índice (a expressão dentro dos colchetes)

      // Verificações Semânticas
      Var *v = busca_var((yyvsp[(1) - (4)].id));
      if (v == NULL){
        fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao declarada. LINHA: %d\n", (yyvsp[(1) - (4)].id), linha);
        erro_semantico = 1;
        (yyval.info).tipo = T_INT;
        t->tipoDados = T_INT;
      }
      else{
        //Verificação de categoria (deve ser um vetor)
        if (v->cat != T_VETOR) {
          fprintf(stderr, "ERRO SEMANTICO: '%s' nao e um vetor. LINHA: %d\n", (yyvsp[(1) - (4)].id), linha);
          erro_semantico = 1;
        }

        //Verificação de índice inteiro
        if ((yyvsp[(3) - (4)].info).tipo != T_INT) {
           fprintf(stderr, "ERRO SEMANTICO: Indice do vetor '%s' deve ser inteiro. LINHA: %d\n", (yyvsp[(1) - (4)].id), linha);
           erro_semantico = 1;
        }
      
        // Obs: Aqui é permitido a operação com inteiro (ex: x = y + z[0])
        // Acesso a vetor resulta em INT (v[0] é int)
        (yyval.info).tipo = v->tipo; 
        t->tipoDados = v->tipo;
      }

      (yyval.info).no = t;
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 753 "parser.y"
    {
                    // 1. Construção da AST
                    // Tratamos comparação como operação aritmética (gera valor 0 ou 1)
                    NoArvore * t = novoNoExpr(OpAritmetica);
                    
                    t->filhos[0] = (yyvsp[(1) - (3)].info).no;
                    t->filhos[1] = (yyvsp[(3) - (3)].info).no;
                    t->atr.op = (yyvsp[(2) - (3)].val); // O token retornado pela regra 'relacional'

                    if ((yyvsp[(1) - (3)].info).tipo == T_VOID || (yyvsp[(3) - (3)].info).tipo == T_VOID) {
                      fprintf(stderr, "ERRO SEMANTICO: Comparacao com VOID. LINHA: %d\n", linha);
                      erro_semantico = 1;
                    }
                    else if ((yyvsp[(1) - (3)].info).tipo == T_VETOR_INT || (yyvsp[(3) - (3)].info).tipo == T_VETOR_INT) {
                      fprintf(stderr, "ERRO SEMANTICO: Comparacao com vetores. LINHA: %d\n", linha);
                      erro_semantico = 1;
                    }
                    
                    // O resultado de uma comparação é sempre INT (0 ou 1)
                    t->tipoDados = T_INT;

                    (yyval.info).no = t;
                    (yyval.info).tipo = T_INT;
                  ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 778 "parser.y"
    {
                    (yyval.info).no = (yyvsp[(1) - (1)].info).no;
                    (yyval.info).tipo = (yyvsp[(1) - (1)].info).tipo;
                  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 787 "parser.y"
    { (yyval.val) = MENOR_IGUAL; ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 788 "parser.y"
    { (yyval.val) = MENOR; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 789 "parser.y"
    { (yyval.val) = MAIOR; ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 790 "parser.y"
    { (yyval.val) = MAIOR_IGUAL; ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 791 "parser.y"
    { (yyval.val) = IGUAL_IGUAL; ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 792 "parser.y"
    { (yyval.val) = DIFERENTE; ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 798 "parser.y"
    {
                  // Cria o nó da árvore
                  NoArvore * t = novoNoExpr(OpAritmetica);
                  
                  // Conecta os filhos (que vieram de $1 e $3)
                  t->filhos[0] = (yyvsp[(1) - (3)].info).no; 
                  t->filhos[1] = (yyvsp[(3) - (3)].info).no;
                  t->atr.op = (yyvsp[(2) - (3)].val); // Guarda qual foi o operador (+ ou -)

                  // Verificação de Compatibilidade
                  if ((yyvsp[(1) - (3)].info).tipo == T_VOID || (yyvsp[(3) - (3)].info).tipo == T_VOID){
                    fprintf(stderr, "ERRO SEMANTICO: Operacao aritmetica com VOID. LINHA: %d\n", linha);
                    erro_semantico = 1;
                    t->tipoDados = T_VOID; // Fallback
                  }
                  else if ((yyvsp[(1) - (3)].info).tipo == T_VETOR_INT || (yyvsp[(3) - (3)].info).tipo == T_VETOR_INT) {
                    fprintf(stderr, "ERRO SEMANTICO: Operacao com uso de vetor sem indice. LINHA: %d\n", linha);
                    erro_semantico = 1;
                    t->tipoDados = T_INT; // Fallback
                  }
                  else{
                    t->tipoDados = T_INT; // Nota: C- possui apenas o tipo 'int' para operações (int + int será do tipo int)
                  }
                  
                  // Retorna o pacote completo (AST + Tipo)
                  (yyval.info).no = t;
                  (yyval.info).tipo = t->tipoDados;
                ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 827 "parser.y"
    { 
                  /* Regra base: só repassa o que veio do termo */
                  (yyval.info).no = (yyvsp[(1) - (1)].info).no; 
                  (yyval.info).tipo = (yyvsp[(1) - (1)].info).tipo; 
              ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 836 "parser.y"
    { (yyval.val) = MAIS; ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 837 "parser.y"
    { (yyval.val) = MENOS; ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 844 "parser.y"
    {
        // Construção da AST
        NoArvore * t = novoNoExpr(OpAritmetica);
        
        t->filhos[0] = (yyvsp[(1) - (3)].info).no;
        t->filhos[1] = (yyvsp[(3) - (3)].info).no;
        t->atr.op = (yyvsp[(2) - (3)].val); // Guarda * ou /

        // Verificação Semântica
        if ((yyvsp[(1) - (3)].info).tipo == T_VOID || (yyvsp[(3) - (3)].info).tipo == T_VOID){
          fprintf(stderr, "ERRO SEMANTICO: Operacao aritmetica com VOID. LINHA: %d\n", linha);
          erro_semantico = 1;
          t->tipoDados = T_VOID;
        }
        else if ((yyvsp[(1) - (3)].info).tipo == T_VETOR_INT || (yyvsp[(3) - (3)].info).tipo == T_VETOR_INT){
          fprintf(stderr, "ERRO SEMANTICO: Operacao aritmetica entre vetores. LINHA: %d\n", linha);
          erro_semantico = 1;
          t->tipoDados = T_INT; // Fallback
        }
        else{
          t->tipoDados = T_INT; // Nota: C- possui apenas o tipo 'int' para operações (int * int será do tipo int)
        }

        (yyval.info).no = t;
        (yyval.info).tipo = t->tipoDados;
      ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 871 "parser.y"
    {
        (yyval.info).no = (yyvsp[(1) - (1)].info).no;
        (yyval.info).tipo = (yyvsp[(1) - (1)].info).tipo;
      ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 879 "parser.y"
    { (yyval.val) = VEZES; ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 880 "parser.y"
    { (yyval.val) = DIVIDIDO; ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 886 "parser.y"
    {
        /* Parênteses não geram nó, apenas agrupam a precedência */
        (yyval.info).no = (yyvsp[(2) - (3)].info).no;
        (yyval.info).tipo = (yyvsp[(2) - (3)].info).tipo;
      ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 892 "parser.y"
    {
          /* Var já criou o nó (Identificador ou Vetor) na regra dele */
          (yyval.info).no = (yyvsp[(1) - (1)].info).no;
          (yyval.info).tipo = (yyvsp[(1) - (1)].info).tipo;
      ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 898 "parser.y"
    {
        /* Ativacao já criou o nó (ChamadaFunc) na regra dele */
        (yyval.info).no = (yyvsp[(1) - (1)].info).no;
        (yyval.info).tipo = (yyvsp[(1) - (1)].info).tipo;
      ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 904 "parser.y"
    {
          /* Cria nó Folha para número */
          NoArvore * t = novoNoExpr(Constante);
          t->atr.val = (yyvsp[(1) - (1)].val);       // Guarda o valor (ex: 10)
          t->tipoDados = T_INT;  // Números em C- são sempre inteiros
          
          (yyval.info).no = t;
          (yyval.info).tipo = T_INT;
      ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 918 "parser.y"
    {
            // Construção da AST
            NoArvore * t = novoNoExpr(ChamadaFunc);
            t->atr.nome = copiaString((yyvsp[(1) - (4)].id));
            t->filhos[0] = (yyvsp[(3) - (4)].info).no; // A lista de argumentos é o primeiro filho

            // Verificação Semântica (Busca na Tabela)
            Var *v = busca_var((yyvsp[(1) - (4)].id));

            if (v == NULL){
              fprintf(stderr, "ERRO SEMANTICO: Funcao '%s' nao declarada. LINHA: %d\n", (yyvsp[(1) - (4)].id), linha);
              erro_semantico = 1;
              // Fallback para não quebrar a árvore
              t->tipoDados = T_INT;
              (yyval.info).tipo = T_INT; 
            }     
            // Verificação de Categoria
            else if (v->cat != T_FUNC){
              fprintf(stderr, "ERRO SEMANTICO: '%s' nao e uma funcao. LINHA: %d\n", (yyvsp[(1) - (4)].id), linha);
              erro_semantico = 1;
              // Fallback
              t->tipoDados = v->tipo;
              (yyval.info).tipo = v->tipo;
            }
            else{
              // Sucesso: O tipo do nó é o tipo de retorno da função
              t->tipoDados = v->tipo;
              (yyval.info).tipo = v->tipo;

              // Verificação de quantidade de parâmetros
              if (v->num_params != (yyvsp[(3) - (4)].info).num_args) {
                fprintf(stderr, "ERRO SEMANTICO: Funcao '%s' espera %d parametro(s), mas recebeu %d - LINHA: %d\n", 
                        (yyvsp[(1) - (4)].id), v->num_params, (yyvsp[(3) - (4)].info).num_args, linha);
                erro_semantico = 1;
              }
              else {
                // Verificação de tipos e categorias dos parâmetros
                for (int i = 0; i < v->num_params; i++) {
                  // Verifica tipo
                  if (v->tipo_params[i] != (yyvsp[(3) - (4)].info).tipos[i]) {
                    fprintf(stderr, "ERRO SEMANTICO: Parametro %d de '%s' esperava ser '%s', mas eh '%s' - LINHA: %d\n", 
                            i + 1, (yyvsp[(1) - (4)].id), get_tipo_nome(v->tipo_params[i]), get_tipo_nome((yyvsp[(3) - (4)].info).tipos[i]), linha);
                    erro_semantico = 1;
                  }
                  // Verifica se é vetor ou não
                  if (v->cat_params[i] == T_VETOR && (yyvsp[(3) - (4)].info).cats[i] != T_VETOR) {
                    fprintf(stderr, "ERRO SEMANTICO: Parametro %d de '%s' esperava ser um vetor - LINHA: %d\n", 
                            i + 1, (yyvsp[(1) - (4)].id), linha);
                    erro_semantico = 1;
                  }
                  else if (v->cat_params[i] == T_VAR && (yyvsp[(3) - (4)].info).cats[i] == T_VETOR) {
                    fprintf(stderr, "ERRO SEMANTICO: Parametro %d de '%s' esperava ser um valor, nao um vetor - LINHA: %d\n", 
                            i + 1, (yyvsp[(1) - (4)].id), linha);
                    erro_semantico = 1;
                  }
                }
              }
            (yyval.info).no = t;
            }
          ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 983 "parser.y"
    {
        (yyval.info) = (yyvsp[(1) - (1)].info);
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 987 "parser.y"
    {
      (yyval.info).num_args = 0;
      (yyval.info).no = NULL;
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 996 "parser.y"
    {
            if ((yyvsp[(3) - (3)].info).tipo == T_VOID){
              fprintf(stderr, "ERRO SEMANTICO: Argumento de funcao nao pode ser VOID. LINHA: %d\n", linha);
              erro_semantico = 1;
            }

            (yyval.info) = (yyvsp[(1) - (3)].info);

            if ((yyval.info).num_args < MAX_PARAMS) {
             /* Adaptação: Usamos $3.tipo em vez de $3 */
             (yyval.info).tipos[(yyval.info).num_args] = ((yyvsp[(3) - (3)].info).tipo == T_INT || (yyvsp[(3) - (3)].info).tipo == T_VETOR_INT) ? T_INT : (yyvsp[(3) - (3)].info).tipo;
             (yyval.info).cats[(yyval.info).num_args]  = ((yyvsp[(3) - (3)].info).tipo == T_VETOR_INT) ? T_VETOR : T_VAR;
             (yyval.info).num_args++;
          }

            NoArvore * t = (yyval.info).no;
            if (t != NULL) {
                while (t->irmao != NULL) {
                    t = t->irmao;
                }
                t->irmao = (yyvsp[(3) - (3)].info).no; // Adiciona o novo argumento ao final
                (yyval.info).no = (yyvsp[(1) - (3)].info).no;    // Retorna o início da lista
            } else {
                (yyval.info).no = (yyvsp[(3) - (3)].info).no;
            }
          ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1024 "parser.y"
    {
          if ((yyvsp[(1) - (1)].info).tipo == T_VOID) {
              fprintf(stderr, "ERRO SEMANTICO: Argumento de funcao nao pode ser VOID. LINHA: %d\n", linha);
              erro_semantico = 1;
          }

          (yyval.info).num_args = 1;
          (yyval.info).tipos[0] = ((yyvsp[(1) - (1)].info).tipo == T_INT || (yyvsp[(1) - (1)].info).tipo == T_VETOR_INT) ? T_INT : (yyvsp[(1) - (1)].info).tipo;
          (yyval.info).cats[0]  = ((yyvsp[(1) - (1)].info).tipo == T_VETOR_INT) ? T_VETOR : T_VAR;

          // Regra base: início da lista
          (yyval.info).no = (yyvsp[(1) - (1)].info).no;
        ;}
    break;



/* Line 1455 of yacc.c  */
#line 2602 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1039 "parser.y"


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
