#include <AStar.c>
#include <Heap.c>

Node tmp[8] = {0};

uint8_t terrain[] = {
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
};


uint32_t heuristic(uint32_t id)
{
    int16_t x = id & 0x7;
    int16_t y = id >> 3;

    return 7 - x + 7 - y;
}

#define add(i) \
    node.id = i; \
    if (terrain[node.id]) { \
        node.weight = terrain[node.id]; \
        tmp[list.length] = node; \
        list.length += 1; \
    }

AStar_List neighbors(uint32_t id)
{
    int16_t x = id & 0x7;
    int16_t y = id >> 3;

    AStar_List list = {0};
    Node node = {0};
    node.weight = 1;

    if (x < 7) {
        add((y << 3) | (x + 1));
    }

    if (x > 0) {
        add((y << 3) | (x - 1));
    }

    if (y < 7) {
        add(((y + 1) << 3) | x);
    }

    if (y > 0) {
        add(((y - 1) << 3) | x);
    }

    list.node = tmp;

    return list;
}


int main()
{
    AStar a = AStar_create(
        heuristic,
        neighbors,
        8*8
    );

    uint32_t result = AStar_run(0, 7 + 8*7, a);

    printf("result %u\n", result);

    AStar_free(a);

    return 0;
}
