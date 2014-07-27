#ifndef __LLVMTODART_FIELD_HPP__
#define __LLVMTODART_FIELD_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class Session;

class Field {
public:
  static Field * CreateField(Session & session, const std::string & fieldName,
                             Type * type);
  
  Field(Session & session, const std::string & fieldName);
  Field(const Field &) = delete;
  Field & operator=(const Field &) = delete;
  
  virtual ~Field() {}
  
  StringRef GetFieldName() const;
  Session & GetSession() const;
  
  virtual void PrintType(raw_ostream & stream) const = 0;
  virtual void PrintDeclaration(raw_ostream & stream,
                                const std::string & indent) const = 0;
  virtual void PrintInitialization(raw_ostream & stream,
                                   const std::string & indent) const = 0;
  virtual Field * Clone() const = 0;
  
private:
  Session & session;
  std::string fieldName;
};

}

#endif
