#include <inttypes.h>
#include <stdio.h>
#include "String.h"
#include "Heap.h"


#define indexOf(x, y) ((y) * g_grid.row + (x))

typedef struct {
    char *data;
    uint8_t width;
    uint8_t height;
    uint16_t bestTime;
    uint8_t row;
    uint8_t endX;
    uint8_t endY;
    uint8_t startX;
    uint8_t startY;
} Grid;

typedef struct {
    uint16_t time;
    uint8_t x;
    uint8_t y;
} Position;


static Position *g_bestSoFar;

#define VISITED_SET_SIZE (1024*4)

static uint16_t *g_visited;
static Grid g_grid = {0};


static uint16_t hashPosition(Position pos)
{
    /* This creates a unique hash for each possible position.

    y < 27, fits in 5 bits (32)
    x < 122, fits in 7 bits (128)

    5 + 7 = 12 used bits (4069)
    27*122 = 3294
    */

    uint16_t p = pos.x;
    p <<= 5;
    p |= pos.y;

    return p;
}

static void Set_insert(Position pos)
{
    uint16_t idx = hashPosition(pos);
    g_visited[idx] = pos.time;
}

static bool Set_member(Position pos)
{
    uint16_t idx = hashPosition(pos);

    return pos.time >= g_visited[idx];
}

static void Set_remove(Position pos)
{
    uint16_t idx = hashPosition(pos);

    g_visited[idx] = -1;
}

static inline uint16_t Position_distanceToGoal(Position pos)
{
    // This turns out to be faster than using abs()
    if (g_grid.endX > g_grid.startX) {
        return g_grid.endX - pos.x + g_grid.endY - pos.y;
    }

    return pos.x + pos.y;
}

static inline bool Position_isAtStart(Position pos)
{
    return (pos.x == g_grid.startX && pos.y == g_grid.startY);
}

static inline bool Position_isAtEnd(Position pos)
{
    return (pos.x == g_grid.endX && pos.y == g_grid.endY);
}

static inline bool Position_isOutside(Position pos)
{
    if (pos.x < 1 || pos.x >= g_grid.width - 1) {
        return true;
    }

    if (pos.y < 1 || pos.y >= g_grid.height - 1) {
        return true;
    }

    return false;
}

static inline uint16_t Position_score(Position pos)
{
    return 2*pos.time + Position_distanceToGoal(pos);
}

static int Position_compare(void *p1, void*p2)
{
    Position *s1 = (Position*)p1;
    Position *s2 = (Position*)p2;

    return Position_score(*s1) - Position_score(*s2);
}

static inline Position position(uint8_t x, uint8_t y, uint16_t time)
{
    return (Position){ time, x, y };
}

static bool isBlocked(Position pos)
{
    if (Position_isOutside(pos) && !Position_isAtStart(pos)) {
        return true;
    }

    uint16_t insideHeight = g_grid.height - 2;

    // scan column
    for (uint16_t insideY = 1; insideY < (g_grid.height - 1); insideY++) {
        char c = g_grid.data[indexOf(pos.x, insideY)];
        uint16_t yt;

        if (c == '^') {
            yt = ((insideHeight-1)*pos.time + insideY - 1) % insideHeight + 1;
        } else if (c == 'v') {
            yt = (pos.time + insideY - 1) % insideHeight + 1;
        } else {
            continue;
        }

        if (yt == pos.y) {
            return true;
        }
    }

    uint16_t insideWidth = g_grid.width - 2;

    // scan row
    for (uint16_t insideX = 1; insideX < (g_grid.width - 1); insideX++) {
        char c = g_grid.data[indexOf(insideX, pos.y)];
        uint16_t xt;

        if (c == '<') {
            xt = ((insideWidth-1)*pos.time + insideX - 1) % insideWidth + 1;
        } else if (c == '>') {
            xt = (pos.time + insideX - 1) % insideWidth + 1;
        } else {
            continue;
        }

        if (xt == pos.x) {
            return true;
        }
    }

    return false;
}


static void addToQueue(Position pos)
{
    if (Set_member(pos) || isBlocked(pos)) {
        return;
    }

    Set_insert(pos);
    Heap_push(g_bestSoFar, pos);
}

static void tick()
{
    Position pos = Heap_pop(g_bestSoFar);
    Set_remove(pos);

    pos.time += 1;

    if (Position_isAtEnd(pos)) {
        g_grid.bestTime = pos.time < g_grid.bestTime ? pos.time : g_grid.bestTime;

        return;
    }

    if ((Position_score(pos)) >= g_grid.bestTime) {
        return;
    }

    addToQueue(position(pos.x, pos.y + 1, pos.time));
    addToQueue(position(pos.x, pos.y - 1, pos.time));

    addToQueue(position(pos.x + 1, pos.y, pos.time));
    addToQueue(position(pos.x - 1, pos.y, pos.time));

    addToQueue(pos);
}

static uint16_t shortestPath(
    uint8_t startX,
    uint8_t startY,
    uint8_t endX,
    uint8_t endY,
    uint16_t time
) {
    g_grid.bestTime = 0xFFFF;
    g_grid.endX = endX;
    g_grid.endY = endY;
    g_grid.startX = startX;
    g_grid.startY = startY;
    Heap_truncate(g_bestSoFar);
    Heap_push(g_bestSoFar, position(startX, startY, time));

    while (Heap_length(g_bestSoFar) > 0) {
        tick();
    }

    return g_grid.bestTime;
}

static void initGrid(String input)
{
    g_grid.data = input.data;

    for (size_t i = 0; i < 200; i++) {
        if (input.data[i] == '\n') {
            g_grid.width = i;
            break;
        }
    }

    if (g_grid.width == 122) {
        g_grid.height = 27;
    } else {
        // Test grid
        g_grid.height = 6;
    }

    g_grid.row = g_grid.width + 1;
}

void Day24_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    g_visited = (uint16_t*)buffer.data;
    for (size_t i = 0; i < VISITED_SET_SIZE; i++) {
        g_visited[i] = -1;
    }

    g_bestSoFar = Heap_fromPtr(
        sizeof(Position),
        Position_compare,
        &g_visited[VISITED_SET_SIZE],
        (sizeof(uint16_t) * VISITED_SET_SIZE - buffer.length)
    );

    initGrid(input);

    uint16_t time = 0;

    // From start to end
    time = shortestPath(
        1, 0,
        g_grid.width - 2, g_grid.height - 2,
        time
    );
    part1 = time;

    // From end to start
    time = shortestPath(
        g_grid.width - 2, g_grid.height - 1,
        1, 1,
        time
    );
    // from start to end
    time = shortestPath(
        1, 0,
        g_grid.width - 2, g_grid.height - 2,
        time
    );
    part2 = time;

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}
