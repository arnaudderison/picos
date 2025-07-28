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

static void handle_scroll(Cursor* cursor) {
    int line;
    int x;

    if(cursor->y < ROWS)
        return ;

    for(line = 0; line < (ROWS - 1); line++) {
        for(x = 0; x < COLS; x++) {
            cursor->buffer[line * COLS + x] = cursor->buffer[(line + 1) * COLS + x];
        }
    }
    line = ROWS - 1;
    for(x = 0; x < COLS; x++) {
        cursor->buffer[line * COLS + x] = (BLACK_ON_BLACK << 8) | ' ';
    }
    cursor->y = ROWS - 1;
    if (cursor->x >= COLS)
        cursor->x = 0;
}

void putchar(Cursor* cursor, const char c) {
    int index = 0;

    handle_scroll(cursor);
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
}

void print(Cursor* cursor, const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(cursor, str[i]);
    }
}