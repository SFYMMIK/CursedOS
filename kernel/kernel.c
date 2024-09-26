#include "include/terminal.h"
#include "include/shell.h"
#include "include/startup.h"
#include "include/fs.h"

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("Kernel initializing...\n");

    terminal_writestring("[ OK ] Memory Management\n");
    terminal_writestring("[ OK ] Interrupt Handling\n");
    terminal_writestring("[ OK ] Scheduler Initialized\n");
    terminal_writestring("[ OK ] Filesystem Mounted\n");

    parse_and_execute_startup();  // Load and execute commands from /rc/startup.rc

    terminal_writestring("CursedOS ver0.2.7 x86_64\n");

    shell_start();  // Start the shell after initialization
}

void kernel_poweroff(void) {
    terminal_writestring("System is powering off...\n");

    // Simulate saving state and data before shutdown
    terminal_writestring("Saving data...\n");
    
    // Halt the CPU
    while (1) {
        asm volatile("hlt");
    }
}
