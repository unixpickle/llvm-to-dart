#include "session.hpp"

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

}
