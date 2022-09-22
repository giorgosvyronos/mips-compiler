#include "ast_whileloop.hpp"

WhileLoop::WhileLoop(Expression* _conditions, Expression* _statement){
  conditions = _conditions;
  if (_statement){
    statement = _statement;
  }
}
void WhileLoop::add(Expression* _exp){}
//     statement->add(_exp);
// }
uint32_t WhileLoop::getSize(Context& context) const{
  if (statement){
    return statement->getSize(context) + conditions->getSize(context);
  } else {
    return conditions->getSize(context);
  }
}
void WhileLoop::setType(const string &_type){}
string WhileLoop::getType() const{
  return "whileloop";
}
string WhileLoop::getVal() const{
  return "";
}
void WhileLoop::codeGen(ostream& fileOut,const string& destReg, Context& context){
  //Create labels and scratch registers
  context.incrementLoopCounter();
  context.incrementUpdateCounter();
  string L1 = string("$LOOP"+to_string(context.getLoopCounter()));
  string L2 = string("$EXIT"+to_string(context.getLoopCounter()));
  string L3 = string("$CONT"+to_string(context.getUpdateCounter()));
  string reg1 = context.getFreeRegister(fileOut,"");
  string scratch_id1 = context.makeLabel("scratch_while");
  context.makeBinding(fileOut,scratch_id1, reg1,"scratch");

  fileOut<<L1<<":"<<endl;

  fileOut<<L3<<":"<<endl;
  //Codegen the condition
  conditions->codeGen(fileOut,reg1, context);
   fileOut<<"beq "<<reg1<<",$0,"<< L2 <<endl;
  // fileOut << L2 << endl;
  
  fileOut<<"nop"<<endl;
  if (statement){
    statement->codeGen(fileOut,destReg, context);
  }
  fileOut<<"j "<<L1<<endl;
  
  fileOut<<"nop"<<endl;
  
  fileOut<<L2<<":"<<endl;
  context.releaseBinding(scratch_id1);
}