#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include "Heap.h"


static void Heap_swap64(void *heap, size_t a, size_t b)
{
    uint64_t *arr = (uint64_t*)heap;
    uint64_t tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

static void Heap_swap32(void *heap, size_t a, size_t b)
{
    uint32_t *arr = (uint32_t*)heap;
    uint32_t tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}


static void Heap_swap(void *heap, size_t a, size_t b)
{
    Heap_Header *header = heap;
    header--;

    if (header->elementSize == 8) {
        return Heap_swap64(heap, a, b);
    } else if (header->elementSize == 4) {
        return Heap_swap32(heap, a, b);
    }

    char *tmp[header->elementSize];
    void *restrict ptrA = heap + header->elementSize * a;
    void *restrict ptrB = heap + header->elementSize * b;

    memcpy(tmp, ptrA, header->elementSize);
    memcpy(ptrA, ptrB, header->elementSize);
    memcpy(ptrB, tmp, header->elementSize);
}


static inline bool Heap_isBefore(void *heap, size_t a, size_t b)
{
    Heap_Header *header = heap;
    header--;

    return header->compare(heap + header->elementSize * a, heap + header->elementSize * b) < 0;
}

void *Heap_create(
    size_t elementSize,
    size_t capacity,
    Heap_function_compare compare
) {
    Heap_Header *header = malloc(sizeof(Heap_Header) + elementSize * capacity);
    assert(header != NULL);

    header->length      = 0;
    header->capacity    = capacity;
    header->elementSize = elementSize;
    header->compare     = compare;
    header->realloc     = realloc;

    return &header[1];
}

void *Heap_fromPtr(
    size_t elementSize,
    Heap_function_compare compare,
    void *ptr,
    size_t length
) {
    Heap_Header *header = ptr;

    header->length      = 0;
    header->elementSize = elementSize;
    header->capacity    = length / elementSize;
    header->compare     = compare;
    header->realloc     = NULL;

    return &header[1];
}

void Heap_free(void *heap)
{
    Heap_Header *header = heap;
    header--;
    free(header);
}


void *Heap_ensureCapacity(void *heap)
{
    Heap_Header *header = heap;
    header--;

    if (header->realloc == NULL) {
        assert(header->length < header->capacity);
        return heap;
    }

    if (header->length == header->capacity) {
        header = realloc(
            header,
            header->elementSize * header->capacity * 2 + sizeof(Heap_Header)
        );
        assert(header != NULL);
        header->capacity *= 2;
        heap = &header[1];
    }

    return heap;
}

void Heap_heapifyUp(void *heap)
{
    Heap_Header *header = heap;
    header--;
    size_t idx = header->length - 1;
    size_t parent = Heap_parentIdx(idx);

    while (idx > 0 && Heap_isBefore(heap, idx, parent)) {
        Heap_swap(heap, parent, idx);
        idx = parent;
        parent = Heap_parentIdx(idx);
    }
}


void Heap_heapifyDown(void *heap)
{
    Heap_Header *header = heap;
    header--;
    size_t idx      = 0;
    size_t left     = Heap_childLeftIdx(idx);
    size_t right    = Heap_childRightIdx(idx);
    size_t len      = header->length;
    size_t smaller;

    while (left < len) {
        if (Heap_isBefore(heap, left, right)) {
            smaller = left;
        } else {
            smaller = right;
        }

        if (Heap_isBefore(heap, idx, smaller)) {
            break;
        }
        Heap_swap(heap, idx, smaller);
        idx = smaller;
        left = Heap_childLeftIdx(idx);
        right = Heap_childRightIdx(idx);
    }
}

