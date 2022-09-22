%code requires{
  #include <string>
  #include <stdio.h>
  #include <cassert>
  #include <iostream>

  #include "ast.hpp"

  extern Program *g_root;
 
  
  int yylex(void);
  void yyerror(const char* );

  using namespace std;
}

%union{
  Expression *expr;
  int integer_constant;
  double double_constant;
  std::string *string;
}

%token tInt tDivision tPipeEqual tDivisionEqual tStringLiteral tIdentifier tIntegerConstant tCharacterConstant tFloatingConstant tFor tWhile tSizeof tAuto tBreak tCase tChar tConst tContinue tDo tDouble tElse tEnum tExtern tFloat tGoTo tIf tLong tRegister tReturn tShort tSigned tStatic tDefault tSwitch tTypedef tUnion tUnsigned tVoid tVolatile tPipe tLBracket tRBracket tDot tExMark tPlus tMinus tPlusPlus tMinusMinus tLSBracket tRSBracket tMore tAnd tDivison tModulo tXor tMultiply tComma tHash tQuesMark tColon tTilde tStruct tSemiColon tCScope tOScope tAndAnd tPipePipe tAssOperator tExMarkEqual tEqualEqual tMoreEqual tLessEqual tMoreMore tLessLess tMinusEqual tPlusEqual tModuloEqual tMultiplyEqual tEqual tXorEqual tAndEqual tDotDotDot tMoreMoreEqual tLessLessEqual tLess
%type <integer_constant> tIntegerConstant
%type <string> tIdentifier TYPES CONDITIONERS tInt tEqual tEqualEqual tMore tLess tLessEqual tMoreEqual tExMarkEqual tSemiColon tCScope tOScope tRBracket tLBracket tComma tWhile tIf tElse tPlusEqual tMinusEqual tPlusPlus tMinusMinus UNARY_OPERATORS OPERATORS tModuloEqual tDivisionEqual tMultiplyEqual tXorEqual tAndEqual tPipeEqual tPipePipe tAndAnd tPipe tXor tAnd tLessLess tMoreMore tPlus tMinus tMultiply tDivision tModulo tContinue tBreak tReturn tFor tSwitch tCase tColon tDefault tLSBracket tRSBracket tEnum
%type <expr> ARRAY_CALL ARRAY_DECL PROGRAMS FUNCTION FUNCTION_DECLARATION STATEMENTS STATEMENT PRIMARY_EXPRESSION PARAMETERS_LIST ROOT IDENTIFIER PARAMETERS DECLARATION_STATEMENT ASSIGNMENT_STATEMENT CONDITION LOOP_STATEMENT IFELSE_STATEMENT CONDITIONAL_EXPRESSION BOOLEAN_OR BOOLEAN_AND BITWISE_OR BITWISE_XOR BITWISE_AND BOOL_EXPRESSION SHIFT_EXPRESSION PLUS_MINUS_EXPRESSION MULTIPLICATIVE_EXPRESSION UNIT_EXPRESSION FUNCTION_CALL PROGRAM END_STATEMENT CASE_STATEMENT ARGUMENTS ARGUMENTS_LIST ENUM_VARIABLES ENUM_STATEMENT


%start ROOT
%%


ROOT : PROGRAMS

PROGRAMS : PROGRAM {g_root->add($1);}
        | PROGRAMS PROGRAM {g_root->add($2);}

PROGRAM : FUNCTION { $$=$1; }
        | FUNCTION_DECLARATION {$$=$1;}
        | DECLARATION_STATEMENT {$$=$1;}
        | ARRAY_DECL {$$=$1;}
        | ASSIGNMENT_STATEMENT {$$=$1;}
        | ENUM_STATEMENT { $$ = $1;}
        
FUNCTION: TYPES tIdentifier PARAMETERS tOScope STATEMENTS tCScope {$$ = new Function(*$2, $3, $5);}

STATEMENTS : STATEMENT {$$ = new Scope(); $$->add($1);}
           | STATEMENTS STATEMENT {$1->add($2); $$ = $1;}

STATEMENT : ASSIGNMENT_STATEMENT {$$=$1;}
          | LOOP_STATEMENT { $$ = $1;}
          | IFELSE_STATEMENT {$$ = $1;}
          | FUNCTION_CALL tSemiColon { $$ = $1; }
          | END_STATEMENT {$$=$1;}
          | CASE_STATEMENT { $$ = $1;}
          | DECLARATION_STATEMENT {$$=$1;}
          | ARRAY_DECL {$$=$1;}

ENUM_STATEMENT : tEnum tIdentifier tOScope ENUM_VARIABLES tCScope tSemiColon {$$ = new Enum(*$2,$4);}

