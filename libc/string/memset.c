#include <string.h>

// Fill n bytes of memory with the constant byte c
void *memset(void *dest, int c, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    while (n--) {
        *d++ = (unsigned char)c;
    }
    
    return dest;

}