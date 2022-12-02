#define RUN(fn, input) \
    printf("%s\n", input); \
    fn(String_fromLit(input)); \
    printf("\n\n")

#define EXPECT(expr, fmt, ...) \
    if (expr) { \
        printf("%4.d: %s -> OK\n", __LINE__, #expr); \
    } else { \
        fprintf(stderr, "\e[91m%4.d: %s -> " fmt "\e[0m\n", __LINE__, #expr, ##__VA_ARGS__); \
    }
