#include "encodable.hpp"

namespace llvmtodart {

raw_ostream & operator<<(raw_ostream & a, const Encodable & e) {
  e.Print(a);
  return a;
}

}
