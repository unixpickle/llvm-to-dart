#include "array-type.hpp"
#include "indent-scope.hpp"
#include "session.hpp"
#include <sstream>

namespace llvmtodart {

ArrayType * ArrayType::Create(Session & s, llvm::Type * type) {
  if (!type->isArrayTy()) return nullptr;
  Type * contained = Type::Create(s, type->getArrayElementType());
  if (!contained) return nullptr;
  return new ArrayType(s, type->getArrayNumElements(), contained);
}

ArrayType::~ArrayType() {
  delete elementType;
}

StringRef ArrayType::GetTypeName() const {
  return typeName;
}

void ArrayType::PrintInitializer(raw_ostream & stream) const {
  auto suffix = GetSession().GetIndentation().size();
  
  stream << "(() {\n";
  
  {
    IndentScope indent(GetSession());
    stream << indent.GetIndentation() << GetTypeName() << " result" << suffix
      << " = [];\n" << indent.GetIndentation() << "for (int i = 0; i < "
      << elements << "; i++) {\n";
    
    {
      IndentScope inner(GetSession());
      stream << inner.GetIndentation() << "result" << suffix << "[i] = ";
      elementType->PrintInitializer(stream);
      stream << ";\n";
    }
    
    stream << indent.GetIndentation() << "}\n" << indent.GetIndentation()
      << "return result" << suffix << ";\n";
  }
  
  stream << GetSession().GetIndentation() << "})()";
}

Type * ArrayType::Clone() const {
  return new ArrayType(GetSession(), elements, elementType->Clone());
}

uint64_t ArrayType::GetSize() const {
  return elementType->GetSize() * elements;
}

ArrayType::ArrayType(Session & s, uint64_t elements, Type * sub)
  : Type(s), elements(elements), elementType(sub),
    typeName("List<" + elementType->GetTypeName().str() + ">") {
}

}
