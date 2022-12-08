#include <inttypes.h>
#include <stdio.h>
#include "String.h"


// We use raw string input as our matrix and it contains
// \n on each row. This would screw up the width and grid[y][x]
#define at(x, y) grid.trees[y * grid.offsetY + x]


typedef struct {
    char *trees;
    size_t width;
    size_t height;
    size_t offsetY;
} Grid;


static uint64_t distanceLeft(
    int x,
    int y,
    Grid grid
) {
    uint8_t tree = at(x, y);
    uint64_t distance = 0;

    for (int i = x-1; i >= 0; i--) {
        distance += 1;
        if (at(i, y) >= tree) {
            return distance;
        }
    }

    // ~ infinity
    return -1;
}

static uint64_t distanceRight(
    int x,
    int y,
    Grid grid
) {
    uint8_t tree = at(x, y);
    uint64_t distance = 0;

    for (int i = x+1; i < grid.width; i++) {
        distance += 1;
        if (at(i, y) >= tree) {
            return distance;
        }
    }

    // ~ infinity
    return -1;
}

static uint64_t distanceUp(
    int x,
    int y,
    Grid grid
) {
    uint8_t tree = at(x, y);
    uint64_t distance = 0;

    for (int i = y-1; i >= 0; i--) {
        distance += 1;
        if (at(x, i) >= tree) {
            return distance;
        }
    }

    // ~ infinity
    return -1;
}

static uint64_t distanceDown(
    int x,
    int y,
    Grid grid
) {
    uint8_t tree = at(x, y);
    uint64_t distance = 0;

    for (int i = y+1; i < grid.height; i++) {
        distance += 1;
        if (at(x, i) >= tree) {
            return distance;
        }
    }

    // ~ infinity
    return -1;
}

static uint64_t min(uint64_t a, uint64_t b)
{
    return (a > b) ? b : a;
}

void Day8_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    size_t height = 99;
    size_t width = 99;

    for (size_t i = 0; i < input.length; i++) {
        if (input.data[i] == '\n') {
            width = i;
            height = i;
            break;
        }
    }
    Grid grid = {
        input.data,
        width,
        height,
        (height + 1)
    };

    for (size_t y = 0; y < grid.height; y++) {
        for (size_t x = 0; x < grid.width; x++) {
            uint64_t left   = distanceLeft(x, y, grid);
            uint64_t right  = distanceRight(x, y, grid);
            uint64_t up     = distanceUp(x, y, grid);
            uint64_t down   = distanceDown(x, y, grid);

            uint64_t score =
                min(up, y)
                * min(down, grid.height - y - 1)
                * min(x, left)
                * min(right, grid.width - x - 1);

            uint64_t visible =
                (left > x)
                || (right > grid.width)
                || (up > y)
                || (down > grid.height);

            part1 += visible;

            if (score > part2) part2 = score;
        }
    }

    snprintf(buffer.data, buffer.length, "%10lu %10lu", part1, part2);
}

