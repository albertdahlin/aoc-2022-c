#pragma once
#include <stdbool.h>

typedef struct {
    char *data;
    size_t length;
} String;

#define skipUntil(exp) \
    while (!(exp) && cur < end) cur++

#define skipLine() \
    skipUntil(*cur == '\n')


static inline bool Char_isDigit(char c)
{
    return ('0' <= c && c <= '9');
}


#define parseInt(var) \
    var = 0; \
    if (!Char_isDigit(*cur)) goto error; \
    while (Char_isDigit(*cur) && cur < end) { \
        var = var * 10 + *cur - '0'; \
        cur++; \
    }

