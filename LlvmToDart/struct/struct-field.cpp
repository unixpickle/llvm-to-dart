#include "struct-field.hpp"
#include "session.hpp"

namespace llvmtodart {

StructField::StructField(Type * t, const string & n, uint64_t o)
  : type(t), fieldName(n), offset(o) {
}

StructField::~StructField() {
  delete type;
}

void StructField::PrintDeclaration(raw_ostream & stream) const {
  type->PrintDeclaration(stream, fieldName);
}

uint64_t StructField::GetSize() const {
  // TODO: calculate the size using DataLayout etc.
  return 0;
}

void StructField::PrintDefinition(raw_ostream & stream) const {
  stream << fieldName << " = ";
  type->PrintInitializer(stream);
  stream << ";";
  if (type->IsStructure()) {
    stream << "\n" << type->GetSession().GetIndentation() << fieldName
      << ".ownerObject = this;\n" << type->GetSession().GetIndentation()
      << fieldName << ".ownerOffset = " << offset << ";";
  }
}

}
