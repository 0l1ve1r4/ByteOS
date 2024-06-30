#include "kernel.h"

void kmain(void){
    stdio_init();       // Initialize the VGA text mode
    heap_init();        // Initialize the heap
    idt_init();         // Initialize the IDT
    kb_init();          // Initialize the keyboard
    kshell_init();      // Initialize the kernel shell

    kshell(NULL);       // Start the kernel shell
    show_info();        // Show the heap size and system information

    while (1);
}

