#include "idt.h"

struct InterruptDescriptor32 idt[IDT_ENTRIES];
struct idt_ptr idtp;

extern void idt_load(uint32_t);
extern void default_handler(); // handler par défaut (fait juste iret)
extern void isr33();           // handler pour IRQ1 (clavier) → vecteur 0x21 = 33

void set_idt_entry(int index, uint32_t handler, uint16_t selector, uint8_t type_attr) {
    idt[index].offset_1  = handler & 0xFFFF;
    idt[index].selector    = selector;
    idt[index].zero        = 0;
    idt[index].type_attributes   = type_attr;
    idt[index].offset_2 = (handler >> 16) & 0xFFFF;
}

void idt_init(void) {
    idtp.limit = sizeof(struct InterruptDescriptor32) * IDT_ENTRIES - 1;
    idtp.base  = (uint32_t)&idt;

    // extern void default_handler();
    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_entry(i, (uint32_t)default_handler, 0x08, 0x8E);
    }

    // Exemple : IRQ1 (clavier)
    set_idt_entry(0x21, (uint32_t)isr33, 0x08, 0x8E);

    idt_load((uint32_t)&idtp);
}