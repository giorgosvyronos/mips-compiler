#include "ast_switch.hpp"

Switch::Switch(Expression* _exp, Expression* _scope){
  exp = _exp;
  scope = _scope;
}
void Switch::add(Expression* _exp){
}
uint32_t Switch::getSize(Context& context) const{
  if(scope){
    return exp->getSize(context) + scope->getSize(context);
  } else {
    return exp->getSize(context);
  }
}
void Switch::setType(const string &_type){}
string Switch::getType() const{
  return "switch";
}
string Switch::getVal() const{
  return "";
}
void Switch::codeGen(ostream& fileOut,const string& destReg, Context& context){
  context.incrementLoopCounter();
  context.incrementCaseCounter();
  string L1 = string("$EXIT"+to_string(context.getLoopCounter()));

  string reg1 = context.getReg(exp->getVal());

  if (scope){
    scope->codeGen(fileOut,reg1, context);
  }
  fileOut << L1 << ":" << endl;
  string L2 = string("$CASE"+to_string(context.getCaseCounter()+1));
  fileOut << L2 << ":" << endl;
}


Case::Case(Expression* _exp, Expression* _sta){
  exp = _exp;
  if (_sta){
    sta = _sta;
  }
  type = "";
}
void Case::add(Expression* _exp){}
uint32_t Case::getSize(Context& context) const{
  if(sta){
    return sta->getSize(context);
  }
}
void Case::setType(const string &_type){
  type = _type;
}
string Case::getType() const{
  return type;
}
string Case::getVal() const{
  return "";
}
void Case::codeGen(ostream& fileOut, const string& destReg, Context& context){
  context.incrementCaseCounter();
  string L0 = string("$CASE"+to_string(context.getCaseCounter()));
  string L1 = string("$CASE"+to_string(context.getCaseCounter()+1));


  string reg1 = context.getFreeRegister(fileOut,"");
  string scratch_id1 = context.makeLabel("scratch_case");
  context.makeBinding(fileOut,scratch_id1, reg1, "scratch");

  fileOut << L0 << ":" << endl;
  if (type.compare("default")!=0){
    exp->codeGen(fileOut,reg1, context);
    fileOut << "bne " << reg1 << "," << destReg << "," << L1 <<endl;
    fileOut << "nop" << endl;
  }
  context.releaseBinding(scratch_id1);
  if (sta){
    sta->codeGen(fileOut,destReg, context);
  }
}