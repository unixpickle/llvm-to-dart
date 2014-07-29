#include "struct-type.hpp"
#include "session.hpp"

namespace llvmtodart {

StructType * StructType::Create(Session & s, llvm::Type * type) {
  if (!type->isStructTy()) return nullptr;
  
  llvm::StructType * casted = static_cast<llvm::StructType *>(type);
  DataLayout dLayout(s.GetModule().getDataLayout());
  uint64_t structSize = dLayout.getStructLayout(casted)->getSizeInBytes();
  
  string newName(s.GetSettings().EscapeSymbol(type->getStructName()));
  return new StructType(s, newName, structSize);
}

StringRef StructType::GetTypeName() const {
  return structName;
}

void StructType::PrintInitializer(raw_ostream & stream) const {
  stream << "new " << structName << "()";
}

Type * StructType::Clone() const {
  return new StructType(GetSession(), structName, size);
}

uint64_t StructType::GetSize() const {
  return size;
}

bool StructType::IsStructure() const {
  return true;
}

StructType::StructType(Session & s, const string & _structName, uint64_t sz)
  : Type(s), structName(_structName), size(sz) {
}

}
