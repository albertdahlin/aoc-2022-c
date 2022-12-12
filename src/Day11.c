#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include "String.h"


#define MONKEY_ITEMS_CAPACITY 36
#define PRIMES (2*3*5*7*11*13*17*19);

typedef uint64_t Item;

typedef Item (*Operation_Unary)(Item);
typedef Item (*Operation_Binary)(Item, Item);

typedef struct Monkey {
    uint_fast8_t itemsLength;
    Operation_Binary inspect;
    uint_fast8_t operationValue;
    uint_fast16_t inspectCount;
    Operation_Unary decide;
    struct Monkey *whenTrue;
    struct Monkey *whenFalse;
    Item items[MONKEY_ITEMS_CAPACITY];
} Monkey;

typedef struct {
    Monkey *monkey;
    size_t length;
} MonkeyList;


#define IS_DIVISIBLE_BY(N) \
    static Item isDivisibleBy##N(Item n) { return n % N == 0; }

IS_DIVISIBLE_BY(2);
IS_DIVISIBLE_BY(3);
IS_DIVISIBLE_BY(5);
IS_DIVISIBLE_BY(7);
IS_DIVISIBLE_BY(11);
IS_DIVISIBLE_BY(13);
IS_DIVISIBLE_BY(17);
IS_DIVISIBLE_BY(19);
IS_DIVISIBLE_BY(23);


static Item opAdd(Item a, Item b)
{
    return (a + b);
}

static Item opMul(Item a, Item b)
{
    return (a * b);
}

static Item opSqr(Item a, Item b)
{
    return (a * a);
}

static inline void Monkey_pushItem(Monkey *monkey, Item item)
{
    monkey->items[monkey->itemsLength] = item;
    monkey->itemsLength += 1;
}

#define CHAR str[pos]
#define SKIP(n) pos += n; if (pos > length) return -__LINE__
#define SKIPLEN(p) pos += (sizeof(p) - 1); if (pos > length) return -__LINE__
#define PASSERT(exp) \
    if (!(exp)) { \
        printf("Parse assert failed: %s at %u\n", #exp, __LINE__); \
        return -__LINE__; \
    }
#define WHILE(exp) for (; (pos < length) && (exp); pos++)


static int64_t Monkey_parse(MonkeyList list, Monkey *monkey, char *str, int64_t length)
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
        monkey->inspect = opMul;
    } else if (CHAR == '+') {
        monkey->inspect = opAdd;
    }

    // Skip to number or old after "* 12"
    SKIPLEN("* ");
    PASSERT(Char_isDigit(CHAR) || CHAR == 'o');

    uint64_t num = 0;

    if (CHAR == 'o') {
        monkey->inspect = opSqr;
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

    switch (num) {
        case 2:
            monkey->decide = isDivisibleBy2;
            break;
        case 3:
            monkey->decide = isDivisibleBy3;
            break;

        case 5:
            monkey->decide = isDivisibleBy5;
            break;

        case 7:
            monkey->decide = isDivisibleBy7;
            break;

        case 11:
            monkey->decide = isDivisibleBy11;
            break;

        case 13:
            monkey->decide = isDivisibleBy13;
            break;

        case 17:
            monkey->decide = isDivisibleBy17;
            break;

        case 19:
            monkey->decide = isDivisibleBy19;
            break;

        case 23:
            monkey->decide = isDivisibleBy23;
            break;

        default:
            printf("Sorry, %ld does not work\n", num);
            return -100;
    }

    // skip nl to next row
    PASSERT(CHAR == '\n');
    SKIP(1);

    // skip to first digit in "    If true: throw to monkey 2"
    SKIPLEN("    If true: throw to monkey ");

    PASSERT(Char_isDigit(CHAR));

    num = CHAR - '0';
    PASSERT(num < list.length);
    monkey->whenTrue = &list.monkey[num];

    // skip nl to next row.
    SKIP(1);
    PASSERT(CHAR == '\n');
    SKIP(1);

    // skip to first digit in "If false: throw to monkey 0"
    SKIPLEN("    If false: throw to monkey ");
    PASSERT(Char_isDigit(CHAR));

    num = CHAR - '0';
    PASSERT(num < list.length);
    monkey->whenFalse = &list.monkey[num];

    return pos;
}

static int64_t MonkeyList_parse(MonkeyList list, String input)
{
    char *str = input.data;
    int64_t len = input.length;

    for (size_t m = 0; m < list.length; m++) {
        Monkey *monkey = &list.monkey[m];
        int64_t parsedSize = Monkey_parse(list, monkey, str, len);
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
#if DNDEBUG
    size_t totalSizeRequired = sizeof(Monkey) * len + sizeof(uint64_t) * MONKEY_ITEMS_CAPACITY;


    assert(buffer->length > totalSizeRequired);
#endif

    void *address = buffer->data;

    MonkeyList list = {0};
    list.monkey = address;
    list.length = len;

    address += sizeof(Monkey) * len;

    buffer->data = address;

    return list;
}


static uint64_t MonkeyList_monkeyBussiness(MonkeyList list)
{
    uint64_t largest = 0;
    uint64_t larger = 0;

    for (size_t m = 0; m < list.length; m++) {
        uint64_t inspectCount = list.monkey[m].inspectCount;
        if (inspectCount > largest) {
            larger = largest;
            largest = inspectCount;
        } else if (inspectCount > larger) {
            larger = inspectCount;
        }
    }

    return larger * largest;
}

static void runPart1(Monkey *monkeys) {
    for (uint_fast16_t round = 0; round < 20; round++) {
        #pragma GCC unroll(8)
        for (uint_fast8_t m = 0; m < 8; m++) {
            Monkey *monkey = &monkeys[m];
            monkey->inspectCount += monkey->itemsLength;
            for (uint_fast8_t i = 0; i < monkey->itemsLength; i++) {
                Item item = monkey->items[i];
                item = monkey->inspect(item, monkey->operationValue);
                item /= 3;

                Monkey *throwTo;
                if (monkey->decide(item)) {
                    throwTo = monkey->whenTrue;
                } else {
                    throwTo = monkey->whenFalse;
                }
                Monkey_pushItem(throwTo, item);
            }
            monkey->itemsLength = 0;
        }
    }
}

static void runPart2(Monkey *monkeys) {
    for (uint_fast16_t round = 0; round < 1e4; round++) {
        #pragma GCC unroll(8)
        for (uint_fast8_t m = 0; m < 8; m++) {
            Monkey *monkey = &monkeys[m];
            monkey->inspectCount += monkey->itemsLength;
            for (uint_fast8_t i = 0; i < monkey->itemsLength; i++) {
                Item item = monkey->items[i];
                item = monkey->inspect(item, monkey->operationValue);

                Monkey *throwTo;
                if (monkey->decide(item)) {
                    item = item % PRIMES;
                    throwTo = monkey->whenTrue;
                } else {
                    throwTo = monkey->whenFalse;
                }
                Monkey_pushItem(throwTo, item);
            }
            monkey->itemsLength = 0;
        }
    }
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

    runPart1(list.monkey);
    part1 = MonkeyList_monkeyBussiness(list);

    if (MonkeyList_parse(list, input) < 0) {
        return;
    }

    runPart2(list.monkey);
    part2 = MonkeyList_monkeyBussiness(list);
    sprintf(buffer.data, "%12lu %12lu", part1, part2);
}

