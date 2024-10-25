/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 
	
	* File: pit.h 
	* Description: Programmable Interval Timer
	* Sources: https://wiki.osdev.org/Programmable_Interval_Timer
*/


/*========================================================================
# 	INCLUDES
========================================================================*/

#include <drivers/pit.h>
#include <utils/ports.h>

/*========================================================================
# 	DEFINES
========================================================================*/

/*========================================================================
# 	ENUMS
========================================================================*/


/*========================================================================
# 	STRUCTS
========================================================================*/

/*========================================================================
# 	FUNCTIONS
========================================================================*/

volatile u32 pit_ticks = 0;

void pit_handler(void) {
    ++pit_ticks;
}

u8 pitInitialize(u32 frequency) {
    u32 divisor = 1193180 / frequency; // 1193180 is the PIT base frequency

    outb(0x43, 0x36);           // Command byte to set the mode
    outb(0x40, divisor & 0xFF); // Set low byte of divisor
    outb(0x40, divisor >> 8);   // Set high byte of divisor

    // Enable interrupts and attach the handler (not shown here)

    return 0;

}

void pitSleep(u32 ms) {
    u32 target_ticks = pit_ticks + ms; // Calculate the target tick count

    while (pit_ticks < target_ticks) {
        // Busy-wait until the required time has passed
        // Optionally, you could put the CPU in a low-power state here if desired
    }
}

