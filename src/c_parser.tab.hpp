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

#ifndef YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/c_parser.y" /* yacc.c:1909  */

  #include <string>
  #include <stdio.h>
  #include <cassert>
  #include <iostream>

  #include "ast.hpp"

  extern Program *g_root;
 
  
  int yylex(void);
  void yyerror(const char* );

  using namespace std;

#line 61 "src/c_parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tInt = 258,
    tDivision = 259,
    tPipeEqual = 260,
    tDivisionEqual = 261,
    tStringLiteral = 262,
    tIdentifier = 263,
    tIntegerConstant = 264,
    tCharacterConstant = 265,
    tFloatingConstant = 266,
    tFor = 267,
    tWhile = 268,
    tSizeof = 269,
    tAuto = 270,
    tBreak = 271,
    tCase = 272,
    tChar = 273,
    tConst = 274,
    tContinue = 275,
    tDo = 276,
    tDouble = 277,
    tElse = 278,
    tEnum = 279,
    tExtern = 280,
    tFloat = 281,
    tGoTo = 282,
    tIf = 283,
    tLong = 284,
    tRegister = 285,
    tReturn = 286,
    tShort = 287,
    tSigned = 288,
    tStatic = 289,
    tDefault = 290,
    tSwitch = 291,
    tTypedef = 292,
    tUnion = 293,
    tUnsigned = 294,
    tVoid = 295,
    tVolatile = 296,
    tPipe = 297,
    tLBracket = 298,
    tRBracket = 299,
    tDot = 300,
    tExMark = 301,
    tPlus = 302,
    tMinus = 303,
    tPlusPlus = 304,
    tMinusMinus = 305,
    tLSBracket = 306,
    tRSBracket = 307,
    tMore = 308,
    tAnd = 309,
    tDivison = 310,
    tModulo = 311,
    tXor = 312,
    tMultiply = 313,
    tComma = 314,
    tHash = 315,
    tQuesMark = 316,
    tColon = 317,
    tTilde = 318,
    tStruct = 319,
    tSemiColon = 320,
    tCScope = 321,
    tOScope = 322,
    tAndAnd = 323,
    tPipePipe = 324,
    tAssOperator = 325,
    tExMarkEqual = 326,
    tEqualEqual = 327,
    tMoreEqual = 328,
    tLessEqual = 329,
    tMoreMore = 330,
    tLessLess = 331,
    tMinusEqual = 332,
    tPlusEqual = 333,
    tModuloEqual = 334,
    tMultiplyEqual = 335,
    tEqual = 336,
    tXorEqual = 337,
    tAndEqual = 338,
    tDotDotDot = 339,
    tMoreMoreEqual = 340,
    tLessLessEqual = 341,
    tLess = 342
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "src/c_parser.y" /* yacc.c:1909  */

  Expression *expr;
  int integer_constant;
  double double_constant;
  std::string *string;

#line 168 "src/c_parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED  */
