#include "primitive-field.hpp"

namespace llvmtodart {

PrimitiveField * PrimitiveField::CreateWithType(Module & m,
                                              const std::string & fieldName,
                                              Type * fieldType) {
  if (fieldType->isFloatTy()) {
    return new PrimitiveField(fieldName, "Float32List", 1);
  } else if (fieldType->isDoubleTy()) {
    return new PrimitiveField(fieldName, "Float64List", 1);
  } else if (fieldType->isPrimitiveType()) {
    DataLayout layout(m.getDataLayout());
    unsigned long long size = layout.getTypeSizeInBits(fieldType);
    if (size % 8) size += 8;
    return new PrimitiveField(fieldName, "Uint8List", size / 8);
  }
  return nullptr;
}

PrimitiveField::PrimitiveField(const std::string & fieldName,
                               const std::string & _prim,
                               unsigned long long _vectorCount)
  : Field(fieldName), primType(_prim), vectorCount(_vectorCount) {
}

void PrimitiveField::PrintType(raw_ostream & stream) const {
  stream << primType;
}

void PrimitiveField::PrintDeclaration(raw_ostream & stream,
                                      const std::string & indent) const {
  stream << indent << primType << " " << GetFieldName() << ";";
}

void PrimitiveField::PrintInitialization(raw_ostream & stream,
                                         const std::string & indent,
                                         const std::string & subIndent) const {
  stream << indent << GetFieldName() << " = new " << primType << "("
    << vectorCount << ");";
}

Field * PrimitiveField::Clone() const {
  return new PrimitiveField(GetFieldName(), primType, vectorCount);
}

}
