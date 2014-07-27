#include "struct.hpp"

namespace llvmtodart {

Struct::Struct(Module & m, const Settings & a, const StructType & b)
  : dart(a), typeInfo(b) {
  for (unsigned int i = 0; i < typeInfo.getNumElements(); i++) {
    Type * fieldType = typeInfo.getElementType(i);
    std::string fieldName(dart.FieldName(i));
    
    Field * f = Field::CreateField(m, fieldName, fieldType);
    if (f) fields.push_back(f);
  }
}

Struct::Struct(const Struct & s) : dart(s.dart), typeInfo(s.typeInfo) {
  for (unsigned int i = 0; i < s.GetFieldCount(); i++) {
    fields.push_back(s.GetField(i).Clone());
  }
}

Struct::~Struct() {
  while (fields.size()) {
    Field * f = fields[fields.size() - 1];
    fields.pop_back();
    delete f;
  }
}

std::string Struct::GetSymbolName() const {
  return dart.EscapeSymbol(typeInfo.getName());
}

void Struct::Print(raw_ostream & stream) const {
  stream << "class " << GetSymbolName() << " {\n";
  for (auto i = 0; i < GetFieldCount(); i++) {
    const Field & field = GetField(i);
    field.PrintDeclaration(stream, dart.GetTab());
    stream << "\n";
  }
  stream << "\n" << dart.GetTab() << GetSymbolName() << "() {\n";
  for (auto i = 0; i < GetFieldCount(); i++) {
    const Field & field = GetField(i);
    field.PrintInitialization(stream, dart.GetTab() + dart.GetTab(),
                              dart.GetTab());
    stream << "\n";
  }
  stream << dart.GetTab() << "}\n}";
}

unsigned int Struct::GetFieldCount() const {
  return (unsigned int)fields.size();
}

const Field & Struct::GetField(unsigned int i) const {
  return *fields[i];
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
