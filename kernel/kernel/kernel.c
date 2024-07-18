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

/* Initialize adding block to heap, (1MB mark and length of 1MB) 
with default block size of 16 bytes */
PRIVATE uint8_t heap_initialization(void){    
	k_heap_init(&kheap);
	k_add_block(&kheap, 0x10000, 0x100000, 16);

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
	kernel_debug("Terminal initialization", init_tty());
	
	kernel_debug("GDT initialization", 	init_GDT());
		
	kernel_debug("IDT initialization", init_IDT());

    kernel_debug("TSS initialization", init_TSS());

	kernel_debug("IRQ initialization", init_IRQ());
	
	kernel_debug("RTC initialization", rtc_initialize());

	kernel_debug("Heap initialization", heap_initialization());

    shell_initialize();

}
