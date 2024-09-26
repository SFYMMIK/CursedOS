#include "include/terminal.h"
#include "include/shell.h"
#include "include/kernel.h"

void shell_start(void) {
    terminal_writestring("Welcome to the CursedOS Terminal\n");
    while (1) {
        terminal_writestring("> ");
        char input[128];
        read_input(input);
        if (strcmp(input, "poweroff") == 0) {
            kernel_poweroff();  // Power off the system directly from the kernel
        } else {
            terminal_writestring("Unknown command.\n");
        }
    }
}

void read_input(char* buffer) {
    // Simulate reading user input
    strcpy(buffer, "poweroff");  // Mock input for testing
}
