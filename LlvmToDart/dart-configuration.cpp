#include "dart-configuration.hpp"
#include <sstream>

namespace llvmtodart {

StringRef DartConfiguration::GetTab() {
  return "  ";
}

StringRef DartConfiguration::FieldName(unsigned int idx) {
  std::stringstream str;
  str << "field" << idx;
  return StringRef(str.str());
}

StringRef DartConfiguration::EscapeSymbol(StringRef name) {
  std::string str((std::string)name);
  
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

