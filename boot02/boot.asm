[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

   ; Charger le kernel (1 secteur → 512 octets) à 0x1000
    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0
    mov bx, 0x1000
    int 0x13
    jc disk_error

    ; -------------------------------
    ; Créer une GDT minimale
    ; -------------------------------
    lgdt [gdt_descriptor]

    ; Activer le bit PE (Protection Enable) dans CR0
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Saut far pour activer le mode protégé + CS
    jmp 0x08:protected_mode_start

; -------------------------------
; GDT (Global Descriptor Table)
; -------------------------------

gdt_start:
    ; NULL descriptor
    dq 0x0000000000000000

    ; Code segment descriptor: base=0, limit=4GB, type=code
    dq 0x00CF9A000000FFFF

    ; Data segment descriptor: base=0, limit=4GB, type=data
    dq 0x00CF92000000FFFF

gdt_descriptor:
    dw gdt_descriptor_end - gdt_start - 1
    dd gdt_start
gdt_descriptor_end:

; -------------------------------
; Passage en 32 bits
; -------------------------------

[BITS 32]
protected_mode_start:
    ; Initialiser les segments
    mov ax, 0x10    ; data segment = GDT[2]
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov esp, 0x90000

    jmp 0x08:0x1000  ; saut vers ton kernel (CS = GDT[1], offset = 0x1000)

disk_error:
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    jmp $

times 510 - ($ - $$) db 0
dw 0xAA55