ENUM_VARIABLES : IDENTIFIER {$$ = new EnumItem(); $$->add($1);}
               | ASSIGNMENT_STATEMENT {$$ = new EnumItem(); $$->add($1);}
               | ENUM_VARIABLES tComma IDENTIFIER {$1->add($3);$$ = $1;}
               | ENUM_VARIABLES tComma ASSIGNMENT_STATEMENT {$1->add($3);$$ = $1;}

DECLARATION_STATEMENT : TYPES IDENTIFIER tSemiColon {$$ = $2;}

ASSIGNMENT_STATEMENT : TYPES IDENTIFIER OPERATORS CONDITIONAL_EXPRESSION tSemiColon {$$ = new BinaryExpression($2,*$3,$4);}
                      | IDENTIFIER OPERATORS CONDITIONAL_EXPRESSION tSemiColon {$$ = new BinaryExpression($1,*$2,$3);}
                      | IDENTIFIER OPERATORS CONDITIONAL_EXPRESSION            {$$ = new BinaryExpression($1,*$2,$3);}
                      | IDENTIFIER UNARY_OPERATORS tSemiColon { $$ = new BinaryExpression($1,*$2,NULL);}
  /* FOR FOR LOOP*/   | IDENTIFIER UNARY_OPERATORS  { $$ = new BinaryExpression($1,*$2,NULL);}
LOOP_STATEMENT : tWhile tLBracket CONDITION tRBracket tOScope STATEMENTS tCScope {$$ = new WhileLoop($3, $6);}
              | tWhile tLBracket CONDITION tRBracket tOScope tCScope {$$ = new WhileLoop($3, NULL);}
               | tFor tLBracket ASSIGNMENT_STATEMENT CONDITION tSemiColon ASSIGNMENT_STATEMENT tRBracket tOScope STATEMENT tCScope { $$ = new ForLoop($3,$4,$6,$9);}
               | tFor tLBracket ASSIGNMENT_STATEMENT CONDITION tSemiColon ASSIGNMENT_STATEMENT tRBracket tOScope tCScope { $$ = new ForLoop($3,$4,$6,NULL);}

IFELSE_STATEMENT : tIf tLBracket CONDITION tRBracket tOScope STATEMENTS tCScope             { $$ = new If($3,$6,NULL);}
	               | tIf tLBracket CONDITION tRBracket tOScope STATEMENTS tCScope tElse tOScope STATEMENTS tCScope          {$$ = new If($3,$6,$10);}
/*SWITCH STATE.*/| tSwitch tLBracket IDENTIFIER tRBracket tOScope STATEMENTS tCScope {$$ = new Switch($3,$6); }


CASE_STATEMENT : tCase PRIMARY_EXPRESSION tColon STATEMENTS { $$ = new Case($2,$4); }
               | tDefault tColon STATEMENTS         {$$ = new Case(NULL,$3); $$->setType("default");}


CONDITION : IDENTIFIER CONDITIONERS PRIMARY_EXPRESSION {$$ = new BinaryExpression($1,*$2,$3);}
          | IDENTIFIER CONDITIONERS IDENTIFIER {$$ = new BinaryExpression($1,*$2,$3);}
          | tIdentifier {$$ = new VariableCond(*$1);}
          | tIntegerConstant {$$ = new BinaryExpression(NULL,to_string($1),NULL);} 
          | CONDITIONAL_EXPRESSION {$$=$1;}
          




CONDITIONAL_EXPRESSION : BOOLEAN_OR { $$ = $1; }

BOOLEAN_OR : BOOLEAN_OR tPipePipe BOOLEAN_AND {$$ = new BinaryExpression($1, *$2, $3); } 
           | BOOLEAN_AND { $$ = $1; }

BOOLEAN_AND : BOOLEAN_AND tAndAnd BITWISE_OR { $$ = new BinaryExpression($1, *$2, $3);} 
            | BOOL_EXPRESSION { $$ = $1; }

BOOL_EXPRESSION : BOOL_EXPRESSION CONDITIONERS BITWISE_OR { $$ = new BinaryExpression($1, *$2, $3); }
                | BITWISE_OR { $$ = $1; }

BITWISE_OR : BITWISE_OR tPipe BITWISE_XOR { $$ = new BinaryExpression($1, *$2, $3); }
           | BITWISE_XOR { $$ = $1; }

BITWISE_XOR : BITWISE_XOR tXor BITWISE_AND { $$ = new BinaryExpression($1, *$2, $3); }
            | BITWISE_AND { $$ = $1; }

