#include "session.hpp"
#include <sstream>

namespace llvmtodart {

Session::Session(const Settings & a, Module & b)
  : settings(a), module(b), structs(*this), globals(*this) {
}

const Settings & Session::GetSettings() const {
  return settings;
}

Module & Session::GetModule() const {
  return module;
}

const GlobalTable & Session::GetGlobals() const {
  return globals;
}

const StructTable & Session::GetStructs() const {
  return structs;
}

std::string Session::GetIndentation() const {
  std::stringstream str("");
  for (int i = 0; i < indentCount; i++) {
    str << GetSettings().GetTab();
  }
  return str.str();
}

}
