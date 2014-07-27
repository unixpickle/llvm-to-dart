#ifndef __LLVMTODART_STRUCT_TABLE_HPP__
#define __LLVMTODART_STRUCT_TABLE_HPP__

#include "struct.hpp"

namespace llvmtodart {

class StructTable {
public:
  StructTable(Settings & config, Module & module);
  
  void Print(raw_ostream & stream) const;
  
private:
  Settings & dart;
  Module & module;
  SetVector<Struct> types;
};

raw_ostream & operator<<(raw_ostream & stream, const StructTable &);

}

#endif
