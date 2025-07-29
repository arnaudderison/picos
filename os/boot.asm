[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Charger le kernel (3 secteurs à partir du secteur 2) à 0x4000
    mov ah, 0x02        ; Fonction "read sectors"
    mov al, 10           ; 3 secteurs
    mov ch, 0           ; Cylinder
    mov cl, 2           ; Secteur 2
    mov dh, 0           ; Head
    mov dl, 0           ; Drive
    mov bx, 0x1000      ; Adresse de destination
    int 0x13
    jc disk_error       ; Si erreur → afficher 'E'

    ; Afficher 'O' pour dire "OK"
    mov ah, 0x0E
    mov al, 'O'
    int 0x10

    ; Charger la GDT
    lgdt [gdt_descriptor]

    ; Activer le bit PE dans CR0 pour entrer en mode protégé
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Saut far en 32 bits
    jmp 0x08:protected_mode_start

disk_error:
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    jmp $

; -------------------------------
; GDT
; -------------------------------

gdt_start:
    dq 0x0000000000000000         ; NULL
    dq 0x00CF9A000000FFFF         ; Code segment (0x08)
    dq 0x00CF92000000FFFF         ; Data segment (0x10)

gdt_descriptor:
    dw gdt_descriptor_end - gdt_start - 1
    dd gdt_start
gdt_descriptor_end:

; -------------------------------
; 32-bit entry point
; -------------------------------

[BITS 32]
protected_mode_start:
    mov ax, 0x10      ; Data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000  ; Stack top
    jmp 0x08:0x1000   ; Jump to kernel

; -------------------------------
; Signature du bootloader
; -------------------------------
times 510 - ($ - $$) db 0
dw 0xAA55
