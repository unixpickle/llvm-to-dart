#include "array-variable.hpp"
#include "indent-scope.hpp"
#include "session.hpp"

namespace llvmtodart {

ArrayVariable * ArrayVariable::CreateWithType(Session & s,
                                              const std::string & name,
                                              Type * type) {
  if (!type->isArrayTy()) return nullptr;
  
  Type * containedType = type->getArrayElementType();
  Variable * subVariable = Variable::CreateVariable(s, "namedLoopVar",
                                                    containedType);
  if (!subVariable) return nullptr;
  
  return new ArrayVariable(s, name, type->getArrayNumElements(), subVariable);
}

ArrayVariable::ArrayVariable(Session & s, const std::string & VariableName,
                       uint64_t elements, Variable * sub)
  : Variable(s, VariableName), elements(elements), subVariable(sub) {
}

ArrayVariable::~ArrayVariable() {
  delete subVariable;
}

void ArrayVariable::PrintType(raw_ostream & stream) const {
  stream << "List<";
  subVariable->PrintType(stream);
  stream << ">";
}

void ArrayVariable::PrintInitialization(raw_ostream & stream) const {
  stream << GetSession().GetIndentation() << GetName() << " = new ";
  PrintType(stream);
  stream << "();\n";
  
  std::string subIndent(GetSession().GetSettings().GetTab());
  
  stream << GetSession().GetIndentation() << "for (int i = 0; i < "
    << elements << "; i++) {\n";
  
  {
    IndentScope scope(GetSession());
    
    subVariable->PrintDeclaration(stream);
    stream << "\n";
    subVariable->PrintInitialization(stream);
    stream << "\n" << scope.GetIndentation() << GetName()
      << ".add(namedLoopVar);\n";
  }
  
  stream << GetSession().GetIndentation() << "}";
}

Variable * ArrayVariable::Clone() const {
  return new ArrayVariable(GetSession(), GetName(), elements,
                           subVariable->Clone());
}

}

