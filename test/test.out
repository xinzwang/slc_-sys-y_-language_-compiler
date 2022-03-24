    .arch armv7-a
    .file "./test"
    .text
    .global main
    .arm
    .fpu neon
    .global b
    .global cc
.global_vars:
    .long b
    .long cc
main:
    @ stack_size=128
main:
    push {fp, lr}
    add    fp, sp, #4
    sub    sp, sp, #232
.main_block_1
    @    %a:-1 
    @    %a:-1 
    mov    r0, #0
    str    r0, [fp, #-4]
    @    %m:-1 
    @    %m:-1 
    mov    r0, #0
    str    r0, [fp, #-8]
    @    %n:-1 
    @    %n:-1 
    mov    r0, #0
    str    r0, [fp, #-12]
    @    %j:-1 
    @    %j:-1 
    mov    r0, #0
    str    r0, [fp, #-16]
    @    %k:-1 
    @    %k:-1 
    mov    r0, #0
    str    r0, [fp, #-20]
    @    %1:12 %m:-1 %n:-1 
    ldr    r0, [fp, #-8]
    ldr    r1, [fp, #-12]
    add    r12, r0, r1
    @    %a:-1 %1:12 
    str    r12, [fp, #-4]
    @    %m:-1 
    ldr    r1, [sp, #-8]
    mov     r0, r1
    sub    sp, fp, #4
    pop    {fp, pc}
    .data
b:
    .long 0
cc:
    .long 5
    .long 5
    .long 5
