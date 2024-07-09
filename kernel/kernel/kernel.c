#include <kernel/tty.h>
#include <kernel/x86.h>
#include <drivers/keyboard.h>
#include <drivers/rtc.h>

#include <stdio.h>
#include <shell.h>

/* Obs: in printf is used %m to use ansii colors */
const char* ansi_green = "\033[32m";
const char* ansi_red = "\033[31m";
const char* ansi_lightgrey = "\033[37m";

#if !defined(__i386__)
#error "Must be compiled with an ix86-elf compiler."
#endif

static void kernel_debug(char* str, int status){
	if(status == 0){
		printf("%s[ OK ]%s %s\n", ansi_green, ansi_lightgrey, str);
	}else{
		printf("%s[FAIL]%s %s\n", ansi_red, ansi_lightgrey, str);
	}
}

void kernel_main(void) {
	init_tty();
	kernel_debug("Terminal initialized", 0);
	
	init_GDT();
	kernel_debug("GDT initialized", 0);
	
	init_IDT();
	kernel_debug("IDT initialized", 0);
	
	init_IRQ();
	kernel_debug("IRQ initialized", 0);
	
	rtc_initialize();
	kernel_debug("RTC initialized", 0);

	
	kernel_debug("Keyboard initialized", 0);

	kernel_debug("Operating System initialized", 0);
    shell_initialize();

}
