#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"

#define push(arr, item) arr[arr##_len] = item; arr##_len += 1

typedef enum {
    LIST,
    NUMBER
} ValueType;

typedef uint16_t SmallPtr;

typedef struct {
    union {
        int16_t number;
        SmallPtr head;
    };
    uint16_t type;
} Value;


typedef struct {
    Value value;
    SmallPtr next;
} Node;


static Node *globalMemory;
static SmallPtr globalMemory_len;

size_t List_length(SmallPtr idx)
{
    Node node;
    size_t length = 0;
    do {
        node = globalMemory[idx];
        length += 1;
    } while ((idx = node.next));

    return length;
}


static size_t List_size(SmallPtr idx)
{
    Node node;
    size_t size = 0;
    do {
        node = globalMemory[idx];
        switch (node.value.type) {
            case LIST:
                size += 1;
                if (node.value.head > 0) {
                    size += List_size(node.value.head);
                }
                break;

            case NUMBER:
                size += 1;
                break;
        }
    } while ((idx = node.next));

    return size;
}



/*
static void List_print(SmallPtr idx)
{
    Node node;
    do {
        node = globalMemory[idx];
        switch (node.value.type) {
            case LIST:
                printf("[");
                if (node.value.head > 0) {
                    List_print(node.value.head);
                }
                printf("]");
                break;

            case NUMBER:
                printf("%d", node.value.number);
                break;
        }
        if (node.next > 0) {
            printf(",");
        }
    } while ((idx = node.next));
}
*/

static char *List_parse(char *string, char *end)
{
    SmallPtr stack[32] = {0};
    size_t level = 0;
    SmallPtr prev = 0;
    Node node = {0};
    SmallPtr first = globalMemory_len;

    for (; string < end; string++) {
        switch (*string) {
            case '[':
                node.value.type = LIST;
                node.value.head = 0;
                node.next = 0;
                globalMemory[globalMemory_len] = node;
                stack[level] = globalMemory_len;
                if (prev > 0) {
                    globalMemory[prev].next = globalMemory_len;
                }
                globalMemory_len += 1;
                level += 1;
                prev = 0;
                break;

            case ']':
                level -= 1;
                prev = stack[level];
                if (prev < globalMemory_len - 1) {
                    globalMemory[prev].value.head = prev + 1;
                }
                break;

            case ',':
            case ' ':
                break;

            default:
                if (Char_isDigit(*string)) {
                    int32_t num = 0;
                    num = 10 * num + *string - '0';

                    for (; (string + 1) < end && Char_isDigit(*(string + 1)); string++) {
                        num = num * 10 + *(string + 1) - '0';
                    }

                    node.value.type = NUMBER;
                    node.value.number = num;
                    node.next = 0;
                    globalMemory[globalMemory_len] = node;
                    if (prev > 0) {
                        globalMemory[prev].next = globalMemory_len;
                    }
                    prev = globalMemory_len;
                    globalMemory_len += 1;
                } else {
                    goto exit;
                }
        }
    }

    exit:
    if (globalMemory_len > first) {
        globalMemory[first].next = globalMemory_len;
    }

    return string;
}

static int64_t compareNumber(uint32_t left, uint32_t right)
{
    if (left < right) {
        return -1;
    } else if (left > right) {
        return 1;
    }

    return 0;
}

static int64_t compare(SmallPtr left, SmallPtr right)
{
    Node l;
    Node r;

    int64_t result = 0;

    if (left == 0 && right > 0) {
        return -1;
    } else if (right == 0 && left > 0) {
        return 1;
    } else if (right == 0 && left == 0) {
        return 0;
    }

    do {
        l = globalMemory[left];
        r = globalMemory[right];

        if (l.value.type == r.value.type) {
            if (l.value.type == LIST) {
                result = compare(l.value.head, r.value.head);
            } else {
                result = compareNumber(l.value.number, r.value.number);
            }
        } else if (l.value.type == LIST) {
            SmallPtr next = globalMemory[right].next;
            globalMemory[right].next = 0;
            result = compare(l.value.head, right);
            globalMemory[right].next = next;
        } else {
            SmallPtr next = globalMemory[left].next;
            globalMemory[left].next = 0;
            result = compare(left, r.value.head);
            globalMemory[left].next = next;
        }

        left = l.next ;
        right = r.next;
    } while (result == 0 && left && right);

    if (result != 0) {
        return result;
    }

    if (left == 0 && right > 0) {
        return -1;
    } else if (right == 0 && left > 0) {
        return 1;
    }

    return result;
}

static int compare_lists(const void *l, const void *r)
{
    SmallPtr left = *(SmallPtr*)l;
    SmallPtr right = *(SmallPtr*)r;

    return compare(left, right);
}

void Day13_solve(String input, String buffer)
{
    char *str = input.data;
    char *end = input.data + input.length;

    globalMemory = (Node*)buffer.data;
    globalMemory_len = 1;

    // Parse and add divider packages to tmp globalMemory.
    char divider1[] = "[[2]]";
    char divider2[] = "[[6]]";

    SmallPtr div1 = globalMemory_len;
    List_parse(divider1, divider1 + sizeof(divider1));

    SmallPtr div2 = globalMemory_len;
    List_parse(divider2, divider2 + sizeof(divider2));

    SmallPtr left = globalMemory_len;

    // parse all lists and push them to the tmp globalMemory.
    while (str < end) {
        str = List_parse(str, end);
        assert(*str == '\n');
        str += 1;
        if (*str == '\n') str += 1;
    }

    // part 1
    SmallPtr ptr = globalMemory_len;
    SmallPtr right = 0;
    int64_t index = 1;
    uint64_t part1 = 0;
    SmallPtr *lists = (SmallPtr*)&globalMemory[ptr];
    size_t lists_len = 0;
    push(lists, div1); // idx of divider 1
    push(lists, div2); // idx of divider 2

    while (left < ptr) {
        right = globalMemory[left].next;
        int64_t result = compare(left, right);
        push(lists, left);
        push(lists, right);
        left = globalMemory[right].next;

        if (result < 0) {
            part1 += index;
        }
        index += 1;
    }

    qsort(lists, lists_len, sizeof(SmallPtr), compare_lists);

    uint64_t part2 = 1;

    // part 2

    for (size_t i = 0; i < lists_len; i++) {
        if (lists[i] == div1) {
            part2 *= i + 1;
        } else if (lists[i] == div2) {
            part2 *= i + 1;
            break;
        }
    }

    sprintf(buffer.data, "%12lu %12lu", part1, part2);
}


