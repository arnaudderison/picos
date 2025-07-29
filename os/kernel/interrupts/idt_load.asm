; idt_load.asm
[bits 32]

[global idt_load]
idt_load:
    mov eax, [esp + 4] ; arg
    lidt [eax]         ; charger l'IDT avec l'instruction CPU
    ret
