#ifndef __LLVMTODART_STRUCT_TABLE_HPP__
#define __LLVMTODART_STRUCT_TABLE_HPP__

#include "llvm-includes.hpp"
#include "struct.hpp"

namespace llvmtodart {

class StructTable {
public:
  StructTable(DartConfiguration & config, Module & module);
  
  void Print(raw_ostream & stream) const;
  
private:
  DartConfiguration & dart;
  Module & module;
  SetVector<Struct> types;
};

raw_ostream & operator<<(raw_ostream & stream, const StructTable &);

}

#endif
