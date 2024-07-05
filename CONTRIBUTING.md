# Contributing to basicOS

Thank you for considering contributing to basicOS! Your help is greatly appreciated. This document provides guidelines for contributing to the project.

## Table of Contents

1. [Code of Conduct](#code-of-conduct)
2. [How Can I Contribute?](#how-can-i-contribute)
   - [Reporting Bugs](#reporting-bugs)
   - [Suggesting Enhancements](#suggesting-enhancements)
   - [Submitting Pull Requests](#submitting-pull-requests)
3. [Development Setup](#development-setup)
4. [Style Guides](#style-guides)
   - [Commit Messages](#commit-messages)
   - [Code Style](#code-style)
5. [Additional Resources](#additional-resources)

## Code of Conduct

This project adheres to the Contributor Covenant Code of Conduct. By participating, you are expected to uphold this code. Please report unacceptable behavior to [me :)](mailto:gssantoz2012@gmail.com).

## How Can I Contribute?

### Reporting Bugs

If you find a bug in the project, please check the [existing issues](https://github.com/iyksh/basicOS/issues) first. If the bug hasn't been reported yet, open a new issue and include as much detail as possible:
- Steps to reproduce the bug
- Expected and actual behavior
- Screenshots, logs, or other supporting information

### Suggesting Enhancements

If you have ideas for new features or improvements, please check the [existing issues](https://github.com/iyksh/basicOS/issues) and the [project roadmap](https://github.com/iyksh/basicOS/projects). If your idea hasn't been suggested yet, open a new issue and describe your suggestion in detail:
- What problem does the enhancement solve?
- How would you like to see it implemented?

### Submitting Pull Requests

To contribute code to basicOS, follow these steps:
1. Fork the repository and clone your fork.
2. Create a new branch for your feature or bugfix: `git checkout -b feature/your-feature-name` or `git checkout -b bugfix/your-bugfix-name`
3. Make your changes, ensuring they adhere to the project's coding standards.
4. Commit your changes with a descriptive commit message.
5. Push your changes to your forked repository.
6. Open a pull request from your branch to the `main` branch of the original repository.

Please ensure your pull request includes:
- A clear description of the changes
- References to any related issues
- Tests for your changes, if applicable

## Development Setup

To set up your development environment for basicOS, follow these instructions:

1. **Clone the repository:**
   ```sh
   git clone https://github.com/iyksh/basicOS.git
   cd basicOS
   ```

2. **Install dependencies:**
   Ensure you have the necessary tools installed (e.g., GCC, NASM, LD, QEMU).

3. **Build the project:**
   Use the provided Makefile to compile the project.
   ```sh
   chmod +x ./build.sh
   ./build.sh
   ```

4. **Run the project:**
   Execute the compiled code using QEMU.
   ```sh
    qemu-system-i386 -kernel $HOME/sysroot/boot/myos.kernel
   ```

## Style Guides

### Commit Messages

- Use the imperative mood in the subject line (e.g., "Add feature" not "Added feature").
- Limit the subject line to 50 characters.
- Include a detailed description of the change.

### Code Style

- Follow the project's existing coding style.
- Ensure your code is well-documented.
- Use meaningful variable and function names.

## Additional Resources

- [OSDev Wiki](https://wiki.osdev.org): A comprehensive resource for operating system development.
- [Project README](https://github.com/iyksh/basicOS/blob/main/README.md): Overview and objectives of the project.
- [Existing Issues](https://github.com/iyksh/basicOS/issues): Current issues and enhancements under consideration.

---
