#include "struct.hpp"
#include "session.hpp"
#include "indent-scope.hpp"

namespace llvmtodart {

Struct::Struct(Session & a, const StructType & b)
  : SessionObject(a), typeInfo(b) {
  for (unsigned int i = 0; i < typeInfo.getNumElements(); i++) {
    Type * VariableType = typeInfo.getElementType(i);
    std::string VariableName(GetSession().GetSettings().VariableName(i));
    
    Variable * f = Variable::CreateVariable(GetSession(), VariableName, VariableType);
    if (f) Variables.push_back(f);
  }
}

Struct::Struct(const Struct & s) : SessionObject(s), typeInfo(s.typeInfo) {
  for (unsigned int i = 0; i < s.GetVariableCount(); i++) {
    Variables.push_back(s.GetVariable(i).Clone());
  }
}

Struct::~Struct() {
  while (Variables.size()) {
    Variable * f = Variables[Variables.size() - 1];
    Variables.pop_back();
    delete f;
  }
}

std::string Struct::GetName() const {
  return GetSession().GetSettings().EscapeSymbol(typeInfo.getName());
}

void Struct::Print(raw_ostream & stream) const {
  stream << GetSession().GetIndentation() << "class " << GetName() << " {\n";
  {
    IndentScope scope(GetSession());
    
    stream << scope.GetIndentation() << "int parentOffset;\n";
    stream << scope.GetIndentation() << "Object parentObject;\n";
    
    for (auto i = 0; i < GetVariableCount(); i++) {
      if (i == 0) stream << "\n";
      const Variable & var = GetVariable(i);
      var.PrintDeclaration(stream);
      stream << "\n";
    }
    stream << "\n" << scope.GetIndentation() << GetName() << "() {\n";
    for (auto i = 0; i < GetVariableCount(); i++) {
      IndentScope scope(GetSession());
      const Variable & var = GetVariable(i);
      var.PrintInitialization(stream);
      stream << "\n";
      
    }
    stream << scope.GetIndentation() << "}\n";
  }
  stream << "}";
}

unsigned int Struct::GetVariableCount() const {
  return (unsigned int)Variables.size();
}

const Variable & Struct::GetVariable(unsigned int i) const {
  return *Variables[i];
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
