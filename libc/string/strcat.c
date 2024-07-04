#include <string.h>

// Concatenate the source string to the destination string
char *strcat(char * restrict dest, const char * restrict src) {
    char* original_dest = dest;

    while (*dest) {                               
        dest++;
    } while (*src) {                                    
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';                        

    return original_dest;
}