#ifndef __LLVMTODART_SCALAR_TYPE_HPP__
#define __LLVMTODART_SCALAR_TYPE_HPP__

#include "type.hpp"

namespace llvmtodart {

class ScalarType : public Type {
public:
  static ScalarType * Create(Session & s, llvm::Type * type);
  
  virtual StringRef GetTypeName() const;
  virtual void PrintInitializer(raw_ostream & stream) const;
  virtual Type * Clone() const;
  
private:
  ScalarType(Session & session, StringRef primType, uint64_t vectorCount);
  
  string primType;
  uint64_t vectorCount;
};

}

#endif
