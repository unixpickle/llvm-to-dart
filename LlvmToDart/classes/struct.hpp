#ifndef __LLVMTODART_STRUCT_HPP__
#define __LLVMTODART_STRUCT_HPP__

#include "llvm-includes.hpp"
#include "dart-configuration.hpp"

namespace llvmtodart {

class Struct {
public:
  Struct(const DartConfiguration &, const StructType &);
  
  void Print(raw_ostream &) const;
  std::string GetSymbolName() const;
  
  unsigned int GetFieldCount() const;
  std::string GetFieldName(unsigned int) const;
  
  bool operator==(const Struct &) const;
  bool operator!=(const Struct &) const;
  bool operator>(const Struct &) const;
  bool operator<(const Struct &) const;
  
protected:
  const DartConfiguration & dart;
  const StructType & typeInfo;
};

}

#endif
