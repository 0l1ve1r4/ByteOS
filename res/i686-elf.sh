#!/bin/bash

# Easy to use script to build a cross compiler for i686-elf for debian based systems
# This script is based on the tutorial from osdev.org
# https://wiki.osdev.org/GCC_Cross-Compiler

GCC_VERSION=13.2.0
BINUTILS_VERSION=2.41
DEPENDENCIES="build-essential bison flex libgmp-dev libmpc-dev libmpfr-dev texinfo"   
BASHRC="$HOME/.bashrc"  

sudo apt update
sudo apt install $DEPENDENCIES

wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz
tar -xzf binutils-$BINUTILS_VERSION.tar.gz

wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-$GCC_VERSION.tar.gz
tar -xzf gcc-$GCC_VERSION.tar.gz

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $PREFIX
mkdir build-binutils build-gcc

cd build-binutils
../binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
make
sudo make install

cd ../build-gcc
../$GCC_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --without-headers
make all-gcc
make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc

echo "export PATH=\"$HOME/opt/cross/bin:\$PATH\"" >> $BASHRC

source $BASHRC