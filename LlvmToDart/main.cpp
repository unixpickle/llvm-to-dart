#include "session.hpp"

using namespace llvmtodart;

int main(int argc, const char * argv[]) {
  if (argc != 2) {
    errs() << "Usage: llvmtodart <some_file.s>\n";
    return 1;
  }
  LLVMContext & context = llvm::getGlobalContext();
  llvm::SMDiagnostic err;
  Module * module = llvm::ParseIRFile(argv[1], err, context);
  if (!module) {
    err.print("llvmtodart", llvm::errs());
    return 1;
  }
  
  Settings settings;
  Session session(settings, *module);
  
  session.GetStructs().Print(outs());
  outs() << "\n";
  
  session.GetGlobals().Print(outs());
  outs() << "\n";
  outs().flush();
  
  return 0;
}

