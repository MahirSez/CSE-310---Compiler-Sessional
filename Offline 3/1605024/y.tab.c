/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1605024.y" /* yacc.c:339  */

#include<bits/stdc++.h>
#include "1605024_SymbolTable.h"


using namespace std;

int yyparse(void);
int yylex(void);


extern FILE *yyin;

SymbolTable table(103);

FILE *fp , *errorFile , *logFile;



extern int line_count;
int error_count;

int ScopeTable::scopeTableID  = 0;
void yyerror(char *s)
{
	cout<<"Syntax error at line "<<line_count<<endl;
}


void SymbolTableInsertion(string name , string type) {

	SymbolInfo *ret = table.sameScopeLookUp(name );
	if( ret == 0 ) {
		
		table.Insert(name , type) ;
	}	
	else {
		fprintf(errorFile , "Error at Line %d: Multiple Declaration of %s\n\n" , line_count , name.c_str()) ;
		error_count++;
	}
}

string removeLTHIRD(string &str) {

	string ret = "";
	for(int i =0 ; i < str.size(); i++) {
		if( str[i] == '[') break;
		ret += str[i];
	}
	return ret;
}

void setDeclarationType(string type , string varList) {

	string tmp = "";
	varList += ',';
	
	for(int i =0 ; i < varList.size() ; i++ )	 {
		if(varList[i] == ',') {

			string str = removeLTHIRD(tmp);
			SymbolInfo* pt = table.sameScopeLookUp(str);

			if( pt->getDeclaredType() == "") {
				pt->setDeclaredType(type);
			}
			tmp = "";
		}
		else tmp += varList[i];
	}
}


vector<string> getParamList(string str) {

	str +=',';
	string tmp = "";

	vector<string> vec;
	for(int i =0 ; i < str.size() ; i++ ) {

		if( str[i] == ',') {
			string ss = "";
			for(int j =0 ; j < tmp.size() ; j++ ) {

				if( tmp[j] == ' ') break;
				else ss += tmp[j];
			}
			vec.push_back(ss);
			tmp = "";
		
		}
		else tmp += str[i];
	}
	
	return vec;
	
}


vector< pair<string, string > > parameterList;
stack< vector<string> >argStack;


void updateGlobalParamList(string str) {

	

	string tmp = "";
	str += ',';

	for(int i =0 ; i < str.size() ; i++ ) {

		if( str[i] == ',') {
		
			string s1 = "" , s2 = "";

			int flag = 0;

			for(int j =0 ; j < tmp.size() ; j++ ) {

				if( tmp[j] == ' ') flag = 1;
				else if( flag == 0) s1 += tmp[j];
				else if( flag == 1) s2 += tmp[j];
				
			}

			tmp = "";

			parameterList.push_back(pair<string,string>(s2, s1));

		}
		else tmp += str[i];
	}
	

}


#line 206 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    IF = 259,
    ELSE = 260,
    FOR = 261,
    WHILE = 262,
    FLOAT = 263,
    DOUBLE = 264,
    CHAR = 265,
    RETURN = 266,
    VOID = 267,
    MAIN = 268,
    PRINTLN = 269,
    ADDOP = 270,
    MULOP = 271,
    ASSIGNOP = 272,
    RELOP = 273,
    LOGICOP = 274,
    NOT = 275,
    SEMICOLON = 276,
    COMMA = 277,
    LPAREN = 278,
    RPAREN = 279,
    LCURL = 280,
    RCURL = 281,
    LTHIRD = 282,
    RTHIRD = 283,
    INCOP = 284,
    DECOP = 285,
    CONST_INT = 286,
    CONST_FLOAT = 287,
    ID = 288,
    LOWER_THAN_ELSE = 289
  };
