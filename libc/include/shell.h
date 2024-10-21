/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef SHELL_H
#define SHELL_H 1

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif
                            
#define MAX_COMMAND_LENGTH 100      

void shell_initialize (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SHELL_H