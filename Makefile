# Variables
NASM = nasm
GCC = gcc
LD = ld
QEMU = qemu-system-i386

BOOTLOADER_SRC = src/boot/bootloader.asm
LINKER_SCRIPT = src/boot/linker.ld
KERNEL_SRC = src/kernel/kernel.c
BOOTLOADER_OBJ = kasm.o
KERNEL_OBJ = kc.o
KERNEL_OUTPUT = kernel-0.0.1

# Targets
all: $(KERNEL_OUTPUT)

$(BOOTLOADER_OBJ): $(BOOTLOADER_SRC)
	$(NASM) -f elf32 $(BOOTLOADER_SRC) -o $(BOOTLOADER_OBJ)

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(GCC) -m32 -c $(KERNEL_SRC) -o $(KERNEL_OBJ)

$(KERNEL_OUTPUT): $(BOOTLOADER_OBJ) $(KERNEL_OBJ)
	$(LD) -m elf_i386 -T $(LINKER_SCRIPT) -o $(KERNEL_OUTPUT) $(BOOTLOADER_OBJ) $(KERNEL_OBJ)

clean:
	rm -f $(BOOTLOADER_OBJ) $(KERNEL_OBJ)

run: $(KERNEL_OUTPUT)
	$(QEMU) -kernel $(KERNEL_OUTPUT)

test: all clean run

.PHONY: all clean run test
