#include "include/fs.h"
#include "include/terminal.h"
#include "include/string.h"

// Simulate a dynamic file structure with commands
typedef struct {
    const char* path;
    const char* content;
} File;

File files[] = {
    { "/rc/startup.rc", NULL }  // Initially no content in startup.rc
};

const char* fs_read_file(const char* path) {
    for (int i = 0; i < sizeof(files) / sizeof(File); i++) {
        if (strcmp(files[i].path, path) == 0) {
            return files[i].content;
        }
    }
    return NULL;  // File not found
}

void fs_write_file(const char* path, const char* content) {
    for (int i = 0; i < sizeof(files) / sizeof(File); i++) {
        if (strcmp(files[i].path, path) == 0) {
            files[i].content = content;  // Set content dynamically
            return;
        }
    }
    terminal_writestring("File not found: ");
    terminal_writestring(path);
    terminal_writestring("\n");
}
