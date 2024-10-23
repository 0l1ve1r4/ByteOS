<div align="center">
  <img src="res/logo.png" alt="ByteOSLogo" style="width: 70%;">

<p align="center">
    <strong>Open-source hobby operating system</strong>
  </p>

<hr>

![Commit activity](https://img.shields.io/github/commit-activity/m/iyksh/ByteOS)
![GitHub top language](https://img.shields.io/github/languages/top/iyksh/ByteOS?logo=c&label=)
[![GitHub license](https://img.shields.io/github/license/iyksh/ByteOS)](https://github.com/iyksh/ByteOS/LICENSE)

</div>

**ByteOS** is a 32-bit x86 architecture operating system designed for educational purposes for those interested in low-level systems programming.

#### [Click here to be redirected to the wiki](https://github.com/iyksh/ByteOS/wiki) 

---

## Installation

Make sure you have the following tools installed:

- i386-elf toolchain.
- qemu-system-i386 for virtual machine.
- GCC (GNU Compiler Collection).
- LD (GNU Linker).

For detailed instructions on building and using a cross-compiler, refer to the [OSdev Wiki](https://osdev.wiki/wiki/GCC_Cross-Compiler). You can also check the [i386-elf.sh](./res/i386-elf.sh) to do this for you.

> **NOTE**
>
> This project is still in very early stages. Test on real hardware at your own risk.
> 
> Ensure you configure your cross-binutils with the `--with-sysroot` option.

---

1. Clone the repository:
   ```bash
   git clone https://github.com/iyksh/ByteOS && cd ByteOS
   ```

2. Build and run the project:
   ```bash
   ./run.sh         # This will automatically clean, build and run the project with QEMU
   ```

---

## TODO

#### 1. Set Up Development Environment
- [X] Choose a cross-compiler (`i386-elf-gcc`)
- [X] Set up a bare-metal development environment

#### 2. Write a Bootloader
- [X] Develop a minimal bootloader 
- [X] Tells GRUB to load the kernel from disk
- [X] Enable paging

#### 3. Kernel Initialization
- [X] Write the kernel in C or assembly
- [X] Implement basic memory management (GDT, IDT)
- [X] Handle bootloader to kernel transition
- [ ] Set up the stack and clear BSS section

#### 4. Paging and Virtual Memory
- [ ] Set up paging for virtual memory management
- [ ] Implement higher-half kernel support

#### 5. Interrupt Handling
- [ ] Write ISRs for CPU exceptions
- [ ] Set up the IDT
- [ ] Implement IRQ handling
- [ ] Add support for software interrupts (int instruction)

#### 6. Basic Drivers
- [X] Write a keyboard driver
- [X] Write a screen driver (VGA)
- [X] Write a timer driver
- [ ] Write a basic serial port driver (for debugging)

#### 7. Memory Management
- [X] Implement physical memory management (bitmap/free list)
- [X] Implement virtual memory management (`malloc`/`free`)
- [ ] Implement paging mechanisms (page tables, page faults)
- [ ] Add a memory allocator (e.g., buddy allocator)

#### 8. File System
- [X] Design a Temporary Filesystem (RAMFS)
- [ ] Design or implement a simple file system (FAT12/16 or custom)
- [ ] Develop disk sector interaction code (block device driver)
- [ ] Implement basic file operations (open, read, write, close)

#### 9. Multitasking and Scheduling
- [ ] Implement basic multitasking (context switching)
- [ ] Develop a simple scheduler (round-robin, priority-based)
- [ ] Add support for threads (user-space threads)

#### 10. User Mode and Process Management
- [ ] Develop user-mode support for running programs
- [ ] Implement system calls for user-kernel interaction
- [ ] Create process control blocks (PCBs) for process management

#### 11. I/O Management
- [X] Implement basic I/O management API
- [X] Manage I/O devices via drivers
- [ ] Implement buffering for I/O operations

#### 12. Testing and Debugging
- [X] Using QEMU or Bochs for testing
- [ ] Use `gdb` with QEMU for debugging
- [ ] Create automated test scripts for components

#### 13. Shell and User Interface 
- [X] Develop a minimal command-line shell
- [X] Implement basic text I/O for user interaction
- [X] Add support for last command completion
- [ ] Add support for command history
- [ ] Add support for tab completion


#### 14. Advanced Features (Optional)
- [ ] Add networking support (TCP/IP stack)
- [ ] Implement SMP (Symmetric Multiprocessing)
- [ ] Add graphical user interface support
- [ ] Support dynamic loading of modules (kernel modules)
- [ ] Implement a simple package manager for software installation
