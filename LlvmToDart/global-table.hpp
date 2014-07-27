#ifndef __LLVMTODART__GLOBAL_TABLE__
#define __LLVMTODART__GLOBAL_TABLE__

#include "llvm-includes.hpp"

namespace llvmtodart {

class GlobalTable {
public:
  GlobalTable(Module & module);
  
  void WriteTo(raw_ostream & stream) const;
  
private:
  const Module::GlobalListType & list;
  Module & module;
};

raw_ostream & operator<<(raw_ostream & stream, const GlobalTable &);

}

#endif
