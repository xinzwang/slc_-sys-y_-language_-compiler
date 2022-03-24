    .arch armv8-a
    .file ""
    .text
    .global main
    .arm
    .fpu neon
.global_vars:
main:
    @ thread_stack_size=128
    @ stack_size=128
.main_pre:
    @ function preprocess
    @ enlarge stack
    push {r11, lr}
    movw r0, #0
    movt r0, #4096
    mov r1, #1
    bl malloc
    movw r11, #0
    movt r11, #4096
    add r12, r0, r11
    pop {r11, lr}
    mov r11, sp
    mov sp, r12
    push {r11}
    @ save callee-save registers and lr
    push {r11, lr}
    @ allocate stack space
    sub sp, sp, #128
    @ process function args
.main_entry:
    @ ret i32 1 
    mov r0, #1
    @ function return
    @ reclaim stack space
    add sp, sp, #128
    @ restore callee-save registers and pc
    pop {r11, pc}
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
