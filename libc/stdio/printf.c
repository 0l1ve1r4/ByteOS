#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#else
#error "You need to implement printf for user space"
#endif

static void printl(void) {
		terminal_newline();	
}

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; i++) {
        if (bytes[i] == '\n') {            
            printl();
        } else {
            if (putchar(bytes[i]) == EOF)
                return false;
        }
    }
    return true;
}

const char* ansicolors[] = {
    "\033[30m", // Black
    "\033[34m", // Blue
    "\033[32m", // Green
    "\033[36m", // Cyan
    "\033[31m", // Red
    "\033[35m", // Magenta
    "\033[33m", // Brown
    "\033[37m", // Light Grey
    "\033[90m", // Dark Grey
    "\033[94m", // Light Blue
    "\033[92m", // Light Green
    "\033[96m", // Light Cyan
    "\033[91m", // Light Red
    "\033[95m", // Light Magenta
    "\033[93m", // Light Brown
    "\033[97m", // White
};
const int max_ansicolor_size = 6;

void verify_ansi_colors(const char* format) {
    char ansi_code[max_ansicolor_size];
    uint8_t ansi_index = 0;

    // Copy the ANSI code into ansi_code array
    while (*format != 'm' && ansi_index < max_ansicolor_size - 1) {
        ansi_code[ansi_index] = *format;
        format++;
        ansi_index++;
    }

    ansi_code[ansi_index] = 'm';
    ansi_code[ansi_index + 1] = '\0';

    // Check if the ANSI code is valid
    for (int i = 0; i < 16; i++) {
        if (strcmp(ansi_code, ansicolors[i]) == 0) {
            set_text_color(i);
            return;
        }
    }
}


int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);
    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;
        
        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'm') {
            format++;
            const char* color = va_arg(parameters, const char*);
            verify_ansi_colors(color);
        }

        else if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        } else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        } else if (*format == 'i' || *format == 'd') {
            format++;
            int i = va_arg(parameters, int);
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%d", i);
            size_t len = strlen(buffer);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(buffer, len))
                return -1;
            written += len;  
        } else if (*format == 'f') {
            format++;
            double f = va_arg(parameters, double);
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "%f", f);
            size_t len = strlen(buffer);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(buffer, len))
                return -1;
            written += len;
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }
    va_end(parameters);
    return written;
}