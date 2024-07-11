#ifndef _TIME_H
#define _TIME_H 1

#include <sys/cdefs.h>
#include <stddef.h>

/* everything here is TODO, except for the RTC functions and
asctime that needs re-implementation */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* date_str; // Extra built-in
    char* time_str; // Extra built-in

} tm;

/* Get the current date UTC */
void gmtime(tm* time);

/* Get the current date of the local time */
tm *localtime(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TIME_H */
