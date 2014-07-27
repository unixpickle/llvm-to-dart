#ifndef __LLVMTODART_SESSION_HPP__
#define __LLVMTODART_SESSION_HPP__

#include "settings.hpp"
#include "global-table.hpp"
#include "struct-table.hpp"

namespace llvmtodart {

class Session {
public:
  Session(const Settings &, Module &);
  
  const Settings & GetSettings() const;
  Module & GetModule() const;
  
  const GlobalTable & GetGlobals() const;
  const StructTable & GetStructs() const;
  
private:
  const Settings & settings;
  Module & module;
  
  StructTable structs;
  GlobalTable globals;
};

}

#endif
