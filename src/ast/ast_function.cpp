#include "ast_function.hpp"

Function::Function(const string &_id, Expression* _parameters, Expression* _scope):id(_id){
  parameters = _parameters;
  scope = _scope;
}
void Function::add(Expression* _exp){}
uint32_t Function::getSize(Context& context) const{
  return scope->getSize(context) + parameters->getSize(context);
}
void Function::setType(const string &_type){
  type = _type;
}
string Function::getType() const{
  return type;
}
string Function::getVal() const{
  return id;
}
void Function::codeGen(ostream& fileOut, const string& destReg, Context& context){
  // uint32_t stack_size = getSize(context)*3;

  // fileOut<<"\t.align	2"<<endl
  // <<"\t.globl	"<<id<<endl
  // <<"\t.set	nomips16"<<endl
  // <<"\t.set	nomicromips"<<endl
  // <<"\t.ent	"<<id<<endl;
  // fileOut<<"\t.type\t"<<id<<", @function"<<endl;
  // fileOut<<id<<":"<<endl;

  // context.incrementFunctionCounter();
  // context.allocateStack(8+stack_size);
  // //Versatile register, clean it just in case
  // fileOut<<"\t"<<"move $t9,$0"<<endl;
  // parameters->codeGen("", context);

  // if (id.compare("main")==0){
  //   fileOut<<"\t"<<"move $2,$0"<<endl;
  //   vector<Expression*> global;
  //   context.loadGlobalExpression(global);
  //   for (Expression* exp: global){
  //     exp->codeGen("", context);
  //   }
  // }

  // fileOut << id << ":" << endl;
  parameters->codeGen(fileOut,"", context);
  scope->codeGen(fileOut,destReg,context);

  //fileOut<<"$EXIT_FUNC"<<to_string(context.getFunctionCounter())<<":"<<endl;

  // fileOut << "jr $ra" << endl;
  // fileOut << "nop" << endl;
   //cout<<"$EXIT_FUNC"<<to_string(context.getFunctionCounter())<<":"<<endl;

  // context.loadLocalVariables();
  // context.deallocateStack(8+stack_size);

  // fileOut<<"\t"<<"j $31"<<endl;
  // fileOut<<"\t"<<"nop" <<endl;
  // fileOut<<endl<<"\t.set	macro"<<endl
	// <<"\t.set	reorder"<<endl
	// <<"\t.end	"<<id<<endl
	// <<"\t.size	"<<id<<", .-"<<id<<endl;
}

 FunctionCall::FunctionCall(const string &_id, Expression* _arguments):id(_id){
   arguments = _arguments;
 }
 void FunctionCall::add(Expression* _exp){
 }
 uint32_t FunctionCall::getSize(Context& context) const{
   if (arguments){
     return arguments->getSize(context);
   }
 }
void FunctionCall::setType(const string &_type){}
string FunctionCall::getType() const{
  return "func_call";
}
string FunctionCall::getVal() const{
  return id;
}
void FunctionCall::codeGen(ostream& fileOut,const string& destReg, Context& context){
  uint32_t stack_pointer = context.getStackPointer();
  //Especially for return address
  // stack_pointer-=4;

  // context.saveCurrentVariables();
  // if (arguments){
  //   arguments->codeGen("parameters", context);
  // }

  // fileOut<<"\t"<<"sw	$31,"<<to_string(stack_pointer)<<"($sp)"<<endl;
  // fileOut<<"\t"<<".option pic0"<<endl;
  if(arguments){
    arguments->codeGen(fileOut,destReg,context);
  }
  
  fileOut << "jal " << id << endl;

  fileOut << "nop" << endl;
  //fileOut<<"\t"<<".option	pic2"<<endl;
  // context.loadCurrentVariables();
  // fileOut<<"\t"<<"lw	$31,"<<to_string(stack_pointer)<<"($sp)"<<endl;
  // if (destReg.compare("")!=0){
  //   fileOut<<"\t"<<"move "<<destReg<<",$2"<<endl;
  }

FunctionDec::FunctionDec(const string &_id, Expression* _parameters):id(_id){
  parameters = _parameters;
}
void FunctionDec::add(Expression* _exp){
}
uint32_t FunctionDec::getSize(Context& context) const{
  if (parameters){
    return parameters->getSize(context);
  }
}
void FunctionDec::setType(const string &_type){
  if (parameters){
    parameters->setType(_type);
  }
}
string FunctionDec::getType() const{
  return "func_dec";
}
string FunctionDec::getVal() const{
  return id;
}
void FunctionDec::codeGen(ostream& fileOut, const string& destReg, Context& context){
  //fileOut << "nop #declaration" << endl;
}