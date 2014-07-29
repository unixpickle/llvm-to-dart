#include "struct.hpp"
#include "session.hpp"
#include "indent-scope.hpp"

namespace llvmtodart {

Struct::Struct(Session & s, llvm::StructType & st, StringRef _name)
  : SessionObject(s), name(_name), typeInfo(st) {
  DataLayout dLayout(s.GetModule().getDataLayout());
  const StructLayout * layout = dLayout.getStructLayout(&st);
  
  unsigned int idx = 0;
  for (auto i = 0; i < typeInfo.getNumElements(); i++) {
    llvm::Type * type = typeInfo.getElementType(i);
    Type * t = Type::Create(s, type);
    if (!t) continue;
    
    uint64_t offset = layout->getElementOffset(i);
    
    StructField * f = new StructField(t, idx++, offset);
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
    PrintFieldAtOffsetMethod(stream);
    stream << "\n";
    PrintFieldAtIndexMethod(stream);
    stream << "\n";
    PrintFieldOffsetMethod(stream);
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

void Struct::PrintFieldAtOffsetMethod(raw_ostream & stream) const {
  stream << GetSession().GetIndentation()
    << "dynamic getFieldAtOffset(int offset) {\n";
  {
    IndentScope scope(GetSession());
    bool hasDone = false;
    for (auto i = 0; i < GetFieldCount(); i++) {
      const StructField & field = GetField(i);
      if (!field.GetType()->GetSize()) continue;
      
      if (!hasDone) {
        hasDone = true;
        stream << scope.GetIndentation();
      } else {
        stream << " else ";
      }
      
      stream << "if (offset >= " << field.GetOffset() << " && offset < "
        << field.GetType()->GetSize() + field.GetOffset() << ") {\n";
      {
        IndentScope scope(GetSession());
        stream << scope.GetIndentation() << "return field" << field.GetIndex()
          << ";\n";
      }
      stream << scope.GetIndentation() << "}";
    }
    if (hasDone) stream << "\n";
    stream << scope.GetIndentation() << "throw new RangeError('"
      << "Invalid offset: ' + offset);\n";
  }
  stream << GetSession().GetIndentation() << "}\n";
}

void Struct::PrintFieldAtIndexMethod(raw_ostream & stream) const {
  stream << GetSession().GetIndentation()
    << "dynamic getFieldAtIndex(int index) {\n";
  {
    IndentScope scope(GetSession());
    stream << scope.GetIndentation() << "switch (offset) {\n";
    {
      IndentScope scope(GetSession());
      for (unsigned int i = 0; i < GetFieldCount(); i++) {
        const StructField & field = GetField(i);
        stream << scope.GetIndentation() << "case " << field.GetIndex()
          << ":\n";
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

void Struct::PrintFieldOffsetMethod(raw_ostream & stream) const {
  stream << GetSession().GetIndentation()
    << "int getFieldOffset(int index) {\n";
  {
    IndentScope scope(GetSession());
    stream << scope.GetIndentation() << "switch (index) {\n";
    {
      IndentScope scope(GetSession());
      for (unsigned int i = 0; i < GetFieldCount(); i++) {
        const StructField & field = GetField(i);
        stream << scope.GetIndentation() << "case " << field.GetIndex()
          << ":\n";
        IndentScope inner(GetSession());
        stream << inner.GetIndentation() << "return " << field.GetOffset()
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
