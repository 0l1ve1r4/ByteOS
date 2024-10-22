/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 
	
	* File: kernel.c 
	* Description: Kernel entry point
	* Sources: 
*/

#include <kernel/tty.h>
#include <kernel/x86.h>
#include <drivers/keyboard.h>
#include <drivers/rtc.h>
#include <kernel/heap.h>
#include <fs/ramfs.h>

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

PRIVATE void kernel_debug(char* str, int status){
	switch (status) {

	case INIT_SUCESS:
		printf("%s[ OK ]%s %s\n", "\033[32m", "\033[37m", str);
		break;
	
	case INIT_FAILURE:
		printf("%s[ FAIL ]%s %s\n", "\033[31m", "\033[37m", str);
		break;

	default:
		printf("%s[ ? ]%s Unknown", "\033[31m", "\033[37m");
		break;
	}

}

/* Initialize adding block to heap, (1MB mark and length of 1MB) 
with default block size of 16 bytes */
PRIVATE u8 heap_initialization(void){  
	initHeap();
	char *ptr = (char*)kMalloc(32); 
	for (u8 i = 0; i < 33; i++) {
		if (i < 32 && ptr[i] != ALLOCATION_REPRESENTATION) {
			printf("SOMETHING WENT WRONG WITH MALLOC");
			return INIT_FAILURE;
		}
	}     

	return INIT_SUCESS;

}


PUBLIC void kernel_main(void) {
	kernel_debug("Terminal initialization", init_tty());
	
	kernel_debug("GDT initialization", 	init_GDT());
		
	kernel_debug("IDT initialization", init_IDT());

    kernel_debug("TSS initialization", init_TSS());

	kernel_debug("IRQ initialization", init_IRQ());
	
	kernel_debug("RTC initialization", rtc_initialize());

	kernel_debug("Heap initialization", heap_initialization());

	kernel_debug("RAM Filesystem", ramfs_init());


    shell_initialize();


}
