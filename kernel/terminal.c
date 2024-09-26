#include <stdint.h>
#include "include/terminal.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
static uint16_t* terminal_buffer = (uint16_t*) 0xB8000;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color = 0x07;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = ' ';
        }
    }
}

void terminal_writestring(const char* str) {
    while (*str) {
        terminal_putchar(*str++);
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
    } else {
        terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = (terminal_color << 8) | c;
        terminal_column++;
        if (terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_row++;
        }
    }
}
