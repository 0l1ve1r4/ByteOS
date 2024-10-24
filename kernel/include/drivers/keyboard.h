#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <types.h>

/*  Handle the keyboard interrupt */
void keyboard_handler(void);        

/* Initialize the keyboard */
void keyboard_initialize(void);      

u8 keyboardDriverGetChar(void);

/* Read the keyboard input and store it in buffer */
void keyboard_scanf(char *buffer);   

#endif