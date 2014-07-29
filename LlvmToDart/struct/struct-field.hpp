#ifndef __LLVMTODART_STRUCT_FIELD_HPP__
#define __LLVMTODART_STRUCT_FIELD_HPP__

#include "type.hpp"

namespace llvmtodart {

class StructField {
public:
  StructField(Type *, unsigned int idx, uint64_t off);
  ~StructField();
  
  StructField(const StructField &) = delete;
  StructField & operator=(const StructField &) = delete;
  
  void PrintDeclaration(raw_ostream &) const;
  void PrintDefinition(raw_ostream &) const;
  
  uint64_t GetOffset() const;
  Type * GetType() const;
  StringRef GetFieldName() const;
  unsigned int GetIndex() const;
  
private:
  Type * type;
  unsigned int index;
  uint64_t offset;
  string fieldName;
};

}

#endif
