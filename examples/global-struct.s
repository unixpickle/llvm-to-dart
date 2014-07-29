; ModuleID = 'global-struct.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

%struct.A = type { i32, i32 }

@a = global %struct.A zeroinitializer, align 4
@llvm.global_ctors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 65535, void ()* @_GLOBAL__I_a }]

define internal void @__cxx_global_var_init() section "__TEXT,__StaticInit,regular,pure_instructions" {
  call void @_ZN1AC1Ev(%struct.A* @a)
  ret void
}

define linkonce_odr void @_ZN1AC1Ev(%struct.A* %this) unnamed_addr ssp uwtable align 2 {
  %1 = alloca %struct.A*, align 8
  store %struct.A* %this, %struct.A** %1, align 8
  %2 = load %struct.A** %1
  call void @_ZN1AC2Ev(%struct.A* %2)
  ret void
}

define i32 @main() nounwind ssp uwtable {
  %1 = alloca i32, align 4
  store i32 0, i32* %1
  store i32 13, i32* getelementptr inbounds (%struct.A* @a, i32 0, i32 0), align 4
  store i32 37, i32* getelementptr inbounds (%struct.A* @a, i32 0, i32 1), align 4
  ret i32 0
}

define linkonce_odr void @_ZN1AC2Ev(%struct.A* %this) unnamed_addr nounwind ssp uwtable align 2 {
  %1 = alloca %struct.A*, align 8
  store %struct.A* %this, %struct.A** %1, align 8
  %2 = load %struct.A** %1
  ret void
}

define internal void @_GLOBAL__I_a() section "__TEXT,__StaticInit,regular,pure_instructions" {
  call void @__cxx_global_var_init()
  ret void
}
