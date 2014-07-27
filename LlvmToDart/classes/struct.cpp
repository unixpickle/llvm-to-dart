#include "struct.hpp"

namespace llvmtodart {

Struct::Struct(const DartConfiguration & a, const StructType & b) : dart(a), typeInfo(b) {
}

std::string Struct::GetSymbolName() const {
  return dart.EscapeSymbol(typeInfo.getName());
}

void Struct::Print(raw_ostream & stream) const {
  stream << "class " << GetSymbolName() << " {\n";
  for (auto i = 0; i < GetFieldCount(); i++) {
    Type * fieldType = typeInfo.getElementType(i);
    if (fieldType->isStructTy()) {
      StringRef name = fieldType->getStructName();
      stream << dart.GetTab() << dart.EscapeSymbol(name) << " "
        << dart.FieldName(i) << ";\n";
    } else if (typeInfo.isSized()) {
      stream << dart.GetTab() << "ByteData " << dart.FieldName(i) << ";\n";
    }
  }
  stream << "}";
}

unsigned int Struct::GetFieldCount() const {
  return typeInfo.getNumElements();
}

std::string Struct::GetFieldName(unsigned int i) const {
  return dart.FieldName(i);
}

bool Struct::operator==(const Struct & s) const {
  return &typeInfo == &s.typeInfo;
}

bool Struct::operator!=(const Struct & s) const {
  return !((*this) == s);
}

bool Struct::operator>(const Struct & s) const {
  return &typeInfo > &s.typeInfo;
}

bool Struct::operator<(const Struct & s) const {
  return &typeInfo < &s.typeInfo;
}

}
