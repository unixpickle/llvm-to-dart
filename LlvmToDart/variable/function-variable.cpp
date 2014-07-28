#include "function-variable.hpp"
#include "session.hpp"

namespace llvmtodart {

FunctionVariable * FunctionVariable::CreateWithType(Session & s,
                                                    const std::string & name,
                                                    Type * type) {
  if (type->isPointerTy()) {
    if (type->getPointerElementType()->isFunctionTy()) {
      type = type->getPointerElementType();
    }
  }
  if (!type->isFunctionTy()) return nullptr;
  
  return new FunctionVariable(s, name, static_cast<FunctionType *>(type));
}

FunctionVariable::FunctionVariable(Session & s, const std::string & name,
                                   FunctionType * t)
  : Variable(s, name), type(t) {
  returnVar = Variable::CreateVariable(s, "ret", t->getReturnType());
  for (unsigned int i = 0; i < t->getFunctionNumParams(); i++) {
    Type * argType = t->getFunctionParamType(i);
    Variable * arg = Variable::CreateVariable(s, "arg", argType);
    if (!arg) continue;
    argumentVars.push_back(arg);
  }
}

FunctionVariable::~FunctionVariable() {
  if (returnVar) delete returnVar;
  while (argumentVars.size()) {
    Variable * v = argumentVars[argumentVars.size() - 1];
    argumentVars.pop_back();
    delete v;
  }
}

void FunctionVariable::PrintType(raw_ostream & stream) const {
  stream << "Function";
}

void FunctionVariable::PrintInitialization(raw_ostream & stream) const {
  stream << GetSession().GetIndentation() << GetName() << " = null;";
}

void FunctionVariable::PrintDeclaration(raw_ostream & stream) const {
  stream << GetSession().GetIndentation();
  returnVar->PrintType(stream);
  stream << " " << GetName() << "(";
  for (unsigned int i = 0; i < argumentVars.size(); i++) {
    argumentVars[i]->PrintType(stream);
    if (i + 1 < argumentVars.size()) {
      stream << ", ";
    }
  }
  stream << ");";
}

Variable * FunctionVariable::Clone() const {
  return new FunctionVariable(GetSession(), GetName(), type);
}

}
