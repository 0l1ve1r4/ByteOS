#!/bin/sh

# ======================= Architecture ====================

# Remember to add your cross compiler on your ~/.bashrc or ~/.profile
# export PATH="$HOME/opt/cross/bin:$PATH"

DEFAULT_TARGET=i686-elf

# ======================= Arguments =======================

ARG1=$1 # build, clean, run, host, target
ARG2=$2 # i686-elf, x86_64-elf, etc.

# ======================= Fast Returns ====================

if [ "$1" = "host" ]; then
    echo "$DEFAULT_TARGET"  
    exit 0
elif [ "$1" = "target" ]; then
    ARG2="$2"  
    if echo "$ARG2" | grep -Eq 'i[[:digit:]]86-'; then
        echo i386
        exit 0
    else
        echo "$ARG2" | grep -Eo '^[[:alnum:]_]*'
        exit 0
    fi
fi

# ======================= Projects ========================

SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

# ======================= Environment =====================

export MAKE="${MAKE:-make}"
export HOST="${HOST:-$(./run.sh host)}"
export AR="${HOST}-ar"
export AS="${HOST}-as"
export CC="${HOST}-gcc"
export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include
export CFLAGS='-O2 -g'
export CPPFLAGS=''
export SYSROOT="$HOME/sysroot"
export CC="i686-elf-gcc --sysroot=$SYSROOT -Wall -Wextra -Werror -Wpedantic"

# ======================= Build ===========================

if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi

# ======================= Functions =======================

headers() {
  set -e
  mkdir -p "$SYSROOT"
  for PROJECT in $SYSTEM_HEADER_PROJECTS; do
    (cd "$PROJECT" && DESTDIR="$SYSROOT" "$MAKE" install-headers)
  done
}

build() {
  set -e
  for PROJECT in $PROJECTS; do
    (cd "$PROJECT" && DESTDIR="$SYSROOT" "$MAKE" install)
  done
}

clean() {
  set -e
  for PROJECT in $PROJECTS; do
    (cd "$PROJECT" && "$MAKE" clean)
  done
  rm -rf "sysroot isodir myos.iso $HOME/sysroot"
}

run() {
  qemu-system-i386 -kernel "$HOME/sysroot/boot/myos.kernel"

}

# ======================= Main =============================

case "$ARG1" in
  build)
    headers
    build
    ;;
  clean)
    clean
    ;;
  run)
    run
    ;;
  *)
    echo "Usage: ./run.sh [build|clean|run]"
    echo "Without arguments, will clean, build, and run."
    clean
    headers
    build
    run
    clean # clean again (optional)
    ;;
esac

# ======================= End ==============================