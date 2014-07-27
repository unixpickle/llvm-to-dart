#ifndef __LLVMTODART_ENCODABLE_HPP__
#define __LLVMTODART_ENCODABLE_HPP__

#include "llvm-includes.hpp"

namespace llvmtodart {

class Encodable {
public:
  virtual void Print(raw_ostream & stream) const = 0;
};

raw_ostream & operator<<(raw_ostream &, const Encodable &);

}

#endif
