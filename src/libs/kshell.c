#include "kshell.h"
#include "kstdlib.h"
#include "kstring.h"

// Implemented at src/kernel/kernel.c
extern void kclear(void);
extern void kprint(const char *str);
extern void kprint_nl(void);

void kshell_init(void) {
    kclear();
    kprint(OS_PROMPT);
}

void kshell(const char* command) {
    kprint_nl();
    
    if (command == NULL || sizeof(command) == 0) {
        // Do nothing =)
    }

    else if (strcmp(command, "exit") == 0){
        kprint("Exiting kernel...");
        power_off();
    }

    else if (strcmp(command, "echo") == 0){
            kprint("echo");
    }

    else if (strcmp(command, "clear") == 0){
        kclear();
    }

    else if (strcmp(command, "help") == 0){
        kprint("Available commands:");
        kprint_nl();
        kprint("  - exit: Shutdown the kernel");
        kprint_nl();
        kprint("  - clear: Clear the screen");
        kprint_nl();
        kprint("  - help: Show this help message");
    }
    
    else {
        kprint("Command: [");
        kprint(command);
        kprint("] not found.");
    }

    kprint_nl();
    kprint(SHELL_PROMPT);

}