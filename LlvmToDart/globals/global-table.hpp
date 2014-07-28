#ifndef __LLVMTODART__GLOBAL_TABLE__
#define __LLVMTODART__GLOBAL_TABLE__

#include "encodable.hpp"
#include "session-object.hpp"

namespace llvmtodart {

class GlobalTable : public Encodable, public SessionObject {
public:
  GlobalTable(Session & session);
  
  virtual void Print(raw_ostream & stream) const;
  
private:
  const Module::GlobalListType & list;
};

}

#endif
