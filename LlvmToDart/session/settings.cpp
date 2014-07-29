#include "settings.hpp"
#include <sstream>

namespace llvmtodart {

std::string Settings::GetTab() const {
  return "  ";
}

std::string Settings::VariableName(unsigned int idx) const {
  std::stringstream str;
  str << "field" << idx;
  return str.str();
}

std::string Settings::EscapeSymbol(StringRef name) const {
  std::string str(name.str());
  
  for (auto i = 0; i < str.length(); ++i) {
    if (str[i] == '_') {
      str.insert(i, "_");
      ++i;
    } else if (str[i] == '.') {
      str[i] = '_';
      str.insert(i + 1, "0");
      ++i;
    }
  }
  
  return str;
}

}

