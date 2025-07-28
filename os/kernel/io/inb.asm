; inb.asm
; void inb(unsigned short port);

global outb

section .text
inb:
    ; Arguments :
    ;   [esp + 4] = port (16 bits)
    
    mov edx, [esp + 4]
    xor eax, eax
    in al, edx
    ret