BITWISE_AND : BITWISE_AND tAnd BOOL_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
            | SHIFT_EXPRESSION { $$ = $1; }

SHIFT_EXPRESSION : SHIFT_EXPRESSION tLessLess PLUS_MINUS_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                 | SHIFT_EXPRESSION tMoreMore PLUS_MINUS_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                 | PLUS_MINUS_EXPRESSION { $$ = $1; }

PLUS_MINUS_EXPRESSION : PLUS_MINUS_EXPRESSION tPlus MULTIPLICATIVE_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                      | PLUS_MINUS_EXPRESSION tMinus MULTIPLICATIVE_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                      | MULTIPLICATIVE_EXPRESSION { $$ = $1; }

MULTIPLICATIVE_EXPRESSION : MULTIPLICATIVE_EXPRESSION tMultiply UNIT_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                          | MULTIPLICATIVE_EXPRESSION tDivision UNIT_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                          | MULTIPLICATIVE_EXPRESSION tModulo UNIT_EXPRESSION { $$ = new BinaryExpression($1, *$2, $3); }
                          |UNIT_EXPRESSION { $$ = $1; }

UNIT_EXPRESSION : PRIMARY_EXPRESSION { $$ = $1; }
                | IDENTIFIER {$$=$1;}
                | FUNCTION_CALL { $$ = $1; }
                
FUNCTION_CALL : IDENTIFIER tLBracket tRBracket {FunctionCall* f = new FunctionCall($$->getVal(), NULL); $$ = f;}
                | IDENTIFIER ARGUMENTS {FunctionCall* f = new FunctionCall($$->getVal(), $2); $$ = f;}

FUNCTION_DECLARATION : TYPES tIdentifier PARAMETERS tSemiColon {$$ = new FunctionDec(*$2, $3);}

ARRAY_DECL : TYPES tIdentifier tLSBracket tIntegerConstant tRSBracket tSemiColon {$$ = new ArrayDec($4,*$2,*$1);}

ARRAY_CALL : tIdentifier tLSBracket tIntegerConstant tRSBracket {$$ = new ArrayAcc($3,*$1);}

PRIMARY_EXPRESSION : tIntegerConstant {$$ = new NumberInt($1);}

IDENTIFIER : tIdentifier {$$ = new Variable(*$1);}
            | ARRAY_CALL {$$=$1;}


CONDITIONERS : tLess {$$=$1;}
             | tMore {$$=$1;}
             | tMoreEqual {$$=$1;}
             | tLessEqual {$$=$1;}
             | tEqualEqual {$$=$1;}
             | tExMarkEqual {$$=$1;}

OPERATORS : tEqual { $$ = $1;}
          | tPlusEqual { $$ = $1;}
          | tMinusEqual { $$ = $1;}
          | tModuloEqual { $$ = $1;}
          | tDivisionEqual { $$ = $1;}
          | tMultiplyEqual { $$ = $1;}
          | tXorEqual { $$ = $1;}
          | tAndEqual { $$ = $1;}
          | tPipeEqual { $$ = $1;}
          | tPlusPlus { $$ = $1;}

UNARY_OPERATORS : tPlusPlus { $$ = $1;}
                | tMinusMinus { $$ = $1;}

PARAMETERS : tLBracket tRBracket {$$ = new ParameterList();}
           | tLBracket PARAMETERS_LIST tRBracket {$$ = $2;}

PARAMETERS_LIST : TYPES tIdentifier {$$ = new ParameterList();
                      Parameter* p = new Parameter(*$2);
                      $$->add(p);}
                | PARAMETERS_LIST tComma TYPES tIdentifier  {Parameter* p = new Parameter(*$4);
                                              $$->add(p);}


ARGUMENTS : tLBracket tRBracket { $$ = new ArgumentList();}
          | tLBracket ARGUMENTS_LIST tRBracket {$$ = $2;}


ARGUMENTS_LIST : CONDITIONAL_EXPRESSION {$$ = new ArgumentList();
                      Argument* a = new Argument($1);
                      $$->add(a);}
               | ARGUMENTS_LIST tComma CONDITIONAL_EXPRESSION {Argument* a = new Argument($3);
                                              $$->add(a);}




END_STATEMENT : tReturn CONDITIONAL_EXPRESSION tSemiColon                    {$$ = new Return($2);}
              | tReturn FUNCTION_CALL tSemiColon                             {$$ = new Return($2);}
              | tBreak tSemiColon                                            { $$ = new Break();}
              | tContinue tSemiColon                                         { $$ = new Continue();}


TYPES: tInt {$$ = $1;};

%%

Program* g_root;
Expression *parseAST(){
  g_root = new Program();
  yyparse();
  return g_root;
}