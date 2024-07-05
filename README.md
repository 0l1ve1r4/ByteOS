![Commit activity](https://img.shields.io/github/commit-activity/m/iyksh/basicOS)
![Lines of code](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fghloc.vercel.app%2Fapi%2Fiyksh%2FbasicOS%2Fbadge%3Ffilter%3D.c%2C.asm%2C.h%2C.sh&query=%24.message&label=lines%20of%20code&color=red)
![Repo Size](https://img.shields.io/github/repo-size/iyksh/basicOS)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/ddef159bc34148e4a89d2a600e9b61e5)](https://app.codacy.com/gh/iyksh/basicOS/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
![GitHub top language](https://img.shields.io/github/languages/top/iyksh/basicOS?logo=c&label=)
[![GitHub license](https://img.shields.io/github/license/iyksh/basicOS)](https://github.com/iyksh/basicOS/LICENSE)

# BasicOS - literally basic

**BasicOS** is a lightweight operating system developed in  (questionable quality) Assembly x86 and C99, tailored for educational purposes.

> **NOTE**
> 
> This project is still in very early stages, test on real hardware at your own risk. 

## Built-in Libs

### Full Built-in

- **string.h**: String manipulation utilities.

### TODO

- **stdio.h**: Input/output.
- **stdlib.h**: Standard Library.

## Roadmap

- **[X]** Make the [Meaty Skeleton](https://osdev.wiki/wiki/Meaty_Skeleton)
- **[ ]** First steps
  - **[X]** VGA driver
  - **[ ]** Interrupt Descriptor Table
  - **[X]** PS/2 Keyboard support
- **[ ]** RTC driver
- **[ ]** ATA PIO mode hard disk driver (28 bit LBA)
- **[ ]** FAT filesystem
  - **[ ]** Read (cd, ls, cat)
  - **[ ]** Write (mkdir, touch, rm, editfile, cp, mv)
- **[ ]** Do better scrolling (it sucks right now)
- **[ ]** Memory management
  - **[ ]** Physical memory management (pooling allocator)
  - **[ ]** Virtual memory management (paging)
  - **[ ]** Implement a heap (dynamic userspace stuff)


## Building and Running

### Prerequisites

### Building a Cross-Compiler

In this project, is used a `i686-elf-gcc` cross-compiler. If you want to have the same gcc/binutils as me, the versions that i used to build was: 
- binutils-2.40
- gcc-12.2.0.

For more info about how building/using a cross-compiler, read at [OSdev Wiki](https://osdev.wiki/wiki/GCC_Cross-Compiler)
> Remember of Installing Dependencies.

> You must configure your cross-binutils with the --with-sysroot option.


### Tools

Make sure you have the following tools installed:
- i686-elf toolchain, as discussed above.
- GRUB, for the grub-mkrescue command, along with the appropriate runtime files.
- Xorriso, the .iso creation engine used by grub-mkrescue.
- GCC (GNU Compiler Collection)
- LD (GNU Linker)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/iyksh/basicOS && cd basicOS
   ```

2. Build and run the project:
   ```bash
   ./build.sh
   ```

3. Run by qemu (recommended):
   ```bash
   qemu-system-i386 -kernel $HOME/sysroot/boot/myos.kernel
   ```

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue to discuss your ideas.

## License

This project is licensed under the GPL3 License. See the [LICENSE](LICENSE) file for more details.

---
