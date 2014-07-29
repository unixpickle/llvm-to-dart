#include "struct-table.hpp"
#include "session.hpp"

namespace llvmtodart {

StructTable::StructTable(Session & s) : SessionObject(s) {
  FindUsedTypes finder;
  finder.runOnModule(GetSession().GetModule());
  auto iterEnd = finder.getTypes().end();
  for (auto iter = finder.getTypes().begin(); iter != iterEnd; ++iter) {
    llvm::Type * type = *iter;
    if (!type->isStructTy()) continue;
    llvm::StructType & info = *static_cast<llvm::StructType *>(type);
    
    if (info.isLiteral()) continue;
    
    string name(GetSession().GetSettings().EscapeSymbol(info.getName()));
    Struct * st = new Struct(GetSession(), info, name);
    types.push_back(st);
  }
}

StructTable::~StructTable() {
  for (auto i = 0; i < types.size(); i++) {
    delete types[i];
  }
}

void StructTable::Print(llvm::raw_ostream & stream) const {
  auto iterEnd = types.end();
  for (auto iter = types.begin(); iter != iterEnd; ++iter) {
    Struct & s = **iter;
    stream << s << "\n\n";
  }
}

raw_ostream & operator<<(raw_ostream & stream, const StructTable & table) {
  table.Print(stream);
  return stream;
}

}
