#include "array-field.hpp"
#include "session.hpp"

namespace llvmtodart {

ArrayField * ArrayField::CreateWithType(Session & s,
                                        const std::string & fieldName,
                                        Type * fieldType) {
  if (!fieldType->isArrayTy()) return nullptr;
  Type * containedType = fieldType->getArrayElementType();
  Field * subField = Field::CreateField(s, "namedLoopVar", containedType);
  if (!subField) return nullptr;
  
  return new ArrayField(s, fieldName, fieldType->getArrayNumElements(),
                        subField);
}

ArrayField::ArrayField(Session & s, const std::string & fieldName,
                       uint64_t elements, Field * sub)
  : Field(s, fieldName), elements(elements), subField(sub) {
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
                                     const std::string & indent) const {
  stream << indent << GetFieldName() << " = new ";
  PrintType(stream);
  stream << "();\n";
  
  std::string subIndent(GetSession().GetSettings().GetTab());
  
  stream << indent << "for (int i = 0; i < " << elements << "; i++) {\n";
  subField->PrintDeclaration(stream, indent + subIndent);
  stream << "\n";
  subField->PrintInitialization(stream, indent + subIndent);
  stream << "\n" << indent << subIndent << GetFieldName()
    << ".add(namedLoopVar);\n";
  stream << indent << "}";
}

Field * ArrayField::Clone() const {
  return new ArrayField(GetSession(), GetFieldName(), elements,
                        subField->Clone());
}

}

