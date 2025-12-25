    .intel_syntax noprefix
    .text

    .globl write_agent

write_agent:
    mov rax, 1
    mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx
    syscall
    ret