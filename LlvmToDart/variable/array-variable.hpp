#ifndef __LLVMTODART_ARRAY_VARIABLE_HPP__
#define __LLVMTODART_ARRAY_VARIABLE_HPP__

#include "variable.hpp"

namespace llvmtodart {

class ArrayVariable : public Variable {
public:
  static ArrayVariable * CreateWithType(Session & s,
                                        const std::string & name, Type * type);
  
  ArrayVariable(Session & s, const std::string & name, uint64_t elements,
                Variable * sub);
  virtual ~ArrayVariable();
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintInitialization(raw_ostream & stream) const;
  virtual Variable * Clone() const;
  
private:
  uint64_t elements;
  Variable * subVariable;
};

}

#endif
