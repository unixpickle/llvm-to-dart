#include "struct-field.hpp"
#include "session.hpp"

namespace llvmtodart {

StructField::StructField(Type * t, unsigned int idx, uint64_t o)
  : type(t), index(idx), offset(o),
    fieldName(t->GetSession().GetSettings().VariableName(index)) {
}

StructField::~StructField() {
  delete type;
}

void StructField::PrintDeclaration(raw_ostream & stream) const {
  type->PrintDeclaration(stream, fieldName);
}

uint64_t StructField::GetOffset() const {
  return offset;
}

Type * StructField::GetType() const {
  return type;
}

StringRef StructField::GetFieldName() const {
  return fieldName;
}

unsigned int StructField::GetIndex() const {
  return index;
}

void StructField::PrintDefinition(raw_ostream & stream) const {
  stream << fieldName << " = ";
  type->PrintInitializer(stream);
  stream << ";";
  if (type->IsStructure()) {
    stream << "\n" << type->GetSession().GetIndentation() << fieldName
      << ".parentObject = this;\n" << type->GetSession().GetIndentation()
      << fieldName << ".parentOffset = " << offset << ";";
  }
}

}
