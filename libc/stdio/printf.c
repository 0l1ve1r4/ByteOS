#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#else
#error "You need to implement printf for user space"
#endif

static void printl(void) {
		terminalNewLine();	
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

void verify_ansi_colors(const unsigned char* format) {
    char ansi_code[max_ansicolor_size];    
    u8 ansi_index = 0;

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
            setTextColor(i);
            return;
        }
    }
}

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; i++) {
        switch (bytes[i]) {
        case '\033':
            verify_ansi_colors(&bytes[i]);
            i += max_ansicolor_size;
            break;
        
        case '\n':
            printl();
            break;
        
        case '\t':
            for (int j = 0; j < 4; j++) {
                if (putchar(' ') == EOF)
                    return false;
            }
            break;

        default:
            if (putchar(bytes[i]) == EOF)
                return false;
            break;
        }
    }

    return true;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        // Swap the characters
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* itoa(int num, char* buffer, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, as it won't be handled in the loop
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // Handle negative numbers for base 10
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';  // Handles hexadecimal numbers
        num = num / base;
    }

    // If the number is negative in base 10, append '-'
    if (isNegative)
        buffer[i++] = '-';

    buffer[i] = '\0';  // Append string terminator

    // Reverse the string since digits were added in reverse order
    reverse(buffer, i);

    return buffer;
}

int printf(const char * restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);
    int written = 0;

    while (*format != '\0') {
        size_t maxrem = I32_MAX - written;
        
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

         if (*format == 'c') {
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

    // Allocate a buffer large enough to hold the string representation of the integer
    char buffer[12]; // 12 bytes are enough to store an int in string format
    itoa(i, buffer, 10);  // Convert integer to string (base 10)
    
    size_t len = strlen(buffer); 
    if (!print(buffer, len)) 
        return -1; 
    written += len; 
}        else if (*format == 'f') {
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