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

- i686-elf toolchain.
- qemu-system-i386 for virtual machine.
- GCC (GNU Compiler Collection).
- LD (GNU Linker).

For detailed instructions on building and using a cross-compiler, refer to the [OSdev Wiki](https://osdev.wiki/wiki/GCC_Cross-Compiler). You can also check the [i686-elf.sh](./res/i686-elf.sh) to do this for you.

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
