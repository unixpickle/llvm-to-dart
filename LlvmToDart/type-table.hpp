#ifndef __LLVMTODART_TYPE_TABLE_HPP__
#define __LLVMTODART_TYPE_TABLE_HPP__

#include "llvm-includes.hpp"
#include "dart-configuration.hpp"

namespace llvmtodart {

class TypeTable {
public:
  TypeTable(DartConfiguration & config, Module & module);
  
  void WriteTo(raw_ostream & stream) const;
  
private:
  DartConfiguration & dart;
  Module & module;
  SetVector<StructType *> types;
};

raw_ostream & operator<<(raw_ostream & stream, const TypeTable &);

}

#endif
