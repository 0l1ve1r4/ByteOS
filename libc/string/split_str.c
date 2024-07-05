#include <string.h>
#include <stdint.h>

char** split_str(const char* str, char delim) {
    static char tokens[UINT8_MAX][UINT8_MAX];       // Static array for tokens
    static char* result[UINT8_MAX + 1];              // Static array for pointers to tokens
    size_t token_index = 0;

    while (*str && token_index < UINT8_MAX) {
        while (*str == delim) { // Skip delimiters
            str++;
        }

        const char* token_start = str; // Find the end of the token
        size_t token_length = 0;

        while (*str && *str != delim && token_length < UINT8_MAX - 1) {
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