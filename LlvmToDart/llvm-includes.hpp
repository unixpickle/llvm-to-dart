//
//  llvm-includes.hpp
//  LlvmToDart
//
//  Created by Alex Nichol on 7/26/14.
//  Copyright (c) 2014 Alex Nichol. All rights reserved.
//

#ifndef __LLVMTODART_LLVM_INCLUDES_HPP__
#define __LLVMTODART_LLVM_INCLUDES_HPP__

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <llvm/Support/SourceMgr.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Analysis/FindUsedTypes.h>
#include <string>

namespace llvmtodart {

using llvm::Module;
using llvm::StringRef;
using llvm::SetVector;
using llvm::raw_ostream;
using llvm::FindUsedTypes;
using llvm::LLVMContext;
using llvm::DataLayout;
using llvm::StructLayout;
using llvm::outs;
using llvm::errs;
using std::string;

}

#endif
