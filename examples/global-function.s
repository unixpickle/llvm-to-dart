; ModuleID = 'global-function.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

define i32 @_Z10myFunctionif(i32 %myIntArg, float %myFloatArg) nounwind ssp uwtable {
  %1 = alloca i32, align 4
  %2 = alloca float, align 4
  store i32 %myIntArg, i32* %1, align 4
  store float %myFloatArg, float* %2, align 4
  %3 = load i32* %1, align 4
  %4 = load float* %2, align 4
  %5 = fptosi float %4 to i32
  %6 = add nsw i32 %3, %5
  ret i32 %6
}

define i32 @main() nounwind ssp uwtable {
  %1 = alloca i32, align 4
  store i32 0, i32* %1
  %2 = call i32 @_Z10myFunctionif(i32 3, float 2.500000e+00)
  ret i32 %2
}
