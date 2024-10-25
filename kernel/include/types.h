//========================================================================
//    This file is part of ByteOS.
//    Copyright (C) 2024 Guilherme Oliveira Santos
//    This is free software: you can redistribute it and/or modify it 
//    under the terms of the GNU GPL3 or (at your option) any later version. 
//	
//	* File: types.h 
//	* Sources: 
//	* Description: Basic system types (names inspired by terry davis)  
//========================================================================

//========================================================================
 	                            #ifndef TYPES_H
                                #define TYPES_H
//========================================================================

//========================================================================
// 	                                DEFINES
//========================================================================

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef void                u0;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;

typedef signed   char       i8;
typedef signed   short      i16;
typedef signed   int        i32;

typedef float               f32;
typedef double              f64;

typedef unsigned char       bool;
typedef unsigned long       size_t;
typedef unsigned long       uintptr_t;

#define false               0
#define true                1

//========================================================================
 	                                #endif
//========================================================================