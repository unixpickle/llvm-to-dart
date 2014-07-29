#ifndef __LLVMTODART_STRUCT_TYPE_HPP__
#define __LLVMTODART_STRUCT_TYPE_HPP__

#include "type.hpp"

namespace llvmtodart {

class StructType : public Type {
public:
  static StructType * Create(Session & s, llvm::Type * type);
  
  virtual StringRef GetTypeName() const;
  virtual void PrintInitializer(raw_ostream & stream) const;
  virtual Type * Clone() const;
  virtual uint64_t GetSize() const;
  virtual bool IsStructure() const;
  
private:
  StructType(Session &, const string & structName, uint64_t size);
  
  string structName;
  uint64_t size;
};

}

#endif
