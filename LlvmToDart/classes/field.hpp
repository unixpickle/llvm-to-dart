#ifndef __LLVMTODART_FIELD_HPP__
#define __LLVMTODART_FIELD_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class Field {
public:
  static Field * CreateField(Module & m, const std::string & fieldName,
                             Type * type);
  
  Field(const std::string & fieldName);
  Field(const Field &) = delete;
  Field & operator=(const Field &) = delete;
  
  virtual ~Field() {}
  
  StringRef GetFieldName() const;
  
  virtual void PrintType(raw_ostream & stream) const = 0;
  virtual void PrintDeclaration(raw_ostream & stream,
                                const std::string & indent) const = 0;
  virtual void PrintInitialization(raw_ostream & stream,
                                   const std::string & indent,
                                   const std::string & subIndent) const = 0;
  virtual Field * Clone() const = 0;
  
private:
  std::string fieldName;
};

}

#endif
