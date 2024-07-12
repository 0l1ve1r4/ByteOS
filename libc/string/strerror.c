#include <string.h>

enum strerrors {
    ENOERR = 0,
    EPERM = 1,
    ENOENT = 2,
    ESRCH = 3,
    EINTR = 4,
    EIO = 5,
};


char *strerror(int errnum) {
    static char buf[256];
    switch (errnum) {
        case ENOERR:
            return "No error";
        case EPERM:
            return "Operation not permitted";
        case ENOENT:
            return "No such file or directory";
        case ESRCH:
            return "No such process";
        case EINTR:
            return "Interrupted system call";
        case EIO:
            return "Input/output error";
        default:
            strncpy(buf, "Unknown error", 14);
            return buf;
    }
}
