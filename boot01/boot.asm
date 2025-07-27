[BITS 16]
[ORG 0x7C00]

cli ; desactive les interruptions (par securite)

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00 ; stack qui pointe juste avant le bootloader

; ------------------------------
; 1. Affichage de "Hi!"
; ------------------------------
mov ah, 0x0E       ; BIOS teletype
mov al, 'H'
int 0x10

mov al, 'i'
int 0x10

mov al, '!'
int 0x10

; ------------------------------
; 2. Lire le 2e secteur (kernel)
; ------------------------------
mov ah, 0x02       ; fonction BIOS : lire secteur
mov al, 1          ; nombre de secteurs à lire
mov ch, 0          ; cylindre 0
mov cl, 2          ; secteur 2
mov dh, 0          ; tête 0
mov dl, 0          ; disque 0 (floppy dans QEMU)
mov bx, 0x1000     ; adresse mémoire où stocker
int 0x13           ; appel BIOS : lit le secteur 2 → 0x1000

; ------------------------------
; 3. Saut vers le kernel
; ------------------------------
jmp 0x0000:0x1000         ; saute à l'adresse du kernel

jc disk_error

disk_error:
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    jmp $

; ------------------------------
; 4. Remplissage + signature
; ------------------------------
times 510 - ($ - $$) db 0  ; remplissage avec 0 jusqu’à 510 octets
dw 0xAA55                  ; signature magique du bootloader
