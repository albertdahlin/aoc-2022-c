#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"


typedef enum {
    ROBOT_ORE,
    ROBOT_CLAY,
    ROBOT_OBSIDIAN,
    ROBOT_GEODE
} Robot;

typedef struct {
    uint8_t id;
    uint8_t oreRobot_ore;
    uint8_t clayRobot_ore;
    uint8_t obsidianRobot_ore;
    uint8_t obsidianRobot_clay;
    uint8_t geodeRobot_ore;
    uint8_t geodeRobot_obsidian;
} Blueprint;


typedef struct {
    uint8_t ore;
    uint8_t clay;
    uint8_t obsidian;
    uint8_t geode;
    uint8_t oreRobot;
    uint8_t clayRobot;
    uint8_t obsidianRobot;
    uint8_t geodeRobot;
} State;

#define push(arr, item) arr[arr##_len] = item; arr##_len += 1
#define CHAR input.data[i]
#define SKIP_TO_DIGIT() for (;i < input.length && !Char_isDigit(CHAR); i++)
#define PARSE_NUMBER(v) \
    (v) = CHAR - '0'; \
    i += 1; \
    for (;i < input.length && Char_isDigit(CHAR); i++) { \
        (v) = (v) * 10 + CHAR - '0'; \
    }


static inline State collect(State state)
{
    state.ore += state.oreRobot;
    state.clay += state.clayRobot;
    state.obsidian += state.obsidianRobot;
    state.geode += state.geodeRobot;

    return state;
}

static inline bool canBuyOreRobot(Blueprint bp, State st)
{
    return st.ore >= bp.oreRobot_ore;
}

static inline State buyOreRobot(Blueprint bp, State st)
{
    st.ore -= bp.oreRobot_ore;
    st.oreRobot += 1;

    return st;
}

static inline bool canBuyClayRobot(Blueprint bp, State st)
{
    return st.ore >= bp.clayRobot_ore;
}

static inline State buyClayRobot(Blueprint bp, State st)
{
    st.ore -= bp.clayRobot_ore;
    st.clayRobot += 1;
    return st;
}

static inline bool canBuyObsidianRobot(Blueprint bp, State st)
{
    return st.ore >= bp.obsidianRobot_ore && st.clay >= bp.obsidianRobot_clay;
}

static inline State buyObsidianRobot(Blueprint bp, State st)
{
    st.ore -= bp.obsidianRobot_ore;
    st.clay -= bp.obsidianRobot_clay;
    st.obsidianRobot += 1;

    return st;
}

static inline bool canBuyGeodeRobot(Blueprint bp, State st)
{
    return st.ore >= bp.geodeRobot_ore && st.obsidian >= bp.geodeRobot_obsidian;
}

static inline void buyGeodeRobot(Blueprint bp, State *st)
{
    st->ore -= bp.geodeRobot_ore;
    st->obsidian -= bp.geodeRobot_obsidian;
    st->geodeRobot += 1;
}

static inline State bestOf(State a, State b)
{
    return a.geode > b.geode ? a : b;
}

static inline State simulate24(int64_t t, Blueprint bp, State state, Robot next)
{
    if (t <= 1) {
        state = collect(state);
        return state;
    }

    if (canBuyGeodeRobot(bp, state)) {
        state = collect(state);
        buyGeodeRobot(bp, &state);
    } else {
        switch (next) {
            case ROBOT_ORE:
                if (canBuyOreRobot(bp, state)) {
                    state = collect(state);
                    state = buyOreRobot(bp, state);
                } else {
                    state = collect(state);
                    return simulate24(t - 1, bp, state, ROBOT_ORE);
                }
                break;

            case ROBOT_CLAY:
                if (canBuyClayRobot(bp, state)) {
                    state = collect(state);
                    state = buyClayRobot(bp, state);
                } else {
                    state = collect(state);
                    return simulate24(t - 1, bp, state, ROBOT_CLAY);
                }
                break;

            case ROBOT_OBSIDIAN:
                if (canBuyObsidianRobot(bp, state)) {
                    state = collect(state);
                    state = buyObsidianRobot(bp, state);
                } else {
                    state = collect(state);
                    return simulate24(t - 1, bp, state, ROBOT_OBSIDIAN);
                }
                break;

            case ROBOT_GEODE:
                if (canBuyGeodeRobot(bp, state)) {
                    state = collect(state);
                    buyGeodeRobot(bp, &state);
                } else {
                    state = collect(state);
                    return simulate24(t - 1, bp, state, ROBOT_GEODE);
                }
                break;
        }
    }


    State best;
    if (state.oreRobot >= 4) {
        best = simulate24(t - 1, bp, state, ROBOT_CLAY);
    } else {
        best = simulate24(t - 1, bp, state, ROBOT_ORE);
        best = bestOf(best, simulate24(t - 1, bp, state, ROBOT_CLAY));
    }
    if (state.clayRobot > 2) {
        best = bestOf(best, simulate24(t - 1, bp, state, ROBOT_OBSIDIAN));
    }

    return best;
}

void Day19_solve(String input, String buffer)
{
    int64_t part1 = 0;
    int64_t part2 = 0;

    Blueprint *blueprints = (Blueprint*)buffer.data;
    size_t blueprints_len = 0;

    for (size_t i = 0; i < input.length; i++) {
        Blueprint bp;
        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.id);

        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.oreRobot_ore);

        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.clayRobot_ore);

        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.obsidianRobot_ore);
        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.obsidianRobot_clay);

        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.geodeRobot_ore);
        SKIP_TO_DIGIT();
        PARSE_NUMBER(bp.geodeRobot_obsidian);

        push(blueprints, bp);

        i += 10;
    }


    State start = {0};

    start.oreRobot = 1;

    State *states = (State*)&blueprints[blueprints_len];

    for (size_t i = 0; i < blueprints_len; i++) {
        State state = simulate24(24, blueprints[i], start, ROBOT_ORE);
        state = bestOf(state, simulate24(24, blueprints[i], start, ROBOT_CLAY));
        part1 += blueprints[i].id * state.geode;
        states[i] = state;
    }

    part2 = 1;

    for (size_t i = 0; i < blueprints_len; i++) {
        if (i == 3) {
            break;
        }
        State state = simulate24(32, blueprints[i], start, ROBOT_ORE);
        state = bestOf(state, simulate24(32, blueprints[i], start, ROBOT_CLAY));
        part2 *= state.geode;
    }

    sprintf(buffer.data, "%14lu %14lu", part1, part2);
}



