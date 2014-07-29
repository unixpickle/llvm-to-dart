#include "function-type.hpp"
#include "session.hpp"

namespace llvmtodart {

FunctionType * FunctionType::Create(Session & s, llvm::Type * type) {
  if (type->isPointerTy()) {
    if (type->getPointerElementType()->isFunctionTy()) {
      type = type->getPointerElementType();
    }
  }
  if (!type->isFunctionTy()) return nullptr;
  
  return new FunctionType(s, static_cast<llvm::FunctionType *>(type));
}

StringRef FunctionType::GetTypeName() const {
  return typeName;
}

void FunctionType::PrintInitializer(raw_ostream & stream) const {
  stream << "null";
}

Type * FunctionType::Clone() const {
  return new FunctionType(GetSession(), type);
}

uint64_t FunctionType::GetSize() const {
  DataLayout layout(GetSession().GetModule().getDataLayout());
  return layout.getPointerSize();
}

FunctionType::FunctionType(Session & s, llvm::FunctionType * t)
  : Type(s), type(t), typeName("Function") {
}

}
