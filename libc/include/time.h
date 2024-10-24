#ifndef _TIME_H
#define _TIME_H 1

#include <sys/cdefs.h>
#include <stddef.h>
#include <types.h>

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
// NOTE: Not always 100% accurate as RTC can be re-programmed to use localtime instead of gmtime
// Which is especially deceiving if there's another OS running/has been run before
void gmtime(tm* time);

void sleep(u32 count);

/* Get the current date of the local time */
// TODO: localtime. Will require Time protocol and syncing with either LAN or a public time server (Not yet available, networking stack first).
// tm *localtime(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TIME_H */
