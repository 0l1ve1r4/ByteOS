#include <string.h>

// Concatenate the first n characters of s2 to s1 
char *strncat(char * restrict s1, const char * restrict s2, size_t n){
    char *d = s1;
    const char *s = s2;

    while (*d) {
        d++;
    }

    while (n-- && (*d++ = *s++)) {
        ;
    }

    *d = '\0';

    return s1;

}