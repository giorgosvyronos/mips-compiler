#ifndef ast_scope_hpp
#define ast_scope_hpp

#include "context.hpp"

class Scope: public Expression{
public:
  Scope();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  vector<Expression*> statements;
};

#endif