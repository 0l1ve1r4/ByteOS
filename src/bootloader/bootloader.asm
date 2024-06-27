;; bootloader.asm

bits 32                   ; nasm directive - 32 bit
section .text
  ; Grub and Multiboot
  align 4
  dd 0x1BADB002           ; magic field, identify the header of GRUB
  dd 0x00                 ; flags field
  dd - (0x1BADB002 + 0x00); checksum. should be zero.

; The dd defines a double word of size 4 bytes.

global start
extern kmain              ; kmain is defined in the c file

start:
  cli                     ; block interrupts
  mov esp, stack_space    ; set stack pointer
  call kmain
  hlt                     ; halt the cpu

  section .bss
  resb 8192               ; 8KB for stack
  stack_space:
