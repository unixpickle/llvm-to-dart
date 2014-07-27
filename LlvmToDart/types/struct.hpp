#ifndef __LLVMTODART_STRUCT_HPP__
#define __LLVMTODART_STRUCT_HPP__

#include "field.hpp"
#include "encodable.hpp"

namespace llvmtodart {

class Session;

class Struct : public Encodable {
public:
  Struct(Session &, const StructType &);
  Struct(const Struct &);
  ~Struct();
  
  Struct & operator=(const Struct &);
  
  virtual void Print(raw_ostream &) const;
  std::string GetName() const;
  
  unsigned int GetFieldCount() const;
  const Field & GetField(unsigned int i) const;
  
  bool operator==(const Struct &) const;
  bool operator!=(const Struct &) const;
  bool operator>(const Struct &) const;
  bool operator<(const Struct &) const;
  
protected:
  Session & session;
  const StructType & typeInfo;
  std::string className;
  std::vector<Field *> fields;
};

}

#endif
