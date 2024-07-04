#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

#if !defined(__i386__)
#error "Must be compiled with an ix86-elf compiler."
#endif

void kernel_main(void) {
	terminal_initialize();
	
	printf("basicOS kernel\n");

	char buffer[255];
	strcpy(buffer, "strcpy test\n");
	printf(buffer);

}
