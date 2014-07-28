#include "struct-variable.hpp"
#include "session.hpp"

namespace llvmtodart {

StructVariable * StructVariable::CreateWithType(Session & s,
                                                const std::string & name,
                                                Type * type) {
  if (!type->isStructTy()) return nullptr;
  std::string newName(s.GetSettings().EscapeSymbol(type->getStructName()));
  return new StructVariable(s, name, newName);
}

StructVariable::StructVariable(Session & s, const std::string & _name,
                         const std::string & _structName)
  : Variable(s, _name), structName(_structName) {
}

void StructVariable::PrintType(raw_ostream & stream) const {
  stream << structName;
}

void StructVariable::PrintInitialization(raw_ostream & stream) const {
  stream << GetSession().GetIndentation() << GetName() << " = new "
    << structName << "();";
}

Variable * StructVariable::Clone() const {
  return new StructVariable(GetSession(), GetName(), structName);
}

}
