#pragma once
#include <inttypes.h>

typedef uint32_t Id;

typedef struct {
    uint32_t weight;
    Id id;
} Node;


typedef struct {
    size_t length;
    Node *node;
} AStar_List;

typedef uint32_t (*AStar_heuristic)(Id);
typedef AStar_List (*AStar_neighbor)(Id);

typedef struct {
    AStar_heuristic heuristic;
    AStar_neighbor neighbor;
    Node *openSet;
    uint32_t *score;
    uint8_t *heapIdx;
    size_t capacity;
} AStar;

AStar AStar_create(
    AStar_heuristic heuristic,
    AStar_neighbor neighbor,
    size_t capacity
);

void AStar_init(AStar*);

Id AStar_run(
    Id start,
    Id goal,
    AStar a
);

Id AStar_floodUntil(
    Id start,
    AStar a
);

void AStar_free(AStar);
