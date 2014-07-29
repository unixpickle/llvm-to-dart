#include "struct.hpp"
#include "session.hpp"
#include "indent-scope.hpp"

namespace llvmtodart {

Struct::Struct(Session & s, const llvm::StructType & st)
  : SessionObject(s), typeInfo(st) {
  uint64_t offset = 0;
  for (auto i = 0; i < typeInfo.getNumElements(); i++) {
    llvm::Type * type = typeInfo.getElementType(i);
    string name(s.GetSettings().VariableName(i));
    Type * t = Type::Create(s, type);
    if (!t) continue;
    StructField * f = new StructField(t, name, offset);
    offset += f->GetSize();
    fields.push_back(f);
  }
}

Struct::Struct(Struct && s)
  : SessionObject(s.GetSession()), typeInfo(s.typeInfo),
    fields(std::move(s.fields)) {
  s.fields.empty();
}

Struct::~Struct() {
  for (auto i = 0; i < fields.size(); i++) {
    delete fields[i];
  }
}

void Struct::Print(raw_ostream & stream) const {
  stream << GetSession().GetIndentation() << "class " << GetName() << " {\n";
  {
    IndentScope scope(GetSession());
    
    stream << scope.GetIndentation() << "int parentOffset;\n";
    stream << scope.GetIndentation() << "Object parentObject;\n";
    
    for (auto i = 0; i < GetFieldCount(); i++) {
      if (i == 0) stream << "\n";
      stream << scope.GetIndentation();
      const StructField & field = GetField(i);
      field.PrintDeclaration(stream);
      stream << "\n";
    }
    stream << "\n" << scope.GetIndentation() << GetName() << "() {\n";
    for (auto i = 0; i < GetFieldCount(); i++) {
      IndentScope inner(GetSession());
      const StructField & field = GetField(i);
      stream << inner.GetIndentation();
      field.PrintDefinition(stream);
      stream << "\n";
    }
    stream << scope.GetIndentation() << "}\n";
  }
  stream << GetSession().GetIndentation() << "}";
}

StringRef Struct::GetName() const {
  return name;
}

unsigned int Struct::GetFieldCount() const {
  return typeInfo.getNumElements();
}

const StructField & Struct::GetField(unsigned int i) const {
  return *fields[i];
}

}
