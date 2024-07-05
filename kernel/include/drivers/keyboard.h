#ifndef KEYBOARD_H
#define KEYBOARD_H

/*  Handle the keyboard interrupt */
void keyboard_handler(void);        

/* Initialize the keyboard */
void keyboard_initialize(void);      

/* Read the keyboard input and store it in buffer */
void keyboard_scanf(char *buffer);   

#endif