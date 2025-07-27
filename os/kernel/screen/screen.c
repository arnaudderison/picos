#include "screen.h"
#include "utils.h"

#define VIDEO_MEMORY (unsigned short*) 0xB8000
#define ROWS 25
#define COLS 80
#define BLACK_ON_BLACK 0x00 

void reset_cursor(Cursor* cursor) {
    cursor->x = 0;
    cursor->y = 0;
    cursor->buffer = VIDEO_MEMORY;
}

void clear_screen(Cursor* cursor) {
    reset_cursor(cursor);
    for (int i = 0; i < ROWS * COLS; i++) {
        cursor->buffer[i] = (BLACK_ON_BLACK << 8) | ' ';
    }
}

void putchar(Cursor* cursor, const char c) {
    int index = 0;

    // if(!isprint(c))
    //     return ;

    if(c == '\n') {
        cursor->y++;
        cursor->x = 0;
    } else {
        index = cursor->y * COLS + cursor->x;
        cursor->buffer[index] = (0x0F << 8) | c;
        cursor->x++;
        if (cursor->x >= COLS) {
            cursor->x = 0;
            cursor->y++;
        }
    }
    // il fadrait scroller plus tard
    if (cursor->y >= ROWS) {
        cursor->y = 0;
    }
}

void print(Cursor* cursor, const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(cursor, str[i]);
    }
}