#include <string.h>

// Copy the first n characters of source to destination
char *strncpy(char * restrict s1, const char * restrict s2, size_t n){
    char *d = s1;
    const char *s = s2;

    while (n-- && (*d++ = *s++)) {
        ;
    }

    return s1;
}