#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include "String.h"

#define at(x, y) ((y) * 400 + ((x - 200)))
static int64_t max(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int64_t min(int64_t a, int64_t b)
{
    return a < b ? a : b;
}

#define for_range(a, b, x) for (int64_t x = min(a, b); x <= max(a, b); x++)


void draw(uint8_t *matrix, int64_t xMin, int64_t xMax, int64_t yMin, int64_t yMax)
{
    for (int64_t y = 0; y < yMax + 3; y++) {
        for (int64_t x = 400; x < 600; x++) {
            if (matrix[at(x, y)] > 0) {
                printf("%c", matrix[at(x,y)]);
            } else if (x == 500) {
                printf(":");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

    printf("\n");
}

void Day14_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    char *str = input.data;

    int64_t xMin = 0xFFFF;
    int64_t yMin = 0xFFFF;

    int64_t xMax = -0xFFFF;
    int64_t yMax = -0xFFFF;

    int64_t x1 = 0;
    int64_t y1 = 0;

    int64_t x0 = 0;
    int64_t y0 = 0;

    uint8_t *matrix = (uint8_t*)buffer.data;

    for (size_t i = 0; i < input.length; i++) {
        if (Char_isDigit(str[i])) {
            x1 = 0;
            y1 = 0;
            for (; i < input.length && Char_isDigit(str[i]); i++) {
                x1 = x1*10 + str[i] - '0';
            }
            assert(str[i] == ',');
            i += 1;
            for (; i < input.length && Char_isDigit(str[i]); i++) {
                y1 = y1*10 + str[i] - '0';
            }

            //printf("%ld %ld\n", x1, y1);
            xMin = min(xMin, x1);
            yMin = min(yMin, y1);
            xMax = max(xMax, x1);
            yMax = max(yMax, y1);

            if (x0 && x0 == x1) {
                for_range (y0, y1, y) {
                    matrix[at(x1, y)] = '#';
                }
            } else if (y0 && y0 == y1) {
                for_range (x0, x1, x) {
                    matrix[at(x, y1)] = '#';
                }
            }

            x0 = x1;
            y0 = y1;
        }
        if (str[i] == '\n') {
            x0 = 0;
            y0 = 0;
        }
    }

    for (size_t i = 0;; i++) {
        int64_t sandX = 500;
        int64_t sandY = 0;

        while (1) {
            if (sandY > yMax) {
                matrix[at(sandX, sandY)] = 'o';
                if (!part1) part1 = i;
                break;
            } else if (matrix[at(sandX, sandY + 1)] == 0) {
                sandY += 1;
            } else if (matrix[at(sandX - 1, sandY + 1)] == 0) {
                sandX -= 1;
                sandY += 1;
            } else if (matrix[at(sandX + 1, sandY + 1)] == 0) {
                sandX += 1;
                sandY += 1;
            } else {
                if (matrix[at(sandX, sandY)] > 0) {
                    part2 = i;
                    goto done;
                }
                matrix[at(sandX, sandY)] = 'o';
                break;
            }
        }
    }
    done:
    //draw(matrix, xMin, xMax, yMin, yMax);

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}

