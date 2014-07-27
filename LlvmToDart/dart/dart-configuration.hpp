#ifndef __LLVMTODART_DART_CONFIGURATION_HPP__
#define __LLVMTODART_DART_CONFIGURATION_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class DartConfiguration {
public:
  virtual std::string GetTab() const;
  virtual std::string FieldName(unsigned int idx) const;
  virtual std::string EscapeSymbol(StringRef name) const;
};

}

#endif
