#include <time.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

#include <drivers/rtc.h>

void gmtime(tm* time){
    strcpy(time->date_str, get_date());
    strcpy(time->time_str, get_time());
}
