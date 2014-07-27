#ifndef __LLVMTODART_STRUCT_TABLE_HPP__
#define __LLVMTODART_STRUCT_TABLE_HPP__

#include "struct.hpp"
#include "encodable.hpp"

namespace llvmtodart {

class Session;

class StructTable : public Encodable {
public:
  StructTable(Session & s);
  
  void Print(raw_ostream & stream) const;
  
private:
  Session & session;
  SetVector<Struct> types;
};

}

#endif
