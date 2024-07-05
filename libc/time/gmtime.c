#include <time.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

#include <drivers/rtc.h>

tm *gmtime(void){
    static tm time;
    static char date_buffer[20];
    static char time_buffer[20];
    strcpy(date_buffer, get_date());
    strcpy(time_buffer, get_time());

    time.date_str = date_buffer;
    time.time_str = time_buffer;

    return &time; 
}