#ifndef __LLVMTODART_FUNCTION_VARIABLE_HPP__
#define __LLVMTODART_FUNCTION_VARIABLE_HPP__

#include "variable.hpp"

namespace llvmtodart {

class FunctionVariable : public Variable {
public:
  static FunctionVariable * CreateWithType(Session & s,
                                           const std::string & name,
                                           Type * type);
  
  FunctionVariable(Session & s, const std::string & name, FunctionType *);
  virtual ~FunctionVariable();
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintInitialization(raw_ostream & stream) const;
  virtual void PrintDeclaration(raw_ostream & stream) const;
  virtual Variable * Clone() const;
  
private:
  FunctionType * type;
  
  Variable * returnVar;
  std::vector<Variable *> argumentVars;
};

}

#endif
