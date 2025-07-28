; outb.asm
; void outb(unsigned short port, unsigned char val);

global outb

section .text
outb:
    ; Arguments :
    ;   [esp + 4] = port (16 bits)
    ;   [esp + 8] = val  (8 bits)
    
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al         ; Écrire AL vers le port DX
    ret
