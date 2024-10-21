#include <string.h>
#include <types.h>

/* Count the number of tokens in a string */
size_t count_tokens(const char* str, char delim) {
    size_t count = 0;
    bool in_token = false;
    while (*str) {
        if (*str == delim) {
            in_token = false;
        } else if (!in_token) {                     
            in_token = true;
            count++;
        }
        str++;
    }
    return count;
}
