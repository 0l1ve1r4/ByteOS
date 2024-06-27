# Creating the object files
nasm -f elf32 src/bootloader/bootloader.asm -o kasm.o
gcc -m32 -c src/kernel/kernel.c -o kc.o # -c make sure that linking doesn´t implicitly happen

# linking
ld -m elf_i386 -T linker.ld -o kernel-0.0.1 kasm.o kc.o

# Cleaning objects
rm -rf *.o

# Running
qemu-system-i386 -kernel kernel-0.0.1