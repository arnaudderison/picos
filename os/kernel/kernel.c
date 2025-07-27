#include "screen.h"

void kernel_main() {
    Cursor cursor;

    clear_screen(&cursor);
    print(&cursor, "coucou je suis la super phrase pour test le mega affichage de l ecran de merde\n");
    print(&cursor, "coucou je suis la super phrase pour test le mega affichage de l ecran de merde\n");
    print(&cursor, "coucou je suis la super phrase pour test le mega affichage de l ecran de merde\n");
    print(&cursor, "coucou je suis la super phrase pour test le mega affichage de l ecran de merde\n");

}
