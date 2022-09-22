#include "ast_forloop.hpp"

ForLoop::ForLoop(Expression* _var, Expression* _cond, Expression* _act, Expression* _statement){
  action = _act;
  variable = _var;
  condition = _cond;
  statement = _statement;
}
void ForLoop::add(Expression* _exp){
  if (statement){
    statement->add(_exp);
  }
}
uint32_t ForLoop::getSize(Context& context) const{
  if (action){
    if (statement){
      return action->getSize(context) + variable->getSize(context) + statement->getSize(context);
    } else {
      return action->getSize(context) + variable->getSize(context);
    }
  } else {
    return variable->getSize(context) + statement->getSize(context);
  }
  return 0;
}
void ForLoop::setType(const string &_type){}
string ForLoop::getType() const{
  return "forloop";
}
string ForLoop::getVal() const{
  return "";
}
void ForLoop::codeGen(ostream& fileOut,const string& destReg, Context& context){
  context.incrementLoopCounter();
  context.incrementUpdateCounter();
  string L1 = string("$LOOP"+to_string(context.getLoopCounter()));
  string L2 = string("$EXIT"+to_string(context.getLoopCounter()));
  string L3 = string("$CONT"+to_string(context.getUpdateCounter()));

  string scratch_id1 = context.makeLabel("scratch_for");
  string reg1 = context.getFreeRegister(fileOut,"");
  context.makeBinding(fileOut,scratch_id1, reg1,"scratch");

  variable->codeGen(fileOut,"", context);

  fileOut << L1 << ":" << endl;
  condition->codeGen(fileOut,reg1, context);
  fileOut<<"beq "<<reg1<<",$0,"<<L2 <<endl;
  // fileOut << L2 << endl;
  fileOut << "nop" <<  endl;
  if (statement){
    statement->codeGen(fileOut,destReg, context);
  }
  if (action){
    fileOut << L3 << ":" << endl;
    action->codeGen(fileOut,"", context);
  }
  fileOut << "j " << L1 << endl;
  fileOut << "nop" << endl;
  fileOut << L2 << ":" << endl;

  context.releaseBinding(scratch_id1);
}