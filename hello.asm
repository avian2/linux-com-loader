    call   greet
    mov    rax, 60
    mov    rdi, 0
    syscall

# A function call, just to show off our working stack.
greet:
    mov     rax, 1
    mov     rdi, 1
    mov     rsi, msg
    mov     rdx, 14
    syscall
    ret

    msg db      "Hello, World!", 10
