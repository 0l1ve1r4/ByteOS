#include <string.h>

char *strpbrk(const char *s1, const char *s2) {
    while (*s1) {
        const char *p = s2;
        while (*p) {
            if (*s1 == *p) {
                return (char *)s1;
            }
            p++;
        }
        s1++;
    }
    return NULL;
}
