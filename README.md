# BasicOS

**BasicOS** is a minimalistic ["operating system"](https://en.wikipedia.org/wiki/Kernel_(operating_system)) developed in Assembly x86 (NASM) and C99, designed for educational purposes.

![Kernel_Startup](./files/kernel.png)

## Features

- **Bootloader**: Includes a 32KB stack.
- **Input**: Basic keyboard input functionality.
- **Output**: Basic screen output functionality.

## Todo

- Implement a shell with built-in commands.

## Building and Running

### Prerequisites

Ensure you have the following tools installed:
- NASM (Netwide Assembler)
- GCC (GNU Compiler Collection)
- LD (GNU Linker)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/iyksh/basicOS && cd basicOS
   ```

2. Build the project:
   ```bash
   make
   ```

3. Running with QEMU (Recommended): 
   ```bash
   make run
   ```

## Contributing

Contributions are welcome! Please submit a pull request or open an issue to discuss your ideas.

## License

This project is licensed under the GPL3 License. See the [LICENSE](LICENSE) file for details.
