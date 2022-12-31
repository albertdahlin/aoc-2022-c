#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Heap.h"
#include "AStar.h"


static int compare(void *p1, void *p2)
{
    Node *n1 = (Node*)p1;
    Node *n2 = (Node*)p2;

    return n1->weight - n2->weight;
}

AStar AStar_create(
    AStar_heuristic heuristic,
    AStar_neighbor neighbor,
    size_t capacity
) {
    AStar a     = {0};
    a.heuristic = heuristic;
    a.neighbor  = neighbor;
    a.capacity  = capacity;

    a.openSet   = Heap_create(sizeof(Node), capacity, compare);
    a.score     = malloc(sizeof(uint32_t) * capacity);
    a.heapIdx   = malloc(sizeof(uint32_t) * capacity);

    AStar_init(&a);

    return a;
}

void AStar_init(AStar *a)
{
    for (size_t i = 0; i < a->capacity; i++) {
        a->score[i] = 0xFFFFFFFF;
        a->heapIdx[i] = 0;
    }
}

void AStar_free(AStar a)
{
    Heap_free(a.openSet);
    free(a.score);
    free(a.heapIdx);
}

Id AStar_run(
    Id start,
    Id goal,
    AStar a
) {
    a.score[start] = 0;

    Node node = {0};
    node.weight = a.heuristic(start);
    node.id = start;
    Heap_push(a.openSet, node);

    while (Heap_length(a.openSet) > 0) {
        node = Heap_pop(a.openSet);
        a.heapIdx[node.id] = 0;

        if (node.id == goal) {
            return a.score[node.id];
        }

        AStar_List list = a.neighbor(node.id);

        for (size_t i = 0; i < list.length; i++) {
            Node neighbor = list.node[i];
            uint32_t score = a.score[node.id] + neighbor.weight;

            if (score < a.score[neighbor.id]) {
                a.score[neighbor.id] = score;
                uint32_t heapIdx = a.heapIdx[neighbor.id];

                if (heapIdx == 0) {
                    neighbor.weight = score + a.heuristic(neighbor.id);
                    a.openSet = Heap_ensureCapacity(a.openSet);
                    a.openSet[Heap_pushIdx(a.openSet)] = neighbor;
                    Heap_heapifyUp(a.openSet);
                    a.heapIdx[neighbor.id] = 1;
                }
            }
        }
    }

    return -1;
}




Id AStar_floodUntil(
    Id start,
    AStar a
) {
    a.score[start] = 0;

    Node node = {0};
    node.weight = 1;
    node.id = start;
    Heap_push(a.openSet, node);

    while (Heap_length(a.openSet) > 0) {
        node = Heap_pop(a.openSet);
        a.heapIdx[node.id] = 0;

        if (a.heuristic(node.id)) {
            return node.weight;
        }

        AStar_List list = a.neighbor(node.id);

        for (size_t i = 0; i < list.length; i++) {
            Node neighbor = list.node[i];
            uint32_t score = a.score[node.id] + neighbor.weight;

            if (score < a.score[neighbor.id]) {
                a.score[neighbor.id] = score;
                uint32_t heapIdx = a.heapIdx[neighbor.id];

                if (heapIdx == 0) {
                    neighbor.weight = score;
                    a.openSet = Heap_ensureCapacity(a.openSet);
                    a.openSet[Heap_pushIdx(a.openSet)] = neighbor;
                    Heap_heapifyUp(a.openSet);
                    a.heapIdx[neighbor.id] = 1;
                }
            }
        }
    }

    return -1;
}
