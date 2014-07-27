#include "array-field.hpp"

namespace llvmtodart {

ArrayField * ArrayField::CreateWithType(Module & m,
                                        const std::string & fieldName,
                                        Type * fieldType) {
  if (!fieldType->isArrayTy()) return nullptr;
  Type * containedType = fieldType->getArrayElementType();
  Field * subField = Field::CreateField(m, "namedLoopVar", containedType);
  if (!subField) return nullptr;
  
  return new ArrayField(fieldName, fieldType->getArrayNumElements(),
                        subField);
}

ArrayField::ArrayField(const std::string & fieldName, uint64_t elements,
                       Field * sub)
  : Field(fieldName), elements(elements), subField(sub) {
}

ArrayField::~ArrayField() {
  delete subField;
}

void ArrayField::PrintType(raw_ostream & stream) const {
  stream << "List<";
  subField->PrintType(stream);
  stream << ">";
}

void ArrayField::PrintDeclaration(raw_ostream & stream,
                                  const std::string & indent) const {
  stream << indent;
  PrintType(stream);
  stream << " " << GetFieldName() << ";";
}

void ArrayField::PrintInitialization(raw_ostream & stream,
                                     const std::string & indent,
                                     const std::string & subIndent) const {
  stream << indent << GetFieldName() << " = new ";
  PrintType(stream);
  stream << "();\n";
  
  stream << indent << "for (int i = 0; i < " << elements << "; i++) {\n";
  subField->PrintDeclaration(stream, indent + subIndent);
  stream << "\n";
  subField->PrintInitialization(stream, indent + subIndent, subIndent);
  stream << "\n" << indent << subIndent << GetFieldName()
    << ".add(namedLoopVar);\n";
  stream << indent << "}";
}

Field * ArrayField::Clone() const {
  return new ArrayField(GetFieldName(), elements, subField->Clone());
}

}

