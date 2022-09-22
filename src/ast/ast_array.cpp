#include "ast_array.hpp"

ArrayAcc::ArrayAcc(const uint32_t &_index, const string& _id){
  index = _index;
  id = _id;
}
void ArrayAcc::add(Expression* _exp){}
uint32_t ArrayAcc::getSize(Context& context) const{
  return 1;
}
void ArrayAcc::setType(const string &_type){
}
string ArrayAcc::getType() const{
  return "array";
}
string ArrayAcc::getVal() const {
  return id+"_"+to_string(index);
}
void ArrayAcc::codeGen(ostream& fileOut, const string& destReg, Context& context){
}



ArrayDec::ArrayDec(const uint32_t &_size, const string& _id, const string& _type){
  type = _type;
  id = _id;
  size = _size;
}
void ArrayDec::add(Expression* _exp){}
uint32_t ArrayDec::getSize(Context& context) const{
  return size;
}
void ArrayDec::setType(const string &_type){
  type =_type;
}
string ArrayDec::getType() const{
  return "array";
}
string ArrayDec::getVal() const {
  return id;
}
void ArrayDec::codeGen(ostream& fileOut, const string& destReg, Context& context){
  for(uint32_t i=0; i<size; i++){
    string reg1 = context.getFreeRegister(fileOut,"");
    string ident = id+"_"+to_string(i);
    context.makeBinding(fileOut, ident, reg1, "scratch");
  }
}




//   if(!(context.isInContext(id))){
//     //This means that what the compiler sees is a DECLARATION
//     if (   (type.compare("char")==0)          || (type.compare("unsigned char")==0)
//         || (type.compare("signed char")==0)   || (type.compare("int")==0)
//         || (type.compare("unsigned int")==0)        || (type.compare("long")==0)
//         || (type.compare("unsigned long")==0)      || (type.compare("short")==0)
//         || (type.compare("unsigned short")==0) || (type.compare("double")==0)
//         || (type.compare("float")==0)
//       ){
//         string reg1 = context.getFreeRegister("");
//         uint32_t fp = context.getFramePointer();
//         cout<<"\t"<<"move $t9, $0"<<endl;
//         cout<<"\t"<<"addu $t9,$t9,"<<to_string(fp)<<endl;
//         cout<<"\t"<<"addu $t9,$t9,$fp"<<endl;
//         cout<<"\t"<<"move "<<reg1<<","<<"$t9"<<"\t#Array binding"<<endl;
//         context.makeBinding(id, reg1,"array");
//         context.setFramePointer(fp + 4*(size+2));
//         if (size!=-1){
//           for (size_t i = 1; i<=size; i++){
//             cout<<"\t"<<"sw $0,"<<i*4<<"("<<reg1<<")"<<endl;
//           }
//         }
//       }
//     } else {
//       if (destReg.compare("s_a_v_e")==0){
//         string array_reg = context.getReg(id);
//         string fp = context.getVarAddress(id);
//         string scratch_reg = context.getFreeRegister("");
//         string scratch = context.makeLabel("scratch");
//         context.makeBinding(scratch, scratch_reg, "scratch");
//         if(counter){
//           counter->codeGen(scratch_reg, context);
//         }
//         cout<<"\t"<<"move $t9, $0"<<endl;
//         cout<<"\t"<<"addu "<<scratch_reg<<","<<scratch_reg<<",1"<<endl;
//         cout<<"\t"<<"li $t9, 4"<<endl;
//         cout<<"\t"<<"mult "<<scratch_reg<<",$t9"<<endl;
//         cout<<"\t"<<"mflo "<<scratch_reg<<endl;
//         cout<<"\t"<<"lw $t9,"<<fp<<"($fp)"<<endl;
//         cout<<"\t"<<"addu "<<scratch_reg<<","<<scratch_reg<<",$t9"<<endl;
//         cout<<"\t"<<"sw "<<array_reg<<",0("<<scratch_reg<<")"<<endl;
//         cout<<"\t"<<"move $t9, $0"<<endl;
//         context.releaseBinding(scratch);
//         return;
//       }
//     if (destReg.compare("")!=0){

//       string array_reg = context.getReg(id);
//       string fp = context.getVarAddress(id);
//       string scratch_reg = context.getFreeRegister("");
//       string scratch = context.makeLabel("scratch");
//       context.makeBinding(scratch, scratch_reg, "scratch");
//       if(counter){
//         counter->codeGen(scratch_reg, context);
//       }
//       cout<<"\t"<<"move $t9, $0"<<endl;
//       cout<<"\t"<<"addu "<<scratch_reg<<","<<scratch_reg<<",1"<<endl;
//       cout<<"\t"<<"li $t9, 4"<<endl;
//       cout<<"\t"<<"mult "<<scratch_reg<<",$t9"<<endl;
//       cout<<"\t"<<"mflo "<<scratch_reg<<endl;
//       cout<<"\t"<<"lw $t9,"<<fp<<"($fp)"<<endl;
//       cout<<"\t"<<"addu "<<scratch_reg<<","<<scratch_reg<<",$t9"<<endl;
//       cout<<"\t"<<"lw "<<destReg<<",0("<<scratch_reg<<")"<<endl;
//       cout<<"\t"<<"move $t9, $0"<<endl;
//       context.releaseBinding(scratch);
//     }
//   }
// }
