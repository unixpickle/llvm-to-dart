#include "type.hpp"
#include "session.hpp"
#include "scalar-type.hpp"
#include "function-type.hpp"
#include "array-type.hpp"
#include "struct-type.hpp"

namespace llvmtodart {

Type * Type::Create(Session & s, llvm::Type * type) {
  Type * res = ScalarType::Create(s, type);
  if (!res) res = FunctionType::Create(s, type);
  if (!res) res = StructType::Create(s, type);
  if (!res) res = ArrayType::Create(s, type);
  return res;
}

void Type::PrintDeclaration(raw_ostream & stream, StringRef name) const {
  stream << GetSession().GetIndentation() << GetTypeName() << " " << name
    << ";";
}

bool Type::IsStructure() const {
  return false;
}

}
