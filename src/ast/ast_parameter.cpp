#include "ast_parameter.hpp"

Parameter::Parameter(const string &_id): id(_id){}

void Parameter::add(Expression* _exp){}
uint32_t Parameter::getSize(Context& context) const{
  return context.getSize(id);
}
void Parameter::setType(const string &_type){
  type =_type;
}
string Parameter::getType() const{
  return type;
}
string Parameter::getVal() const {
  return id;
}
void Parameter::codeGen(ostream& fileOut, const string& destReg, Context& context){
  string reg1 = context.getFreeRegister(fileOut,"");
  fileOut << "move " << reg1 << ", $a"; 
  context.makeBinding(fileOut,id,reg1,"scratch");

  // void Parameter::codeGen(const string& destReg, Context& context){
   // if(!(context.isInContext(id))){
   //   string reg1 = context.getFreeRegister("parameter");
   //   context.makeBinding(id, reg1,type);
   //   cout<<"\t #Making Parameter Binding "<<id<<endl;
   // }
}

ParameterList::ParameterList(){}
void ParameterList::add(Expression* _exp){
  parameters.push_back(_exp);
}
uint32_t ParameterList::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* par: parameters){
    sum+= par->getSize(context);
  }
  return sum;
}
void ParameterList::setType(const string &_type){
  for (Expression* exp: parameters){
    exp->setType(_type);
  }
}
string ParameterList::getType() const{
  return "param_list";
}
string ParameterList::getVal() const{
  return "";
}
void ParameterList::codeGen(ostream& fileOut,const string& destReg, Context& context){
  int i=0;
  for (Expression* exp: parameters){
    exp->codeGen(fileOut,"",context);
    fileOut << i << endl;
    i++;
  }
}