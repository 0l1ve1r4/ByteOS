#include "string.h"


// Copy the source string to the destination string
char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;                         // Save the original destination address
    while (*src) {                                      // while the source string is not null
        *dest = *src;                                   // Copy the source character to the destination
        dest++; 
        src++;
    }
    *dest = '\0';                                       // Null-terminate the destination string

    return original_dest;           
}

// Convert an unsigned integer to a string  
char* uint_to_str(uint32_t n) {
    uint32_t len = num_length(n);                       // Get the length of the number
    static char str[12];                                // Enough to hold 32-bit uint max and the null terminator
    str[len] = '\0';                                    // Null-terminate the string
    
    while (len > 0) {                                   // Fill the string in reverse order
        str[--len] = '0' + (n % 10);                    // with the digits of the number.
        n /= 10;
    }
    return str;
}

// Convert a float to a string
char* float_to_str(float n) {               
    static char str[20]; 
    char* p = str;                                      // Pointer to the string
    if (n < 0) {                                        // Handle negative numbers
        *p++ = '-';
        n = -n;
    }
    
    uint32_t int_part = (uint32_t)n;                    // before the decimal point 
    float float_part = n - int_part;        
    
    char* int_str = uint_to_str(int_part);
    strcpy(p, int_str);
    p += strlen(int_str);
    
    *p++ = '.';                                         // Convert the fractional part
    float_part *= 1000000;                              // Adjust the multiplier to control the precision
    char* float_str = uint_to_str((uint32_t)float_part);
    
    char* end = float_str + strlen(float_str) - 1;      // Remove trailing zeros in the fractional part
    while (end > float_str && *end == '0') {
        end--;
    }
    *(end + 1) = '\0';                                  // Null-terminate the string
    
    strcpy(p, float_str);
    
    return str;
}
// Return the length of the string
size_t strlen(const char* str) {            
    size_t length = 0;
    while (*str) {                                      // Increment the length until the null terminator
        length++; str++;
    } return length;
}

// Compare two strings and return 0 if they are equal or the difference between the first differing characters
uint32_t strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {                 // Compare each character using pointer arithmetic
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
        n /= 10;                                        // Divide by 10 to remove the last digit
    } while (n > 0);    
    return len;
}

// Copy n bytes from src to dest and return dest
void* memcpy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    
    while (n--) {                                       // Copy n bytes from src to dest
        *d++ = *s++;                                    // Increment the pointers
    }
    
    return dest;
}

// Fill n bytes of memory with the constant byte c
void *memset(void *dest, int c, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    while (n--) {
        *d++ = (unsigned char)c;
    }
    return dest;
}

// Concatenate the source string to the destination string
char* strcat(char* dest, const char* src) {
    char* original_dest = dest;

    while (*dest) {                                     // Move the destination pointer to the end of the string
        dest++;
    } while (*src) {                                    // Copy the source string to the end of the destination string
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';                                       // Null-terminate the destination string

    return original_dest;
}

// Helper function to count the number of tokens
size_t count_tokens(const char* str, char delim) {
    size_t count = 0;
    uint32_t in_token = 0;
    while (*str) {
        if (*str == delim) {
            in_token = 0;
        } else if (!in_token) {                         // Start of a new token
            in_token = 1;
            count++;
        }
        str++;
    }
    return count;
}

char** split(const char* str, char delim) {
    static char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH]; // Static array for tokens
    static char* result[MAX_TOKENS + 1];              // Static array for pointers to tokens
    size_t token_index = 0;

    while (*str && token_index < MAX_TOKENS) {
        while (*str == delim) { // Skip delimiters
            str++;
        }

        const char* token_start = str; // Find the end of the token
        size_t token_length = 0;

        while (*str && *str != delim && token_length < MAX_TOKEN_LENGTH - 1) {
            str++;
            token_length++;
        }

        if (token_length > 0) { // Copy the token to the static array
            for (size_t i = 0; i < token_length; i++) {
                tokens[token_index][i] = token_start[i];
            }
            tokens[token_index][token_length] = '\0'; // Null-terminate the token
            result[token_index] = tokens[token_index]; // Store the pointer to the token
            token_index++;
        }
    }

    result[token_index] = NULL; // Null-terminate the array of pointers

    return result;
}