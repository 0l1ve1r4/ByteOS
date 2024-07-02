# Variables
NASM = nasm
GCC = gcc -fno-stack-protector -std=c99
GCC_FLAGS = -Wall -Wextra -m32
LD = ld
QEMU = qemu-system-i386

BOOTLOADER_SRC = boot/bootloader.asm
LINKER_SCRIPT = boot/linker.ld

KERNEL_SRC = $(wildcard kernel/*.c)
DRIVERS_SRC = $(wildcard drivers/*.c)
BUILTINS_INCLUDES = $(wildcard include/*.h)
SYSTEM_INCLUDES = $(wildcard sys/*.h)
USERSPACE = $(wildcard userspace/*.c)

BOOTLOADER_OBJ = kasm.o
KERNEL_OBJ = $(KERNEL_SRC:.c=.o)
DRIVERS_OBJ = $(DRIVERS_SRC:.c=.o)
SYSTEM_INCLUDES_OBJ = $(SYSTEM_INCLUDES:.h=.o)
BUILTINS_INCLUDES_OBJ = $(BUILTINS_INCLUDES:.h=.o)
USERSPACE_OBJ = $(USERSPACE:.c=.o)

KERNEL_OUTPUT = kernel-0.0.1

# Targets
all: $(KERNEL_OUTPUT)

$(BOOTLOADER_OBJ): $(BOOTLOADER_SRC)
	$(NASM) -f elf32 $(BOOTLOADER_SRC) -o $(BOOTLOADER_OBJ)

%.o: %.c
	$(GCC) $(GCC_FLAGS) -c $< -o $@

$(KERNEL_OUTPUT): $(BOOTLOADER_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ) $(SYSTEM_INCLUDES_OBJ) $(BUILTINS_INCLUDES_OBJ) $(USERSPACE_OBJ)
	$(LD) -m elf_i386 -T $(LINKER_SCRIPT) -o $(KERNEL_OUTPUT) -nostdlib -L /usr/lib/gcc/x86_64-linux-gnu/11/32/ $(BOOTLOADER_OBJ) \
	$(KERNEL_OBJ) $(DRIVERS_OBJ) $(USERSPACE_OBJ) $(SYSTEM_INCLUDES_OBJ) $(BUILTINS_INCLUDES_OBJ) -lgcc	

clean:
	rm -f $(BOOTLOADER_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ) $(SYSTEM_INCLUDES_OBJ) $(BUILTINS_INCLUDES_OBJ) $(USERSPACE_OBJ)

run: $(KERNEL_OUTPUT)
	$(QEMU) -kernel $(KERNEL_OUTPUT)

test: all clean run

.PHONY: all clean run test
