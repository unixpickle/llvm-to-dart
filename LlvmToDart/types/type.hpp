#ifndef __LLVMTODART_TYPE_HPP__
#define __LLVMTODART_TYPE_HPP__

#include "llvm-includes.hpp"
#include "session-object.hpp"

namespace llvmtodart {

class Session;

class Type : public SessionObject {
public:
  static Type * Create(Session & session, llvm::Type * type);
  
  // delete copy and assignment
  Type(const Type &) = delete;
  Type & operator=(const Type &) = delete;
  
  // destructor needs to be virtual
  virtual ~Type() {}
  
  virtual StringRef GetTypeName() const = 0;
  
  virtual void PrintInitializer(raw_ostream & stream) const = 0;
  virtual void PrintDeclaration(raw_ostream & stream, StringRef name) const;
  virtual Type * Clone() const = 0;
  
  virtual bool IsStructure() const;
  
protected:
  Type(Session & session);
};

}

#endif
