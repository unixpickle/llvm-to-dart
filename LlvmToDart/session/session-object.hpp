#ifndef __LLVMTODART_SESSION_OBJECT_HPP__
#define __LLVMTODART_SESSION_OBJECT_HPP__

namespace llvmtodart {

class Session;

class SessionObject {
public:
  SessionObject(Session &);
  
  Session & GetSession() const;
  
private:
  Session & session;
};

}

#endif
