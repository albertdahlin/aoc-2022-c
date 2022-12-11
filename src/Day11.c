#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include "String.h"


#define MONKEY_ITEMS_CAPACITY 64
#define PRIMES (2*3*5*7*11*13*17*19);


typedef enum Operation {
    OP_NONE,
    OP_ADD,
    OP_MUL,
    OP_SQUARE
} Operation;

typedef struct {
    uint64_t *items;
    uint64_t itemsLength;
    uint64_t inspectCount;
    Operation operation;
    uint64_t operationValue;
    uint64_t testValue;
    uint64_t whenTrue;
    uint64_t whenFalse;
} Monkey;


typedef struct {
    Monkey *monkeys;
    size_t length;
} MonkeyList;


static void Monkey_pushItem(Monkey *monkey, uint64_t item)
{
    assert(monkey->itemsLength < MONKEY_ITEMS_CAPACITY);
    monkey->items[monkey->itemsLength] = item;
    monkey->itemsLength += 1;
}

static uint64_t Monkey_newWorryLevel(Monkey *monkey, uint64_t item)
{
    assert(monkey->operation > 0);

    switch (monkey->operation) {
        case OP_NONE:
            break;
        case OP_ADD:
            if (__builtin_uaddl_overflow(item, monkey->operationValue, &item)) {
                assert(!"ADD OVERFLOW");
            }
            break;

        case OP_MUL:
            if (__builtin_umull_overflow(item, monkey->operationValue, &item)) {
                assert(!"MUL OVERFLOW");
            }
            break;
        case OP_SQUARE:
            if (__builtin_umull_overflow(item, item, &item)) {
                assert(!"SQUARE OVERFLOW");
            }
            break;
    }

    return item;
}

static void Monkey_print(Monkey *monkey)
{
    printf("  Items: ");
    for (size_t i = 0; i < monkey->itemsLength; i++) {
        printf("%lu ", monkey->items[i]);
    }
    printf("\n");
    printf("  Operation: ");
    switch (monkey->operation) {
        case OP_NONE:
            printf("ERROR\n");
            break;
        case OP_ADD:
            printf("old + %lu\n", monkey->operationValue);
            break;
        case OP_MUL:
            printf("old * %lu\n", monkey->operationValue);
            break;
        case OP_SQUARE:
            printf("old * old\n");
            break;
    }
    printf("  Test Value: %lu\n", monkey->testValue);
    printf("  When true: %lu\n", monkey->whenTrue);
    printf("  When false: %lu\n", monkey->whenFalse);
}

static void MonkeyList_print(MonkeyList list)
{
    for (size_t i = 0; i < list.length; i++) {
        printf("Monkey %zu:\n", i);
        Monkey_print(&list.monkeys[i]);
    }
}

static void MonkeyList_throwItem(MonkeyList list, size_t to, uint64_t item)
{
    assert(to < list.length);
    Monkey_pushItem(&list.monkeys[to], item);
}

static void MonkeyList_playRound1(MonkeyList list)
{
    for (size_t m = 0; m < list.length; m++) {
        Monkey *monkey = &list.monkeys[m];
        for (size_t i = 0; i < monkey->itemsLength; i++) {
            monkey->inspectCount += 1;
            uint64_t item = monkey->items[i];
            item = Monkey_newWorryLevel(monkey, item);
            item /= 3;

            if ((item % monkey->testValue) == 0) {
                MonkeyList_throwItem(list, monkey->whenTrue, item);
            } else {
                MonkeyList_throwItem(list, monkey->whenFalse, item);
            }
        }
        monkey->itemsLength = 0;
    }
}

static void MonkeyList_playRound2(MonkeyList list)
{
    for (size_t m = 0; m < list.length; m++) {
        Monkey *monkey = &list.monkeys[m];
        for (size_t i = 0; i < monkey->itemsLength; i++) {
            monkey->inspectCount += 1;
            uint64_t item = monkey->items[i];
            item = Monkey_newWorryLevel(monkey, item);

            if ((item % monkey->testValue) == 0) {
                item = item % PRIMES;
                MonkeyList_throwItem(list, monkey->whenTrue, item);
            } else {
                MonkeyList_throwItem(list, monkey->whenFalse, item);
            }
        }
        monkey->itemsLength = 0;
    }
}

static uint64_t MonkeyList_monkeyBussinessLevel(MonkeyList list)
{
    uint64_t largest = 0;
    uint64_t larger = 0;

    for (size_t m = 0; m < list.length; m++) {
        uint64_t inspectCount = list.monkeys[m].inspectCount;
        if (inspectCount > largest) {
            larger = largest;
            largest = inspectCount;
        } else if (inspectCount > larger) {
            larger = inspectCount;
        }
    }

    return larger * largest;
}

#define CHAR str[pos]
#define SKIP(n) pos += n; if (pos > length) return -__LINE__
#define SKIPLEN(p) pos += (sizeof(p) - 1); if (pos > length) return -__LINE__
#define PASSERT(exp) if (!(exp)) { \
    printf("Parse assert failed: %s at %u\n", #exp, __LINE__); \
    return -__LINE__; \
}
#define WHILE(exp) for (; (pos < length) && (exp); pos++)


