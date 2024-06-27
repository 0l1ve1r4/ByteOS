# BasicOS
**BasicOS** is a very simple operating system written in Assembly x86 and C for educational purposes.

## Features/Functions

- Multi-stage bootloader
- e820 Memory Map reading
- Basic I/O from PS2 port and serial port
- Serial port printf capability
- Simple 80x25 Text display interface
- Simple VGA interface
- ATA Drive reading/writing
- Basic kernel memory management
- Basic multiprocessing capabilities
- Basic LEAN filesystem implementation

## Building and Running

1. **Build Toolchain**:
   - Make sure you have NASM, GCC, and LD installed.
   - To build, run `make` in a terminal.

2. **Running with QEMU (Recommended)**:
   - Execute the following command in the root directory of the project:
     ```
     qemu-system-x86_64 -drive format=raw,file="image/os-image.img" -m 32M
     ```

3. **Running with VirtualBox**:
   - Convert the raw image to a VMDK format:
     ```
     VBoxManage convertfromraw "image/os-image.img" "image/testimage.vmdk" --format vmdk
     ```
   - Create a new VM in VirtualBox and use the newly created VMDK as the disk.
