#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"

#define push(arr, item) arr[arr##_len] = item; arr##_len += 1
#define CHAR input.data[i]
#define SKIP_TO_DIGIT() for (;i < input.length && !Char_isDigit(CHAR); i++)
#define PARSE_NUMBER(v) \
    (v) = CHAR - '0'; \
    i += 1; \
    for (;i < input.length && Char_isDigit(CHAR); i++) { \
        (v) = (v) * 10 + CHAR - '0'; \
    }


typedef int16_t Number;

typedef struct {
    int16_t value;
    uint16_t next;
    uint16_t prev;
    uint16_t flags;
} Node;

static size_t parse(String input, Number *numbers)
{
    size_t numbers_len = 0;
    Number num = 0;

    for (size_t i = 0; i < input.length; i++) {
        if (CHAR == 'Q') break;
        int16_t sign = 1;
        if (CHAR == '-') {
            sign = -1;
            i++;
        }
        PARSE_NUMBER(num);
        num *= sign;
        push(numbers, num);
    }

    return numbers_len;
}

void shiftForward(Number *numbers, size_t at, size_t n)
{
    Number num = numbers[at];
    printf("fowrward at %zu %d, %zu\n", at, numbers[at], n);
    assert((at + n) < 7);

    for (size_t i = at + 1; i <= at + n; i++) {
        numbers[i - 1] = numbers[i];
    }

    numbers[at+n] = num;
}

void shiftBackward(Number *numbers, size_t at, size_t n)
{
    Number num = numbers[at];
    assert((at - n) >= 0);
    printf("backward %d %zu\n", numbers[at], n);

    for (size_t i = at; i > at - n; i--) {
        numbers[i] = numbers[i-1];
    }

    numbers[at-n] = num;
}

Node move(Node *list, Node node, int16_t n)
{
    if (n == 0) {
        return node;
    } else if (n > 0) {
        while (n > 0) {
            node = list[node.next];
            n -= 1;
        }
    } else {
        while (n < 0) {
            node = list[node.prev];
            n += 1;
        }
    }

    return node;
}

static void delete(Node *list, Node node)
{
    Node prev = list[node.prev];
    Node next = list[node.next];
    prev.next = node.next;
    next.prev = node.prev;
}

void Day20_solve(String input, String buffer)
{
    int64_t part1 = 0;
    int64_t part2 = 0;

    /*
    Number *numbers = (Number*)buffer.data;
    size_t numbers_len = parse(input, numbers);

    Node *list = (Node*)&numbers[numbers_len];

    Node node;

    for (size_t i = 0; i < numbers_len; i++) {
        node.next = i + 1;
        node.prev = i - 1;
        node.value = numbers[i];
        list[i + 1] = node;
    }

    list[1].prev = numbers_len;
    list[numbers_len].next = 0;

    size_t pos = 2;

    node = list[1];
    delete(list, node);

    do {
        node = list[pos];
        int16_t val = numbers[pos];
        printf("%d\n", val);
    } while (pos = node.next);

    //node = move(list, node, -3);
    //printf("node %d\n", node.value);


    for (size_t i = 0; i < input.length; i++) {
        Number num = numbers[i];
        int16_t shift = num.value;
        if (num.value > 0) {
            if ((i + num.value) >= numbers_len) {
                shift = -numbers_len + num.value;
            }
        } else {
            if (num.value < -i) {
                shift = num.value + numbers_len - i;
            }
        }
        if (shift > 0) {
            shiftForward(numbers, i, shift);
        } else {
            shiftBackward(numbers, i, -shift);
        }
    }
    */


    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}

