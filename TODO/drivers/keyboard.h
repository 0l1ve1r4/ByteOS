/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_initialize(void);     // Initialize the keyboard
void keyboard_scanf(char *buffer);  // Read the keyboard input and store it in buffer

#endif