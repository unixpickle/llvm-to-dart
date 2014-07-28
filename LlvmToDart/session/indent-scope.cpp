#include "indent-scope.hpp"
#include "session.hpp"
#include <sstream>

namespace llvmtodart {

IndentScope::IndentScope(Session & s)
  : session(s), count(++s.indentCount), indentation(session.GetIndentation()) {
}

IndentScope::~IndentScope() {
  --session.indentCount;
}

int IndentScope::GetCount() {
  return count;
}

std::string IndentScope::GetIndentation() {
  return indentation;
}

}
