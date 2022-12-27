#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"


#define GRID_SIZE 256
typedef uint8_t Grid[GRID_SIZE][GRID_SIZE];

typedef struct {
    int32_t x;
    int32_t y;
} Point;


static Point moveTail(Point head, Point tail)
{
    int32_t dx = (head.x - tail.x) / 2;
    int32_t dy = (head.y - tail.y) / 2;

    if (dx && dy) {
        tail.x += dx;
        tail.y += dy;
    } else if (dx) {
        tail.x += dx;
        tail.y = head.y;
    } else if (dy) {
        tail.x = head.x;
        tail.y += dy;
    }

    return tail;
}


static inline bool isFirstVisit(Grid grid, Point point, uint64_t part)
{
    size_t x = point.x + GRID_SIZE / 2;
    size_t y = point.y + GRID_SIZE / 2;

    if (grid[y][x] & part) {
        return false;
    }

    grid[y][x] |= part;

    return true;
}

void Day9_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    char *str = input.data;
    char dir, n1, n2;

    Grid grid = {0};

    uint64_t distance;
    Point rope[16] = {0};

    for (size_t i = 3; i < input.length; i += 4) {
        dir = str[i-3];
        n1 = str[i-1];
        n2 = str[i];

        distance = n1 - '0';

        if (n2 >= '0') {
            distance = distance * 10 + n2 - '0';
            i += 1;
        }

        int32_t dx = 0;
        int32_t dy = 0;
        switch (dir) {
            case 'U':
                dy = 1;
                break;

            case 'R':
                dx = 1;
                break;

            case 'D':
                dy = -1;
                break;

            case 'L':
                dx = -1;
                break;

            default:
                printf("Not a direction");
                goto fail;
        }

        while (distance > 0) {
            distance -= 1;
            rope[0].x += dx;
            rope[0].y += dy;

            for (size_t i = 1; i < 10; i++) {
                rope[i] = moveTail(rope[i-1], rope[i]);
            }

            if (isFirstVisit(grid, rope[1], 1)) {
                part1 += 1;
            }

            if (isFirstVisit(grid, rope[9], 2)) {
                part2 += 1;
            }
        }
    }

    snprintf(buffer.data, buffer.length, "%14lu %14lu", part1, part2);
    fail:
    return;
}
