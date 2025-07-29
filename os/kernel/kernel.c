#include "screen.h"
#include "idt.h"
#include "ports.h"

void kernel_main() {
    // clear_screen();

    PIC_remap(0x20, 0x28);
    idt_init();
    outb(0x21, 0xFF);
    asm volatile("sti");
    // reset_cursor();
    print("K");
    // print("coucou je suis la super phrase pour test le mega affichage de l ecran de flute\n");
    // print("coucou je suis la super phrase pour test le mega affichage de l ecran de flute\n");
    // print("coucou je suis la super phrase pour test le mega affichage de l ecran de flute\n");
    // print("coucou je suis la super phrase pour test le mega affichage de l ecran de flute\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("\n");
    // print("je suis la derniere ligne********************************************************");
    // print("je suis la derniere ligne********************************************************");
    // asm volatile("cli");

    // char* video = (char*) 0xB8000;
    // video[0] = 'H';
    // video[1] = 0x0F;
    // video[2] = 'i';
    // video[3] = 0x0F;
    // video[4] = '!';
    // video[5] = 0x0F;

    while(1){}

}
