#ifndef __LLVMTODART_FUNCTION_TYPE_HPP__
#define __LLVMTODART_FUNCTION_TYPE_HPP__

#include "type.hpp"

namespace llvmtodart {

class FunctionType : public Type {
public:
  static FunctionType * Create(Session & s, llvm::Type * type);
  
  virtual ~FunctionType();
  
  virtual StringRef GetTypeName() const;
  virtual void PrintInitializer(raw_ostream & stream) const;
  virtual void PrintDeclaration(raw_ostream & stream, StringRef name) const;
  virtual Type * Clone() const;
  virtual uint64_t GetSize() const;
  
private:
  FunctionType(Session &, llvm::FunctionType * t);
  
  llvm::FunctionType * type;
  string typeName;
  
  Type * returnType;
  std::vector<Type *> argumentTypes;
};

}

#endif
