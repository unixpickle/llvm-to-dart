#include "session-object.hpp"

namespace llvmtodart {

SessionObject::SessionObject(Session & s) : session(s) {
}

Session & SessionObject::GetSession() const {
  return session;
}

}
