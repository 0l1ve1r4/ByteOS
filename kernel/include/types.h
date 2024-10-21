#ifndef TYPES_H
#define TYPES_H

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

#endif /* TYPES_H */
