#include <string.h>

// Copy the source string to the destination string
char *strcpy(char* restrict dest, const char* restrict src) {
    char* original_dest = dest;               
    while (*src) {                             
        *dest = *src;                                  
        dest++; 
        src++;
    }
    *dest = '\0';                                       // Null-terminate the destination string
    
    return original_dest;           

}