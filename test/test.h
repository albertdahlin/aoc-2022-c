#pragma once

#include <String.h>

#define TEST_INIT() \
    char buffer[1024*32] = {0}; \
    String output = (String){ \
        buffer, \
        sizeof(buffer) \
    }

#define RUN(fn, input, p1, p2) \
    printf("Input:\n%s\n", input); \
    fn((String){input, sizeof(input) - 1}, output); \
    printf("\nResult:  %.30s", output.data); \
    printf("\nCorrect: %10s %10s\n\n", p1, p2)

#define EXPECT(expr, fmt, ...) \
    if (expr) { \
        printf("%4.d: %s -> OK\n", __LINE__, #expr); \
    } else { \
        fprintf(stderr, "\e[91m%4.d: %s -> " fmt "\e[0m\n", __LINE__, #expr, ##__VA_ARGS__); \
    }
