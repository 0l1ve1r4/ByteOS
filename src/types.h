#ifndef _TYPES_H
#define _TYPES_H

// Define some types
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;

typedef signed char             int8_t;
typedef signed short int        int16_t;
typedef signed int              int32_t;

typedef uint8_t                 bool;   
typedef uint32_t size_t;

#define TRUE                    (uint8_t) 1
#define FALSE                   (uint8_t) 0
#define NULL                    0L

// Screen constants
#define LINES (uint8_t) 25
#define COLUMNS_IN_LINE (uint8_t) 80
#define BYTES_EACH_ELEMENT (uint8_t) 2
#define LINE_SIZE (uint16_t) (COLUMNS_IN_LINE * BYTES_EACH_ELEMENT)
#define SCREENSIZE (uint16_t) (BYTES_EACH_ELEMENT * COLUMNS_IN_LINE * LINES)

#define MAX_UINT32 0xFFFFFFFF
#define MAX_UINT16 0xFFFF
#define MAX_UINT8 0xFF

#define MAX_INT32 0x7FFFFFFF
#define MAX_INT16 0x7FFF
#define MAX_INT8 0x7F   

#define MAX_UINT32_STR_SIZE 10
#define MAX_UINT16_STR_SIZE 5
#define MAX_UINT8_STR_SIZE 3

#define MAX_INT32_STR_SIZE 11   
#define MAX_INT16_STR_SIZE 6
#define MAX_INT8_STR_SIZE 4

// Useful constants
#define KB (uint32_t) 1024
#define MB (uint32_t) 1024 * 1024
#define GB (uint32_t) 1024 * 1024 * 1024
#define BUFFER_SIZE 256 

#endif