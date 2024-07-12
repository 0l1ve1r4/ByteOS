![Commit activity](https://img.shields.io/github/commit-activity/m/iyksh/ByteOS)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/9c8eee0fc7554427aa7100e8e6662ee5)](https://app.codacy.com/gh/iyksh/ByteOS/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
![GitHub top language](https://img.shields.io/github/languages/top/iyksh/ByteOS?logo=c&label=)
[![GitHub license](https://img.shields.io/github/license/iyksh/ByteOS)](https://github.com/iyksh/ByteOS/LICENSE)

# ByteOS

## Introduction

**ByteOS** is a 32-bit operating system designed for educational purposes for those interested in low-level systems programming, 
with the purpose of a well-documented wiki and bringing more "hands on" for those who want to learn the implementation of "everything" made from scratch.

#### [Click here to be redirected to the wiki](https://github.com/iyksh/ByteOS/wiki) 

---

## Installation

Make sure you have the following tools installed:

- i686-elf toolchain.
- qemu-system-i386 for virtual machine.
- GCC (GNU Compiler Collection).
- LD (GNU Linker).

For detailed instructions on building and using a cross-compiler, refer to the [OSdev Wiki](https://osdev.wiki/wiki/GCC_Cross-Compiler).

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

## Contributing

Contributions are welcome! Whether it's reporting bugs, suggesting new features, or submitting pull requests, your involvement is appreciated. In this project, i am following this [Github Project Roadmap](https://github.com/users/iyksh/projects/3).

## License

This project is licensed under the GPL3 License. See the [LICENSE](LICENSE) file for more details.
