#ifndef context_hpp
 #define context_hpp

 #include "var.hpp"
 #include "reg.hpp"
 #include <map>
 #include <string>
 #include <iostream>
 #include <fstream>
 #include <vector>
 #include <cstdint>
 #include <stack>
 #include <sstream>
 #include <algorithm>


 using namespace std; 
 //Base class, from which others inherit

 class Context;


 class Expression {
 public:
   virtual ~Expression(){}
    virtual void add(Expression* _exp)= 0;
    virtual string getType() const = 0;
    virtual void setType(const string &_type) = 0;
    virtual string getVal() const = 0;
    virtual uint32_t getSize(Context& context) const = 0;
    virtual void codeGen(ostream& os,const string& destReg, Context& context) = 0;
 };

 /*
 |Register | Assembly name | Comment |
 |r0       | $zero         | Always 0 |
 |r1       | $at           | Reserved for assembler |
 |r2-r3    | $v0-$v1       | Stores result |
 |r4-r7    | $a0-$a3       | Stores arguments |
 |r8-r15   | $t0-$t7       | Temporaries, not saved |
 |r16-r23  | $s0-$s7       | Contents saved for later |
 |r24-r25  | $t8-$t9       | More temporaries not saved |
 |r26-r27  | $k0-$k1       | Reserved by OS |
 |r28      | $gp           | Global pointer |
 |r29      | $sp           | Stack pointer |
 |r30      | $fp           | Frame pointer |
 |r31      | $ra           | Return address |
 */


 class Context{
 public:
   Context();


   //REGISTER allocation methods
   string getFreeRegister(ostream& fileOut, const string& parameter_flag);
   bool isInContext(ostream& fileOut, const string& var_id);
   void makeBinding(ostream& fileOut, const string& var_id, const string& reg_id,const string& type);
   void updateBinding(ostream& fileOut, const string& var_id,const string& type);
   void releaseBinding(const string& var_id);
   string getReg(const string& var_id);
   void saveVariable(ostream& fileOut, const string& var_id,const bool& erase);
   void loadVariable(ostream& fileOut, const string& var_id, const string& reg_id,const bool& erase);
   string getVarAddress(const string& var_id);
   void setVarAddress(const string& var_id,const string& fp);
   string getVarType(const string& var_id);

   //STACK operations
   void allocateStack(ostream& fileOut, const int32_t& val);
   void deallocateStack(ostream& fileOut, const int32_t& val);
   void loadCurrentVariables(ostream& fileOut);
   void saveCurrentVariables(ostream& fileOut);
   void loadLocalVariables(ostream& fileOut);
   int32_t getStackPointer();
   uint32_t getFramePointer();
   void saveGlobalExpression(Expression* _exp);
   void loadGlobalExpression(vector<Expression*>& v);

   //INCREMENT and DECREMENT
   void incrementScopeCounter();
   void decrementScopeCounter();
   void incrementFunctionCounter();
   void decrementFunctionCounter();
   void incrementIfCounter();
   void decrementIfCounter();
   void incrementLoopCounter();
   void decrementLoopCounter();
   void incrementUpdateCounter();
   void decrementUpdateCounter();
   void incrementListCounter();
   void decrementListCounter();
   void incrementCaseCounter();
   void decrementCaseCounter();
   void incrementEnumCounter();
   void decrementEnumCounter();
   //GETTERS
   uint32_t setFramePointer(const uint32_t& fp);
   uint32_t getListCounter();
   uint32_t getFunctionCounter();
   uint32_t getIfCounter();
   uint32_t getLoopCounter();
   uint32_t getUpdateCounter();
   uint32_t getCaseCounter();
   uint32_t getEnumCounter();
   uint32_t getSize(const string& _id);
   string makeLabel(string base);

   //CLEARING
   void clearContext();
   void clearScopeContext(ostream& fileOut);
 private:
   map<string, string> bindings;
   vector<Var> variables;
   vector<Reg> registers;
   vector<Expression*> global;
   int32_t stack_pointer;
   uint32_t frame_pointer;
   uint32_t label_counter;
   uint32_t function_counter;
   uint32_t scope_counter;
   uint32_t if_counter;
   uint32_t loop_counter;
   uint32_t case_counter;
   uint32_t enum_counter;
   uint32_t list_counter;
   uint32_t update_counter;
 };

 #endif