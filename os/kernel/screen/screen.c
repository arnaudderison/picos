#include "screen.h"
#include "utils.h"

#define VIDEO_MEMORY (unsigned short*) 0xB8000
#define ROWS 25
#define COLS 80
#define BLACK_ON_BLACK 0x00

static Cursor cursor = {
    .x = 0,
    .y = 0,
    .buffer = VIDEO_MEMORY
};

Cursor* get_cursor() {
    return &cursor;
}

void reset_cursor() {
    cursor.x = 0;
    cursor.y = 0;
    cursor.buffer = VIDEO_MEMORY;
}

void clear_screen() {
    reset_cursor();
    for (int i = 0; i < ROWS * COLS; i++) {
        cursor.buffer[i] = (BLACK_ON_BLACK << 8) | ' ';
    }
}

static void handle_scroll() {
    if (cursor.y < ROWS)
        return;

    for (int line = 0; line < (ROWS - 1); line++) {
        for (int x = 0; x < COLS; x++) {
            cursor.buffer[line * COLS + x] = cursor.buffer[(line + 1) * COLS + x];
        }
    }

    int last = ROWS - 1;
    for (int x = 0; x < COLS; x++) {
        cursor.buffer[last * COLS + x] = (BLACK_ON_BLACK << 8) | ' ';
    }

    cursor.y = last;
    if (cursor.x >= COLS)
        cursor.x = 0;
}

void putchar(char c) {
    handle_scroll();

    if (c == '\n') {
        cursor.y++;
        cursor.x = 0;
    } else {
        int index = cursor.y * COLS + cursor.x;
        cursor.buffer[index] = (0x0F << 8) | c;
        cursor.x++;
        if (cursor.x >= COLS) {
            cursor.x = 0;
            cursor.y++;
        }
    }
}

void print(const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
    }
}
