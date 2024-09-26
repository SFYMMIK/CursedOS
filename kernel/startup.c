#include "include/fs.h"
#include "include/terminal.h"
#include "include/string.h"

void parse_and_execute_startup(void) {
    const char* startup_commands = fs_read_file("/rc/startup.rc");
    
    if (startup_commands && *startup_commands != '\0') {
        terminal_writestring("Executing startup.rc...\n");
        char command[128];
        int index = 0;

        // Parse commands from startup.rc and execute them
        while (*startup_commands) {
            if (*startup_commands == ' ') {
                command[index] = '\0';
                execute_command(command);
                index = 0;
            } else {
                command[index++] = *startup_commands;
            }
            startup_commands++;
        }

        if (index > 0) {
            command[index] = '\0';
            execute_command(command);
        }
    } else {
        terminal_writestring("No commands in startup.rc or file not found.\n");
    }
}

void execute_command(const char* command) {
    if (strcmp(command, "gcc") == 0) {
        terminal_writestring("GCC invoked.\n");
    } else if (strcmp(command, "poweroff") == 0) {
        kernel_poweroff();  // Direct call to the kernel for shutdown
    } else {
        terminal_writestring("Unknown command: ");
        terminal_writestring(command);
        terminal_putchar('\n');
    }
}
