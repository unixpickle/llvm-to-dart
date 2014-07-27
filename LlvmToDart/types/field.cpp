#include "field.hpp"
#include "primitive-field.hpp"
#include "struct-field.hpp"
#include "array-field.hpp"

namespace llvmtodart {

Field * Field::CreateField(Session & s, const std::string & fieldName,
                           Type * fieldType) {
  Field * f = PrimitiveField::CreateWithType(s, fieldName, fieldType);
  if (!f) f = StructField::CreateWithType(s, fieldName, fieldType);
  if (!f) f = ArrayField::CreateWithType(s, fieldName, fieldType);
  return f;
}

Field::Field(Session & session, const std::string & _fieldName)
  : session(session), fieldName(_fieldName) {
}

StringRef Field::GetFieldName() const {
  return StringRef(fieldName);
}

Session & Field::GetSession() const {
  return session;
}

}
