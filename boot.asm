[BITS 16]          ; Code 16 bits (mode réel)
[ORG 0x7C00]       ; BIOS charge ici

mov ah, 0x0E       ; Mode "teletype"
mov al, 'H'        ; Caractère à afficher
int 0x10           ; Appel BIOS → affiche le caractère

jmp $              ; Boucle infinie

times 510 - ($ - $$) db 0 ; Remplissage jusqu'à 510 octets
dw 0xAA55                 ; Signature obligatoire
