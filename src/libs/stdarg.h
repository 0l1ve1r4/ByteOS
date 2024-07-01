#ifndef KSTDARG_H
#define KSTDARG_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

typedef char* va_list;

// Macro to align size to the nearest multiple of `align`
#define ALIGN_SIZE(size, align) (((size) + (align) - 1) & ~((align) - 1))

// Macro to get the size of an argument type, aligned to the size of `int`
#define VA_ARG_SIZE(type) ALIGN_SIZE(sizeof(type), sizeof(int))

// Macro to initialize the `va_list` with the address of the first argument
#define va_start(ap, param) (ap = (va_list)&param + VA_ARG_SIZE(param))

// Macro to retrieve the next argument from the `va_list`
#define va_arg(ap, type) (*(type*)((ap += VA_ARG_SIZE(type)) - VA_ARG_SIZE(type)))

// Macro to end the use of the `va_list`
#define va_end(ap) (ap = (va_list)0)

#endif // KSTDARG_H
