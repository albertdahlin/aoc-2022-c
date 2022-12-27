#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"

// 0000 0000

#define push(arr, item) arr[arr##_len] = item; arr##_len += 1

typedef struct {
    uint8_t rate;
    uint8_t tunnels[6];
    uint8_t tunnels_len;
} Valve;


static int16_t toIndex(char a, char b)
{
    a -= 'A';
    b -= 'A';
    return ((a << 5) | b);
}

static int64_t max(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static inline bool visit(int8_t idx, uint64_t *mask)
{
    uint64_t m = (1UL << idx);
    bool isVisited = m & *mask;
    *mask |= m;

    return !isVisited;
}

static int64_t bfs(Valve *valves, uint8_t idx, uint32_t pressure, int time, uint64_t mask)
{
    if (time <= 1) {
        return pressure;
    }

    Valve valve = valves[idx];

    if (valve.rate > 0 && visit(idx, &mask)) {
        pressure += valve.rate * (time - 1);
        time -= 1;
    }

    for (size_t i = 0; i < valve.tunnels_len; i++) {
        uint8_t tidx = valve.tunnels[i];
        pressure = max(
            pressure,
            bfs(valves, tidx, pressure, time - 1, mask)
        );
    }

    return pressure;
}

#define SKIPLEN(p) i += (sizeof(p) - 1); if (i > input.length) return -__LINE__
#define CHAR input.data[i]
#define SKIP(n) i += n; if (i > input.length) return -__LINE__
#define SKIP_EOL() for (;i < input.length && CHAR != '\n'; i++)
#define SKIP_WHILE(exp) for (;i < input.length && (exp); i++)
#define PARSE_NUMBER(v) \
    (v) = CHAR - '0'; \
    i += 1; \
    for (;i < input.length && Char_isDigit(CHAR); i++) { \
        (v) = (v) * 10 + CHAR - '0'; \
    }
static int64_t parse(String input, Valve *valves)
{
    size_t valves_len = 0;
    uint8_t *indexes = (uint8_t*)&valves[64];

    for (size_t i = 0; i < input.length; i++) {
        if (CHAR == 'Q') break;
        Valve valve = {0};
        SKIPLEN("Valve ");
        char v1 = CHAR;
        i += 1;
        char v2 = CHAR;
        uint16_t idx = toIndex(v1, v2);

        indexes[idx] = valves_len;

        SKIPLEN(" has flow rate=");
        PARSE_NUMBER(valve.rate);
        SKIPLEN("; tunnels lead to valves ");
        push(valves, valve);
        SKIP_EOL();
    }

    int v = 0;
    for (size_t i = 0; i < input.length; i++) {
        if (CHAR == 'Q') break;
        SKIPLEN("Valve XX has flow rate=0; tunnels lead to valves");
        SKIP_WHILE('A' > CHAR || CHAR > 'Z');

        int tunnel = 0;

        for (;i < input.length && (CHAR != '\n'); i++) {
            if (CHAR == ',') continue;
            if (CHAR == ' ') continue;
            char v1 = CHAR;
            i += 1;
            char v2 = CHAR;
            uint16_t idx = toIndex(v1, v2);
            valves[v].tunnels[tunnel] = indexes[idx];
            tunnel += 1;
        }
        valves[v].tunnels_len = tunnel;

        SKIP_EOL();
        v += 1;
    }

    return indexes[0];
}

void Day16_solve(String input, String buffer)
{
    int64_t part1 = 0;
    int64_t part2 = 0;
    Valve *valves = (Valve*)buffer.data;
    int64_t root = parse(input, valves);

    //part1 = bfs(valves, root, 0, 30, 0);


    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}

