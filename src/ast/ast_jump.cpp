#include "ast_jump.hpp"

Return::Return(Expression* _ret){
  ret = _ret;
}
void Return::add(Expression* _exp){}
uint32_t Return::getSize(Context& context) const{
  if(ret){
      return ret->getSize(context);
  }
  return 0;
}
void Return::setType(const string &_type){}
string Return::getType() const{
  return "return";
}
string Return::getVal() const{
  return "";
}
void Return::codeGen(ostream& fileOut, const string& destReg, Context& context){
  if(ret){
    fileOut<<"move $v0,$0"<<endl;
    if ((ret->getType()=="intCon") || (ret->getType()=="doubleCon") || (ret->getType()=="charCon")){
      fileOut<<"li $v0,"<<ret->getVal()<<endl;
    } else if(ret->getType()=="variable" || ret->getType()=="array"){
        string reg1 = context.getReg(ret->getVal());
        fileOut << "move " << destReg << " ," << reg1 << endl;
    }else if(ret->getType()=="func_call"){
      context.incrementListCounter();
      uint32_t func = context.getListCounter();
      fileOut << "move $s" << func << ", $ra" << endl;
      ret->codeGen(fileOut, destReg, context);
      fileOut << "move $ra, $s" << func << endl;
    }else {
      string reg1 = context.getFreeRegister(fileOut,"");
      ret->codeGen(fileOut,reg1, context);
      fileOut << "move " << destReg << " ," << reg1 << endl;
    }
     fileOut << "jr $ra" << endl;
    fileOut << "nop" << endl;
    // fileOut<<"j $EXIT_FUNC"<<to_string(context.getFunctionCounter())<<endl;
    // fileOut<<"nop"<<endl;
  }
}

Continue::Continue(){}
void Continue::add(Expression* _exp){}
uint32_t Continue::getSize(Context& context) const{
  return 0;
}

void Continue::setType(const string &_type){}
string Continue::getType() const{
  return "Continue";
}
string Continue::getVal() const{
  return "";
}
void Continue::codeGen(ostream& fileOut, const string& destReg, Context& context){
    fileOut << "j $CONT" << to_string(context.getUpdateCounter()) << endl;
    fileOut << "nop" << endl;
}

Break::Break(){}
void Break::add(Expression* _exp){}
uint32_t Break::getSize(Context& context) const{
  return 0;
}
void Break::setType(const string &_type){}
string Break::getType() const{
  return "Break";
}
string Break::getVal() const{
  return "";
}
void Break::codeGen(ostream& fileOut,const string& destReg, Context& context){
    fileOut << "j $EXIT" << to_string(context.getLoopCounter()) << endl;
    fileOut << "nop" << endl;
}