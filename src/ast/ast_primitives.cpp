#include "ast_primitives.hpp"

#include <string>
#include <iostream>

using namespace std;

  NumberInt::NumberInt(const int &_val): val(_val){}
  
  void NumberInt::add(Expression* _exp){}
  uint32_t NumberInt::getSize(Context& context) const{
    return 4;
  }
  string NumberInt::getType() const{
    return "intCon";
  }
  void NumberInt::setType(const string &_type){}
  string NumberInt::getVal() const{
    ostringstream strs;
    strs << val;
    return strs.str();
  }
  // void NumberInt::codeGen(const string& destReg, Context& context){
  //   fileOut<<"\t"<<"li "<<destReg<<","<<to_string(val)
  //   <<"\t #Value to register "<<to_string(val)
  //   <<endl;
  // }
  


  void NumberInt::codeGen(ostream& fileOut,const string& destReg, Context& context){
      fileOut << "li " << destReg << "," << to_string(val) << endl;
  }