#include <stdio.h>
#include <drivers/keyboard.h>

int scanf(char* buffer){
    keyboard_scanf(buffer);
    return 0;
}