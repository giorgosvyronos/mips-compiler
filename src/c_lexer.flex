%option noyywrap
%option nounput
%option noinput

%{
  #include <stdlib.h>
  #include <string>
  #include <iostream>
  #include <stdio.h>

  #include "c_parser.tab.hpp"
  using namespace std;
  string source_file = "";
  int stream_line = 1;
  int source_line = 1;
  int column = 1;
%}

FLOATING_SUFFIX           [flFL]
SIGN                      [+-]
DIGIT                     [0-9]
DIGIT_SEQUENCE            ([0-9]+)

NONDIGIT                  [_a-zA-Z]
NONZERO_DIGIT             [1-9]
DECIMAL_CONSTANT          (0|({NONZERO_DIGIT}{DIGIT}*))
INTEGER_CONSTANT          ({DECIMAL_CONSTANT}?)

IDENTIFIER                ({NONDIGIT}({DIGIT}|{NONDIGIT})*)

COMMENT                   (\/\/[^\n]*)|(\/\\*(.*?)\\*\/)
WHITE_SPACE               [ ]
TAB                       [\t]
NEW_LINE                  [\n\r]
PREPROCESSOR              (\#[^\n]*)
INVALID                   (.)

%%
{COMMENT}                 {;}
{NEW_LINE}                {source_line++; stream_line++; column = 1;}
{WHITE_SPACE}             {column++;}
{TAB}                     {column+=8;}
{PREPROCESSOR}            {;}
(int)                     {yylval.string = new string("int");               return tInt;}
(return)                  {yylval.string = new string("return");            return tReturn;}
(continue)                {yylval.string = new string("continue");          return tContinue;}
(break)                   {yylval.string = new string("break");             return tBreak; }
(unsigned)                {yylval.string = new string("unsigned");          return tUnsigned;}
(void)                    {yylval.string = new string("void");              return tVoid;}
(volatile)                {yylval.string = new string("volatile");          return tVolatile;}
(while)                   {yylval.string = new string("while");             return tWhile;}
(if)                      {yylval.string = new string("if");                return tIf;}
(else)                    {yylval.string = new string("else");              return tElse;}
(for)                     {yylval.string = new string("for");               return tFor; }
(switch)                  {yylval.string = new string("switch");            return tSwitch;}
(case)                    {yylval.string = new string("case");              return tCase;}
(default)                 {yylval.string = new string("default");           return tDefault;}
(enum)                    {yylval.string = new string("enum");               return tEnum;}

\|                        {yylval.string = new string("|");                 return tPipe;}
\=                        {yylval.string = new string("=");                 return tEqual;}
\(                        {return tLBracket;}
\)                        {return tRBracket;}
\.                        {return tDot;}
\!                        {return tExMark;}
\+                        {yylval.string = new string("+");                 return tPlus;}
\-                        {yylval.string = new string("-");                 return tMinus;}
\+\+                      {yylval.string = new string("++");                return tPlusPlus;}
\-\-                      {yylval.string = new string("--");                return tMinusMinus;}
\[                        {yylval.string = new string("[");                 return tLSBracket;}
\]                        {yylval.string = new string("]");                return tRSBracket;}
\&                        {yylval.string = new string("&");                 return tAnd;}
\/                        {yylval.string = new string("/");                 return tDivision;}
\%                        {yylval.string = new string("%");                 return tModulo;}
\^                        {yylval.string = new string("^");                 return tXor;}
\*                        {yylval.string = new string("*");                 return tMultiply;}
\,                        {return tComma;}
\#                        {return tHash;}
\?                        {return tQuesMark;}
\:                        {return tColon;}
\~                        {return tTilde;}
\;                        {return tSemiColon;}
\}                        {return tCScope;}
\{                        {return tOScope;}
\&\&                      {yylval.string = new string("&&");                return tAndAnd;}
\|\|                      {yylval.string = new string("||");                return tPipePipe;}
\|\=                      {yylval.string = new string("|=");                return tPipeEqual;}
\-\>                      {yylval.string = new string("->");                return tAssOperator;}
\!\=                      {yylval.string = new string("!=");                return tExMarkEqual;}
\=\=                      {yylval.string = new string("==");                return tEqualEqual;}
\>\=                      {yylval.string = new string(">=");                return tMoreEqual;}
\<\=                      {yylval.string = new string("<=");                return tLessEqual;}
\>\>                      {yylval.string = new string(">>");                return tMoreMore;}
\<\<                      {yylval.string = new string("<<");                return tLessLess;}
\-\=                      {yylval.string = new string("-=");                return tMinusEqual;}
\+\=                      {yylval.string = new string("+=");                return tPlusEqual;}
\%\=                      {yylval.string = new string("%=");                return tModuloEqual;}
\/\=                      {yylval.string = new string("/=");                return tDivisionEqual;}
\*\=                      {yylval.string = new string("*=");                return tMultiplyEqual;}
\^\=                      {yylval.string = new string("^=");                return tXorEqual;}
\&\=                      {yylval.string = new string("&=");                return tAndEqual;}
\.\.\.                    {return tDotDotDot;}
\>\>\=                    {yylval.string = new string(">>=");               return tMoreMoreEqual;}
\<\<\=                    {yylval.string = new string("<<=");               return tLessLessEqual;}
\<                        {yylval.string = new string("<");                 return tLess;}
\>                        {yylval.string = new string(">");                 return tMore;}
{IDENTIFIER}              {yylval.string = new string(yytext);              return tIdentifier; }
{INTEGER_CONSTANT}        {yylval.integer_constant = atoi(yytext);          return tIntegerConstant;}
{INVALID}                 {;}
%%

void yyerror(char const* c){
  fprintf (stderr, "Flex Error: String: %s, Source Line: %d\n", yytext, source_line);
  exit(1);
}