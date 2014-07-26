#include "globals.hpp"

namespace llvmtodart {

Globals::Globals(Module & m) : module(m), list(m.getGlobalList()) {
}

raw_ostream & operator<<(raw_ostream & stream, const Globals & globals) {
  auto iter = globals.list.begin();
  auto end = globals.list.end();
  while (iter != end) {
    const GlobalVariable & variable = *iter;
    stream << variable.getName() << "\n";
    ++iter;
  }
  return stream;
}

}