static int64_t Monkey_parse(Monkey *monkey, char *str, int64_t length)
{
    int64_t pos = 0;
    monkey->itemsLength = 0;
    monkey->inspectCount = 0;

    // Something is wrong.
    PASSERT(length > 0);

    // We should be at M in "Monkey"
    PASSERT(CHAR == 'M');

    // skip row "Monkey n:", length + nl
    SKIPLEN("Monkey 1:\n");

    // Skip to first digit, "  Starting items: "
    SKIPLEN("  Starting items: ");
    PASSERT(Char_isDigit(CHAR));

    // parse items
    uint64_t item = 0;
    WHILE (1) {
        if (CHAR == '\n') {
            if (item > 0) {
                Monkey_pushItem(monkey, item);
            }
            break;
        } else if (Char_isDigit(CHAR)) {
            item = item*10 + CHAR - '0';
        } else if (CHAR == ',') {
            Monkey_pushItem(monkey, item);
            item = 0;
        }
    }
    // skip to next row
    SKIP(1);


    // Skip to + or * in "  Operation: new = old x"
    SKIPLEN("  Operation: new = old ");
    PASSERT(CHAR == '*' || CHAR == '+');

    if (CHAR == '*') {
        monkey->operation = OP_MUL;
    } else if (CHAR == '+') {
        monkey->operation = OP_ADD;
    }

    // Skip to number or old after "* 12"
    SKIPLEN("* ");
    PASSERT(Char_isDigit(CHAR) || CHAR == 'o');

    uint64_t num = 0;

    if (CHAR == 'o') {
        monkey->operation = OP_SQUARE;
        // Skip rest of "old"
        SKIP(2);
    } else {
        // must be number
        num = num*10 + CHAR - '0';
    }

    // Skip to next digit or nl
    SKIP(1);

    // number might be 2 digits.
    if (Char_isDigit(CHAR)) {
        num = num*10 + CHAR - '0';
        // skip to nl
        SKIP(1);
    }

    monkey->operationValue = num;

    // skip nl to next row;
    SKIP(1);

    // skip to number in "  Test: divislbe by n"
    SKIPLEN("  Test: divisible by ");
    PASSERT(Char_isDigit(CHAR));

    num = 0;
    num = num*10 + CHAR - '0';

    SKIP(1);

    if (Char_isDigit(CHAR)) {
        num = num*10 + CHAR - '0';
        SKIP(1);
    }

    monkey->testValue = num;

    // skip nl to next row
    PASSERT(CHAR == '\n');
    SKIP(1);

    // skip to first digit in "    If true: throw to monkey 2"
    SKIPLEN("    If true: throw to monkey ");

    PASSERT(Char_isDigit(CHAR));

    monkey->whenTrue = CHAR - '0';

    // skip nl to next row.
    SKIP(1);
    PASSERT(CHAR == '\n');
    SKIP(1);

    // skip to first digit in "If false: throw to monkey 0"
    SKIPLEN("    If false: throw to monkey ");
    PASSERT(Char_isDigit(CHAR));

    monkey->whenFalse = CHAR - '0';

    PASSERT(monkey->testValue > 0);
    PASSERT(monkey->operation > 0);

    return pos;
}

static int64_t MonkeyList_parse(MonkeyList list, String input)
{
    char *str = input.data;
    int64_t len = input.length;

    for (size_t m = 0; m < list.length; m++) {
        Monkey *monkey = &list.monkeys[m];
        int64_t parsedSize = Monkey_parse(monkey, str, len);
        if (parsedSize > 0) {
            parsedSize += 3;
            str += parsedSize;
            len -= parsedSize;
        } else {
            printf("PARSE ERROR at Monkey %zu: %ld\n", m, parsedSize);
            return parsedSize;
        }
    }

    return 0;
}


static MonkeyList MonkeyList_create(size_t len, String *buffer)
{
    size_t totalSizeRequired = sizeof(Monkey) * len + sizeof(uint64_t) * MONKEY_ITEMS_CAPACITY;

    assert(buffer->length > totalSizeRequired);

    void *address = buffer->data;

    MonkeyList list = {0};
    list.monkeys = address;
    list.length = len;

    address += sizeof(Monkey) * len;

    for (size_t i = 0; i < len; i++) {
        uint64_t *items = address;
        list.monkeys[i].items = items;
        address += sizeof(uint64_t) * MONKEY_ITEMS_CAPACITY;
    }

    buffer->data = address;

    return list;
}


void Day11_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    String tmp = {0};
    tmp.data = buffer.data;
    tmp.length = buffer.length;

    size_t numberOfMonkeys = 8;

    MonkeyList list = MonkeyList_create(numberOfMonkeys, &tmp);

    if (MonkeyList_parse(list, input) < 0) {
        return;
    }

    for (size_t i = 0; i < 20; i++) {
        MonkeyList_playRound1(list);
    }

    part1 = MonkeyList_monkeyBussinessLevel(list);

    if (MonkeyList_parse(list, input) < 0) {
        return;
    }

    uint64_t modBy = 1;
    for (size_t m = 0; m < list.length; m++) {
        Monkey *monkey = &list.monkeys[m];
        modBy *= monkey->testValue;
    }

    for (size_t i = 0; i < 1e4; i++) {
        MonkeyList_playRound2(list);
    }

    part2 = MonkeyList_monkeyBussinessLevel(list);

    sprintf(buffer.data, "%10lu %10lu", part1, part2);
}
