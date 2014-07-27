#include "type-table.hpp"

namespace llvmtodart {

TypeTable::TypeTable(DartConfiguration & _dart, Module & m)
  : dart(_dart), module(m) {
  FindUsedTypes finder;
  finder.runOnModule(module);
  auto iterEnd = finder.getTypes().end();
  for (auto iter = finder.getTypes().begin(); iter != iterEnd; ++iter) {
    Type * type = *iter;
    if (!type->isStructTy()) continue;
    types.insert(static_cast<StructType *>(type));
  }
}

void TypeTable::WriteTo(llvm::raw_ostream & stream) const {
  auto iterEnd = types.end();
  for (auto iter = types.begin(); iter != iterEnd; ++iter) {
    StructType * type = *iter;
    stream << "class " << dart.EscapeSymbol(type->getName()) << " {\n";
    for (auto i = 0; i < type->getNumElements(); i++) {
      Type * fieldType = type->getElementType(i);
      if (fieldType->isStructTy()) {
        StringRef name = static_cast<StructType *>(fieldType)->getName();
        stream << dart.GetTab() << dart.EscapeSymbol(name) << " "
          << dart.FieldName(i) << ";\n";
      } else if (fieldType->isSized()) {
        stream << dart.GetTab() << "ByteData " << dart.FieldName(i) << ";\n";
      }
    }
    stream << "}\n\n";
  }
}

raw_ostream & operator<<(raw_ostream & stream, const TypeTable & globals) {
  globals.WriteTo(stream);
  return stream;
}

}
