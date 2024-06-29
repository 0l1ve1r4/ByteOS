bits 32                         ; NASM directive to set 32-bit mode

section .text 
    align 4
    dd 0x1BADB002              ; Multiboot header magic number
    dd 0x00                    ; Multiboot flags
    dd - (0x1BADB002 + 0x00)   ; Multiboot checksum

; Functions definied here
global start                    ; Entry point for the kernel
global keyboard_handler         ; Keyboard interrupt handler
global read_port                ; Function to read from a port
global write_port               ; Function to write to a port
global load_idt                 ; Function to load the IDT

; Functions defined in C files
extern kmain                    ; Main kernel function
extern keyboard_handler_main    ; Main keyboard handler function

; Read from port function
read_port:
    mov edx, [esp + 4]          ; Load port address from stack
    in al, dx                   ; Read from port into AL
    ret                         ; Return

; Write to port function
write_port:
    mov edx, [esp + 4]          ; Load port address from stack
    mov al, [esp + 8]           ; Load value to write from stack
    out dx, al                  ; Write value to port
    ret                         ; Return

; Load IDT function
load_idt:
    mov edx, [esp + 4]          ; Load pointer to IDT from stack
    lidt [edx]                  ; Load the IDT
    sti                         ; Enable interrupts
    ret                         ; Return

; Keyboard interrupt handler
keyboard_handler:
    call keyboard_handler_main  ; Call the C handler function
    iretd                       ; Return from interrupt

; Kernel entry point
start:
    cli                         ; Disable interrupts
    mov esp, stack_space + 32768 ; Initialize stack pointer
    call kmain                  ; Call the main kernel function
    hlt                         ; Halt the CPU

section .bss
    align 4                     ; Align the stack space
    resb 32768                  ; Reserve 32KB for stack
stack_space:
