# Variables
NASM = nasm
GCC = gcc -fno-stack-protector -std=c99
GCC_FLAGS = -Wall -Wextra -Werror -m32
LD = ld
QEMU = qemu-system-i386

BOOTLOADER_SRC = src/boot/bootloader.asm
LINKER_SCRIPT = src/boot/linker.ld
KERNEL_SRC = $(wildcard src/kernel/*.c)
LIBS = $(wildcard src/libs/*.c)

BOOTLOADER_OBJ = kasm.o
KERNEL_OBJ = $(KERNEL_SRC:.c=.o)
LIBS_OBJ = $(LIBS:.c=.o)	

KERNEL_OUTPUT = kernel-0.0.1

# Targets
all: $(KERNEL_OUTPUT)

$(BOOTLOADER_OBJ): $(BOOTLOADER_SRC)
	$(NASM) -f elf32 $(BOOTLOADER_SRC) -o $(BOOTLOADER_OBJ)

%.o: %.c
	$(GCC) $(GCC_FLAGS) -c $< -o $@

$(KERNEL_OUTPUT): $(BOOTLOADER_OBJ) $(KERNEL_OBJ) $(LIBS_OBJ)
	$(LD) -m elf_i386 -T $(LINKER_SCRIPT) -o $(KERNEL_OUTPUT) $(BOOTLOADER_OBJ) $(KERNEL_OBJ) $(LIBS_OBJ)

clean:
	rm -f $(BOOTLOADER_OBJ) $(KERNEL_OBJ) $(LIBS_OBJ)

run: $(KERNEL_OUTPUT)
	$(QEMU) -kernel $(KERNEL_OUTPUT)

test: all clean run

.PHONY: all clean run test
