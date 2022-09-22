#ifndef ast_whileloop_hpp
#define ast_whileloop_hpp

#include "context.hpp"

class WhileLoop: public Expression{
public:
  WhileLoop(Expression* _conditions, Expression* _statement);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  Expression* statement;
  Expression* conditions;
};

#endif