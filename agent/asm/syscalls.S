    .intel_syntax noprefix
    .text

    .globl write

write:
    mov rax, 1
    mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx
    syscall
    ret