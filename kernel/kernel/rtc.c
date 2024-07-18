#include <drivers/rtc.h>
#include <utils/ports.h>

#include <stdio.h>

static const char* rtc_startup_time;
static const char* rtc_startup_date;   

enum CMOS_Registers {
    CMOS_ADDRESS = 0x70,
    CMOS_DATA = 0x71
};

static uint8_t get_RTC_register(int reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

static uint8_t get_time_unit(int reg) {
    uint8_t unit = get_RTC_register(reg);
    uint8_t registerB = get_RTC_register(0x0B);
    if (!(registerB & 0x04)) {
        if (reg == 0x04) {
            unit = ((unit & 0x0F) + (((unit & 0x70) / 16) * 10)) | (unit & 0x80);
        } else {
            unit = (unit & 0x0F) + ((unit / 16) * 10);
        }
    }
    return unit;
}

static char* unit_converter(uint8_t s1, uint8_t s2, uint8_t s3, char delimiter) {
    static char to_return[9];
    uint8_t units[] = {s1, s2, s3};

    for (int i = 0, j = 0; i < 3; ++i) {
        to_return[j++] = '0' + units[i] / 10;
        to_return[j++] = '0' + units[i] % 10;
        if (i < 2) {
            to_return[j++] = delimiter;
        }
    }
    to_return[8] = '\0';
    return to_return;
}

const char* get_date(void) {
    return unit_converter(get_time_unit(0x07), 
            get_time_unit(0x08), 
            get_time_unit(0x09), '/');
}

const char* get_time(void) {
    return unit_converter(get_time_unit(0x04), 
            get_time_unit(0x02), 
            get_time_unit(0x00), ':');
}

uint8_t rtc_initialize(void){
    rtc_startup_time = get_time();
    rtc_startup_date = get_date();

    return 0;

}