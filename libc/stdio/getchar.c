#include <types.h>
#include <drivers/keyboard.h>

u8 getchar(void) {
    return keyboardDriverGetChar();    
}
