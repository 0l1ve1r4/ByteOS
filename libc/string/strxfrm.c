#include <string.h>

size_t strxfrm(char *restrict s1, const char *restrict s2, size_t n) {
    size_t len = strlen(s2);
    if (n > 0) {
        size_t copy_len = (len < n - 1) ? len : n - 1;
        memcpy(s1, s2, copy_len);
        s1[copy_len] = '\0';
    }
    return len;
}