#endif
/* Tokens.  */
#define INT 258
#define IF 259
#define ELSE 260
#define FOR 261
#define WHILE 262
#define FLOAT 263
#define DOUBLE 264
#define CHAR 265
#define RETURN 266
#define VOID 267
#define MAIN 268
#define PRINTLN 269
#define ADDOP 270
#define MULOP 271
#define ASSIGNOP 272
#define RELOP 273
#define LOGICOP 274
#define NOT 275
#define SEMICOLON 276
#define COMMA 277
#define LPAREN 278
#define RPAREN 279
#define LCURL 280
#define RCURL 281
#define LTHIRD 282
#define RTHIRD 283
#define INCOP 284
#define DECOP 285
#define CONST_INT 286
#define CONST_FLOAT 287
#define ID 288
#define LOWER_THAN_ELSE 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  SymbolInfo*  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 325 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   151,   151,   159,   166,   173,   179,   186,   195,   271,
     327,   327,   411,   411,   479,   487,   494,   501,   510,   510,
     556,   598,   608,   614,   619,   626,   635,   650,   657,   673,
     680,   688,   694,   700,   706,   712,   718,   726,   732,   739,
     750,   756,   765,   792,   828,   835,   853,   859,   868,   874,
     883,   889,   902,   908,   929,   937,   945,   953,   959,   959,
    1016,  1023,  1029,  1035,  1041,  1049,  1055,  1058,  1065
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "IF", "ELSE", "FOR", "WHILE",
  "FLOAT", "DOUBLE", "CHAR", "RETURN", "VOID", "MAIN", "PRINTLN", "ADDOP",
  "MULOP", "ASSIGNOP", "RELOP", "LOGICOP", "NOT", "SEMICOLON", "COMMA",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "INCOP",
  "DECOP", "CONST_INT", "CONST_FLOAT", "ID", "LOWER_THAN_ELSE", "$accept",
  "start", "program", "unit", "func_declaration", "func_definition", "$@1",
  "$@2", "parameter_list", "compound_statement", "$@3", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "$@4", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -59

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      40,   -79,   -79,   -79,    15,    40,   -79,   -79,   -79,   -79,
     -24,   -79,   -79,     5,    23,     9,    27,   -79,   -13,    39,
       7,     3,    18,    35,   -79,    48,    40,    44,   -79,   -79,
      43,    51,   -79,    33,   -79,    48,    52,   -79,    95,   -79,
     -79,   -79,    58,    59,    60,   109,    63,   109,   109,   -79,
     109,   -79,   -79,    30,   -79,   -79,    55,    64,   -79,   -79,
      -7,    70,   -79,    73,    41,    77,   -79,   -79,   109,   102,
     109,    79,    61,    25,   -79,   -79,    80,   109,    82,    81,
     -79,   -79,   109,   -79,   -79,   -79,   109,   109,   109,   109,
      87,   102,    88,   -79,    89,   -79,    86,   109,   -79,   -79,
      77,   104,   -79,    95,   109,    95,   100,   -79,   -79,   106,
     114,   126,   113,   -79,   -79,   -79,   109,    95,    95,   -79,
     -79,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    22,    23,    24,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    27,     0,     0,     0,    21,     0,    12,
       0,    17,     0,    25,     9,     0,     0,    10,    16,    28,
       0,    18,    13,    15,     8,     0,     0,    20,     0,    14,
      11,    26,     0,     0,     0,     0,     0,     0,     0,    40,
       0,    61,    62,    42,    33,    31,     0,     0,    29,    32,
      57,     0,    44,    46,    48,    50,    52,    56,     0,     0,
       0,     0,     0,    57,    54,    55,     0,     0,     0,    27,
      19,    30,     0,    63,    64,    41,     0,     0,     0,     0,
       0,     0,     0,    39,     0,    60,     0,    66,    45,    47,
      51,    49,    53,     0,     0,     0,     0,    43,    68,     0,
      65,    35,     0,    37,    38,    59,     0,     0,     0,    67,
      36,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -79,   133,   -79,   -79,   -79,   -79,   -79,   -11,
     -79,    13,    11,   -79,   -79,   -54,   -61,   -47,   -43,   -78,
      53,    56,    62,   -42,   -79,   -79,   -79,   -79
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    35,    25,    20,    54,
      38,    55,    56,    14,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    78,   109,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      73,    73,    71,    81,    98,    74,    75,    76,    91,    13,
      82,    10,     1,     9,    32,    11,    10,     2,     9,   108,
      23,     3,    83,    84,    40,    90,    21,    92,    15,    26,
     104,    27,    16,    19,    96,    73,    28,    33,   119,    73,
      73,    73,    73,     1,    17,    18,    29,   102,     2,   111,
      73,   113,     3,   -58,    83,    84,    87,    77,    22,    88,
      24,   112,    30,   120,   121,    34,    39,     1,    42,    73,
      43,    44,     2,    31,    36,    45,     3,    37,    46,    47,
      41,    68,    69,    70,    48,    49,    72,    50,    79,    31,
      80,    85,    86,    89,    94,    51,    52,    53,     1,    42,
      93,    43,    44,     2,    95,    97,    45,     3,    16,    46,
      47,   103,   105,   106,   107,    48,    49,    47,    50,    87,
      31,   114,    48,    49,    47,    50,    51,    52,    53,    48,
     115,   117,    50,    51,    52,    53,   116,   118,    12,    99,
      51,    52,    53,     0,   101,     0,     0,     0,     0,   100
};

