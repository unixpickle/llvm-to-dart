; ModuleID = 'func-ptr.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

%struct.MyClass = type { i16 (i32, i8)* }

define signext i16 @_Z10myFunctionic(i32 %a, i8 signext %b) nounwind ssp uwtable {
  %1 = alloca i32, align 4
  %2 = alloca i8, align 1
  store i32 %a, i32* %1, align 4
  store i8 %b, i8* %2, align 1
  %3 = load i32* %1, align 4
  %4 = trunc i32 %3 to i16
  %5 = sext i16 %4 to i32
  %6 = load i8* %2, align 1
  %7 = sext i8 %6 to i16
  %8 = sext i16 %7 to i32
  %9 = add nsw i32 %5, %8
  %10 = trunc i32 %9 to i16
  ret i16 %10
}

define i32 @main() ssp uwtable {
  %1 = alloca i32, align 4
  %c = alloca %struct.MyClass, align 8
  store i32 0, i32* %1
  %2 = getelementptr inbounds %struct.MyClass* %c, i32 0, i32 0
  store i16 (i32, i8)* @_Z10myFunctionic, i16 (i32, i8)** %2, align 8
  %3 = getelementptr inbounds %struct.MyClass* %c, i32 0, i32 0
  %4 = load i16 (i32, i8)** %3, align 8
  %5 = call signext i16 %4(i32 3, i8 signext 97)
  %6 = sext i16 %5 to i32
  ret i32 %6
}
