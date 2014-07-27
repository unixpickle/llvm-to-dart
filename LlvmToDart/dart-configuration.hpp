#ifndef __LLVMTODART_DART_CONFIGURATION_HPP__
#define __LLVMTODART_DART_CONFIGURATION_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class DartConfiguration {
public:
  virtual StringRef GetTab();
  virtual StringRef FieldName(unsigned int idx);
  virtual StringRef EscapeSymbol(StringRef name);
};

}

#endif
