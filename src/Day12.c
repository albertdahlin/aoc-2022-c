#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"
#include <unistd.h>


typedef struct {
    char *data;
    int64_t width;
    int64_t height;
    int64_t row;
} Grid;

typedef struct {
    int64_t x;
    int64_t y;
} Point;


#define at(x, y) grid.data[((y)*grid.row + (x))]
#define visit(x, y) visited[((y)*grid.row + (x))]

static Point P(int64_t x, int64_t y)
{
    return (Point){ x, y };
}

static void draw(Grid grid, Point pos, Point target, uint32_t *visited)
{
    printf("\e[1;1H");
    char *str = grid.data;
    uint32_t *out = visited;
    for (size_t row = 0; row < grid.height; row++) {
        for (size_t col = 0; col < grid.width; col++) {
            size_t i = row*grid.row + col;
            if (pos.x == col && pos.y == row) {
                printf("#");
            } else if (target.x == col && target.y == row) {
                printf("E");
            } else if (str[i] == 'S') {
                printf("S");
            } else if (out[i] < 0xFFFFFFFF) {
                //putchar(str[i] & 0b11011111);
                printf("\e[90m%c\e[0m", str[i]);
            } else {
                putchar(str[i]);
            }
        }
        printf("\n");
    }
    printf("\n");
    //usleep(1600);
}

static uint32_t hscore(Point pos, Point target)
{
    return abs(pos.x - target.x) + abs(pos.y - target.y);
}

static void findTarget(Grid grid, Point pos, Point target, uint32_t score, uint32_t *visited)
{
    int8_t up = 0x8F;
    int8_t down = 0x8F;
    int8_t left = 0x8F;
    int8_t right = 0x8F;

    int8_t m = at(pos.x, pos.y);

    if (m == 'S') {
        m = 'a';
    }

    if (m == 'a') {
        //score = 0;
    }

    if (score >= visit(pos.x, pos.y)) {
        return;
    }

    visit(pos.x, pos.y) = score;

    if (m == 'E') {
        printf("FOUND %ld,%ld : %c\n", pos.x, pos.y, m);
    }

    if (pos.x > 0) left = at(pos.x - 1, pos.y);
    if (pos.x < grid.width) right = at(pos.x + 1, pos.y);
    if (pos.y > 0) up = at(pos.x, pos.y - 1);
    if (pos.y < grid.height) down = at(pos.x, pos.y + 1);
    //printf("m %ld,%ld : %c %c %c %c\n", pos.x, pos.y, up, right, down, left);

    int8_t du = up - m;
    int8_t dr = right - m;
    int8_t dd = down - m;
    int8_t dl = left - m;

    if (dr <= 1) {
        findTarget(grid, P(pos.x + 1, pos.y), target, score + 1, visited);
        //printf("  v %ld,%ld : %c \n", pos.x, pos.y, down);
    }

    if (du <= 1) {
        findTarget(grid, P(pos.x, pos.y - 1), target, score + 1, visited);
        //printf("  ^ %ld,%ld : %c \n", pos.x, pos.y, up);
    }


    if (dd <= 1) {
        findTarget(grid, P(pos.x, pos.y + 1), target, score + 1, visited);
        //printf("  v %ld,%ld : %c \n", pos.x, pos.y, down);
    }

    if (dl <= 1) {
        //printf("  < %ld,%ld : %c \n", pos.x, pos.y, left);
        findTarget(grid, P(pos.x - 1, pos.y), target, score + 1, visited);
    }
}


void Day12_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    uint64_t width = 0;
    uint64_t height = 0;

    char *str = input.data;
    uint32_t *out = (uint32_t*)buffer.data;
    Point start, target;
    assert((input.length * 4) < buffer.length);

    for (size_t i = 0; i < input.length; i++) {
        if (width == 0 && str[i] == '\n') width = i;
        if (str[i] == '\n') height++;
        if (str[i] == 'S') {
            str[i] = 'z';
            start.x = i;
        }
        if (str[i] == 'a') {
            //start.x = i;
        }
        if (str[i] == 'E') {
            target.x = i;
            str[i] = 'z';
        }
        out[i] = 0xFFFFFFFF;
    }

    start.y = start.x / (width+1);
    start.x = start.x % (width+1);
    target.y = target.x / (width+1);
    target.x = target.x % (width+1);

    Grid grid = {0};
    grid.data = input.data;
    grid.width = width;
    grid.height = height;
    grid.row = width + 1;

    //start.y += 1;
    //
    //printf("\[1;1H\e[2J");

    findTarget(grid, start, target, 0, out);

    part1 = out[target.y*grid.row + target.x];

    //printf("%lux%lu\n", width, height);
    //findTarget(grid, P(1, 1), target);

    /*
    printf("%lu,%lu\n", start.x, start.y);
    printf("%lu,%lu\n", target.x, target.y);
    */

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}

