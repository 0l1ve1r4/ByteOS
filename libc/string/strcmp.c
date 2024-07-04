#include <string.h>

// Compare two strings, return 0 are equal or the difference
int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {     
        str1++;                     
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;

}