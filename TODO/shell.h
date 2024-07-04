/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <stddef.h>

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch" // Ignore GCC warning

#define OS_PROMPT " _               _       ___  ____  \n"\
                  "| |__   __ _ ___(_) ___ / _ \\/ ___| \n"\
                  "| '_ \\ / _` / __| |/ __| | | \\___ \\ \n"\
                  "| |_) | (_| \\__ \\ | (__| |_| |___) |\n"\
                  "|_.__/ \\__,_|___/_|\\___|\\___/|____/ \n"\
                  "A x86 kernel written from scratch!\n\n"

#define MAX_COMMAND_LENGTH 100      

void shell_initialize (void);

#endif // SHELL_H