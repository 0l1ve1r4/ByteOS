#include <stdlib.h>
#include <types.h>

#include <stdarg.h>

/* Internal helper functions */
int snprintf_string(char *s, size_t n, const char *str, int precision);
int snprintf_char(char *s, size_t n, int c); 
int vsnprintf_internal(char *s, size_t n, const char *format, va_list args);

/* Write formatted output to sized buffer */
int snprintf(char * restrict s, size_t n, const char * restrict format, ...) {
    va_list args;
    int count;

    va_start(args, format);
    count = vsnprintf_internal(s, n, format, args);
    va_end(args);

    return count;
}

int vsnprintf_internal(char *s, size_t n, const char *format, va_list args) {
    int written = 0;
    int ret;

    while (*format != '\0')
    {
        if (*format == '%')
        {
            const char *fmt = format;
            int width = 0;
            int precision = -1;
            int skip = 0;

            // Parse format specifier
            format++;
            if (*format == '-')
            {
                // Left align
                skip = 1;
                format++;
            }

            // Parse width
            while (*format >= '0' && *format <= '9')
            {
                width = width * 10 + (*format - '0');
                format++;
            }

            // Parse precision
            if (*format == '.')
            {
                format++;
                precision = 0;
                while (*format >= '0' && *format <= '9')
                {
                    precision = precision * 10 + (*format - '0');
                    format++;
                }
            }

            // Handle format specifier
            switch (*format)
            {
                case 'c': // Character
                    ret = snprintf_char(s, n, va_arg(args, int));
                    break;
                case 's': // String
                    ret = snprintf_string(s, n, va_arg(args, const char *), precision);
                    break;
                // Handle other format specifiers as needed (e.g., %d, %x, %f)
                // Remember to increment 's' and decrement 'n' accordingly.
                default:
                    // Handle unsupported format specifier
                    ret = snprintf_string(s, n, fmt, 0); // Print the original format string
                    skip = 1;
                    break;
            }

            format++;
            if (skip) continue;

            written += ret;
            s += ret;
            n -= ret;
        }
        else
        {
            if (n > 1)
            {
                *s++ = *format;
                n--;
            }
            else
            {
                break;
            }
            written++;
        }
        format++;
    }

    if (n > 0)
        *s = '\0';

    return written;
}

int snprintf_char(char *s, size_t n, int c)
{
    if (n > 1)
    {
        *s = (char)c;
        *(s + 1) = '\0';
        return 1;
    }
    return 0;
}

int snprintf_string(char *s, size_t n, const char *str, int precision)
{
    int len = 0;
    while (*str && (precision < 0 || len < precision))
    {
        if (n > 1)
        {
            *s++ = *str++;
            n--;
        }
        len++;
    }
    if (n > 0)
        *s = '\0';
    return len;
}
