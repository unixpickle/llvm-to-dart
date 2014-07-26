#include "globals.hpp"

using namespace llvmtodart;

int main(int argc, const char * argv[]) {
  if (argc != 2) {
    errs() << "Usage: llvmtodart <some file.s>";
    return 1;
  }
  
  LLVMContext & context = llvm::getGlobalContext();
  llvm::SMDiagnostic err;
  Module * module = llvm::ParseIRFile(argv[1], err, context);
  if (!module) {
    err.print("llvmtodart", llvm::errs());
    return 1;
  }
  
  Globals globals(*module);
  outs() << globals;
  
  return 0;
}

