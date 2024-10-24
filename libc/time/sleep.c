#include <time.h>

void sleep(u32 count){
    while (count--) {
        asm volatile("nop"); 
    }
}