#ifndef ast_array_hpp
#define ast_array_hpp

#include "context.hpp"

class ArrayDec: public Expression{
public:
  ArrayDec(const uint32_t &_size, const string& _id, const string& _type);
  // Array(Expression* _id, const uint32_t& _counter);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  // string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  uint32_t size;
  string id;
  string type;
  //Expression* counter;
};

class ArrayAcc: public Expression{
public:
  ArrayAcc(const uint32_t &_index, const string& _id);
  // Array(Expression* _id, const uint32_t& _counter);
  void add(Expression* _exp);
  uint32_t getSize(Context& context) const;
  // string print(const bool& complete) const;
  void setType(const string &_type);
  string getType() const;
  string getVal() const;
  void codeGen(ostream& fileOut, const string& destReg, Context& context);
private:
  uint32_t index;
  string id;
  //Expression* counter;
};


#endif
