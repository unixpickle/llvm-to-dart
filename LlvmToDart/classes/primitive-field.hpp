#ifndef __LLVMTODART_PRIMITIVE_FIELD_HPP__
#define __LLVMTODART_PRIMITIVE_FIELD_HPP__

#include "field.hpp"

namespace llvmtodart {

class PrimitiveField : public Field {
public:
  static PrimitiveField * CreateWithType(Module & m,
                                         const std::string & fieldName,
                                         Type * fieldType);
  
  PrimitiveField(const std::string & fieldName, const std::string & primType,
                 unsigned long long vectorCount);
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintDeclaration(raw_ostream & stream,
                                const std::string & indent) const;
  virtual void PrintInitialization(raw_ostream & stream,
                                   const std::string & indent) const;
  virtual Field * Clone() const;
  
private:
  std::string primType;
  unsigned long long vectorCount;
};

}

#endif
