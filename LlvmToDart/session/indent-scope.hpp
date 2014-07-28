#ifndef __LLVMTODART_INDENT_SCOPE_HPP__
#define __LLVMTODART_INDENT_SCOPE_HPP__

#include <string>

namespace llvmtodart {

class Session;

class IndentScope {
public:
  IndentScope(Session &);
  ~IndentScope();
  
  int GetCount();
  std::string GetIndentation();
  
private:
  Session & session;
  int count;
  std::string indentation;
};

}

#endif
