[BITS 32]
[GLOBAL _start]
[EXTERN kernel_main]

_start:
    cli
    mov esp, 0x90000       ; stack
    call kernel_main
    
halt:
    hlt
    jmp halt

