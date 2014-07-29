#include "struct.hpp"
#include "session.hpp"
#include "indent-scope.hpp"

namespace llvmtodart {

Struct::Struct(Session & s, llvm::StructType & st, StringRef _name)
  : SessionObject(s), name(_name), typeInfo(st) {
  DataLayout dLayout(s.GetModule().getDataLayout());
  const StructLayout * layout = dLayout.getStructLayout(&st);
  
  for (auto i = 0; i < typeInfo.getNumElements(); i++) {
    llvm::Type * type = typeInfo.getElementType(i);
    Type * t = Type::Create(s, type);
    if (!t) continue;
    
    uint64_t offset = layout->getElementOffset(i);
    
    StructField * f = new StructField(t, i, offset);
    fields.push_back(f);
  }
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
      const StructField & field = GetField(i);
      stream << scope.GetIndentation();
      field.PrintDeclaration(stream);
      stream << "\n";
    }
    stream << "\n" << scope.GetIndentation() << GetName() << "() {\n";
    for (auto i = 0; i < GetFieldCount(); i++) {
      IndentScope scope(GetSession());
      const StructField & field = GetField(i);
      stream << scope.GetIndentation();
      field.PrintDefinition(stream);
      stream << "\n";
    }
    stream << scope.GetIndentation() << "}\n\n";
    PrintFieldIndexMethod(stream);
    stream << "\n";
    PrintFieldAccessMethod(stream);
  }
  stream << GetSession().GetIndentation() << "}";
}

StringRef Struct::GetName() const {
  return name;
}

unsigned int Struct::GetFieldCount() const {
  return (unsigned int)fields.size();
}

const StructField & Struct::GetField(unsigned int i) const {
  return *fields[i];
}

void Struct::PrintFieldIndexMethod(raw_ostream & stream) const {
  stream << GetSession().GetIndentation()
    << "int fieldIndexAtOffset(int offset) {\n";
  {
    IndentScope scope(GetSession());
    stream << scope.GetIndentation() << "switch (offset) {\n";
    {
      IndentScope scope(GetSession());
      for (unsigned int i = 0; i < GetFieldCount(); i++) {
        const StructField & field = GetField(i);
        stream << scope.GetIndentation() << "case " << field.GetOffset() << ":\n";
        IndentScope inner(GetSession());
        stream << inner.GetIndentation() << "return " << field.GetIndex()
        << ";\n";
      }
      stream << scope.GetIndentation() << "default:\n";
      {
        IndentScope scope(GetSession());
        stream << scope.GetIndentation() << "throw new RangeError('"
        << "Invalid field offset: ' + offset);\n";
      }
    }
    stream << scope.GetIndentation() << "}\n";
  }
  stream << GetSession().GetIndentation() << "}\n";
}

void Struct::PrintFieldAccessMethod(raw_ostream & stream) const {
  stream << GetSession().GetIndentation()
    << "dynamic fieldAtIndex(int index) {\n";
  {
    IndentScope scope(GetSession());
    stream << scope.GetIndentation() << "switch (offset) {\n";
    {
      IndentScope scope(GetSession());
      for (unsigned int i = 0; i < GetFieldCount(); i++) {
        const StructField & field = GetField(i);
        stream << scope.GetIndentation() << "case " << field.GetIndex() << ":\n";
        IndentScope inner(GetSession());
        stream << inner.GetIndentation() << "return field" << field.GetIndex()
          << ";\n";
      }
      stream << scope.GetIndentation() << "default:\n";
      {
        IndentScope scope(GetSession());
        stream << scope.GetIndentation() << "throw new RangeError('"
        << "Invalid field index: ' + index);\n";
      }
    }
    stream << scope.GetIndentation() << "}\n";
  }
  stream << GetSession().GetIndentation() << "}\n";
}

}
