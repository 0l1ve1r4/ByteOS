bits 32
section .text 
        ;multiboot spec
        align 4
        dd 0x1BADB002              ;magic
        dd 0x00                    ;flags
        dd - (0x1BADB002 + 0x00)   ;checksum, should be zero.

global start
global keyboard_handler
global read_port
global write_port
global load_idt

; c file functions
extern kmain 	

start:
	cli 				
	mov esp, stack_space
	call kmain
	hlt 			

section .bss
resb 32768; 32KB for stack
stack_space:
