#include "ast_if_then_else.hpp"

If::If(Expression* _conditions, Expression* _scope_true, Expression* _scope_false){
  conditions = _conditions;
  if (_scope_true){
    scope_true = _scope_true;
  }
  if (_scope_false){
    scope_false = _scope_false;
  }
}
void If::add(Expression* _exp){}
uint32_t If::getSize(Context& context) const{
  if (scope_false && scope_true){
    return conditions->getSize(context) + scope_true->getSize(context) + scope_false->getSize(context);
  } else {
    if (scope_true){
      return conditions->getSize(context) + scope_true->getSize(context);
    } else {
      return 0;
    }
  }
}

void If::setType(const string &_type){
  scope_true->setType(_type);
}
string If::getType() const{
  return "if";
}
string If::getVal() const{
  return "";
}
void If::codeGen(ostream& fileOut, const string& destReg, Context& context){
  string L1 = context.makeLabel("If_FALSE");
  string L2 = context.makeLabel("If_EXIT");

  string reg1 = context.getFreeRegister(fileOut,"");
  string scratch_id1 = context.makeLabel("scratch_if");
  context.makeBinding(fileOut,scratch_id1, reg1, "scratch");

  conditions->codeGen(fileOut,reg1, context);
  fileOut<<"beq "<<reg1<<",$0,"<<L1 <<endl;
  // fileOut << L1 << endl;
  fileOut<<"nop"<<endl;
  if (scope_true){
    scope_true->codeGen(fileOut,destReg, context);
  }

  fileOut<<"j "<<L2<<endl;
  fileOut<<"nop"<<endl;
  fileOut<<L1<<":"<<endl;
  if(scope_false){
    scope_false->codeGen(fileOut,destReg, context);
  }
  fileOut<<L2<<":"<<endl;
  context.releaseBinding(scratch_id1);
}