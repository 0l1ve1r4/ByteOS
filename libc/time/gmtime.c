#include <time.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

#include <drivers/rtc.h>

void gmtime(tm* time){
    strncpy(time->date_str, get_date(), 9);
    strncpy(time->time_str, get_time(), 9);
}
