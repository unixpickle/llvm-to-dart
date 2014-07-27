#include "struct.hpp"
#include "session.hpp"

namespace llvmtodart {

Struct::Struct(Session & a, const StructType & b)
  : session(a), typeInfo(b) {
  for (unsigned int i = 0; i < typeInfo.getNumElements(); i++) {
    Type * fieldType = typeInfo.getElementType(i);
    std::string fieldName(session.GetSettings().FieldName(i));
    
    Field * f = Field::CreateField(session, fieldName, fieldType);
    if (f) fields.push_back(f);
  }
}

Struct::Struct(const Struct & s) : session(s.session), typeInfo(s.typeInfo) {
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

std::string Struct::GetName() const {
  return session.GetSettings().EscapeSymbol(typeInfo.getName());
}

void Struct::Print(raw_ostream & stream) const {
  std::string tab(session.GetSettings().GetTab());
  
  stream << "class " << GetName() << " {\n";
  for (auto i = 0; i < GetFieldCount(); i++) {
    const Field & field = GetField(i);
    field.PrintDeclaration(stream, tab);
    stream << "\n";
  }
  stream << "\n" << tab << GetName()
    << "() {\n";
  for (auto i = 0; i < GetFieldCount(); i++) {
    const Field & field = GetField(i);
    field.PrintInitialization(stream, tab + tab);
    stream << "\n";
  }
  stream << tab << "}\n}";
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
