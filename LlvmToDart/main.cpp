#include "global-table.hpp"
#include "struct-table.hpp"

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
  
  Settings dart;
  
  StructTable types(dart, *module);
  outs() << types << "\n";
  
  GlobalTable globals(*module);
  outs() << globals << "\n";
  
  outs().flush();
  
  return 0;
}

