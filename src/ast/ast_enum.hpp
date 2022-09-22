#ifndef ast_enum_hpp
#define ast_enum_hpp

#include "context.hpp"

class Enum: public Expression{
public:
  Enum(const string &_id, Expression* _scope);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  string id, type;
  Expression* scope;
};

class EnumItem: public Expression{
public:
  EnumItem();
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  Expression* exp;
  vector <Expression*> statements;
  string type;
};

#endif