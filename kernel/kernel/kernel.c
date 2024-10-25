/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 
	
	* File: kernel.c 
	* Description: Kernel entry point
	* Sources: 
*/

/*========================================================================
# 	Includes
========================================================================*/

/* Kernel */
#include <kernel/tty.h>
#include <kernel/x86.h>
#include <kernel/heap.h>
#include <kernel/shell.h>

/* Drivers */
#include <drivers/keyboard.h>
#include <drivers/rtc.h>
#include <drivers/pit.h>

/* Others */
#include <fs/tmpfs.h>
#include <gui/gaming.h>

/* libc */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(__i386__)
#error "Must be compiled with an ix86-elf compiler."
#endif


/*========================================================================
# 	Defines
========================================================================*/

#define INIT_SUCESS 	0x00 
#define INIT_FAILURE 	0x01
#define PIT_INTERVAL	0X3E8 /* 1 ms */

/*========================================================================
# 	Functions
========================================================================*/

/* boot.s*/
extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

static void kernel_debug(char* str, int status){
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

static u8 pagingInitilization(void){
	u32 page_directory[1024] __attribute__((aligned(4096)));
	//set each entry to not present
	for(u16 i = 0; i < 1024; i++)
	{
    // This sets the following flags to the pages:
    //   Supervisor: Only kernel-mode can access them
    //   Write Enabled: It can be both read from and written to
    //   Not Present: The page table is not present
    page_directory[i] = 0x00000002;
	
	}

	u32 first_page_table[1024] __attribute__((aligned(4096)));

	//we will fill all 1024 entries in the table, mapping 4 megabytes
	for(u16 i = 0; i < 1024; i++)
	{
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
	}
	page_directory[0] = ((unsigned int)first_page_table) | 3;

	loadPageDirectory(page_directory);
	enablePaging();

	return 0;
}

/*========================================================================
# 	Main
========================================================================*/

void kernel_main(void) {
	kernel_debug("Terminal initialization", init_tty());
	
	kernel_debug("Paging initialization", pagingInitilization());

	kernel_debug("GDT initialization", 	init_GDT());
		
	kernel_debug("IDT initialization", 	init_IDT());

    kernel_debug("TSS initialization", 	init_TSS());

	kernel_debug("IRQ initialization", 	init_IRQ());
	
	kernel_debug("RTC initialization", 	rtc_initialize());

	kernel_debug("PIT initialization", 	pitInitialize(PIT_INTERVAL));

	kernel_debug("Heap initialization", initHeap());

	kernel_debug("RAM Filesystem", 		ramfs_init());

    shell_initialize();

}
