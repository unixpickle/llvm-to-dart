; ModuleID = 'global-class.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

%class.B = type { i32 (...)**, float, float }

@b = global %class.B zeroinitializer, align 8
@_ZTV1B = linkonce_odr unnamed_addr constant [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1B to i8*), i8* bitcast (void (%class.B*)* @_ZN1B10myFunctionEv to i8*), i8* bitcast (void (%class.B*)* @_ZN1B11myFunction2Ev to i8*), i8* bitcast (i64 (%class.B*)* @_ZN1B11myFunction3Ev to i8*)]
@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS1B = linkonce_odr constant [3 x i8] c"1B\00"
@_ZTI1B = linkonce_odr unnamed_addr constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8]* @_ZTS1B, i32 0, i32 0) }
@llvm.global_ctors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 65535, void ()* @_GLOBAL__I_a }]

define internal void @__cxx_global_var_init() section "__TEXT,__StaticInit,regular,pure_instructions" {
  call void @_ZN1BC1Ev(%class.B* @b)
  ret void
}

define linkonce_odr void @_ZN1BC1Ev(%class.B* %this) unnamed_addr ssp uwtable align 2 {
  %1 = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %1, align 8
  %2 = load %class.B** %1
  call void @_ZN1BC2Ev(%class.B* %2)
  ret void
}

define i32 @main() nounwind ssp uwtable {
  store float 3.000000e+00, float* getelementptr inbounds (%class.B* @b, i32 0, i32 1), align 4
  store float 2.500000e+00, float* getelementptr inbounds (%class.B* @b, i32 0, i32 2), align 4
  ret i32 0
}

define linkonce_odr void @_ZN1BC2Ev(%class.B* %this) unnamed_addr nounwind ssp uwtable align 2 {
  %1 = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %1, align 8
  %2 = load %class.B** %1
  %3 = bitcast %class.B* %2 to i8***
  store i8** getelementptr inbounds ([5 x i8*]* @_ZTV1B, i64 0, i64 2), i8*** %3
  %4 = getelementptr inbounds %class.B* %2, i32 0, i32 1
  store float 3.000000e+00, float* %4, align 4
  %5 = getelementptr inbounds %class.B* %2, i32 0, i32 2
  %6 = getelementptr inbounds %class.B* %2, i32 0, i32 1
  %7 = load float* %6, align 4
  %8 = fadd float %7, 2.000000e+00
  store float %8, float* %5, align 4
  ret void
}

define linkonce_odr void @_ZN1B10myFunctionEv(%class.B* %this) unnamed_addr nounwind ssp uwtable align 2 {
  %1 = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %1, align 8
  %2 = load %class.B** %1
  ret void
}

define linkonce_odr void @_ZN1B11myFunction2Ev(%class.B* %this) unnamed_addr nounwind ssp uwtable align 2 {
  %1 = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %1, align 8
  %2 = load %class.B** %1
  ret void
}

define linkonce_odr i64 @_ZN1B11myFunction3Ev(%class.B* %this) unnamed_addr nounwind ssp uwtable align 2 {
  %1 = alloca %class.B*, align 8
  store %class.B* %this, %class.B** %1, align 8
  %2 = load %class.B** %1
  ret i64 3
}

define internal void @_GLOBAL__I_a() section "__TEXT,__StaticInit,regular,pure_instructions" {
  call void @__cxx_global_var_init()
  ret void
}
