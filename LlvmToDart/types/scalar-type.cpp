#include "scalar-type.hpp"
#include "session.hpp"
#include <sstream>

namespace llvmtodart {

namespace {

bool IsNumericType(llvm::Type * t) {
  return t->isFloatTy() | t->isDoubleTy() | t->isIntegerTy();
}

}

ScalarType * ScalarType::Create(Session & s, llvm::Type * type) {
  uint64_t count = 1;
  // scalar array
  if (type->isArrayTy()) {
    if (!IsNumericType(type->getArrayElementType())) return nullptr;
    count = type->getArrayNumElements();
    type = type->getArrayElementType();
  }
  
  if (type->isFloatTy()) {
    return new ScalarType(s, "Float32List", count);
  } else if (type->isDoubleTy()) {
    return new ScalarType(s, "Float64List", count);
  } else if (type->isIntegerTy()) {
    DataLayout layout(s.GetModule().getDataLayout());
    unsigned long long size = layout.getTypeSizeInBits(type);
    if (size == 8 || size == 0x10 || size == 0x20 || size == 0x40) {
      std::stringstream stream("");
      stream << "Uint" << size << "List";
      return new ScalarType(s, stream.str(), count);
    }
    
    if (size % 8) size += 8;
    return new ScalarType(s, "Uint8List", count * (size / 8));
  }
  
  return nullptr;
}

StringRef ScalarType::GetTypeName() const {
  return primType;
}

void ScalarType::PrintInitializer(raw_ostream & stream) const {
  stream << "new " << GetTypeName() << "(" << vectorCount << ")";
}

Type * ScalarType::Clone() const {
  return new ScalarType(GetSession(), primType, vectorCount);
}

}
