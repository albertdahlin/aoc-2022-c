#include <stdio.h>
#include <inttypes.h>
#include "String.h"

static uint64_t isContained(
    uint64_t x1,
    uint64_t y1,
    uint64_t x2,
    uint64_t y2
) {
    return (x1 >= x2 && y1 <= y2) || (x1 <= x2 && y1 >= y2);
}

static uint64_t isOverlap(
    uint64_t x1,
    uint64_t y1,
    uint64_t x2,
    uint64_t y2
) {
    return (y1 >= x2 && y2 >= x1);
}

void Day4_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    uint8_t c;

    uint64_t pairs[3] = {0};
    size_t   idx = 0;
    uint64_t tmp = 0;

    for (size_t i = 0; i < input.length; i++) {
        c = input.data[i];

        // Assume c is only digits, dash, comma or whitespace.
        if (c >= '0') {
            // c must be a digit.
            // Parse digits to tmp integer.
            tmp = 10*tmp + c - '0';
        } else if (c > ' ') {
            // c must be comma or dash.
            // Done parsing a number, store it.
            pairs[idx] = tmp;
            idx += 1;
            tmp = 0;
        } else {
            // c must be whitespace.
            // Done parsing a line, check if things overlap etc.
            part1 += isContained(pairs[0], pairs[1], pairs[2], tmp);
            part2 += isOverlap(pairs[0], pairs[1], pairs[2], tmp);
            tmp = 0;
            idx = 0;
        }
    }

    sprintf(buffer.data, "%10lu %10lu", part1, part2);
}

