//
//  main.cpp
//  LlvmToDart
//
//  Created by Alex Nichol on 7/26/14.
//  Copyright (c) 2014 Alex Nichol. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <iostream>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;

int main(int argc, const char * argv[]) {
  if (argc != 2) {
    cerr << "Usage: llvmtodart <some file.s>" << endl;
    return 1;
  }
  
  llvm::LLVMContext & context = llvm::getGlobalContext();
  llvm::SMDiagnostic err;
  llvm::Module * module = llvm::ParseIRFile(argv[1], err, context);
  
  if (!module) {
    err.print("llvmtodart", llvm::errs());
    return 1;
  }
  
  return 0;
}

