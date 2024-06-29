#ifndef _TYPES_H
#define _TYPES_H

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
#define BUFFER_SIZE 256 

#define KB (uint32_t) 1024
#define MB (uint32_t) 1024 * 1024
#define GB (uint32_t) 1024 * 1024 * 1024

#endif