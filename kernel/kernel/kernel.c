#include <kernel/tty.h>
#include <kernel/x86.h>
#include <drivers/keyboard.h>
#include <drivers/rtc.h>
#include <kernel/heap.h>


#include <stdio.h>
#include <stdlib.h>
#include <shell.h>
#include <string.h>

#if !defined(__i386__)
#error "Must be compiled with an ix86-elf compiler."
#endif

#define PUBLIC
#define PRIVATE 		static
#define INIT_SUCESS 	0 
#define INIT_FAILURE 	1

PRIVATE KHEAPBM			kheap;

PRIVATE void kernel_debug(char* str, int status){
	switch (status) {

	case INIT_SUCESS:
		printf("%s[ OK ]%s %s\n", "\033[32m", "\033[37m", str);
		break;
	
	case INIT_FAILURE:
		printf("%s[ FAIL ]%s %s\n", "\033[31m", "\033[37m", str);
		break;

	default:
		printf("%s[ ? ]%s Unknown Status: [%i]\n", "\033[31m", "\033[37m", status);
		break;
	}

}

PRIVATE uint8_t heap_initialization(void){    
	k_heap_init(&kheap);
	k_add_block(&kheap, 0x01000, 0x100000, 16);

	char *ptr = (char*)k_malloc(&kheap, sizeof(char) * 10); 
	for (uint8_t i = 0; i < 10; i++) {
		ptr[i] = i + '0';
	}     

	if (strcmp(ptr, "0123456789") == 0){
		k_free(&kheap, ptr);
		return INIT_SUCESS;
	}
	
	return INIT_FAILURE;

}


PUBLIC void kernel_main(void) {
  	init_tty();
	kernel_debug("Terminal initialized", 0);

	init_GDT();
	kernel_debug("GDT initialized", 0);
	
	init_IDT();
	kernel_debug("IDT initialized", 0);

    init_TSS();
    kernel_debug("TSS initialized", 0);

	init_IRQ();
	kernel_debug("IRQ initialized", 0);
	kernel_debug("Keyboard initialized", 0);
	
	rtc_initialize();
	kernel_debug("RTC initialized", 0);

	kernel_debug("Heap initialization", heap_initialization());

    shell_initialize();

}
