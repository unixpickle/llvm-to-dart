#include "struct-field.hpp"

namespace llvmtodart {

StructField * StructField::CreateWithType(Session & s,
                                          const std::string & fieldName,
                                          Type * fieldType) {
  if (!fieldType->isStructTy()) return nullptr;
  return new StructField(s, fieldName, fieldType->getStructName());
}

StructField::StructField(Session & s, const std::string & _fieldName,
                         const std::string & _structName)
  : Field(s, _fieldName), structName(_structName) {
}

void StructField::PrintType(raw_ostream & stream) const {
  stream << structName;
}

void StructField::PrintDeclaration(raw_ostream & stream,
                                   const std::string & indent) const {
  stream << indent << structName << " " << GetFieldName() << ";";
}

void StructField::PrintInitialization(raw_ostream & stream,
                                      const std::string & indent) const {
  stream << indent << GetFieldName() << " = new " << structName << "();";
}

Field * StructField::Clone() const {
  return new StructField(GetSession(), GetFieldName(), structName);
}

}
