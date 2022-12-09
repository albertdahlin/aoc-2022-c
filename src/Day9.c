#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"


typedef struct {
    int64_t x;
    int64_t y;
} Point;


static Point moveTail(Point head, Point tail)
{
    int64_t dx = (head.x - tail.x) / 2;
    int64_t dy = (head.y - tail.y) / 2;

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

void Day9_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    char *str = input.data;
    char dir, n1, n2;

    uint8_t grid[1024][1024] = {0};

    uint64_t distance;
    Point head = {0};
    Point tails[9] = {0};

    for (size_t i = 3; i < input.length; i += 4) {
        dir = str[i-3];
        n1 = str[i-1];
        n2 = str[i];

        distance = n1 - '0';

        if (n2 >= '0') {
            distance = distance * 10 + n2 - '0';
            i += 1;
        }

        while (distance > 0) {
            switch (dir) {
                case 'U':
                    head.y += 1;
                    break;

                case 'R':
                    head.x += 1;
                    break;

                case 'D':
                    head.y -= 1;
                    break;

                case 'L':
                    head.x -= 1;
                    break;

                default:
                    printf("Not a direction");
                    goto fail;
            }
            distance -= 1;
            tails[0] = moveTail(head, tails[0]);

            for (size_t i = 1; i < 9; i++) {
                tails[i] = moveTail(tails[i-1], tails[i]);
            }

            // Use first bit for part 1
            grid[tails[0].y + 512][tails[0].x + 512] |= 1;
            // Use second bit for part 2
            grid[tails[8].y + 512][tails[8].x + 512] |= 2;
        }
    }

    for (size_t y = 0; y < 1024; y++) {
        for (size_t x = 0; x < 1024; x++) {
            part1 += grid[y][x] & 1;
            part2 += (grid[y][x] & 2) >> 1;
        }
    }

    snprintf(buffer.data, buffer.length, "%10lu %10lu", part1, part2);
    fail:
    return;
}

