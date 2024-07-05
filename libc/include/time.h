#ifndef _TIME_H
#define _TIME_H 1

#include <sys/cdefs.h>
#include <drivers/rtc.h>

#include <stddef.h>

/* everything here is TODO, except for the RTC functions and
asctime that needs re-implementation */

#ifdef __cplusplus
extern "C" {
#endif

struct tm {
    int tm_sec;   
    int tm_min;   
    int tm_hour;    
    int tm_mday;  
    int tm_mon;   
    int tm_year;  
    int tm_wday;   
    int tm_yday;  
    int tm_isdst;  
};

typedef long clock_t;
typedef long time_t;

/* Number of clock ticks per second */
clock_t clock(void);        

/* Get the difference between two times */
double difftime(time_t time1, time_t time0);

/* Convert tm structure to time_t */
time_t mktime(struct tm *timeptr);

/* Get the current date */
time_t time(time_t *timer);

/* Convert time_t to tm structure */
char *asctime(void); // temporary implementation
//char *asctime(const struct tm *timeptr);

/* Convert time_t to string */
char *ctime(const time_t *timer);

/* Get the current date */
struct tm *gmtime(const time_t *timer);

/* Get the current date */
struct tm *localtime(const time_t *timer);

/* Format time as string */
size_t strftime(char * restrict s, size_t maxsize, const char * restrict format, const struct tm * restrict timeptr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TIME_H */