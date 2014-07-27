#include "struct-table.hpp"

namespace llvmtodart {

StructTable::StructTable(DartConfiguration & _dart, Module & m)
  : dart(_dart), module(m) {
  FindUsedTypes finder;
  finder.runOnModule(module);
  auto iterEnd = finder.getTypes().end();
  for (auto iter = finder.getTypes().begin(); iter != iterEnd; ++iter) {
    Type * type = *iter;
    if (!type->isStructTy()) continue;
    Struct st(module, dart, *static_cast<StructType *>(type));
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
