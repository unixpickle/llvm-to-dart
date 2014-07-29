#ifndef __LLVMTODART_ARRAY_TYPE_HPP__
#define __LLVMTODART_ARRAY_TYPE_HPP__

#include "type.hpp"

namespace llvmtodart {

class ArrayType : public Type {
public:
  static ArrayType * Create(Session & s, llvm::Type * type);
  
  virtual ~ArrayType();
  
  virtual StringRef GetTypeName() const;
  virtual void PrintInitializer(raw_ostream & stream) const;
  virtual Type * Clone() const;
  virtual uint64_t GetSize() const;
  
private:
  ArrayType(Session & s, uint64_t elements, Type * sub);
  
  uint64_t elements;
  Type * elementType;
  string typeName;
};

}

#endif
