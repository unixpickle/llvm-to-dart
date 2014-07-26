#ifndef __LLVMTODART__GLOBALS__
#define __LLVMTODART__GLOBALS__

#include "llvm-includes.hpp"

namespace llvmtodart {

class Globals {
public:
  Globals(Module & module);
  
protected:
  const Module::GlobalListType & list;
  Module & module;
  
  friend raw_ostream & operator<<(raw_ostream &, const Globals &);
};

raw_ostream & operator<<(raw_ostream & stream, const Globals &);

}

#endif
