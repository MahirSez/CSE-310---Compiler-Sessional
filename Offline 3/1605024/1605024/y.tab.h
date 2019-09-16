/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
