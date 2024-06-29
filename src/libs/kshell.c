#include "kshell.h"
#include "kstdlib.h"

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
    
    else {
        kprint("Command: [");
        kprint(command);
        kprint("] not found.");
    }

    kprint_nl();
    kprint(SHELL_PROMPT);

}