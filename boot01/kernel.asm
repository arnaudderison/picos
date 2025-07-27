[BITS 16]         ; On reste en mode réel
[ORG 0x1000]      ; L'adresse où le bootloader nous charge

start:
    mov ah, 0x0E
    mov al, 'K'
    int 0x10

    mov al, 'E'
    int 0x10

    mov al, 'R'
    int 0x10

    mov al, 'N'
    int 0x10

    mov al, 'E'
    int 0x10

    mov al, 'L'
    int 0x10

hang:
    jmp hang       ; Boucle infinie


times 510 - ($ - $$) db 0  ; remplissage avec 0 jusqu’à 510 octets
dw 0xAA55                  ; signature magique du bootloader
