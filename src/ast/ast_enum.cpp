#include "ast_enum.hpp"

Enum::Enum(const string &_id, Expression* _scope):id(_id){
  scope = _scope;
}
void Enum::add(Expression* _exp){}
uint32_t Enum::getSize(Context& context) const{
  return scope->getSize(context);
}
void Enum::setType(const string &_type){}
string Enum::getType() const{
  return "enum";
}
string Enum::getVal() const{
  return id;
}
void Enum::codeGen(ostream& fileOut, const string& destReg, Context& context){
  // fileOut << id << ":" << endl;
  if(scope){
  scope->codeGen(fileOut,destReg,context);
  }

}

EnumItem::EnumItem(){
}
void EnumItem::add(Expression* _exp){
if (_exp){
    statements.push_back(_exp);
    //fileOut<<"added to scope" << endl;
  }
}
uint32_t EnumItem::getSize(Context& context) const{}
void EnumItem::setType(const string &_type){
  type = _type;
}
string EnumItem::getType() const{
  return type;
}
string EnumItem::getVal() const{
  return "";
}
void EnumItem::codeGen(ostream& fileOut, const string& destReg, Context& context){

for(Expression* sta: statements){

  string tp = sta->getType();
  if(tp=="variable"){
      string reg1 = context.getFreeRegister(fileOut,"");
      context.makeBinding(fileOut,sta->getVal(), reg1, "scratch");
      fileOut << "li " << reg1 << ", " << context.getEnumCounter() << endl;
  }else{
     string reg1 = context.getFreeRegister(fileOut,"");
     sta->codeGen(fileOut,reg1,context);
  }

  context.incrementEnumCounter();
}
}