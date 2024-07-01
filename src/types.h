// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef TYPES_H
#define TYPES_H

// FUNCTIONS PROTOTYPE
#define _PROTOTYPE(function, params) function params

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long int  uint64_t;

typedef signed char             int8_t;
typedef signed short int        int16_t;
typedef signed int              int32_t;

typedef uint32_t                size_t;
typedef uint8_t                 bool;   

#define TRUE                    (uint8_t) 1
#define FALSE                   (uint8_t) 0
#define NULL                    0L

#define EXIT_SUCCESS            (uint8_t) 0
#define EXIT_FAILURE            (uint8_t) 1

#define MAX_UINT32              0xFFFFFFFF
#define MAX_UINT16              0xFFFF
#define MAX_UINT8               0xFF

#define MAX_INT32               0x7FFFFFFF
#define MAX_INT16               0x7FFF
#define MAX_INT8                0x7F   

#define MAX_FLOAT_STR_SIZE      (uint8_t)   20
#define MAX_UINT32_STR_SIZE     (uint8_t)   10
#define MAX_UINT16_STR_SIZE     (uint8_t)   5
#define MAX_UINT8_STR_SIZE      (uint8_t)   3

#define MAX_INT32_STR_SIZE      (uint8_t)   11   
#define MAX_INT16_STR_SIZE      (uint8_t)   6
#define MAX_INT8_STR_SIZE       (uint8_t)   4

#define KB                      (uint16_t)  1024
#define MB                      (uint32_t)  1024 * 1024
#define GB                      (uint32_t)  1024 * 1024 * 1024
#define BUFFER_SIZE             (uint8_t)   255 

#endif // TYPES_H