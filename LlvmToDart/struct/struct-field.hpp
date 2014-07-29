#ifndef __LLVMTODART_STRUCT_FIELD_HPP__
#define __LLVMTODART_STRUCT_FIELD_HPP__

#include "type.hpp"

namespace llvmtodart {

class StructField {
public:
  StructField(Type *, const string &, uint64_t);
  ~StructField();
  
  void PrintDeclaration(raw_ostream &) const;
  void PrintDefinition(raw_ostream &) const;
  uint64_t GetSize() const;
  
private:
  Type * type;
  string fieldName;
  uint64_t offset;
};

}

#endif
