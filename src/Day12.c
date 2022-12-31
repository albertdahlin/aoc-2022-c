#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"
#include "AStar.h"
#include "Heap.h"


typedef struct {
    char *data;
    int64_t width;
    int64_t height;
    int64_t row;
    uint8_t targetX;
    uint8_t targetY;
} Grid;

static Grid g_grid;
static Node g_tmp[4];

static inline uint32_t pack(uint8_t x, uint8_t y)
{
    /*

    x < 167, 8 bit
    y < 41, 6 bit

    14 bit total. (16384)

    41x167 = 6847

    */
    uint32_t p = y;
    p <<= 8;
    p |= x;

    return p;
}

static uint32_t distanceToTarget(uint32_t id)
{
    uint8_t x = id & 0xFF;
    uint8_t y = id >> 8;

    return abs(g_grid.targetX - x) + abs(g_grid.targetY - y);
}

#define indexOf(x, y) ((y)*g_grid.row + (x))

#define addIfHigher(x, y) \
    node.id = pack((x), (y)); \
    if (g_grid.data[indexOf(x, y)] <= height) { \
        g_tmp[list.length] = node; \
        list.length += 1; \
    }

static AStar_List maxOneHigher(uint32_t id)
{
    uint8_t x = id & 0xFF;
    uint8_t y = id >> 8;

    AStar_List list = {0};
    Node node = {0};
    node.weight = 1;
    uint8_t height = g_grid.data[indexOf(x, y)] + 1;


    if (x < (g_grid.width - 1)) {
        addIfHigher(x + 1, y);
    }

    if (x > 0) {
        addIfHigher(x - 1, y);
    }

    if (y < (g_grid.height - 1)) {
        addIfHigher(x, y + 1);
    }

    if (y > 0) {
        addIfHigher(x, y - 1);
    }

    list.node = g_tmp;

    return list;
}

#define addIfLower(x, y) \
    node.id = pack((x), (y)); \
    if (g_grid.data[indexOf(x, y)] >= height) { \
        g_tmp[list.length] = node; \
        list.length += 1; \
    }

static AStar_List maxOneLower(uint32_t id)
{
    uint8_t x = id & 0xFF;
    uint8_t y = id >> 8;

    AStar_List list = {0};
    Node node = {0};
    node.weight = 1;
    uint8_t height = g_grid.data[indexOf(x, y)] - 1;


    if (x < (g_grid.width - 1)) {
        addIfLower(x + 1, y);
    }

    if (x > 0) {
        addIfLower(x - 1, y);
    }

    if (y < (g_grid.height - 1)) {
        addIfLower(x, y + 1);
    }

    if (y > 0) {
        addIfLower(x, y - 1);
    }

    list.node = g_tmp;

    return list;
}

static uint32_t isHeightEqA(Id id)
{
    uint8_t x = id & 0xFF;
    uint8_t y = id >> 8;
    uint8_t height = g_grid.data[indexOf(x, y)];

    return (height == 'a');
}


void Day12_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    uint64_t width = 0;
    uint64_t height = 0;

    char *str = input.data;
    char *out = buffer.data;
    uint64_t startX = 0;
    uint64_t startY = 0;
    uint64_t targetX = 0;
    uint64_t targetY = 0;

    for (size_t i = 0; i < input.length; i++) {
        out[i] = str[i];
        if (width == 0 && str[i] == '\n') width = i;
        if (str[i] == '\n') height++;
        if (str[i] == 'S') {
            startX = i;
            out[i] = 'a';
        }
        if (str[i] == 'E') {
            targetX = i;
            out[i] = 'z';
        }
    }
    g_grid.data     = out;
    g_grid.width    = width;
    g_grid.height   = height;
    g_grid.row      = width + 1;

    startY         = startX / (width+1);
    startX         = startX % (width+1);
    targetY        = targetX / (width+1);
    targetX        = targetX % (width+1);
    g_grid.targetX = targetX;
    g_grid.targetY = targetY;

    AStar a = AStar_create(
        distanceToTarget,
        maxOneHigher,
        16384
    );

    part1 = AStar_run(
        pack(startX, startY),
        pack(targetX, targetY),
        a
    );

    AStar_init(&a);
    a.heuristic = isHeightEqA;
    a.neighbor = maxOneLower;

    part2 = AStar_floodUntil(
        pack(targetX, targetY),
        a
    );

    AStar_free(a);

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}

