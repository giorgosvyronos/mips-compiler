#include "ast_scope.hpp"

Scope::Scope(){}
void Scope::add(Expression* _sta){
  if (_sta){
    statements.push_back(_sta);
    //fileOut<<"added to scope" << endl;
  }
}
uint32_t Scope::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* sta: statements){
    sum+= sta->getSize(context);
  }
  return sum;
}
void Scope::setType(const string &_type){}
string Scope::getType() const{
  return "scope";
}
string Scope::getVal() const{
  return "";
}
void Scope::codeGen(ostream& fileOut, const string& destReg, Context& context){
  // context.incrementScopeCounter();
  for (Expression* sta: statements){
    //fileOut<<"scope analysis..." << endl;
    sta->codeGen(fileOut,destReg,context);
  }
  // context.clearScopeContext();
  // context.decrementScopeCounter();
}