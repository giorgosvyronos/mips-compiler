#ifndef ast_argument_hpp
#define ast_argument_hpp

#include "context.hpp"

class Argument : public Expression {
public:
  Argument(Expression* _var);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  Expression* var;
  string type;
};

class ArgumentList: public Expression{
public:
  ArgumentList();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  vector<Expression*> arguments;
};

#endif