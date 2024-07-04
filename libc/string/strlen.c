#include <string.h>

// Return the length of the string
size_t strlen(const char* str) {            
    size_t length = 0;
    while (*str) {
        length++; str++;
    } return length;
}