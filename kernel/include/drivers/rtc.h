/* Real Time Clock Driver, references: 
    * https://github.com/jakeSteinburger/SpecOS/blob/main/drivers/rtc.h 
    * https://developer.toradex.com/software/linux-resources/linux-features/real-time-clock-rtc-linux/ */

#ifndef RTC_H
#define RTC_H

#include <types.h>

struct rtc_time {
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

/* Get the current date */
const char* get_date(void);

/* Get the current time in UTC */
const char* get_time(void);

u8 rtc_initialize(void);

#endif /* RTC_H */