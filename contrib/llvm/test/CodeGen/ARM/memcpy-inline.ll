; RUN: llc < %s -mtriple=thumbv7-apple-ios -mcpu=cortex-a8 -pre-RA-sched=source -disable-post-ra | FileCheck %s

%struct.x = type { i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8 }

@src = external global %struct.x
@dst = external global %struct.x

@.str1 = private unnamed_addr constant [31 x i8] c"DHRYSTONE PROGRAM, SOME STRING\00", align 1
@.str2 = private unnamed_addr constant [36 x i8] c"DHRYSTONE PROGRAM, SOME STRING BLAH\00", align 1
@.str3 = private unnamed_addr constant [24 x i8] c"DHRYSTONE PROGRAM, SOME\00", align 1
@.str4 = private unnamed_addr constant [18 x i8] c"DHRYSTONE PROGR  \00", align 1
@.str5 = private unnamed_addr constant [7 x i8] c"DHRYST\00", align 1
@.str6 = private unnamed_addr constant [14 x i8] c"/tmp/rmXXXXXX\00", align 1
@spool.splbuf = internal global [512 x i8] zeroinitializer, align 16

define i32 @t0() {
entry:
; CHECK: t0:
; CHECK: vldr [[REG1:d[0-9]+]],
; CHECK: vstr [[REG1]], 
  call void @llvm.memcpy.p0i8.p0i8.i32(i8* getelementptr inbounds (%struct.x* @dst, i32 0, i32 0), i8* getelementptr inbounds (%struct.x* @src, i32 0, i32 0), i32 11, i32 8, i1 false)
  ret i32 0
}

define void @t1(i8* nocapture %C) nounwind {
entry:
; CHECK: t1:
; CHECK: vld1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r1]
; CHECK: vst1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r0]
; CHECK: adds r0, #15
; CHECK: adds r1, #15
; CHECK: vld1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r1]
; CHECK: vst1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r0]
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %C, i8* getelementptr inbounds ([31 x i8]* @.str1, i64 0, i64 0), i64 31, i32 1, i1 false)
  ret void
}

define void @t2(i8* nocapture %C) nounwind {
entry:
; CHECK: t2:
; CHECK: ldr [[REG2:r[0-9]+]], [r1, #32]
; CHECK: str [[REG2]], [r0, #32]
; CHECK: vld1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r1]
; CHECK: vst1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r0]
; CHECK: adds r0, #16
; CHECK: adds r1, #16
; CHECK: vld1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r1]
; CHECK: vst1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r0]
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %C, i8* getelementptr inbounds ([36 x i8]* @.str2, i64 0, i64 0), i64 36, i32 1, i1 false)
  ret void
}

define void @t3(i8* nocapture %C) nounwind {
entry:
; CHECK: t3:
; CHECK: vld1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r1]
; CHECK: vst1.8 {d{{[0-9]+}}, d{{[0-9]+}}}, [r0]
; CHECK: adds r0, #16
; CHECK: adds r1, #16
; CHECK: vld1.8 {d{{[0-9]+}}}, [r1]
; CHECK: vst1.8 {d{{[0-9]+}}}, [r0]
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %C, i8* getelementptr inbounds ([24 x i8]* @.str3, i64 0, i64 0), i64 24, i32 1, i1 false)
  ret void
}

define void @t4(i8* nocapture %C) nounwind {
entry:
; CHECK: t4:
; CHECK: vld1.8 {[[REG3:d[0-9]+]], [[REG4:d[0-9]+]]}, [r1]
; CHECK: vst1.8 {[[REG3]], [[REG4]]}, [r0]
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %C, i8* getelementptr inbounds ([18 x i8]* @.str4, i64 0, i64 0), i64 18, i32 1, i1 false)
  ret void
}

define void @t5(i8* nocapture %C) nounwind {
entry:
; CHECK: t5:
; CHECK: movs [[REG5:r[0-9]+]], #0
; CHECK: strb [[REG5]], [r0, #6]
; CHECK: movw [[REG6:r[0-9]+]], #21587
; CHECK: strh [[REG6]], [r0, #4]
; CHECK: ldr [[REG7:r[0-9]+]], 
; CHECK: str [[REG7]]
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %C, i8* getelementptr inbounds ([7 x i8]* @.str5, i64 0, i64 0), i64 7, i32 1, i1 false)
  ret void
}

define void @t6() nounwind {
entry:
; CHECK: t6:
; CHECK: vld1.8 {[[REG8:d[0-9]+]]}, [r0]
; CHECK: vstr [[REG8]], [r1]
; CHECK: adds r1, #6
; CHECK: adds r0, #6
; CHECK: vld1.8
; CHECK: vst1.16
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* getelementptr inbounds ([512 x i8]* @spool.splbuf, i64 0, i64 0), i8* getelementptr inbounds ([14 x i8]* @.str6, i64 0, i64 0), i64 14, i32 1, i1 false)
  ret void
}

%struct.Foo = type { i32, i32, i32, i32 }

define void @t7(%struct.Foo* nocapture %a, %struct.Foo* nocapture %b) nounwind {
entry:
; CHECK: t7
; CHECK: vld1.32
; CHECK: vst1.32
  %0 = bitcast %struct.Foo* %a to i8*
  %1 = bitcast %struct.Foo* %b to i8*
  tail call void @llvm.memcpy.p0i8.p0i8.i32(i8* %0, i8* %1, i32 16, i32 4, i1 false)
  ret void
}

declare void @llvm.memcpy.p0i8.p0i8.i32(i8* nocapture, i8* nocapture, i32, i32, i1) nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture, i64, i32, i1) nounwind
