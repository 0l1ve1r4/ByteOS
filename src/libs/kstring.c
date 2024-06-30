#include "kstring.h"

// Copy the source string to the destination string
char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;             // Save the original destination address
    while (*src) {                          // while the source string is not null
        *dest = *src;                       // Copy the source character to the destination
        dest++; 
        src++;
    }
    *dest = '\0';                           // Null-terminate the destination string

    return original_dest;
}

// Convert any unsigned integer less than 32 bits to a string
char* uint_to_str(uint32_t n) {
    uint32_t len = num_length(n);           // Get the length of the number
    static char str[12];                    // Enough to hold 32-bit uint max 
    str[len] = '\0';                        // and the null terminator.
    
    while (len > 0) {                       // Fill the string in reverse order
        str[--len] = '0' + (n % 10);        // with the digits of the number.
        n /= 10;
    }
    return str;
}

// Return the length of the string
size_t strlen(const char* str) {            
    size_t length = 0;
    while (*str) {                          // Increment the length until the null terminator
        length++; str++;
    } return length;
}

// Compare two strings and return 0 if they are equal or the difference between the first differing characters
uint32_t strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {     // Compare each character using pointer arithmetic
        str1++;                     
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

// Calculate the length of any unsigned integer less than 32 bits
uint32_t num_length(uint32_t n) {
    uint32_t len = 0;
    do {
        len++;
        n /= 10;                            // Divide by 10 to remove the last digit
    } while (n > 0);    
    return len;
}

// Copy n bytes from src to dest and return dest
void* memcpy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    
    while (n--) {                           // Copy n bytes from src to dest
        *d++ = *s++;                        // Increment the pointers
    }
    
    return dest;
}

// Concatenate the source string to the destination string
char* strcat(char* dest, const char* src) {
    char* original_dest = dest;

    while (*dest) {                         // Move the destination pointer to the end of the string
        dest++;
    } while (*src) {                        // Copy the source string to the end of the destination string
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';                           // Null-terminate the destination string

    return original_dest;
}