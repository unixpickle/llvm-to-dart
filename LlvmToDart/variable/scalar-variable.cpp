#include "scalar-variable.hpp"
#include "session.hpp"
#include <sstream>

namespace llvmtodart {

namespace {

bool IsNumericType(Type * t) {
  return t->isFloatTy() | t->isDoubleTy() | t->isIntegerTy();
}

}

ScalarVariable * ScalarVariable::CreateWithType(Session & s,
                                                const std::string & name,
                                                Type * type) {
  unsigned long long count = 1;
  // scalar array
  if (type->isArrayTy()) {
    if (!IsNumericType(type->getArrayElementType())) return nullptr;
    count = type->getArrayNumElements();
    type = type->getArrayElementType();
  }
  
  if (type->isFloatTy()) {
    return new ScalarVariable(s, name, "Float32List", count);
  } else if (type->isDoubleTy()) {
    return new ScalarVariable(s, name, "Float64List", count);
  } else if (type->isIntegerTy()) {
    DataLayout layout(s.GetModule().getDataLayout());
    unsigned long long size = layout.getTypeSizeInBits(type);
    if (size == 8 || size == 0x10 || size == 0x20 || size == 0x40) {
      std::stringstream stream("");
      stream << "Uint" << size << "List";
      return new ScalarVariable(s, name, stream.str(), count);
    }
    
    if (size % 8) size += 8;
    return new ScalarVariable(s, name, "Uint8List", count * (size / 8));
  }
  
  return nullptr;
}

ScalarVariable::ScalarVariable(Session & s, const std::string & name,
                               const std::string & _prim,
                               unsigned long long _vectorCount)
  : Variable(s, name), primType(_prim), vectorCount(_vectorCount) {
}

void ScalarVariable::PrintType(raw_ostream & stream) const {
  stream << primType;
}

void ScalarVariable::PrintInitialization(raw_ostream & stream) const {
  stream << GetSession().GetIndentation() << GetName() << " = new " << primType
    << "(" << vectorCount << ");";
}

Variable * ScalarVariable::Clone() const {
  return new ScalarVariable(GetSession(), GetName(), primType, vectorCount);
}

}
