#include "field.hpp"
#include "primitive-field.hpp"
#include "struct-field.hpp"
#include "array-field.hpp"

namespace llvmtodart {

Field * Field::CreateField(Module & m, const std::string & fieldName,
                           Type * fieldType) {
  Field * f = PrimitiveField::CreateWithType(m, fieldName, fieldType);
  if (!f) f = StructField::CreateWithType(m, fieldName, fieldType);
  if (!f) f = ArrayField::CreateWithType(m, fieldName, fieldType);
  return f;
}

Field::Field(const std::string & _fieldName) : fieldName(_fieldName) {
}

StringRef Field::GetFieldName() const {
  return StringRef(fieldName);
}

}
