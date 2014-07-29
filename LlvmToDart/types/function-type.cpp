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

FunctionType::~FunctionType() {
  if (returnType) delete returnType;
  for (auto i = 0; i < argumentTypes.size(); i++) {
    delete argumentTypes[i];
  }
}

StringRef FunctionType::GetTypeName() const {
  return typeName;
}

void FunctionType::PrintInitializer(raw_ostream & stream) const {
  stream << "null";
}

void FunctionType::PrintDeclaration(raw_ostream & stream,
                                    StringRef name) const {
  stream << GetSession().GetIndentation() << returnType->GetTypeName()
    << " " << name << "(";
  for (auto i = 0; i < argumentTypes.size(); i++) {
    stream << argumentTypes[i]->GetTypeName();
    if (i + 1 < argumentTypes.size()) {
      stream << ", ";
    }
  }
  stream << ");";
}

Type * FunctionType::Clone() const {
  return new FunctionType(GetSession(), type);
}


FunctionType::FunctionType(Session & s, llvm::FunctionType * t)
  : Type(s), type(t), typeName("Function") {
  returnType = Type::Create(s, t->getReturnType());
  for (unsigned int i = 0; i < t->getFunctionNumParams(); i++) {
    llvm::Type * argType = t->getFunctionParamType(i);
    Type * arg = Type::Create(s, argType);
    if (!arg) continue;
    argumentTypes.push_back(arg);
  }
}

}
