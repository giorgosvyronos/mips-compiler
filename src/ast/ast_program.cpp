#include "ast_program.hpp"

Program::Program(){}
void Program::add(Expression* _exp){
  if (_exp){
    statements.push_back(_exp);
   // fileOut<< "added" << endl;
  }
}
uint32_t Program::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* sta: statements){
    sum+= sta->getSize(context);
  }
  return sum;
}
void Program::setType(const string &_type){}
string Program::getType() const{
  return "prog";
}
string Program::getVal() const{
  return "";
}
void Program::codeGen(ostream& fileOut, const string& destReg, Context& context){
  
  vector <Expression*> st;
    for(Expression* exp:statements){
      st.insert(st.begin(),exp);
    }
  //get to front enum
   fileOut << ".data" << endl;
   fileOut << endl;
  Expression* temp = NULL;
  int i=0;
  // if(statements.size()>1 && statements[0]->getVal()!="main"){
    for (Expression* exp: st){
    if(exp->getType()=="enum"){
      iter_swap(st.begin(), st.begin()+i);
      }
      i++;
    }
    // }




  for (Expression* exp: st){
    if(exp->getType()=="variable"){
      // fileOut << ".global " << exp->getVal() << endl;
      fileOut << exp->getVal() << ":" << endl << "\t" << ".word 0" << endl; 
    }else if(exp->getType()=="array"){
      fileOut << exp->getVal() << ":" << "\t .word 0" << endl;
      for(uint32_t i=1; i<exp->getSize(context); i++){
      fileOut << "\t" << ".word 0" << endl;
      }
    }else if(exp->getType()=="enum"){
      temp = exp;
      
    }else{
    fileOut << ".globl " << exp->getVal() << endl;
    if(exp->getType()!="func_dec"){fileOut << exp->getVal() << ":" << endl;}
    if(temp){temp->codeGen(fileOut,destReg,context);}
    exp->codeGen(fileOut,destReg, context);
    fileOut << endl;
    }
  //context.clearContext();
  }
  fileOut << ".data" << endl;
}

/*
enum X{
    vv,   ASSIGNMENTE STATEMENT: IDENTIFIER OPERATOR CONDITIONAL EXPRESSION
				|....
				|
FUNCTION_ENUM: TENUM IDENTIFIER { ENUM_STATEMENTS}

ENUM_STATEMENTS = ENUM_STATEMENT 
			| ENUM_STATEMENTS ENUM_STATEMENT

ENUM_STATEMENT : IDENTIFIER,
		IDENTIFIER TEQUAL CONDITIONAL_EXPRESSION
		 


CONDITIONAL EXPR    new BinaryExpression(IDENTIFIER,"=",NULL)
enum X{ 
yy, xx=20 
};

int g()
{
    return xx;
}



X: 
$t0=0 (yy)
$t1=20 (xx)

g:
.
..

.
move $v0, $t1;
j $ra
nop




main
*/
