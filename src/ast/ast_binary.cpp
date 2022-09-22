#include "ast_binary.hpp"

BinaryExpression::BinaryExpression(Expression* _left, const string& _op, Expression* _right){
  if (_left){
    left = _left;
  }
  if (_right){
    right = _right;
  }
  op = _op;

}
void BinaryExpression::add(Expression* _exp){}

void BinaryExpression::codeGen(ostream& fileOut, const string& destReg, Context& context){

  string reg1;
  string reg2;
  if(op == "="){
    
    string id = left->getVal();
    if(context.isInContext(fileOut,id)){
      reg1 = context.getReg(id);
    }
    else{
    reg1 = context.getFreeRegister(fileOut,"");
    context.makeBinding(fileOut,id, reg1,"scratch");
    }
    string id2 = right->getVal();
    if(right->getType()=="func_call"){
      
      reg2 = context.getFreeRegister(fileOut,"");
      context.makeBinding(fileOut,id2, reg2,"scratch");
      context.incrementListCounter();
      uint32_t func = context.getListCounter();
      fileOut << "move $s" << func << ", $ra" << endl;
      right->codeGen(fileOut,reg2,context);
      fileOut << "move $ra, $s" << func << endl;
      fileOut << "move " << reg2 << ", $v0" << endl;
    }else{
    if(context.isInContext(fileOut,id2)){
      reg2 = context.getReg(id2);
    }
    else{
    
    reg2 = context.getFreeRegister(fileOut,"");
    right->codeGen(fileOut,reg2, context);
    }
    }
    //fileOut << "move " << reg1 << ", $0" << endl;
    fileOut << "move " << reg1 << ", " << reg2 << endl;
  }
  else if(op == "<" || op == "==" || op == ">" || op == ">=" || op == "<=" || op == "!="  || op == "||" || op == "&&"
          /*=============HAVE WITH OR ALL OTHERS==========*/){
    string first = left->getType();
    string second = right->getType(); 
    if (first == "variable"){
      reg1 = context.getReg(left->getVal());
    }
    else if (first == "intCon"){
      // reg1 = context.getFreeRegister("");
      // context.makeBinding("cond1",reg1,"cond");
      reg1 = destReg;
      right->codeGen(fileOut,reg1,context);
    }else if(first == "func_call")
    {
      reg1 = context.getFreeRegister(fileOut,"");
      context.incrementListCounter();
      uint32_t func = context.getListCounter();
      fileOut << "move $s" << func << ", $ra" << endl;
      left->codeGen(fileOut,reg1, context);
      fileOut << "move $ra, $s" << func << endl;
      fileOut << "move " << reg1 << ", $v0" << endl;
    }
    if (second == "variable"){
      reg2 = context.getReg(right->getVal());
    }
    else if (second == "intCon"){
      // reg2 = context.getFreeRegister("");
      // context.makeBinding("cond2",reg2,"cond");
      reg2 = destReg;
      right->codeGen(fileOut,reg2,context);
    }


    if(op == "<"){
      fileOut <<"slt "<<destReg<<","<<reg1<<","<<reg2 << endl;
    }
    else if(op == ">"){
      fileOut <<"slt "<<destReg<<","<<reg2<<","<<reg1 << endl;
    }
    else if (op.compare("==")==0){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"bne "<<reg1<<","<<reg2<<","<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<L2<<":"<<endl;
    }
    else if(op == ">="){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"blt "<<reg1<<","<<reg2<<","<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<L2<<":"<<endl;
    }
    else if(op == "<="){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"bgt "<<reg1<<","<<reg2<<","<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<L2<<":"<<endl;
    }
    else if(op == "!="){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"beq "<<reg1<<","<<reg2<<","<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<L2<<":"<<endl;
    }
    else if(op == "&&"){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"beq "<<reg1<<","<<"$0"<<","<<L1 <<endl;
      fileOut<<"beq "<<reg2<<","<<"$0"<<","<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<L2<<":"<<endl;
    }
    else if(op == "||"){
      string L1 = context.makeLabel("L");
      string L2 = context.makeLabel("L");
      fileOut<<"bne "<<reg1<<","<<"$0"<<","<<L1 <<endl;
      fileOut<<"bne "<<reg2<<","<<"$0"<<","<<L1 <<endl;
      fileOut<<"nop"<<endl;
      fileOut<<"li "<<destReg<<", 0"<<endl;
      fileOut<<"b "<<L2<<endl;
      fileOut<<"nop"<<endl;
      fileOut<<L1<<":"<<endl;
      fileOut<<"li "<<destReg<<", 1"<<endl;
      fileOut<<L2<<":"<<endl;
    }





  }else if (op == "1")
  {
    fileOut<<"li "<<destReg<<", 1"<<endl;
  }
  else if (op == "0")
  {
    fileOut<<"li "<<destReg<<", 0"<<endl;
  }  
  else if(
    op == "+="  ||
    op == "-="  ||
    op == "%="  ||
    op == "/="  ||
    op == "*="  ||
    op == "^="  ||
    op == "&="  ||
    op == "|="    ){
    string first = left->getType();
    string second = right->getType(); 
    string id = left->getVal();
    if(context.isInContext(fileOut,id)){
      reg1 = context.getReg(id);
    }
    else{
    reg1 = context.getFreeRegister(fileOut,"");
    context.makeBinding(fileOut,id, reg1,"scratch");
    }
    if (first == "variable"){
      reg1 = context.getReg(left->getVal());
    }
    if (second == "variable"){
      reg2 = context.getReg(right->getVal());
    }
    else if (second == "intCon"){
      reg2 = context.getFreeRegister(fileOut,"");
      // context.makeBinding("cond2",reg2,"scratch");
      // reg2 = destReg;
      right->codeGen(fileOut,reg2,context);
    }
    else if (second == "binexp"){
      reg2 = context.getFreeRegister(fileOut,"");
      // context.makeBinding("cond2",reg2,"scratch");
      // reg2 = destReg;
      right->codeGen(fileOut,reg2,context);
    }else if(right->getType()=="func_call"){
      reg2 = context.getFreeRegister(fileOut,"");
      context.incrementListCounter();
      uint32_t func = context.getListCounter();
      fileOut << "move $s" << func << ", $ra" << endl;
      right->codeGen(fileOut,reg2, context);
      fileOut << "move $ra, $s" << func << endl;
      fileOut << "move " << reg2 << ", $v0" << endl;
    }


    if(op == "+="){
      fileOut << "add " << reg1 << ", " << reg1 << ", " << reg2 << endl; /*BACK TO THE CODE GEN WHICH CALLED IT WE PRINT THE LABEL*/
    }
    else if(op == "-="){
      fileOut << "sub " << reg1 << ", " << reg1 << ", " << reg2 << endl; 
    }
    else if(op == "%="){
      fileOut << "div " << reg1 << "," << reg2 <<endl;
      fileOut << "mfhi " << reg1 << endl;
    }
    else if(op == "/="){
      fileOut << "div " << reg1 << "," << reg2 << endl;
      fileOut << "mflo " << reg1 << endl;
    }
    else if(op == "*="){
      fileOut << "mult " << reg1 << "," << reg2 << endl;
      fileOut << "mflo " << reg1 << endl;
    }
    else if(op == "^="){
      fileOut << "xor " << reg1 << "," << reg1 << "," << reg2 << endl; 
    }
    else if(op == "&="){
      fileOut << "and " << reg1 << "," << reg1 << "," << reg2 << endl; 
    }
    else if(op.compare("|=")==0){
      fileOut << "or " << reg1 << "," << reg1 << "," << reg2 << endl; 
    }
  }
  else if((op.compare("++")==0)||(op.compare("--")==0)){
    left->codeGen(fileOut,"", context);
    reg1 = context.getReg(left->getVal());

    if(op.compare("++")==0){
      fileOut << "addiu " << reg1 << ", " << reg1 << ", " << "1" << endl;
    }
    if(op.compare("--")==0){
      fileOut << "subi " << reg1 << ", " << reg1 << ", " << "1" << endl;
    }
  }
  else if    ((op.compare("*")==0) || (op.compare("/")==0) || (op.compare("%")) || 
         (op.compare("+")==0) || (op.compare("-")==0) || (op.compare("<<")==0) ||
         (op.compare(">>")==0) || (op.compare("&")==0) || (op.compare("|")==0) ||
         (op.compare("^")==0)
         ){
    
    string scratch_id1 = context.makeLabel("scratch");
    string scratch_id2 = context.makeLabel("scratch");
    if(left->getType()=="func_call"){
      reg1 = context.getFreeRegister(fileOut,"");
      context.makeBinding(fileOut,scratch_id1, reg1,"scratch");
      context.incrementListCounter();
      uint32_t func = context.getListCounter();
      fileOut << "move $s" << func << ", $ra" << endl;
      left->codeGen(fileOut,reg1, context);
      fileOut << "move $ra, $s" << func << endl;
      fileOut << "move " << reg1 << ", $v0" << endl;
    }else{
    if (context.isInContext(fileOut,left->getVal())){
      reg1 = context.getReg(left->getVal());
    } else {
      reg1 = context.getFreeRegister(fileOut,"");
      context.makeBinding(fileOut,scratch_id1, reg1,"scratch");
      left->codeGen(fileOut,reg1, context);
      }
    }

    if (right){
      if(right->getType()=="func_call"){
      reg2 = context.getFreeRegister(fileOut,"");
      context.makeBinding(fileOut,scratch_id2, reg2,"scratch");
      context.incrementListCounter();
      uint32_t func = context.getListCounter();
      fileOut << "move $s" << func << ", $ra" << endl;
      left->codeGen(fileOut,reg1, context);
      fileOut << "move $ra, $s" << func << endl;
      fileOut << "move " << reg2 << ", $v0" << endl;
    }else{
      if (context.isInContext(fileOut,right->getVal())){
        reg2 = context.getReg(right->getVal());
      } else {
        reg2 = context.getFreeRegister(fileOut,"");
        context.makeBinding(fileOut,scratch_id2, reg2,"scratch");
        right->codeGen(fileOut,reg2, context);
      }
      }
    }
    context.releaseBinding(scratch_id1);
    context.releaseBinding(scratch_id2);

    if (op.compare("*")==0){
      fileOut << "mult " << reg1 << "," << reg2 << endl;
      fileOut << "mflo " << destReg << endl;
    }
    if (op.compare("/")==0){
      fileOut << "div " <<  reg1 << " , " << reg2 << endl;
      fileOut << "mflo " << destReg << endl;
    }
    if (op.compare("%")==0){
      fileOut << "div " <<  reg1 << reg2 << endl;
      fileOut << "mfhi " << destReg << endl;
    }
    if (op.compare("+")==0){
      if (reg2.compare("")!=0){
        fileOut << "add " << destReg << "," << reg1 << "," << reg2 << endl;
      } else {
        fileOut << "add " << destReg << ",$0," << reg1 << endl;
      }
    }
    if (op.compare("-")==0){
      if (reg2.compare("")!=0){
        fileOut << "sub " << destReg << "," << reg1 << "," << reg2 << endl;
      } else {
        fileOut << "sub " << destReg << ",$0," << reg1 << endl;
      }
    }
    if (op.compare("<<")==0){
      fileOut << "sll " << destReg << "," << reg1 << "," << reg2 << endl;
    }
    if (op.compare(">>")==0){
      fileOut << "sra " << destReg << "," << reg1 << "," << reg2 << endl;
    }
    if (op.compare("&")==0){
      fileOut<< "and " << destReg << "," << reg1 << "," << reg2 << endl;
    }
    if (op.compare("|")==0){
      fileOut << "or " << destReg << "," << reg1 << "," << reg2 << endl;
    }
    if (op.compare("^")==0){
      fileOut << "xor " << destReg << "," << reg1 << "," << reg2 << endl;
    }
  }
}


uint32_t BinaryExpression::getSize(Context& context) const{
  if (right && left){
    return left->getSize(context) + right->getSize(context);
  } else {
    if (left){
      return left->getSize(context);
    }
  }
  return 0;
}



void BinaryExpression::setType(const string &_type){
  if (left){
    left->setType(_type);
  }
}
string BinaryExpression::getType() const{
  return "binexp";
}
string BinaryExpression::getVal() const{
  return "";
}