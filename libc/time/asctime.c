#include <time.h>
#include <string.h>

char* asctime(void){
    static char buffer[20];
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    strcat(buffer, get_date());
    strcat(buffer, " ");
    strcat(buffer, get_time());

    return buffer;
}