#include <string.h>

// Copy the source string to the destination string

/* CRITICAL [MS-banned] (CWE-120). Consider using strncpy */
/*
char *strcpy(char* restrict dest, const char* restrict src) {
    char* original_dest = dest;               
    while (*src) {                             
        *dest = *src;                                  
        dest++; 
        src++;
    }
    *dest = '\0';                              
    
    return original_dest;           

}*/