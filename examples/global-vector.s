; ModuleID = 'global-vector.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

@myGlobal = global i32 3, align 4
@myGlobalList = global [2 x i32] [i32 2, i32 1], align 4

define i32 @main() nounwind ssp uwtable {
  %1 = alloca i32, align 4
  %ptr = alloca i32*, align 8
  store i32 0, i32* %1
  store i32 4, i32* @myGlobal, align 4
  store i32* getelementptr inbounds ([2 x i32]* @myGlobalList, i32 0, i32 0), i32** %ptr, align 8
  %2 = load i32** %ptr, align 8
  store i32 2, i32* %2, align 4
  %3 = load i32** %ptr, align 8
  %4 = getelementptr inbounds i32* %3, i32 1
  store i32* %4, i32** %ptr, align 8
  %5 = load i32** %ptr, align 8
  store i32 3, i32* %5, align 4
  ret i32 0
}
