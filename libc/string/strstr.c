#include <string.h>

char *strstr(const char *s1, const char *s2) {
    if (*s2 == '\0') {
        return (char *)s1;
    }

    for (const char *p1 = s1; *p1; p1++) {
        const char *p1_sub = p1, *p2 = s2;
        while (*p1_sub && *p2 && *p1_sub == *p2) {
            p1_sub++;
            p2++;
        }
        if (*p2 == '\0') {
            return (char *)p1;
        }
    }
    return NULL;
}
