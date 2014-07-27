#ifndef __LLVMTODART_ARRAY_FIELD_HPP__
#define __LLVMTODART_ARRAY_FIELD_HPP__

#include "field.hpp"

namespace llvmtodart {

class ArrayField : public Field {
public:
  static ArrayField * CreateWithType(Session & s,
                                     const std::string & fieldName,
                                     Type * fieldType);
  
  ArrayField(Session & s, const std::string & fieldName, uint64_t elements,
             Field * sub);
  virtual ~ArrayField();
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintDeclaration(raw_ostream & stream,
                                const std::string & indent) const;
  virtual void PrintInitialization(raw_ostream & stream,
                                   const std::string & indent) const;
  virtual Field * Clone() const;
  
private:
  uint64_t elements;
  Field * subField;
};

}

#endif
