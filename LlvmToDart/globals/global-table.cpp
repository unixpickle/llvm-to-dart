#include "global-table.hpp"
#include "session.hpp"

namespace llvmtodart {

GlobalTable::GlobalTable(Session & s)
  : session(s), list(s.GetModule().getGlobalList()) {
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

}
