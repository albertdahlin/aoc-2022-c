#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"


typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} Position;

#define GRID_WIDTH 32
#define indexOf(x,y,z) ((x) + (y) * GRID_WIDTH + (z) * GRID_WIDTH * GRID_WIDTH)
#define push(arr, item) arr[arr##_len] = item; arr##_len += 1
#define CHAR input.data[i]
#define PARSE_NUMBER(v) \
    (v) = CHAR - '0'; \
    i += 1; \
    for (;i < input.length && Char_isDigit(CHAR); i++) { \
        (v) = (v) * 10 + CHAR - '0'; \
    }

static int64_t bfs(int16_t x, int16_t y, int16_t z, uint8_t *grid)
{
    if (x < 0 || x > GRID_WIDTH) {
        return 0;
    }
    if (y < 0 || y > GRID_WIDTH) {
        return 0;
    }
    if (z < 0 || z > GRID_WIDTH) {
        return 0;
    }

    if (grid[indexOf(x,y,z)] == 4) {
        return 1;
    }

    if (grid[indexOf(x,y,z)] > 0) {
        return 0;
    }

    grid[indexOf(x,y,z)] = 1;

    int64_t v = 0;

    v += bfs(x + 1, y, z, grid);
    v += bfs(x - 1, y, z, grid);
    v += bfs(x, y + 1, z, grid);
    v += bfs(x, y - 1, z, grid);
    v += bfs(x, y, z + 1, grid);
    v += bfs(x, y, z - 1, grid);

    return v;
}

void Day18_solve(String input, String buffer)
{
    int64_t part1 = 0;
    int64_t part2 = 0;

    Position *position = (Position*)buffer.data;
    size_t position_len = 0;

    for (size_t i = 0; i < input.length; i++) {
        if (CHAR == 'Q') {
            break;
        }
        if (Char_isDigit(CHAR)) {
            Position pos;
            PARSE_NUMBER(pos.x);
            pos.x += 1;
            i += 1;
            PARSE_NUMBER(pos.y);
            pos.y += 1;
            i += 1;
            PARSE_NUMBER(pos.z);
            pos.z += 1;
            push(position, pos);
        }
    }

    uint8_t *grid = (uint8_t*)&position[position_len];

    for (size_t i = 0; i < position_len; i++) {
        Position pos = position[i];
        grid[indexOf(pos.x, pos.y, pos.z)] = 4;
    }


    for (size_t i = 0; i < position_len; i++) {
        Position pos = position[i];
        part1 += grid[indexOf(pos.x + 1, pos.y, pos.z)] == 0;
        part1 += grid[indexOf(pos.x - 1, pos.y, pos.z)] == 0;
        part1 += grid[indexOf(pos.x, pos.y + 1, pos.z)] == 0;
        part1 += grid[indexOf(pos.x, pos.y - 1, pos.z)] == 0;
        part1 += grid[indexOf(pos.x, pos.y, pos.z + 1)] == 0;
        part1 += grid[indexOf(pos.x, pos.y, pos.z - 1)] == 0;
    }

    part2 = bfs(0, 0, 0, grid);

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}



