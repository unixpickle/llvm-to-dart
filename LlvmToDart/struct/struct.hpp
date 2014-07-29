#ifndef __LLVMTODART_STRUCT_HPP__
#define __LLVMTODART_STRUCT_HPP__

#include "type.hpp"
#include "encodable.hpp"
#include "session-object.hpp"

namespace llvmtodart {

class Session;

class Struct : public Encodable, public SessionObject {
public:
  Struct(Session &, const StructType &);
  Struct(const Struct &);
  ~Struct();
  
  Struct & operator=(const Struct &);
  
  virtual void Print(raw_ostream &) const;
  std::string GetName() const;
  
  unsigned int GetVariableCount() const;
  const Variable & GetVariable(unsigned int i) const;
  
  bool operator==(const Struct &) const;
  bool operator!=(const Struct &) const;
  bool operator>(const Struct &) const;
  bool operator<(const Struct &) const;
  
protected:
  const StructType & typeInfo;
  std::vector<Variable *> Variables;
};

}

#endif
