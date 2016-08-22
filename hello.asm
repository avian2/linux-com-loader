section .data
    msg db      "Hello, World!", 10

section .text
    call   greet
    mov    rax, 60
    mov    rdi, 0
    syscall

greet:
    mov     rax, 1
    mov     rdi, 1
    mov     rsi, msg
    mov     rdx, 14
    syscall
    ret
