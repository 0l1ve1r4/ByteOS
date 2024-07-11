![Commit activity](https://img.shields.io/github/commit-activity/m/iyksh/ByteOS)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/9c8eee0fc7554427aa7100e8e6662ee5)](https://app.codacy.com/gh/iyksh/ByteOS/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
![GitHub top language](https://img.shields.io/github/languages/top/iyksh/ByteOS?logo=c&label=)
[![GitHub license](https://img.shields.io/github/license/iyksh/ByteOS)](https://github.com/iyksh/ByteOS/LICENSE)

# ByteOS

## Introduction

**ByteOS** is a 32 bits operating system designed for educational purposes for those (me) interested in low-level systems programming. 

> **NOTE**
>
> This project is still in very early stages. Test on real hardware at your own risk.

## Table of Contents

- [Project Description](#project-description)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Project Description

### Overview

This OS aims to provide a minimalistic and simple operating system that covers the basic functionalities expected from an OS. 

### Built-in Libraries

To maintain control and ensure that the system operates almost entirely from scratch, standard libraries are being rewritten. This approach helps in understanding the inner workings of these libraries and how they interact with the OS.

#### Completed Libraries

- **string.h**: String manipulation utilities.

#### Partially Made Libraries

- **stdio.h**: Basic input/output functions.
- **stdlib.h**: Standard utility functions.
- **time.h**: Time management functions.

## Installation

### Prerequisites

#### Building a Cross-Compiler

ByteOS uses an `i686-elf-gcc` cross-compiler. The versions used to build the project are:

- binutils-2.40
- gcc-12.2.0

For detailed instructions on building and using a cross-compiler, refer to the [OSdev Wiki](https://osdev.wiki/wiki/GCC_Cross-Compiler).

> **Note:** Ensure you configure your cross-binutils with the `--with-sysroot` option.

#### Required Tools

Make sure you have the following tools installed:

- i686-elf toolchain.
- qemu-system-i386 for virtual machine.
- GCC (GNU Compiler Collection).
- LD (GNU Linker).

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/iyksh/ByteOS && cd ByteOS
   ```

2. Build and run the project:
   ```bash
   ./run.sh       # This will automatically clean, build and run the project with QEMU
   ```

## Contributing

Contributions are welcome! Whether it's reporting bugs, suggesting new features, or submitting pull requests, your involvement is appreciated. In this project, i am following this [Github Project Roadmap](https://github.com/users/iyksh/projects/3).

## License

This project is licensed under the GPL3 License. See the [LICENSE](LICENSE) file for more details.