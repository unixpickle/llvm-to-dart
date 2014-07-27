#include "field.hpp"

namespace llvmtodart {

Field::Field(const std::string & _fieldName) : fieldName(_fieldName) {
}

StringRef Field::GetFieldName() const {
  return StringRef(fieldName);
}

}
