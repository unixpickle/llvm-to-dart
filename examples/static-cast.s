; ModuleID = 'static-cast.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.9.0"

%struct.Sub = type { i32 (...)**, %struct.SuperA, %struct.SuperB, i16 }
%struct.SuperA = type { i32, i8 }
%struct.SuperB = type { i32, i8 }

@_ZTV3Sub = linkonce_odr unnamed_addr constant [3 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI3Sub to i8*), i8* bitcast (void (%struct.Sub*)* @_ZN3Sub3fooEv to i8*)]
@_ZTVN10__cxxabiv121__vmi_class_type_infoE = external global i8*
@_ZTS3Sub = linkonce_odr constant [5 x i8] c"3Sub\00"
@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS6SuperA = linkonce_odr constant [8 x i8] c"6SuperA\00"
@_ZTI6SuperA = linkonce_odr unnamed_addr constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([8 x i8]* @_ZTS6SuperA, i32 0, i32 0) }
@_ZTS6SuperB = linkonce_odr constant [8 x i8] c"6SuperB\00"
@_ZTI6SuperB = linkonce_odr unnamed_addr constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([8 x i8]* @_ZTS6SuperB, i32 0, i32 0) }
@_ZTI3Sub = linkonce_odr unnamed_addr constant { i8*, i8*, i32, i32, i8*, i64, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([5 x i8]* @_ZTS3Sub, i32 0, i32 0), i32 0, i32 2, i8* bitcast ({ i8*, i8* }* @_ZTI6SuperA to i8*), i64 2050, i8* bitcast ({ i8*, i8* }* @_ZTI6SuperB to i8*), i64 4098 }

define i32 @main() ssp uwtable {
  %1 = alloca i32, align 4
  %s = alloca %struct.Sub, align 8
  %superPtrA = alloca %struct.SuperA*, align 8
  %superPtrB = alloca %struct.SuperB*, align 8
  %subPtr = alloca %struct.Sub*, align 8
  store i32 0, i32* %1
  call void @_ZN3SubC1Ev(%struct.Sub* %s) nounwind
  call void @_ZN3Sub3fooEv(%struct.Sub* %s)
  %2 = icmp eq %struct.Sub* %s, null
  br i1 %2, label %7, label %3

; <label>:3                                       ; preds = %0
  %4 = bitcast %struct.Sub* %s to i8*
  %5 = getelementptr inbounds i8* %4, i64 8
  %6 = bitcast i8* %5 to %struct.SuperA*
  br label %7

; <label>:7                                       ; preds = %3, %0
  %8 = phi %struct.SuperA* [ %6, %3 ], [ null, %0 ]
  store %struct.SuperA* %8, %struct.SuperA** %superPtrA, align 8
  %9 = icmp eq %struct.Sub* %s, null
  br i1 %9, label %14, label %10

; <label>:10                                      ; preds = %7
  %11 = bitcast %struct.Sub* %s to i8*
  %12 = getelementptr inbounds i8* %11, i64 16
  %13 = bitcast i8* %12 to %struct.SuperB*
  br label %14

; <label>:14                                      ; preds = %10, %7
  %15 = phi %struct.SuperB* [ %13, %10 ], [ null, %7 ]
  store %struct.SuperB* %15, %struct.SuperB** %superPtrB, align 8
  %16 = load %struct.SuperA** %superPtrA, align 8
  %17 = icmp eq %struct.SuperA* %16, null
  br i1 %17, label %22, label %18

; <label>:18                                      ; preds = %14
  %19 = bitcast %struct.SuperA* %16 to i8*
  %20 = getelementptr i8* %19, i64 -8
  %21 = bitcast i8* %20 to %struct.Sub*
  br label %23

; <label>:22                                      ; preds = %14
  br label %23

; <label>:23                                      ; preds = %22, %18
  %24 = phi %struct.Sub* [ %21, %18 ], [ null, %22 ]
  store %struct.Sub* %24, %struct.Sub** %subPtr, align 8
  %25 = load %struct.SuperB** %superPtrB, align 8
  %26 = icmp eq %struct.SuperB* %25, null
  br i1 %26, label %31, label %27

; <label>:27                                      ; preds = %23
  %28 = bitcast %struct.SuperB* %25 to i8*
  %29 = getelementptr i8* %28, i64 -16
  %30 = bitcast i8* %29 to %struct.Sub*
  br label %32

; <label>:31                                      ; preds = %23
  br label %32

; <label>:32                                      ; preds = %31, %27
  %33 = phi %struct.Sub* [ %30, %27 ], [ null, %31 ]
  store %struct.Sub* %33, %struct.Sub** %subPtr, align 8
  ret i32 32
}

define linkonce_odr void @_ZN3SubC1Ev(%struct.Sub* %this) unnamed_addr nounwind ssp inlinehint uwtable align 2 {
  %1 = alloca %struct.Sub*, align 8
  store %struct.Sub* %this, %struct.Sub** %1, align 8
  %2 = load %struct.Sub** %1
  call void @_ZN3SubC2Ev(%struct.Sub* %2) nounwind
  ret void
}

define linkonce_odr void @_ZN3Sub3fooEv(%struct.Sub* %this) unnamed_addr nounwind ssp uwtable align 2 {
  %1 = alloca %struct.Sub*, align 8
  store %struct.Sub* %this, %struct.Sub** %1, align 8
  %2 = load %struct.Sub** %1
  %3 = getelementptr inbounds %struct.Sub* %2, i32 0, i32 3
  store i16 2, i16* %3, align 2
  ret void
}

define linkonce_odr void @_ZN3SubC2Ev(%struct.Sub* %this) unnamed_addr nounwind ssp inlinehint uwtable align 2 {
  %1 = alloca %struct.Sub*, align 8
  store %struct.Sub* %this, %struct.Sub** %1, align 8
  %2 = load %struct.Sub** %1
  %3 = bitcast %struct.Sub* %2 to i8*
  %4 = getelementptr inbounds i8* %3, i64 8
  %5 = bitcast i8* %4 to %struct.SuperA*
  %6 = bitcast %struct.Sub* %2 to i8*
  %7 = getelementptr inbounds i8* %6, i64 16
  %8 = bitcast i8* %7 to %struct.SuperB*
  %9 = bitcast %struct.Sub* %2 to i8***
  store i8** getelementptr inbounds ([3 x i8*]* @_ZTV3Sub, i64 0, i64 2), i8*** %9
  ret void
}
