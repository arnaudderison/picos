#ifndef SCREEN_H
#define SCREEN_H

typedef struct {
    int y;
    int x;
    unsigned short* buffer;
} Cursor;


void reset_cursor();
void clear_screen();
void putchar(const char c);
void print(const char* str);

#endif