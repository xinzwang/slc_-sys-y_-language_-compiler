; ModuleID = 'test1.c'
source_filename = "test1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@b = global i32 0, align 4
@c = global [5 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5], align 16
@d = global [2 x [3 x i32]] [[3 x i32] [i32 1, i32 3, i32 5], [3 x i32] [i32 2, i32 4, i32 6]], align 16
@ca = constant i32 0, align 4
@cb = constant i32 0, align 4
@cc = constant [5 x i32] [i32 0, i32 0, i32 3, i32 4, i32 5], align 16
@cd = constant [2 x [3 x i32]] [[3 x i32] [i32 1, i32 3, i32 5], [3 x i32] [i32 2, i32 4, i32 6]], align 16
@main.mc = private unnamed_addr constant [3 x i32] [i32 3, i32 6, i32 9], align 4
@main.me = private unnamed_addr constant [2 x [3 x i32]] [[3 x i32] [i32 33, i32 26, i32 21], [3 x i32] [i32 90, i32 45, i32 13]], align 16
@a = common global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca [3 x i32], align 4
  %5 = alloca [2 x [4 x [6 x i32]]], align 16
  %6 = alloca i32, align 4
  %7 = alloca [2 x [3 x i32]], align 16
  store i32 0, i32* %3, align 4
  %8 = bitcast [3 x i32]* %4 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* bitcast ([3 x i32]* @main.mc to i8*), i64 12, i32 4, i1 false)
  store i32 4, i32* %6, align 4
  %9 = load i32, i32* @b, align 4
  store i32 %9, i32* %2, align 4
  %10 = load i32, i32* %2, align 4
  %11 = getelementptr inbounds [3 x i32], [3 x i32]* %4, i64 0, i64 2
  store i32 %10, i32* %11, align 4
  %12 = getelementptr inbounds [3 x i32], [3 x i32]* %4, i64 0, i64 2
  %13 = load i32, i32* %12, align 4
  %14 = getelementptr inbounds [2 x [4 x [6 x i32]]], [2 x [4 x [6 x i32]]]* %5, i64 0, i64 1
  %15 = getelementptr inbounds [4 x [6 x i32]], [4 x [6 x i32]]* %14, i64 0, i64 3
  %16 = getelementptr inbounds [6 x i32], [6 x i32]* %15, i64 0, i64 4
  store i32 %13, i32* %16, align 8
  %17 = bitcast [2 x [3 x i32]]* %7 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %17, i8* bitcast ([2 x [3 x i32]]* @main.me to i8*), i64 24, i32 16, i1 false)
  %18 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %7, i64 0, i64 0
  %19 = getelementptr inbounds [3 x i32], [3 x i32]* %18, i64 0, i64 0
  %20 = load i32, i32* %19, align 16
  %21 = call i32 (i32, ...) bitcast (i32 (...)* @print to i32 (i32, ...)*)(i32 %20)
  ret i32 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

declare i32 @print(...) #2

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"}
