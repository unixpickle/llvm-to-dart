#include "global-table.hpp"

namespace llvmtodart {

GlobalTable::GlobalTable(Module & m) : module(m), list(m.getGlobalList()) {
}

void GlobalTable::Print(llvm::raw_ostream & stream) const {
  auto iter = list.begin();
  auto end = list.end();
  while (iter != end) {
    const GlobalVariable & variable = *iter;
    stream << variable.getName() << ": ";
    variable.getType()->print(stream);
    stream << "\n";
    ++iter;
  }
}

raw_ostream & operator<<(raw_ostream & stream, const GlobalTable & globals) {
  globals.Print(stream);
  return stream;
}

}
