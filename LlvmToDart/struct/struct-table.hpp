#ifndef __LLVMTODART_STRUCT_TABLE_HPP__
#define __LLVMTODART_STRUCT_TABLE_HPP__

#include "struct.hpp"
#include "encodable.hpp"
#include "session-object.hpp"

namespace llvmtodart {

class Session;

class StructTable : public Encodable, public SessionObject {
public:
  StructTable(Session & s);
  
  virtual void Print(raw_ostream & stream) const;
  
private:
  SetVector<Struct> types;
};

}

#endif
