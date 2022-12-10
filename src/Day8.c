#include <inttypes.h>
#include <stdio.h>
#include "String.h"


// We use raw string input as our matrix and it contains
// '\n' at the end of each row.
#define SIDE_LENGTH 99
#define INDEX(row, col) ((SIDE_LENGTH + 1) * (row) + (col))

static uint64_t distanceLeft(
    int64_t i,
    int64_t left,
    char *grid
) {
    uint8_t tree = grid[i];

    for (int64_t dist = 1; dist < left; dist++) {
        if (grid[i - dist] >= tree) {
            return dist;
        }
    }

    return left;
}

static uint64_t distanceRight(
    int64_t i,
    int64_t right,
    char *grid
) {
    uint8_t tree = grid[i];

    for (int64_t dist = 1; dist < right; dist++) {
        if (grid[i + dist] >= tree) {
            return dist;
        }
    }

    return right;
}

static uint64_t distanceUp(
    int64_t i,
    int64_t up,
    char *grid
) {
    uint8_t tree = grid[i];

    for (int64_t dist = 1; (dist < up); dist++) {
        if (grid[i - (SIDE_LENGTH+1)*dist] >= tree) {
            return dist;
        }
    }

    return up;
}

static uint64_t distanceDown(
    int64_t i,
    int64_t down,
    char *grid
) {
    uint8_t tree = grid[i];

    for (int64_t dist = 1; (dist < down); dist++) {
        if (grid[i + (SIDE_LENGTH+1)*dist] >= tree) {
            return dist;
        }
    }

    return down;
}


void Day8_solve(String input, String buffer)
{
    if (input.length < (SIDE_LENGTH * SIDE_LENGTH + SIDE_LENGTH)) {
        printf("Input is too small, expecting a 99x99 grid.\n");
        return;
    }

    char *grid = input.data;

    // We need to keep track of trees already counted to avoid double counts.
    char *visited = buffer.data;


    // Since we know edges are always visible we can just add the number of
    // trees found at edges.

    uint64_t part1 = 4 * SIDE_LENGTH - 4;
    uint64_t part2 = 0;

    /*
    The algorithm:

    Scan the grid from the outside four times, from top,
    from left, from right, from bottom.
    This allow us to skip many trees.

    For example:
    Scan a row from left - right and keep track of the tallest tree seen so far.
    If current tree is taller, calculate score and count it as visible. Otherwise
    you can just skip it.

    */

    // Scan through rows left-right
    // We skip the edge since they are always visible (start at row=1, col=1).
    for (int64_t row = 1; row < SIDE_LENGTH - 1; row++) {
        // Tallest tree seen so far.
        char tallestTree = grid[INDEX(row, 0)];

        for (int64_t col = 1; col < SIDE_LENGTH - 1; col++) {
            // offset in char array (input).
            int64_t i = INDEX(row, col);
            char tree = grid[i];

            if (tree > tallestTree) {
                visited[i] = tree;
                part1 += 1;
                tallestTree = tree;

                uint64_t score =
                    col
                        * distanceRight(i, SIDE_LENGTH - col - 1, grid)
                        * distanceUp(i, row, grid)
                        * distanceDown(i, SIDE_LENGTH - row - 1, grid);

                if (score > part2) {
                    part2 = score;
                }

                // No tree will be taller, no point to continue this row.
                if (tallestTree == '9') break;
            }
        }
    }

    // Scan through rows right-left (reverse)
    for (int64_t row = SIDE_LENGTH - 2; row > 0; row--) {
        char tallestTree = grid[INDEX(row, SIDE_LENGTH - 1)];
        for (int64_t col = SIDE_LENGTH - 2; col > 0; col--) {
            int64_t i = INDEX(row, col);
            char tree = grid[i];

            if (tree > tallestTree) {
                if (!visited[i]) {
                    part1 += 1;
                    uint64_t score =
                        distanceLeft(i, col, grid)
                            * (SIDE_LENGTH - col)
                            * distanceUp(i, row, grid)
                            * distanceDown(i, SIDE_LENGTH - row - 1, grid);

                    if (score > part2) {
                        part2 = score;
                    }
                }
                visited[i] = 1;
                tallestTree = tree;
                if (tallestTree == '9') break;
            }
        }
    }


    // Scan through columns top-down
    for (int64_t col = 1; col < SIDE_LENGTH - 1; col++) {
        char tallestTree = grid[INDEX(0, col)];
        for (int64_t row = 1; row < SIDE_LENGTH - 1; row++) {
            int64_t i = INDEX(row, col);
            char tree = grid[i];

            if (tree > tallestTree) {
                if (!visited[i]) {
                    part1 += 1;
                    uint64_t score =
                        distanceLeft(i, col, grid)
                            * distanceRight(i, SIDE_LENGTH - col - 1, grid)
                            * row
                            * distanceDown(i, SIDE_LENGTH - row - 1, grid);

                    if (score > part2) {
                        part2 = score;
                    }
                }
                visited[i] = 1;
                tallestTree = tree;
                if (tallestTree == '9') break;
            }
        }
    }


    // Scan through columns bottom-up
    for (int64_t col = SIDE_LENGTH - 2; col > 0; col--) {
        char tallestTree = grid[INDEX(SIDE_LENGTH - 1, col)];
        for (int64_t row = SIDE_LENGTH - 2; row > 0; row--) {
            int64_t i = INDEX(row, col);
            char tree = grid[i];

            if (tree > tallestTree) {
                if (!visited[i]) {
                    part1 += 1;
                    uint64_t score =
                        distanceLeft(i, col, grid)
                            * distanceRight(i, SIDE_LENGTH - col - 1, grid)
                            * distanceUp(i, row, grid)
                            * (SIDE_LENGTH - row);

                    if (score > part2) {
                        part2 = score;
                    }
                }
                visited[i] = 1;
                tallestTree = tree;
                if (tallestTree == '9') break;
            }
        }
    }

    snprintf(buffer.data, buffer.length, "%10lu %10lu", part1, part2);
}

