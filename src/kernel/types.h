#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;

typedef signed char             int8_t;
typedef signed short int        int16_t;
typedef signed int              int32_t;

typedef uint32_t size_t;

#define TRUE                    (uint8_t) 1
#define FALSE                   (uint8_t) 0
#define NULL                    0L

// Screen constants
#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_EACH_ELEMENT 2
#define SCREENSIZE BYTES_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#endif