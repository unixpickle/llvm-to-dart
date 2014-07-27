#include "struct-field.hpp"

namespace llvmtodart {

StructField * StructField::CreateWithType(Module & m,
                                          const std::string & fieldName,
                                          Type * fieldType) {
  if (!fieldType->isStructTy()) return nullptr;
  return new StructField(fieldName, fieldType->getStructName());
}

StructField::StructField(const std::string & _fieldName,
                         const std::string & _structName)
  : Field(_fieldName), structName(_structName) {
}

void StructField::PrintType(raw_ostream & stream) const {
  stream << structName;
}

void StructField::PrintDeclaration(raw_ostream & stream,
                                   const std::string & indent) const {
  stream << indent << structName << " " << GetFieldName() << ";";
}

void StructField::PrintInitialization(raw_ostream & stream,
                                      const std::string & indent,
                                      const std::string & subIndent) const {
  stream << indent << GetFieldName() << " = new " << structName << "();";
}

Field * StructField::Clone() const {
  return new StructField(GetFieldName(), structName);
}

}