static const yytype_int8 yycheck[] =
{
      47,    48,    45,    57,    82,    47,    48,    50,    69,    33,
      17,     0,     3,     0,    25,     0,     5,     8,     5,    97,
      33,    12,    29,    30,    35,    68,    15,    70,    23,    22,
      91,    24,    27,    24,    77,    82,    33,    26,   116,    86,
      87,    88,    89,     3,    21,    22,    28,    89,     8,   103,
      97,   105,    12,    23,    29,    30,    15,    27,    31,    18,
      21,   104,    27,   117,   118,    21,    33,     3,     4,   116,
       6,     7,     8,    25,    31,    11,    12,    26,    14,    15,
      28,    23,    23,    23,    20,    21,    23,    23,    33,    25,
      26,    21,    19,    16,    33,    31,    32,    33,     3,     4,
      21,     6,     7,     8,    24,    23,    11,    12,    27,    14,
      15,    24,    24,    24,    28,    20,    21,    15,    23,    15,
      25,    21,    20,    21,    15,    23,    31,    32,    33,    20,
      24,     5,    23,    31,    32,    33,    22,    24,     5,    86,
      31,    32,    33,    -1,    88,    -1,    -1,    -1,    -1,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,    12,    36,    37,    38,    39,    40,    46,
      47,     0,    38,    33,    48,    23,    27,    21,    22,    24,
      43,    47,    31,    33,    21,    42,    22,    24,    33,    28,
      27,    25,    44,    47,    21,    41,    31,    26,    45,    33,
      44,    28,     4,     6,     7,    11,    14,    15,    20,    21,
      23,    31,    32,    33,    44,    46,    47,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    23,    23,
      23,    53,    23,    52,    58,    58,    53,    27,    60,    33,
      26,    50,    17,    29,    30,    21,    19,    15,    18,    16,
      53,    51,    53,    21,    33,    24,    53,    23,    54,    55,
      57,    56,    58,    24,    51,    24,    24,    28,    54,    61,
      62,    50,    53,    50,    21,    24,    22,     5,    24,    54,
      50,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    39,    39,
      41,    40,    42,    40,    43,    43,    43,    43,    45,    44,
      44,    46,    47,    47,    47,    48,    48,    48,    48,    49,
      49,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    58,    58,    58,    59,    60,    59,
      59,    59,    59,    59,    59,    61,    61,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       2,     3,     1,     1,     1,     3,     6,     1,     4,     1,
       2,     1,     1,     1,     7,     5,     7,     5,     5,     3,
       1,     2,     1,     4,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     2,     2,     1,     1,     0,     5,
       3,     1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 151 "1605024.y" /* yacc.c:1646  */
    {
			fprintf(logFile , "\tSymbol Table:\n\n");
			table.printAll();
			fprintf(logFile , "Total Lines: %d\n\n",line_count);
			fprintf(logFile , "Total Errors: %d\n\n",error_count);
			fprintf(errorFile , "Total Errors: %d\n\n",error_count);
		}
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 159 "1605024.y" /* yacc.c:1646  */
    {

				(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() ) ;

				fprintf(logFile , "At line no: %d program: program unit\n\n",line_count);
				fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
			}
#line 1509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 166 "1605024.y" /* yacc.c:1646  */
    { 
				(yyval) = (yyvsp[0]) ;
				fprintf(logFile , "At line no: %d program: unit\n\n",line_count);
				fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
			}
#line 1519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 173 "1605024.y" /* yacc.c:1646  */
    { 
			(yyval) = (yyvsp[0]) ;

			fprintf(logFile , "At line no: %d unit:	var_declaration\n\n",line_count);
			fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
		}
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 179 "1605024.y" /* yacc.c:1646  */
    {

			(yyval) = (yyvsp[0]) ;

			fprintf(logFile , "At line no: %d unit:	func_declaration\n\n",line_count);
			fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
		}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 186 "1605024.y" /* yacc.c:1646  */
    {

			(yyval) = (yyvsp[0]) ;

			fprintf(logFile , "At line no: %d unit:	func_definition\n\n",line_count);
			fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
		}
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 195 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-5])->getName() + " " + (yyvsp[-4])->getName() + "( " + (yyvsp[-2])->getName() + " );\n");
						fprintf(logFile , "At line no: %d func_declaration:	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );


						string name = (yyvsp[-4])->getName();
						string type = (yyvsp[-4])->getType();
						SymbolInfo* pt = table.sameScopeLookUp( name ) ;
						vector<string> ret1 = getParamList((yyvsp[-2])->getName() );
						

						if( pt == 0 ) {		///funtion not declared yet
							
							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function((yyvsp[-4])->getName() );

							fun->declare();

							string returnType = (yyvsp[-5])->getName();
							fun->setReturnType(returnType);
							

							for(int i = 0 ; i < ret1.size() ; i++ ) {

								fun->addParameter( ret1[i] );
							}

							pt->setFunction(fun);
							break;
						}

						

						//name found in scope table
						if( pt->getFunction() ==0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();


						if( declaredFunction->getReturnType() != (yyvsp[-5])->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function Return Type Mismatch\n\n" , line_count) ;
							error_count++;
						}


						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret1.size() != ret2.size() ) {		//parameter list size mismatch
							
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						for(int i =0 ;i < ret1.size() ; i++ ) {		//paramter type mismatch

							if( ret1[i] != ret2[i] ) {
									
								fprintf(errorFile , "Error at Line %d: Function Parameter Type Mismatch\n\n" , line_count) ;
								error_count++;
							}
						}


					}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 271 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-4])->getName() + " " + (yyvsp[-3])->getName() + "();\n");
						fprintf(logFile , "At line no: %d func_declaration:	type_specifier ID LPAREN RPAREN SEMICOLON\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

						string name = (yyvsp[-3])->getName();
						string type = (yyvsp[-3])->getType();
						SymbolInfo* pt = table.sameScopeLookUp( name ) ;

						if( pt == 0 ) {		///function not yet declared

							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function((yyvsp[-3])->getName() );

							fun->declare();

							string returnType = (yyvsp[-4])->getName();
							fun->setReturnType(returnType);
							pt->setFunction(fun);

							break;
						}


						//name found in scope table
						if( pt->getFunction() ==0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();


						if( declaredFunction->getReturnType() != (yyvsp[-4])->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function `" , line_count) ;
							error_count++;
						}


						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret2.size() != 0 ) {		//parameter list size mismatch
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
						}
						
					}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 327 "1605024.y" /* yacc.c:1646  */
    {


						string name = (yyvsp[-3])->getName();
						string type = (yyvsp[-3])->getType();
						string parameters = (yyvsp[-1])->getName();

						SymbolInfo* pt = table.sameScopeLookUp( name ) ;
						vector<string> ret1 = getParamList(parameters );

						updateGlobalParamList(parameters);

						if( pt == 0 ) {		///function not yet declared
							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function((yyvsp[-3])->getName() );

							fun->define();
							fun->declare();

							string returnType = (yyvsp[-4])->getName();
							fun->setReturnType(returnType);

							for(int i = 0 ; i < ret1.size() ; i++ ) {

								fun->addParameter( ret1[i] );
							}
							pt->setFunction(fun);

							break;
						}

						//name found in scope table
						if( pt->getFunction() == 0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();

						if( declaredFunction->isDefined() ) {	//Already defined

							fprintf(errorFile , "Error at Line %d: Multiple Definition of Function %s\n\n" , line_count , name.c_str()) ;
							error_count++;
							break;
						}
						declaredFunction->define();

						if( declaredFunction->getReturnType() != (yyvsp[-4])->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function Return Type Mismatch\n\n" , line_count) ;
							error_count++;
						}

						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret1.size() != ret2.size() ) {		//parameter list size mismatch
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						for(int i =0 ;i < ret1.size() ; i++ ) {		//paramter type mismatch

							if( ret1[i] != ret2[i] ) {
									
								fprintf(errorFile , "Error at Line %d: Function Parameter Type Mismatch\n\n" , line_count) ;
								error_count++;
							}
						}

					}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 403 "1605024.y" /* yacc.c:1646  */
    {


						(yyval) = new SymbolInfo((yyvsp[-6])->getName() + " " + (yyvsp[-5])->getName() + "( " + (yyvsp[-3])->getName() + " ) " + (yyvsp[0])->getName() );
						fprintf(logFile , "At line no: %d func_definition:	type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
						
					}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 411 "1605024.y" /* yacc.c:1646  */
    {

						
						string name = (yyvsp[-2])->getName();
						string type = (yyvsp[-2])->getType();
						SymbolInfo* pt = table.sameScopeLookUp( name ) ;

						if( pt == 0 ) {		///function not yet declared
							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function((yyvsp[-2])->getName() );

							fun->define();
							fun->declare();

							string returnType = (yyvsp[-3])->getName();
							fun->setReturnType(returnType);
							
							pt->setFunction(fun);
							break;
						}
						
						//name found in scope table
						if( pt->getFunction() == 0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();

						if( declaredFunction->isDefined() ) {	//Already defined

							fprintf(errorFile , "Error at Line %d: Multiple Definistion of Function %s\n\n" , line_count , name.c_str()) ;
							error_count++;
							break;
						}
						declaredFunction->define();

						if( declaredFunction->getReturnType() != (yyvsp[-3])->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function Return Type Mismatch\n\n" , line_count) ;
							error_count++;
						}

						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret2.size() != 0) {		//parameter list size mismatch
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						

					}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 470 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-5])->getName() + " " + (yyvsp[-4])->getName() + "() " + (yyvsp[0])->getName() );
						fprintf(logFile , "At line no: %d func_definition:	type_specifier ID LPAREN RPAREN compound_statement\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
					}
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 479 "1605024.y" /* yacc.c:1646  */
    {

					(yyval) = new SymbolInfo((yyvsp[-3])->getName() + "," + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName() );

					fprintf(logFile , "At line no: %d parameter_list: parameter_list COMMA type_specifier ID\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

				}
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 487 "1605024.y" /* yacc.c:1646  */
    {
					
					(yyval) = new SymbolInfo((yyvsp[-2])->getName() + "," + (yyvsp[0])->getName());

					fprintf(logFile , "At line no: %d parameter_list: parameter_list COMMA type_specifier\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
				}
#line 1888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 494 "1605024.y" /* yacc.c:1646  */
    {
					
					(yyval) = new SymbolInfo((yyvsp[-1])->getName() + " " + (yyvsp[0])->getName());

					fprintf(logFile , "At line no: %d parameter_list: type_specifier ID\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
				}
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 501 "1605024.y" /* yacc.c:1646  */
    {
					
					(yyval) = (yyvsp[0]);
					fprintf(logFile , "At line no: %d parameter_list: type_specifier\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
				}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 510 "1605024.y" /* yacc.c:1646  */
    {


						table.enterScope();

						for(int i= 0 ; i < parameterList.size() ; i++)	 {
							

							string name = parameterList[i].first;
							string dec_type = parameterList[i].second;
							string type = "ID";

							if( name == "" ) {

								fprintf(errorFile , "Error at Line %d: Parameter name missing at function definition\n\n" , line_count );
								error_count++;
								continue;
							}

							SymbolInfo *ret = table.sameScopeLookUp(name );
							if( ret == 0 ) {
								
								table.Insert(name , type) ;
								ret = table.sameScopeLookUp(name);
								ret->setDeclaredType(dec_type);
								
							}
							else {
								fprintf(errorFile , "Error at Line %d: Multiple Declaration of %s\n\n" , line_count , name.c_str()) ;
								error_count++;
							}
						}
						parameterList.clear();
					}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 544 "1605024.y" /* yacc.c:1646  */
    {
						
	
						(yyval) = new SymbolInfo("{\n" + (yyvsp[-1])->getName() + "}\n");
						fprintf(logFile , "At line no: %d compound_statement: LCURL statements RCURL\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

						table.printAll();
						table.exitScope();
					}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 556 "1605024.y" /* yacc.c:1646  */
    {

						table.enterScope();

						for(int i= 0 ; i < parameterList.size() ; i++)	 {
							

							string name = parameterList[i].first;
							string dec_type = parameterList[i].second;
							string type = "ID";

							if( name == "" ) {

								fprintf(errorFile , "Error at Line %d: Parameter name missing at function definition\n\n" , line_count );
								error_count++;
								continue;
							}							

							SymbolInfo *ret = table.sameScopeLookUp(name );
							if( ret == 0 ) {
								
								table.Insert(name , type) ;
								ret = table.sameScopeLookUp(name);
								ret->setDeclaredType(dec_type);
								
							}
							else {
								fprintf(errorFile , "Error at Line %d: Multiple Declaration of %s\n\n" , line_count , name.c_str()) ;
								error_count++;
							}
						}
						parameterList.clear();
						
						(yyval) = new SymbolInfo("{\n}\n");
						fprintf(logFile , "At line no: %d compound_statement: LCURL RCURL\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

						table.printAll();
						table.exitScope();
					}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 598 "1605024.y" /* yacc.c:1646  */
    {

					(yyval) = new SymbolInfo((yyvsp[-2]) -> getName() + " " +(yyvsp[-1])->getName()  + ";\n"  );
					fprintf(logFile , "At line no: %d var_declaration: type_specifier declaration_list SEMICOLON\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

					setDeclarationType((yyvsp[-2])->getName()  , (yyvsp[-1])->getName() ) ;
				}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 608 "1605024.y" /* yacc.c:1646  */
    {	
					(yyval) = new SymbolInfo("int");
					fprintf(logFile , "At line no: %d type_specifier: INT\n\n",line_count);
					fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

				}
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 614 "1605024.y" /* yacc.c:1646  */
    {
					(yyval) = new SymbolInfo("float" );
					fprintf(logFile , "At line no: %d type_specifier: FLOAT\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
				}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 619 "1605024.y" /* yacc.c:1646  */
    {
					(yyval) = new SymbolInfo("void" );
					fprintf(logFile , "At line no: %d type_specifier: VOID\n\n",line_count);
					fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );
				}
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 626 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-2]) -> getName() + ","  + (yyvsp[0])->getName() );
						fprintf(logFile , "At line no: %d declaration_list: declaration_list COMMA ID\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

						SymbolTableInsertion((yyvsp[0])->getName() , (yyvsp[0])->getType() );	//error handled in function

					}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 635 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-5]) -> getName() + ","  +(yyvsp[-3])->getName() + "["  + (yyvsp[-1])->getName() + "]" , "");
						fprintf(logFile , "At line no: %d declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",line_count);
						fprintf(logFile , "%s\n\n" , (yyval)->getName().c_str() );

						SymbolTableInsertion((yyvsp[-3])->getName() , (yyvsp[-3])->getType() );		//error handled in function

						
						SymbolInfo *pt = table.sameScopeLookUp((yyvsp[-3]) -> getName() );
						if( pt != 0)	{
							pt->isArray = true;
						}
						
					}
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 650 "1605024.y" /* yacc.c:1646  */
    {
						
						(yyval) = (yyvsp[0]);
						fprintf(logFile , "At line no: %d declaration_list: ID\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
						SymbolTableInsertion((yyval)->getName()  , (yyval)->getType ());		//error handled in function
					}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 657 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-3]) -> getName() + "["  +(yyvsp[-1])->getName() + "]" , "");
						fprintf(logFile , "At line no: %d declaration_list: ID LTHIRD CONST_INT RTHIRD\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

						SymbolTableInsertion((yyvsp[-3])->getName()  , (yyvsp[-3])->getType ());		//error handled in function

						SymbolInfo *pt = table.sameScopeLookUp((yyvsp[-3]) -> getName() );

						if( pt != 0 ) {	
							pt->isArray = true;
						}
					}
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 673 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = (yyvsp[0]); 
				fprintf(logFile , "At line no: %d statements: statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

			}
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 680 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() ) ;
				fprintf(logFile , "At line no: %d statements: statements statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 688 "1605024.y" /* yacc.c:1646  */
    {

				(yyval) = (yyvsp[0]);
				fprintf(logFile , "At line no: %d statement: var_declaration\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 694 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = (yyvsp[0]);
				fprintf(logFile , "At line no: %d statement: expression_statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 700 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = (yyvsp[0]);
				fprintf(logFile , "At line no: %d statement: compound_statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 706 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = new SymbolInfo("for( " + (yyvsp[-4])->getName() + " "+ (yyvsp[-3])->getName() + " "+ (yyvsp[-2])->getName() + " ) " + (yyvsp[0])->getName() ) ;
				fprintf(logFile , "At line no: %d statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 712 "1605024.y" /* yacc.c:1646  */
    {

				(yyval) = new SymbolInfo("if( " + (yyvsp[-2])->getName() + " ) " + (yyvsp[0])->getName() );
				fprintf(logFile , "At line no: %d statement: IF LPAREN expression RPAREN statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 718 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = new SymbolInfo("if( " + (yyvsp[-4])->getName() + " ) " + (yyvsp[-2])->getName() + " else " + (yyvsp[0])->getName());
				fprintf(logFile , "At line no: %d statement: IF LPAREN expression RPAREN statement statement ELSE statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

				
			}
#line 2210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 726 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = new SymbolInfo("while( " + (yyvsp[-2])->getName()  + " )" + (yyvsp[0])->getName()  ) ;
				fprintf(logFile , "At line no: %d statement: WHILE LPAREN expression RPAREN statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 732 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = new SymbolInfo("println( " + (yyvsp[-2])->getName() + " );\n");
				fprintf(logFile , "At line no: %d statement: PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

			}
#line 2233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 739 "1605024.y" /* yacc.c:1646  */
    {
				
				
				(yyval) = new SymbolInfo("return " + (yyvsp[-1])->getName() + " ;\n");
				fprintf(logFile , "At line no: %d statement: RETURN expression SEMICOLON\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 750 "1605024.y" /* yacc.c:1646  */
    {

							(yyval) = new SymbolInfo(";\n");
							fprintf(logFile , "At line no: %d expression_statement: SEMICOLON\n\n",line_count);
							fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
						}
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 756 "1605024.y" /* yacc.c:1646  */
    {

							(yyval) = new SymbolInfo((yyvsp[-1])->getName() + " ;\n");
							fprintf(logFile , "At line no: %d expression_statement: expression SEMICOLON\n\n",line_count);
							fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

						}
#line 2268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 765 "1605024.y" /* yacc.c:1646  */
    {

				(yyval) = (yyvsp[0]);
				string name = (yyval)->getName();

				fprintf(logFile , "At line no: %d variable:	ID\n\n",line_count);
				fprintf(logFile , "%s\n\n", name.c_str() ) ;
				
				SymbolInfo *pt = table.globalLookUp(name);
				if( pt == 0 ) {
					fprintf(errorFile , "Error at Line %d : Undeclared Variable: %s\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if( pt->getFunction() != 0 ) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch , %s is declared as a Function\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if( pt->isArray) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch\n\n",line_count );
					error_count++;

					(yyval)->setDeclaredType(pt->getDeclaredType());
					(yyval)->isArray = true;
				}
				else (yyval)->setDeclaredType(pt->getDeclaredType());
				
			}
#line 2300 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 792 "1605024.y" /* yacc.c:1646  */
    {
				
				(yyval) = new SymbolInfo((yyvsp[-3])->getName() + "[" + (yyvsp[-1])->getName() + "]" );
				string name = (yyvsp[-3])->getName();

				fprintf(logFile , "At line no: %d variable:	ID LTHIRD expression RTHIRD\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() );

				SymbolInfo *pt = table.globalLookUp(name);
				if( pt == 0 ) {
					fprintf(errorFile , "Error at Line %d : Undeclared Variable: %s\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if( pt->getFunction() != 0 ) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch , %s is declared as a Function\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if(pt->isArray == 0) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch\n\n",line_count , name.c_str() );
					error_count++;

					(yyval)->setDeclaredType(pt->getDeclaredType());
					(yyval)->isArray = false;
				}
				else {
					(yyval)->setDeclaredType(pt->getDeclaredType());
					(yyval)->isArray = true;
				}

				if((yyvsp[-1])->getDeclaredType() != "int") {
					fprintf(errorFile ,"Error at Line %d : Non-integer Array Index\n\n" , line_count );
					error_count++;
				}
			}
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 828 "1605024.y" /* yacc.c:1646  */
    {

				
				(yyval) = (yyvsp[0]);
				fprintf(logFile , "At line no: %d expression: logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			}
#line 2351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 835 "1605024.y" /* yacc.c:1646  */
    {
				
				
				(yyval) = new SymbolInfo((yyvsp[-2])->getName() + " = " + (yyvsp[0])->getName());
				fprintf(logFile , "At line no: %d expression: variable ASSIGNOP logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
	
				if( (yyvsp[-2])->getDeclaredType() == "" || (yyvsp[0])->getDeclaredType() == "" || (yyvsp[-2])->getDeclaredType() != (yyvsp[0])->getDeclaredType() ) {

					fprintf(errorFile , "Error at line %d : Assignment Operation, Type Mismatch\n\n", line_count);
					error_count++;
				}

				if( (yyvsp[-2])->getDeclaredType() == "float" ||  (yyvsp[0])->getDeclaredType() == "float" )	(yyval)->setDeclaredType("float");
				else if( (yyvsp[-2])->getDeclaredType() == "int" ||  (yyvsp[0])->getDeclaredType() == "int" ) (yyval)->setDeclaredType("int");
			}
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 853 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = (yyvsp[0]);
						fprintf(logFile , "At line no: %d logic_expression:	rel_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
					}
#line 2383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 859 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName());
						(yyval)->setDeclaredType("int" ) ;
						fprintf(logFile , "At line no: %d logic_expression:	rel_expression LOGICOP rel_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
					}
#line 2395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 868 "1605024.y" /* yacc.c:1646  */
    {

					(yyval) = (yyvsp[0]);
					fprintf(logFile , "At line no: %d rel_expression: simple_expression\n\n",line_count);
					fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
				}
#line 2406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 874 "1605024.y" /* yacc.c:1646  */
    {

					(yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName());
					(yyval)->setDeclaredType("int") ;
					fprintf(logFile , "At line no: %d rel_expression: simple_expression RELOP simple_expression\n\n",line_count);
					fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
				}
#line 2418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 883 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = (yyvsp[0]);
						fprintf(logFile , "At line no: %d simple_expression: term\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
					}
#line 2429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 889 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName());

						
						fprintf(logFile , "At line no: %d simple_expression: simple_expression ADDOP term\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

						if( (yyvsp[-2])->getDeclaredType() == "float" ||  (yyvsp[0])->getDeclaredType() == "float" )	(yyval)->setDeclaredType("float");
						else if( (yyvsp[-2])->getDeclaredType() == "int" ||  (yyvsp[0])->getDeclaredType() == "int" ) (yyval)->setDeclaredType("int");
					}
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 902 "1605024.y" /* yacc.c:1646  */
    {

			(yyval) = (yyvsp[0]);
			fprintf(logFile , "At line no: %d term:	unary_expression\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
		}
#line 2456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 908 "1605024.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName());
			fprintf(logFile , "At line no: %d term: term MULOP unary_expression\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

			if( (yyvsp[-2])->getDeclaredType() == "float" ||  (yyvsp[0])->getDeclaredType() == "float" )	(yyval)->setDeclaredType("float");
			else if( (yyvsp[-2])->getDeclaredType() == "int" ||  (yyvsp[0])->getDeclaredType() == "int" ) (yyval)->setDeclaredType("int");

			if((yyvsp[-1])->getName() == "%") {

				if((yyvsp[-2])->getDeclaredType() != "int" || (yyvsp[0]) ->getDeclaredType() != "int") {

					fprintf(errorFile ,"Error at line %d : non-Integer operand on modulus operator\n\n",line_count );
					error_count++;
				}
				(yyval)->setDeclaredType ("int");
			}
		}
#line 2480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 929 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() );
						fprintf(logFile , "At line no: %d unary_expression:	ADDOP unary_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

						(yyval)->setDeclaredType((yyvsp[0])->getDeclaredType());
					}
#line 2493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 937 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() );
						fprintf(logFile , "At line no: %d unary_expression:	NOY unary_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;

						(yyval)->setDeclaredType("int");
					}
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 945 "1605024.y" /* yacc.c:1646  */
    {

						(yyval) = (yyvsp[0]);
						fprintf(logFile , "At line no: %d unary_expression: factor\n\n",line_count);
						fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
					}
#line 2517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 953 "1605024.y" /* yacc.c:1646  */
    {	

			(yyval) = (yyvsp[0]);
			fprintf(logFile , "At line no: %d factor: variable\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
		}
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 959 "1605024.y" /* yacc.c:1646  */
    {	argStack.push(vector<string>() ); }
#line 2534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 959 "1605024.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo((yyvsp[-4])->getName() + "(" + (yyvsp[-1])->getName() + ")" );
			fprintf(logFile , "At line no: %d factor: ID LPAREN argument_list RPAREN\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			
			SymbolInfo* pt = table.globalLookUp((yyvsp[-4])->getName() );


			vector<string>arg = argStack.top();
			argStack.pop();


			if(pt == 0 ) {

				fprintf(errorFile , "Error at line: %d : Function not defined\n\n",line_count );
				error_count++;
				break;
			}

			Function *fun = pt->getFunction();

			if( fun ==0 ) {

				fprintf(errorFile , "Error at line: %d : %s is not declared as a Function\n\n",line_count , (yyvsp[-4])->getName().c_str() ); 
				error_count++;
				break;
			}

			(yyval)->setDeclaredType(fun->getReturnType() ) ;

			if(fun->isDefined() == 0) {

				fprintf(errorFile , "Error at line: %d : Function declared, but not defined\n\n",line_count  ); 
				error_count++;
			}
			
			vector<string>param = fun->getParameterList() ;


			if(param.size() != arg.size() ) {

				fprintf(errorFile , "Error at line: %d : Function parameter count mismatch\n\n",line_count ); 
				error_count++;
				break;
			}

			for(int i =0 ; i < param.size() ; i++ ) {

				if( param[i] != arg[i] ) {

					fprintf(errorFile , "Error at line: %d : Function parameter type mismatch\n\n",line_count ); 
					error_count++;
				}
			}

		}
#line 2596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1016 "1605024.y" /* yacc.c:1646  */
    {
			
			(yyval) = new SymbolInfo("( " + (yyvsp[-1])->getName() + " )");
			fprintf(logFile , "At line no: %d factor: LPAREN expression RPAREN\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;			
			(yyval)->setDeclaredType((yyvsp[-1])->getDeclaredType() ) ;
		}
#line 2608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1023 "1605024.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[0]);
			fprintf(logFile , "At line no: %d factor: CONST_INT\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;			
			(yyval)->setDeclaredType("int");
		}
#line 2619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1029 "1605024.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[0]);
			fprintf(logFile , "At line no: %d factor: CONST_FLOAT\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;	
			(yyval)->setDeclaredType("float");		
		}
#line 2630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1035 "1605024.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo((yyvsp[-1])->getName() + "++" ) ;
			fprintf(logFile , "At line no: %d factor: variable INCOP\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			(yyval)->setDeclaredType((yyvsp[-1])->getDeclaredType() ) ;
		}
#line 2641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1041 "1605024.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo((yyvsp[-1])->getName() +"--" ) ;
			fprintf(logFile , "At line no: %d factor: variable DECOP\n\n",line_count);
			fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
			(yyval)->setDeclaredType((yyvsp[-1])->getDeclaredType() ) ;
		}
#line 2652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1049 "1605024.y" /* yacc.c:1646  */
    {

					(yyval) = (yyvsp[0]);
					fprintf(logFile , "At line no: %d argument_list: arguments\n\n",line_count);
					fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
				}
#line 2663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1058 "1605024.y" /* yacc.c:1646  */
    {

				(yyval) = new SymbolInfo((yyvsp[-2])->getName() + " , " + (yyvsp[0])->getName());
				fprintf(logFile , "At line no: %d arguments: arguments COMMA logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;
				argStack.top().push_back((yyvsp[0])->getDeclaredType());
			}
#line 2675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1065 "1605024.y" /* yacc.c:1646  */
    {

				(yyval) = (yyvsp[0]);
				fprintf(logFile , "At line no: %d arguments: logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", (yyval)->getName().c_str() ) ;	
				argStack.top().push_back((yyvsp[0])->getDeclaredType());
			}
#line 2687 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2691 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1075 "1605024.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		return 0;
	}

	
	errorFile = fopen("1605024_error.txt" , "w");
	logFile = fopen("1605024_log.txt" , "w");

	yyin=fp;
	yyparse();
	

	fclose(fp);
	
	return 0;
}

