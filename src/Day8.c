#include <inttypes.h>
#include <stdio.h>
#include "String.h"


// We use raw string input as our matrix and it contains
// '\n' at the end of each row.
// This would screw up the width and grid[y][x]
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

    for (int i = x-1; i >= 0; i--) {
        if (at(i, y) >= tree) {
            return x-i;
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

    for (int i = x+1; i < grid.width; i++) {
        if (at(i, y) >= tree) {
            return i - x;
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

    for (int i = y-1; i >= 0; i--) {
        if (at(x, i) >= tree) {
            return y - i;
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

    for (int i = y+1; i < grid.height; i++) {
        if (at(x, i) >= tree) {
            return i - y;
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

    /*
    for (size_t i = 0; i < input.length; i++) {
        if (input.data[i] == '\n') {
            width = i;
            height = i;
            break;
        }
    }
    */
    Grid grid = {
        input.data,
        width,
        height,
        (height + 1)
    };

    // Since trees on the edges are always visible we can save
    // some time not evaulating them. We just add the number of 
    // trees in all 4 edges to the starting value.
    part1 = 4 * grid.width - 4;


    for (size_t y = 1; y < grid.height - 1; y++) {
        for (size_t x = 1; x < grid.width - 1; x++) {
            // Get the visible distance from x,y in each direction.
            // Value 0xFF..F is for infinity when visibility is
            // past the edge.
            uint64_t left   = distanceLeft(x, y, grid);
            uint64_t right  = distanceRight(x, y, grid);
            uint64_t up     = distanceUp(x, y, grid);
            uint64_t down   = distanceDown(x, y, grid);

            // For some reason the code runs faster if
            // score (part2) is evaluated before visibility (part1)
            uint64_t score =
                min(up, y)
                * min(down, grid.height - y - 1)
                * min(x, left)
                * min(right, grid.width - x - 1);

            if (score > part2) part2 = score;

            uint64_t isAnyVisible =
                (left > x)
                || (right > grid.width)
                || (up > y)
                || (down > grid.height);

            part1 += isAnyVisible;



        }
    }

    snprintf(buffer.data, buffer.length, "%10lu %10lu", part1, part2);
}

