[BITS 32]
[GLOBAL _start]
[EXTERN kernel_main]

_start:
    ; Initialisation basique
    cli
    mov esp, 0x90000    ; Stack pointer
    
    ; Appeler le kernel principal
    call kernel_main

halt:
    hlt
    jmp halt