#include "ast_variable.hpp"

VariableCond::VariableCond(const string &_id): id(_id),type(""){}
void VariableCond::add(Expression* _exp){}
uint32_t VariableCond::getSize(Context& context) const{
    return context.getSize(id);
}
void VariableCond::setType(const string &_type){
  type = _type;
}
string VariableCond::getType() const{
  //return type;
  return "variable";
}
string VariableCond::getVal() const{
  return id;
}
void VariableCond::codeGen(ostream& fileOut,const string& destReg, Context& context){
  string reg1 = context.getReg(id);

    string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"beq "<<reg1<<",$0,"<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<L2<<":"<<endl;


  // fileOut << "beq " << reg1 << ", $0, ";
}



Variable::Variable(const string &_id): id(_id),type(""){}
void Variable::add(Expression* _exp){}
uint32_t Variable::getSize(Context& context) const{
    return context.getSize(id);
}
void Variable::setType(const string &_type){
  type = _type;
}
string Variable::getType() const{
  //return type;
  return "variable";
}
string Variable::getVal() const{
  return id;
}
void Variable::codeGen(ostream& fileOut,const string& destReg, Context& context){
  //fileOut<< "checked" << endl;
  string reg1 = context.getFreeRegister(fileOut,"");
  context.makeBinding(fileOut,id,reg1,"scratch");
}
//     if(!(context.isInContext(id))){
//       //This means that what the compiler sees is a DECLARATION
//       if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
//           || (type.compare("signed char")==0)   || (type.compare("int")==0)
//           || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
//           || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
//           || (type.compare("unsigned short")==0) || (type.compare("double")==0)
//           || (type.compare("float")==0)
//         ){
//         //Might be an expression
//         if (destReg.compare("global_expression")==0){
//           fileOut<<"\t"<<".globl "<<id<<endl;
//           fileOut<<"\t"<<".data"<<endl;
//           fileOut<<"\t"<<".align 2"<<endl;
//           fileOut<<"\t"<<".type "<<id<<", @object"<<endl;
//           fileOut<<"\t"<<".size "<<id<<", 4"<<endl;
//           fileOut<<id<<":"<<endl;
//           fileOut<<"\t"<<".word 0"<<endl;
//           fileOut<<"\t"<<".text"<<endl;
//         } else if (destReg.compare("global")==0){
//           fileOut<<"\t"<<".comm	"<<id<<",4,4"<<endl;
//         } else {
//           string reg1 = context.getFreeRegister("");
//           context.makeBinding(id, reg1,type);
//         }
//       } else {
//         //GLOBAL VARIABLE
//         string reg_id = context.getFreeRegister("");
//         context.makeBinding(id, reg_id,"global");
//         if (destReg.compare("")!=0){
//           context.loadVariable(id, destReg, false);
//         }
//       }
//     } else {
//       //REDECLARATION
//       if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
//           || (type.compare("signed char")==0)   || (type.compare("int")==0)
//           || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
//           || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
//           || (type.compare("unsigned short")==0) || (type.compare("double")==0)
//           || (type.compare("float")==0)
//         ){
//         context.updateBinding(id,type);
//       }
//       if (destReg.compare("")!=0){
//         fileOut<<"\t"<<"move "<<destReg<<","<<context.getReg(id)
//         <<"\t #Moving var "<<id<<" to destination"
//         <<endl;
//       }
//     }
// }

// VariableList::VariableList(){}
// void VariableList::add(Expression* _exp) {
//   variables.push_back(_exp);
// }
// uint32_t VariableList::getSize(Context& context) const{
//   uint32_t sum = 0;
//   for (Expression* var: variables){
//     sum+= var->getSize(context);
//   }
//   return sum;
// }
// string VariableList::print(const bool& complete) const{
//   stringstream ss;
//     for (Expression* exp: variables){
//       ss<<exp->print(complete);
//     }
//   return ss.str();
// }
// void VariableList::setType(const string &_type){
//   for (Expression* exp: variables){
//     exp->setType(_type);
//   }
// }
// string VariableList::getType() const{
//   return "variable_list";
// }
// string VariableList::getVal() const{
//   return "";
// }
// void VariableList::codeGen(const string& destReg, Context& context){
//   for (Expression* var: variables){
//     var->codeGen(destReg,context);
//   }
// }