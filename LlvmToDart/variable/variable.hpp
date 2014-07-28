#ifndef __LLVMTODART_VARIABLE_HPP__
#define __LLVMTODART_VARIABLE_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class Session;

class Variable {
public:
  static Variable * CreateVariable(Session & session,
                                const std::string & name, Type * type);
  
  Variable(Session & session, const std::string & name);
  
  // delete copy and assignment
  Variable(const Variable &) = delete;
  Variable & operator=(const Variable &) = delete;
  
  // destructor needs to be virtual
  virtual ~Variable() {}
  
  StringRef GetName() const;
  Session & GetSession() const;
  
  virtual void PrintType(raw_ostream & stream) const = 0;
  virtual void PrintInitialization(raw_ostream & stream) const = 0;
  virtual void PrintDeclaration(raw_ostream & stream) const;
  virtual Variable * Clone() const = 0;
  
private:
  Session & session;
  std::string name;
};

}

#endif
