#ifndef __LLVMTODART_SETTINGS_HPP__
#define __LLVMTODART_SETTINGS_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class Settings {
public:
  virtual std::string GetTab() const;
  virtual std::string FieldName(unsigned int idx) const;
  virtual std::string EscapeSymbol(StringRef name) const;
};

}

#endif
