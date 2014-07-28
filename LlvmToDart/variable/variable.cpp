#include "variable.hpp"
#include "session.hpp"
#include "scalar-variable.hpp"
#include "struct-variable.hpp"
#include "array-variable.hpp"
#include "function-variable.hpp"

namespace llvmtodart {

Variable * Variable::CreateVariable(Session & s, const std::string & name,
                           Type * type) {
  Variable * f = ScalarVariable::CreateWithType(s, name, type);
  if (!f) f = StructVariable::CreateWithType(s, name, type);
  if (!f) f = ArrayVariable::CreateWithType(s, name, type);
  if (!f) f = FunctionVariable::CreateWithType(s, name, type);
  return f;
}

Variable::Variable(Session & session, const std::string & _name)
  : session(session), name(_name) {
}

StringRef Variable::GetName() const {
  return StringRef(name);
}

Session & Variable::GetSession() const {
  return session;
}

void Variable::PrintDeclaration(raw_ostream & stream) const {
  stream << session.GetIndentation();
  PrintType(stream);
  stream << " " << GetName() << ";";
}

}
