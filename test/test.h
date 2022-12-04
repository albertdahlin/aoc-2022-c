#define RUN(fn, input, p1, p2) \
    printf("Input: %s\nResult:  ", input); \
    fn(String_fromLit(input)); \
    printf("\nCorrect: %10s %10s\n\n", p1, p2)

#define EXPECT(expr, fmt, ...) \
    if (expr) { \
        printf("%4.d: %s -> OK\n", __LINE__, #expr); \
    } else { \
        fprintf(stderr, "\e[91m%4.d: %s -> " fmt "\e[0m\n", __LINE__, #expr, ##__VA_ARGS__); \
    }
