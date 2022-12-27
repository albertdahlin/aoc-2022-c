#pragma once
#include <assert.h>
#include <inttypes.h>


static inline size_t Heap_childLeftIdx(size_t idx)
{
    return 2 * idx + 1;
}


static inline size_t Heap_childRightIdx(size_t idx)
{
    return 2 * idx + 2;
}


static inline size_t Heap_parentIdx(size_t idx)
{
    return ((idx - 1) / 2);
}


typedef int (*Heap_function_compare)(void*, void*);
typedef void *(*Heap_function_realloc)(void*, size_t);

typedef struct {
    size_t length;
    size_t capacity;
    size_t elementSize;
    Heap_function_compare compare;
    Heap_function_realloc realloc;
} Heap_Header;


void *Heap_create(
    size_t elementSize,
    size_t capacity,
    Heap_function_compare compare
);

void *Heap_fromPtr(
    size_t elementSize,
    Heap_function_compare compare,
    void *ptr,
    size_t length
);

void Heap_free(void *heap);

void *Heap_ensureCapacity(void *heap);

static inline size_t Heap_length(void *heap)
{
    Heap_Header *header = heap;
    header--;

    return header->length;
}


static inline void Heap_truncate(void *heap)
{
    Heap_Header *header = heap;
    header--;
    header->length = 0;
}


static inline size_t Heap_pushIdx(void *heap)
{
    Heap_Header *header = heap;
    header--;
    size_t len = header->length;
    header->length++;

    return len;
}


static inline size_t Heap_popIdx(void *heap)
{
    Heap_Header *header = heap;
    header--;
    assert(header->length > 0);
    header->length--;

    return header->length;
}


void Heap_heapifyUp(void *heap);
void Heap_heapifyDown(void *heap);


#define Heap_push(heap, item) \
    heap = Heap_ensureCapacity(heap); \
    heap[Heap_pushIdx(heap)] = (item); \
    Heap_heapifyUp(heap)


#define Heap_pop(heap) \
    heap[0]; \
    heap[0] = heap[Heap_popIdx(heap)]; \
    Heap_heapifyDown(heap)


#define Heap_for(heap, idx) \
    for (size_t idx = 0; idx < Heap_length(heap); idx++)

