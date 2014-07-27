#ifndef __LLVMTODART_ARRAY_FIELD_HPP__
#define __LLVMTODART_ARRAY_FIELD_HPP__

namespace llvmtodart {

class ArrayField : public Field {
public:
  static ArrayField * CreateWithType(Module & m,
                                     const std::string & fieldName,
                                     Type * fieldType);
  
  ArrayField(const std::string & fieldName, const std::string & structName);
  
  virtual void PrintType(raw_ostream & stream) const;
  virtual void PrintDeclaration(raw_ostream & stream,
                                const std::string & indent) const;
  virtual void PrintInitialization(raw_ostream & stream,
                                   const std::string & indent) const;
  virtual Field * Clone() const;
  
private:
  std::string structName;
};

}

#endif
