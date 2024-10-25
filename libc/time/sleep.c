#include <time.h>

// TODO: PIT Driver
void sleep(u32 count){
    while (count--) {
        asm volatile("nop"); 
    }
}