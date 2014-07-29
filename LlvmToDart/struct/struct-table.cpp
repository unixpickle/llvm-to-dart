#include "struct-table.hpp"
#include "session.hpp"

namespace llvmtodart {

StructTable::StructTable(Session & s) : SessionObject(s) {
  FindUsedTypes finder;
  finder.runOnModule(GetSession().GetModule());
  auto iterEnd = finder.getTypes().end();
  for (auto iter = finder.getTypes().begin(); iter != iterEnd; ++iter) {
    Type * type = *iter;
    if (!type->isStructTy()) continue;
    StructType & info = *static_cast<StructType *>(type);
    
    // TODO: come up with system for literals
    if (info.isLiteral()) continue;
    
    Struct st(GetSession(), info);
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
