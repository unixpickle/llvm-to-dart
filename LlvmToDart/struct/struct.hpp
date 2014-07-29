#ifndef __LLVMTODART_STRUCT_HPP__
#define __LLVMTODART_STRUCT_HPP__

#include "type.hpp"
#include "encodable.hpp"
#include "session-object.hpp"
#include "struct-field.hpp"

namespace llvmtodart {

class Session;

class Struct : public Encodable, public SessionObject {
public:
  Struct(Session &, llvm::StructType &, StringRef name);
  ~Struct();
  
  Struct(const Struct &) = delete;
  Struct & operator=(const Struct &) = delete;
  
  virtual void Print(raw_ostream &) const;
  StringRef GetName() const;
  
  unsigned int GetFieldCount() const;
  const StructField & GetField(unsigned int i) const;
  
protected:
  string name;
  const llvm::StructType & typeInfo;
  std::vector<StructField *> fields;
  
private:
  void PrintFieldIndexMethod(raw_ostream &) const;
  void PrintFieldAccessMethod(raw_ostream &) const;
};

}

#endif
