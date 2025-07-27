#ifndef SCREEN_H
#define SCREEN_H

typedef struct {
    int y;
    int x;
    unsigned short* buffer;
} Cursor;

void reset_cursor(Cursor* cursor);
void clear_screen(Cursor* cursor);
void putchar(Cursor* cursor, const char c);
void print(Cursor* cursor, const char* str);

#endif