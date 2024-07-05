/* Real Time Clock Driver, references: 
    * https://github.com/jakeSteinburger/SpecOS/blob/main/drivers/rtc.h 
    * https://developer.toradex.com/software/linux-resources/linux-features/real-time-clock-rtc-linux/ */

#ifndef RTC_H
#define RTC_H

#include <stdint.h>

/* Get the current date */
const char* get_date(void);

/* Get the current time in UTC */
const char* get_time(void);

#endif /* RTC_H */