#include "struct-type.hpp"
#include "session.hpp"

namespace llvmtodart {

StructType * StructType::Create(Session & s, llvm::Type * type) {
  if (!type->isStructTy()) return nullptr;
  string newName(s.GetSettings().EscapeSymbol(type->getStructName()));
  return new StructType(s, newName);
}

StringRef StructType::GetTypeName() const {
  return structName;
}

void StructType::PrintInitializer(raw_ostream & stream) const {
  stream << "new " << structName << "()";
}

Type * StructType::Clone() const {
  return new StructType(GetSession(), structName);
}

bool StructType::IsStructure() const {
  return true;
}

StructType::StructType(Session & s, const string & _structName)
  : Type(s), structName(_structName) {
}

}
