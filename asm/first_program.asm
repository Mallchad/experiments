BITS 64

section .text

global _start
_start:
    main_loop:
    xor rax, rax
    add rax, 69
    jmp main_loop

    xor edi, edi
    mov   eax, 231     ; __NR_exit_group
    syscall
