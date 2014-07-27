#ifndef __LLVMTODART__GLOBAL_TABLE__
#define __LLVMTODART__GLOBAL_TABLE__

#include "encodable.hpp"

namespace llvmtodart {

class Session;

class GlobalTable : public Encodable {
public:
  GlobalTable(Session & session);
  
  virtual void Print(raw_ostream & stream) const;
  
private:
  const Module::GlobalListType & list;
  Session & session;
};

}

#endif
