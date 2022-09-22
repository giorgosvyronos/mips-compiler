#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include "context.hpp"


class NumberInt: public Expression{
public:
  NumberInt(const int &_val);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut,const string& destReg, Context& context);
private:
  int val;
};
#endif