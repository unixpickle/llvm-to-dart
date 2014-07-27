#include "dart-configuration.hpp"
#include <sstream>

namespace llvmtodart {

std::string DartConfiguration::GetTab() const {
  return "  ";
}

std::string DartConfiguration::FieldName(unsigned int idx) const {
  std::stringstream str;
  str << "field" << idx;
  return str.str();
}

std::string DartConfiguration::EscapeSymbol(StringRef name) const {
  std::string str(name.str());
  
  for (auto i = 0; i < str.length(); ++i) {
    if (str[i] == '_') {
      str.insert(i, "_");
      ++i;
    } else if (str[i] == '.') {
      str[i] = '_';
      str.insert(i + 1, "d");
      ++i;
    }
  }
  
  return str;
}

}

