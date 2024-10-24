#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <drivers/keyboard.h>

/* TODO: Make a better implementation */
int scanf(const char *format, ...){
    va_list parameters;
    va_start(parameters, format);
    
    char * buffer = (char *) va_arg(parameters, char*);
    
    keyboard_scanf(buffer);

    if (buffer[0] == '\0'){
        return -1;
    }
    return 0;    
}