#include <stdint.h>
#include "ports.h"
#include "screen.h"

// Fonction appelée par tous les stubs ISR. Tu peux ici gérer chaque IRQ.
void irq_handler(uint8_t irq) {
    if (irq == 33) {
        // uint8_t scancode = inb(0x60); // lecture du port clavier (scancode)
        // TODO : traitement clavier ici (affichage, buffer...)
        inb(0x60);
        outb(0x20, 0x20); // Envoie un EOI (End of Interrupt) au PIC master
    }
}