#ifndef __LLVMTODART_STRUCT_HPP__
#define __LLVMTODART_STRUCT_HPP__

#include "llvm-includes.hpp"
#include "settings.hpp"
#include "field.hpp"

namespace llvmtodart {

class Struct {
public:
  Struct(Module & m, const Settings &, const StructType &);
  Struct(const Struct & s);
  ~Struct();
  
  Struct & operator=(const Struct &);
  
  void Print(raw_ostream &) const;
  std::string GetSymbolName() const;
  
  unsigned int GetFieldCount() const;
  const Field & GetField(unsigned int i) const;
  
  bool operator==(const Struct &) const;
  bool operator!=(const Struct &) const;
  bool operator>(const Struct &) const;
  bool operator<(const Struct &) const;
  
protected:
  const Settings & dart;
  const StructType & typeInfo;
  std::vector<Field *> fields;
};

}

#endif
