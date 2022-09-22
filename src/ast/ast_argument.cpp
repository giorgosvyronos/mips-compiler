#include "ast_argument.hpp"

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}


Argument::Argument(Expression* _var){
  if(_var){
    var = _var;
  }
}

void Argument::add(Expression* _exp){}
uint32_t Argument::getSize(Context& context) const{
  return var->getSize(context);
}
void Argument::setType(const string &_type){
  var->setType(_type);
}
string Argument::getType() const{
  return type;
}
string Argument::getVal() const {
  return "";
}
void Argument::codeGen(ostream& fileOut, const string& destReg, Context& context){
    string reg1;
    if(var->getType()=="intCon"){
      string val = var->getVal();
      fileOut << "li " << destReg << ", " << val << endl;
    }else if(var->getType()=="variable"){
      reg1 = context.getReg(var->getVal());
      fileOut << "move " << destReg << ", " << reg1 << endl;
    }else if(var->getType()=="func_call"){
      reg1 = context.getFreeRegister(fileOut,"");
      var->codeGen(fileOut,reg1, context);
      fileOut << "move " << reg1 << ", $v0" << endl;
    }else if(var->getType()=="binexp"){
      reg1 = context.getFreeRegister(fileOut,"");
      var->codeGen(fileOut,reg1,context);
      fileOut << "move " << destReg << ", " << reg1 << endl;
    }
}




ArgumentList::ArgumentList(){}
void ArgumentList::add(Expression* _exp){
  arguments.push_back(_exp);
}
uint32_t ArgumentList::getSize(Context& context) const{
  uint32_t sum = 0;
  for (Expression* arg: arguments){
    sum+= arg->getSize(context);
  }
  return sum;
}
void ArgumentList::setType(const string &_type){}
string ArgumentList::getType() const{
  return "argument_list";
}
string ArgumentList::getVal() const{
  return "";
}
void ArgumentList::codeGen(ostream& fileOut, const string& destReg, Context& context){
  int i=0;
  string reg1 = "$a";
  for (Expression* exp: arguments){
    string reg2 = reg1+to_string(i);
    exp->codeGen(fileOut,reg2,context);
    i++;
  }
}

