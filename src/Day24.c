#include <inttypes.h>
#include <stdio.h>
#include "String.h"
#include "Heap.h"


#define indexOf(x, y) ((y) * grid.row + (x))

typedef struct {
    char *data;
    uint8_t width;
    uint8_t height;
    uint16_t time;
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
} State;


State *bestSoFar;
size_t bestSoFar_len = 0;
Grid grid = {0};

#define Heap_push_State(heap, item) \
    heap[bestSoFar_len++] = (item); \
    Heap_heapifyUp_State(heap)


#define Heap_pop_State(heap) \
    heap[0]; \
    heap[0] = heap[--bestSoFar_len]; \
    Heap_heapifyDown_State(heap)


static bool alreadyAdded(State s)
{
    for (size_t i = 0; i < bestSoFar_len; i++) {
        State s2 = bestSoFar[i];
        if (s.x == s2.x && s.y == s2.y && s.time == s2.time) {
            return true;
        }
    }

    return false;
}

static uint16_t stateScore(State s)
{
    return s.time + (abs(grid.endX - s.x) + abs(grid.endY - s.y));
}

static void Heap_heapifyUp_State(State *heap)
{
    size_t idx = bestSoFar_len - 1;
    size_t parent = Heap_parentIdx(idx);

    while (idx > 0 && stateScore(heap[idx]) < stateScore(heap[parent])) {
        State i = heap[parent];
        heap[parent] = heap[idx];
        heap[idx] = i;
        idx = parent;
        parent = Heap_parentIdx(idx);
    }
}


static void Heap_heapifyDown_State(State *heap)
{
    size_t idx = 0;
    size_t left = Heap_childLeftIdx(idx);
    size_t right = Heap_childRightIdx(idx);
    size_t smaller = 0;
    size_t len = bestSoFar_len;

    while (left < len) {
        if (stateScore(heap[left]) < stateScore(heap[right])) {
            smaller = left;
        } else {
            smaller = right;
        }

        if (stateScore(heap[idx]) < stateScore(heap[smaller])) {
            break;
        }
        State i = heap[idx];
        heap[idx] = heap[smaller];
        heap[smaller] = i;
        idx = smaller;
        left = Heap_childLeftIdx(idx);
        right = Heap_childRightIdx(idx);
    }
}

static State state(uint8_t x, uint8_t y, uint16_t time)
{
    return (State){ time, x, y };
}

static bool isFree(uint8_t x, uint8_t y, uint16_t time)
{
    if (!(x == grid.startX && y == grid.startY)) {
        if (x < 1 || x >= grid.width - 1) {
            return false;
        }

        if (y < 1 || y >= grid.height - 1) {
            return false;
        }
    }

    uint16_t bh = grid.height - 2;

    // scan column
    for (uint16_t by = 1; by < (grid.height - 1); by++) {
        char c = grid.data[indexOf(x, by)];
        uint16_t yt;

        if (c == '^') {
            yt = ((bh-1)*time + by - 1) % bh + 1;
        } else if (c == 'v') {
            yt = (time + by - 1) % bh + 1;
        } else {
            continue;
        }

        if (yt == y) {
            return false;
        }
    }

    uint16_t bw = grid.width - 2;

    // scan row
    for (uint16_t bx = 1; bx < (grid.width - 1); bx++) {
        char c = grid.data[indexOf(bx, y)];
        uint16_t xt;

        if (c == '<') {
            xt = ((bw-1)*time + bx - 1) % bw + 1;
        } else if (c == '>') {
            xt = (time + bx - 1) % bw + 1;
        } else {
            continue;
        }

        if (xt == x) {
            return false;
        }
    }

    return true;
}


static void addIfNew(State s)
{
    if (alreadyAdded(s)) {
        return;
    }
    if (isFree(s.x, s.y, s.time)) {
        Heap_push_State(bestSoFar, s);
    }
}

static void tick()
{
    State s = Heap_pop_State(bestSoFar);

    s.time += 1;

    if (s.x == grid.endX && s.y == grid.endY) {
        if (s.time < grid.time) {
            grid.time = s.time;
        }

        return;
    }

    if ((stateScore(s)) >= grid.time) {
        return;
    }

    addIfNew(state(s.x, s.y + 1, s.time));
    addIfNew(state(s.x, s.y - 1, s.time));

    addIfNew(state(s.x + 1, s.y, s.time));
    addIfNew(state(s.x - 1, s.y, s.time));

    addIfNew(s);
}

static uint64_t run(
    uint8_t startX,
    uint8_t startY,
    uint8_t endX,
    uint8_t endY,
    uint16_t time
) {
    bestSoFar_len = 0;
    grid.time = 0xFFFF;
    grid.endX = endX;
    grid.endY = endY;
    grid.startX = startX;
    grid.startY = startY;
    Heap_push_State(bestSoFar, state(startX, startY, time));

    while (bestSoFar_len > 0) {
        tick();
    }

    return grid.time;
}

void Day24_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    grid.data = input.data;

    for (size_t i = 0; i < 200; i++) {
        if (input.data[i] == '\n') {
            grid.width = i;
            break;
        }
    }

    if (grid.width == 122) {
        grid.height = 27;
    } else {
        grid.height = 6;
    }

    grid.row = grid.width + 1;

    bestSoFar = (State*)buffer.data;
    part1 = run(1, 0, grid.width - 2, grid.height - 2, 0);
    part2 = run(grid.width - 2, grid.height - 1, 1, 1, part1);
    part2 = run(1, 0, grid.width - 2, grid.height - 2, part2);

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}
