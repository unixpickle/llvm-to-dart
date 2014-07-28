#ifndef __LLVMTODART_STRUCT_VARIABLE_HPP__
#define __LLVMTODART_STRUCT_VARIABLE_HPP__

#include "Variable.hpp"

namespace llvmtodart {

class StructVariable : public Variable {
public:
  static StructVariable * CreateWithType(Session & s,
                                         const std::string & name,
                                         Type * type);
  
  StructVariable(Session & s, const std::string & name,
                 const std::string & structName);
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintInitialization(raw_ostream & stream) const;
  virtual Variable * Clone() const;
  
private:
  std::string structName;
};

}

#endif
