#pragma once
#include <stdbool.h>

typedef struct {
    char *data;
    size_t length;
} String;


static inline bool Char_isDigit(char c)
{
    return ('0' <= c && c <= '9');
}


