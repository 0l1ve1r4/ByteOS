![Commit activity](https://img.shields.io/github/commit-activity/m/iyksh/basicOS)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/9c8eee0fc7554427aa7100e8e6662ee5)](https://app.codacy.com/gh/iyksh/basicOS/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
![GitHub top language](https://img.shields.io/github/languages/top/iyksh/basicOS?logo=c&label=)
[![GitHub license](https://img.shields.io/github/license/iyksh/basicOS)](https://github.com/iyksh/basicOS/LICENSE)

# BasicOS - literally Basic

## Introduction

**BasicOS** is a 32 bits operating system designed for educational purposes for those (me) interested in low-level systems programming. 

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

BasicOS uses an `i686-elf-gcc` cross-compiler. The versions used to build the project are:

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
   git clone https://github.com/iyksh/basicOS && cd basicOS
   ```

2. Build and run the project:
   ```bash
   ./run.sh       # This will automatically clean, build and run the project with QEMU
   ```

## Contributing

Contributions are welcome! Whether it's reporting bugs, suggesting new features, or submitting pull requests, your involvement is appreciated. In this project, i am following this [OSDev.wiki](https://osdev.wiki/wiki/Creating_an_Operating_System) roadmap.

### Phase 0: Introduction

- **[X] 1.1** Welcome to Operating Systems Development
- **[X] 1.2** Building the latest GCC

### Phase I: Beginning

- **[X] 2.1** Setting up a Cross-Toolchain
- **[X] 2.2** Creating a Hello World kernel
- **[X] 2.3** Setting up a Project
- **[X] 2.4** Calling Global Constructors
- **[X] 2.5** Terminal Support
- **[ ] 2.6** Stack Smash Protector
- **[ ] 2.7** Multiboot
- **[ ] 2.8** Global Descriptor Table
- **[ ] 2.9** Memory Management
- **[ ] 2.10** Interrupts
- **[ ] 2.11** Multithreaded Kernel
- **[ ] 2.12** Keyboard
- **[ ] 2.13** Internal Kernel Debugger
- **[ ] 2.14** Filesystem Support

### Phase II: User-Space

- **[ ] 3.1** User-Space
- **[ ] 3.2** Program Loading
- **[ ] 3.3** System Calls
- **[ ] 3.4** OS Specific Toolchain
- **[ ] 3.5** Creating a C Library
- **[ ] 3.6** Fork and Execute
- **[ ] 3.7** Shell

### Phase III: Extending your Operating System

- **[ ] 4.1** Time
- **[ ] 4.2** Threads
- **[ ] 4.3** Thread Local Storage
- **[ ] 4.4** Symmetric Multiprocessing
- **[ ] 4.5** Secondary Storage
- **[ ] 4.6** Real Filesystems
- **[ ] 4.7** Graphics
- **[ ] 4.8** User Interface
- **[ ] 4.9** Networking
- **[ ] 4.10** Sound
- **[ ] 4.11** Universal Serial Bus

### Phase IV: Bootstrapping

- **[ ] 5.1** Porting Software
- **[ ] 5.2** Porting GCC
- **[ ] 5.3** Compiling your OS under your OS
- **[ ] 5.4** Fully Self-hosting

### Phase V: Profit

- **[ ] 6.1** Completion

## License

This project is licensed under the GPL3 License. See the [LICENSE](LICENSE) file for more details.