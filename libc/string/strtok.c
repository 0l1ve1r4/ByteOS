#include <string.h>

char *strtok(char *restrict s1, const char *restrict s2) {
    static char *lasts;

    if (s1 == NULL) {
        s1 = lasts;
    }
    if (s1 == NULL) {
        return NULL;
    }

    s1 += strspn(s1, s2);
    if (*s1 == '\0') {
        lasts = NULL;
        return NULL;
    }

    char *token_end = s1 + strcspn(s1, s2);
    if (*token_end != '\0') {
        *token_end = '\0';
        lasts = token_end + 1;
    } else {
        lasts = NULL;
    }

    return s1;
}
