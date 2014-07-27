#include "struct-table.hpp"
#include "session.hpp"

namespace llvmtodart {

StructTable::StructTable(Session & s) : session(s) {
  FindUsedTypes finder;
  finder.runOnModule(session.GetModule());
  auto iterEnd = finder.getTypes().end();
  for (auto iter = finder.getTypes().begin(); iter != iterEnd; ++iter) {
    Type * type = *iter;
    if (!type->isStructTy()) continue;
    StructType & info = *static_cast<StructType *>(type);
    if (info.isLiteral()) continue;
    Struct st(session, info);
    types.insert(st);
  }
}

void StructTable::Print(llvm::raw_ostream & stream) const {
  auto iterEnd = types.end();
  for (auto iter = types.begin(); iter != iterEnd; ++iter) {
    Struct s = *iter;
    s.Print(stream);
    stream << "\n\n";
  }
}

raw_ostream & operator<<(raw_ostream & stream, const StructTable & globals) {
  globals.Print(stream);
  return stream;
}

}
