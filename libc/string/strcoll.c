#include <string.h>

// A simplified version, not considering locale
int strcoll(const char *s1, const char *s2) {
    return strcmp(s1, s2); 
}
