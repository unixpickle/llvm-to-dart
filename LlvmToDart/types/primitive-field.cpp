#include "primitive-field.hpp"
#include "session.hpp"
#include <sstream>

namespace llvmtodart {

namespace {

bool IsNumericType(Type * t) {
  return t->isFloatTy() | t->isDoubleTy() | t->isIntegerTy();
}

}

PrimitiveField * PrimitiveField::CreateWithType(Session & s,
                                                const std::string & fieldName,
                                                Type * fieldType) {
  unsigned long long fieldCount = 1;
  if (fieldType->isArrayTy()) {
    if (!IsNumericType(fieldType->getArrayElementType())) return nullptr;
    fieldCount = fieldType->getArrayNumElements();
    fieldType = fieldType->getArrayElementType();
  }
  if (fieldType->isFloatTy()) {
    return new PrimitiveField(s, fieldName, "Float32List", fieldCount);
  } else if (fieldType->isDoubleTy()) {
    return new PrimitiveField(s, fieldName, "Float64List", fieldCount);
  } else if (fieldType->isIntegerTy()) {
    DataLayout layout(s.GetModule().getDataLayout());
    unsigned long long size = layout.getTypeSizeInBits(fieldType);
    if (size == 8 || size == 0x10 || size == 0x20 || size == 0x40) {
      std::stringstream stream("");
      stream << "Uint" << size << "List";
      return new PrimitiveField(s, fieldName, stream.str(), fieldCount);
    }
    
    if (size % 8) size += 8;
    return new PrimitiveField(s, fieldName, "Uint8List",
                              fieldCount * (size / 8));
  }
  return nullptr;
}

PrimitiveField::PrimitiveField(Session & s, const std::string & fieldName,
                               const std::string & _prim,
                               unsigned long long _vectorCount)
  : Field(s, fieldName), primType(_prim), vectorCount(_vectorCount) {
}

void PrimitiveField::PrintType(raw_ostream & stream) const {
  stream << primType;
}

void PrimitiveField::PrintDeclaration(raw_ostream & stream,
                                      const std::string & indent) const {
  stream << indent << primType << " " << GetFieldName() << ";";
}

void PrimitiveField::PrintInitialization(raw_ostream & stream,
                                         const std::string & indent) const {
  stream << indent << GetFieldName() << " = new " << primType << "("
    << vectorCount << ");";
}

Field * PrimitiveField::Clone() const {
  return new PrimitiveField(GetSession(), GetFieldName(), primType, vectorCount);
}

}
