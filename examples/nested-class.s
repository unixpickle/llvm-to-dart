; ModuleID = 'nested-class.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

%struct.MainClass = type { i32 }
%struct.MainClass.0 = type { %struct.SomeClass, i32, i64, float, double, %struct.SomeClass, [3 x %struct.SomeClass], [3 x [2 x %struct.SomeClass]] }
%struct.SomeClass = type { [8 x i8] }

define void @_Z11myFunction1v() nounwind ssp uwtable {
  %c = alloca %struct.MainClass, align 4
  %1 = getelementptr inbounds %struct.MainClass* %c, i32 0, i32 0
  store i32 2, i32* %1, align 4
  ret void
}

define void @_Z11myFunction2v() nounwind ssp uwtable {
  %c = alloca %struct.MainClass.0, align 8
  %1 = getelementptr inbounds %struct.MainClass.0* %c, i32 0, i32 1
  store i32 2, i32* %1, align 4
  %2 = getelementptr inbounds %struct.MainClass.0* %c, i32 0, i32 2
  store i64 34359738368, i64* %2, align 8
  %3 = getelementptr inbounds %struct.MainClass.0* %c, i32 0, i32 3
  store float 0x40091EB860000000, float* %3, align 4
  %4 = getelementptr inbounds %struct.MainClass.0* %c, i32 0, i32 4
  store double 3.141500e+00, double* %4, align 8
  ret void
}

define i32 @main() nounwind ssp uwtable {
  %1 = alloca i32, align 4
  store i32 0, i32* %1
  call void @_Z11myFunction1v()
  call void @_Z11myFunction2v()
  ret i32 0
}
