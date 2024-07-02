; This file is part of basicOS.
; Copyright (C) 2024 Guilherme Oliveira Santos

; This is free software: you can redistribute it and/or modify it 
; under the terms of the GNU GPL3 or (at your option) any later version.

; This program is distributed in hope that it will be useful, but 
; WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
; or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

bits 32                        ; NASM directive to set 32-bit mode

section .text 
    align 4
    dd 0x1BADB002              ; Multiboot header magic number
    dd 0x00                    ; Multiboot flags
    dd - (0x1BADB002 + 0x00)   ; Multiboot checksum

; Functions definied here
global start                    ; Entry point for the kernel
global keyboard_handler         ; Keyboard interrupt handler

; Functions defined in C files
extern kernel_main              ; Main kernel function
extern keyboard_handler_main    ; Main keyboard handler function

; Keyboard interrupt handler
keyboard_handler:
    call keyboard_handler_main  ; Call the C handler function
    iretd                       ; Return from interrupt

; Kernel entry point
start:
    cli                         ; Disable interrupts
    mov esp, stack_space + 32768; Initialize stack pointer
    call kernel_main            ; Call the main kernel function
    hlt                         ; Halt the CPU

section .bss
    align 4                     ; Align the stack space
    resb 32768                  ; Reserve 32KB for stack
stack_space:
