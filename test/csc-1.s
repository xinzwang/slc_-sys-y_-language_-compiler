    .arch armv8-a
    .file ""
    .text
    .global fun
    .global main
    .arm
    .fpu neon
    .global cb
    .global a
    .global b
.global_vars:
    .long cb
    .long a
    .long b
fun:
    @ thread_stack_size=128
    @ stack_size=128
.fun_pre:
    @ function preprocess
    @ save callee-save registers and lr
    push {r11, lr}
    @ allocate stack space
    sub sp, sp, #128
    @ process function args
.fun_entry:
    @ Br GT i32 %0i32 0 <label> %1 <label> %11 
    cmp r0, #0
    ble .fun_11+0
.fun_entry_branch_1:
    @ branch instruction eliminated
.fun_entry_branch_2:
    @ branch instruction eliminated
.fun_1:
    @ i32 %2  = Sub i32 %0i32 0 
    sub r1, r0, #0
    @ i32 %3  = Load i32* @a 
    adrl r11, .global_vars+4
    ldr r12, [r11, #0]
    ldr r0, [r12, #0]
    @ i32 %4  = Add i32 %2 i32 %3 
    add r0, r1, r0, lsl #0
    @ i32 %5  = Load [ 5 x i32]* @cb i32 %4 i32 2 
    adrl r11, .global_vars+0
    ldr r12, [r11, #0]
    ldr r1, [r12, +r0, lsl #2]
    @ i32 %6  = Call getint 
    push {r1}
    bl getint
    pop {r1}
    @ Store i32 %6 [ 5 x i32]* @b i32 %5 i32 2 
    adrl r11, .global_vars+8
    ldr lr, [r11, #0]
    str r0, [lr, +r1, lsl #2]
    @ i32 %7  = Sub i32 %5 i32 %6 
    sub r0, r1, r0, lsl #0
    @ i32 %8  = Sub i32 %7 i32 1 
    sub r1, r0, #1
    @ i32 %9  = Call fun i32 %8 
    push {r0}
    mov r0, r1
    bl fun
    mov r1, r0
    pop {r0}
    @ i32 %10  = Mul i32 %7 i32 %9 
    mul r0, r0, r1
    @ ret i32 %10 
    @ function return
    @ reclaim stack space
    add sp, sp, #128
    @ restore callee-save registers and pc
    pop {r11, pc}
.fun_11:
    @ ret i32 %0
    @ function return
    @ reclaim stack space
    add sp, sp, #128
    @ restore callee-save registers and pc
    pop {r11, pc}
.fun_post:
    @ function postcode
main:
    @ thread_stack_size=128
    @ stack_size=148
.main_pre:
    @ function preprocess
    @ enlarge stack
    push {r4, r11, lr}
    movw r0, #0
    movt r0, #4096
    mov r1, #1
    bl malloc
    movw r11, #0
    movt r11, #4096
    add r12, r0, r11
    pop {r4, r11, lr}
    mov r11, sp
    mov sp, r12
    push {r11}
    @ save callee-save registers and lr
    push {r4, r11, lr}
    @ allocate stack space
    sub sp, sp, #148
    @ process function args
.main_entry:
    @ [ 5 x i32]* %0  = Alloca 
    add r3, sp, #128
    @ i32 %1  = Call getint 
    push {r3}
    bl getint
    pop {r3}
    @ Store i32 %1 i32* @a 
    adrl r11, .global_vars+4
    ldr lr, [r11, #0]
    str r0, [lr, #0]
    @ i32 %2  = Call getint 
    push {r3}
    bl getint
    pop {r3}
    @ Store i32 %2 [ 5 x i32]* %0 
    str r0, [r3, #0]
    @ i32 %3  = Call getint 
    push {r3}
    bl getint
    pop {r3}
    @ Store i32 %3 [ 5 x i32]* %0 i32 4 
    str r0, [r3, #4]
    @ i32 %4  = Call getint 
    push {r3}
    bl getint
    pop {r3}
    @ Store i32 %4 [ 5 x i32]* %0 i32 8 
    str r0, [r3, #8]
    @ i32 %5  = Call getint 
    push {r3}
    bl getint
    pop {r3}
    @ Store i32 %5 [ 5 x i32]* %0 i32 12 
    str r0, [r3, #12]
    @ i32 %6  = Call getint 
    push {r3}
    bl getint
    pop {r3}
    @ Store i32 %6 [ 5 x i32]* %0 i32 16 
    str r0, [r3, #16]
    @ i32 %7  = Load [ 5 x i32]* %0 i32 4 
    ldr r0, [r3, #4]
    @ i32 %8  = Load [ 5 x i32]* %0 i32 %7 i32 2 
    ldr r1, [r3, +r0, lsl #2]
    @ i32 %9  = Load i32* @a 
    adrl r11, .global_vars+4
    ldr r12, [r11, #0]
    ldr r4, [r12, #0]
    @ i32 %10  = Add i32 %9 i32 10 
    add r0, r4, #10
    @ i32 %11  = Mul i32 %10 i32 %9 
    mul r0, r0, r4
    @ i32 %12  = Sub i32 %8 i32 %11 
    sub r0, r1, r0, lsl #0
    @ i32 %13  = Sub i32 %12 i32 8 
    sub r0, r0, #8
    @ Store i32 %13 [ 5 x i32]* %0 i32 4 
    str r0, [r3, #4]
    @ Br <label> %14 
.main_entry_branch_1:
    @ %15 <= 
    mov r0, #0
    @ branch instruction eliminated
.main_14:
    @ i32 %15  = PHI i32 %35 <label> %33 i32 0 <label> %entry 
    @ i32 %16  = PHI i32 %34 <label> %33 
    @ Br LT i32 %15 i32 5 <label> %17 <label> %36 
    cmp r0, #5
    bge .main_36+0
.main_14_branch_1:
    @ branch instruction eliminated
.main_14_branch_2:
    @ branch instruction eliminated
.main_17:
    @ i32 %18  = And i32 %15 i32 1 
    and r2, r0, #1
    @ Br EQ i32 %18 i32 0 <label> %19 <label> %22 
    cmp r2, #0
    bne .main_22+0
.main_17_branch_1:
    @ branch instruction eliminated
.main_17_branch_2:
    @ branch instruction eliminated
.main_19:
    @ i32 %20  = Load [ 5 x i32]* @cb i32 %15 i32 2 
    adrl r11, .global_vars+0
    ldr r12, [r11, #0]
    ldr r2, [r12, +r0, lsl #2]
    @ i32 %21  = Add i32 %16 i32 %20 
    add r1, r1, r2, lsl #0
    @ Br <label> %25 
.main_19_branch_1:
    @ %26 <= %21
    b .main_25+0
.main_22:
    @ i32 %23  = Load [ 5 x i32]* @b i32 %15 i32 2 
    adrl r11, .global_vars+8
    ldr r12, [r11, #0]
    ldr r2, [r12, +r0, lsl #2]
    @ i32 %24  = Add i32 %16 i32 %23 
    add r1, r1, r2, lsl #0
    @ Br <label> %25 
.main_22_branch_1:
    @ %26 <= %24
    @ branch instruction eliminated
.main_25:
    @ i32 %26  = PHI i32 %21 <label> %19 i32 %24 <label> %22 
    @ i32 %27  = Load [ 5 x i32]* %0 i32 %15 i32 2 
    ldr r2, [r3, +r0, lsl #2]
    @ i32 %28  = Add i32 %26 i32 %27 
    add r1, r1, r2, lsl #0
    @ Br GT i32 %28 i32 3 <label> %29 <label> %31 
    cmp r1, #3
    ble .main_31+0
.main_25_branch_1:
    @ branch instruction eliminated
.main_25_branch_2:
    @ branch instruction eliminated
.main_29:
    @ i32 %30  = Sub i32 %28 i32 %9 
    sub r1, r1, r4, lsl #0
    @ Br <label> %33 
.main_29_branch_1:
    @ %34 <= %30
    b .main_33+0
.main_31:
    @ i32 %32  = Sub i32 %28 i32 0 
    @ Br <label> %33 
.main_31_branch_1:
    @ %34 <= %32
    @ branch instruction eliminated
.main_33:
    @ i32 %34  = PHI i32 %30 <label> %29 i32 %32 <label> %31 
    @ i32 %35  = Add i32 %15 i32 1 
    add r0, r0, #1
    @ Br <label> %14 
.main_33_branch_1:
    @ %15 <= %35
    @ %16 <= %34
    b .main_14+0
.main_36:
    @ i32 %37  = Call fun i32 %16 
    mov r0, r1
    bl fun
    @ Call putint i32 %37 
    push {r0, r1, r2, r3}
    bl putint
    pop {r0, r1, r2, r3}
    @ ret i32 0 
    mov r0, #0
    @ function return
    @ reclaim stack space
    add sp, sp, #148
    @ restore callee-save registers and pc
    pop {r4, r11, pc}
    @ enlarged stack reclaim
    pop {r12}
    mov sp, r12
.main_post:
    @ function postcode
__mtstart:
    movw r11, #0
    movt r11, #256
    sub sp, sp, r11
    push {r0, r1, r2, r3}
    mov r3, r7
    mov r2, #4
.__mtstart_1:
    sub r2, r2, #1
    cmp r2, #0
    beq .__mtstart_2+0
    mov r7, #120
    mov r0, #273
    mov r1, sp
    swi #0
    cmp r0, #0
    bne .__mtstart_1+0
.__mtstart_2:
    mov r10, r2
    mov r7, r3
    pop {r0, r1, r2, r3}
    movw r11, #0
    movt r11, #256
    add sp, sp, r11
    mov pc, lr
__mtend:
    cmp r10, #0
    beq .__mtend_2+0
.__mtend_1:
    mov r7, #1
    swi #0
.__mtend_2:
    push {r0, r1, r2, r3}
    mov r1, #4
.__mtend_3:
    sub r1, r1, #1
    cmp r1, #0
    beq .__mtend_4+0
    push {r1, lr}
    sub sp, sp, #4
    mov r0, sp
    bl wait
    add sp, sp, #4
    pop {r1, lr}
    b .__mtend_3+0
.__mtend_4:
    pop {r0, r1, r2, r3}
    mov r10, #0
    mov pc, lr
    .data
cb:
    .long 1
    .long 2
    .long 3
    .long 4
    .long 5
a:
    .long 6
b:
    .long 11
    .long 8
    .long 10
    .long 7
    .long 9
