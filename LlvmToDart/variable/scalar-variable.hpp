#ifndef __LLVMTODART_SCALAR_VARIABLE_HPP__
#define __LLVMTODART_SCALAR_VARIABLE_HPP__

#include "variable.hpp"

namespace llvmtodart {

class ScalarVariable : public Variable {
public:
  static ScalarVariable * CreateWithType(Session & s,
                                         const std::string & name,
                                         Type * type);
  
  ScalarVariable(Session & session, const std::string & name,
                 const std::string & primType,
                 unsigned long long vectorCount);
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintInitialization(raw_ostream & stream) const;
  virtual Variable * Clone() const;
  
private:
  std::string primType;
  unsigned long long vectorCount;
};

}

#endif
