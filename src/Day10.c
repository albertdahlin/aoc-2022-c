#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"

#define SKIP(n) i += n;
#define CURRENT_CHAR str[i]
#define PUT_CHAR(c) *out = c;out++

void Day10_solve(String input, String buffer)
{
    uint64_t part1 = 0;

    char *str = input.data;
    char *out = buffer.data + 256;

    int64_t addxPending[2] = {0};
    int64_t xReg = 1;
    int64_t cyclesPending = 0;
    int64_t cycle = 1;

    for (int64_t i = 0; i < input.length; i++) {
        int64_t num = 0;
        int64_t sign = 1;

        if (CURRENT_CHAR == 'a') {
            SKIP(5);
            if (CURRENT_CHAR == '-') {
                sign = -1;
                SKIP(1);
            }

            if (CURRENT_CHAR >= '0') {
                num = num * 10 + CURRENT_CHAR - '0';
                SKIP(1);
            }
            if (CURRENT_CHAR >= '0') {
                num = num * 10 + CURRENT_CHAR - '0';
                SKIP(1);
            }
            cyclesPending = 2;
            num *= sign;
            addxPending[(cycle + 2) % 2] = num;
        }

        if (CURRENT_CHAR == 'n') {
            SKIP(4);
            cyclesPending = 1;
        }

        while (cyclesPending > 0) {
            int64_t col = (cycle - 1) % 40;

            if (labs(xReg - col) <= 1) {
                PUT_CHAR('#');
            } else {
                PUT_CHAR('.');
            }
            if (col == 39) {
                PUT_CHAR('\n');
            }

            cycle += 1;
            xReg += addxPending[cycle % 2];
            addxPending[cycle % 2] = 0;
            cyclesPending -= 1;

            if ((cycle + 20) % 40 == 0) {
                part1 += cycle * xReg;
            }
        }
    }

    sprintf(buffer.data, "%10lu \n%.245s", part1, buffer.data+256);
}

