#include <stdio.h>
#include <String.h>
#include <Day11.c>
#include "test.h"



int main()
{
    TEST_INIT();

    MonkeyList list = MonkeyList_create(4, &output);

    Monkey *m = &list.monkeys[0];

    Monkey_pushItem(m, 79);
    Monkey_pushItem(m, 98);
    m->operation = OP_MUL;
    m->operationValue = 19;
    m->testValue = 23;
    m->whenTrue = 2;
    m->whenFalse = 3;

    m = &list.monkeys[1];
    Monkey_pushItem(m, 54);
    Monkey_pushItem(m, 65);
    Monkey_pushItem(m, 75);
    Monkey_pushItem(m, 74);
    m->operation = OP_ADD;
    m->operationValue = 6;
    m->testValue = 19;
    m->whenTrue = 2;
    m->whenFalse = 0;

    m = &list.monkeys[2];
    Monkey_pushItem(m, 79);
    Monkey_pushItem(m, 60);
    Monkey_pushItem(m, 97);
    m->operation = OP_SQUARE;
    m->operationValue = 0;
    m->testValue = 13;
    m->whenTrue = 1;
    m->whenFalse = 3;

    m = &list.monkeys[3];
    Monkey_pushItem(m, 74);
    m->operation = OP_ADD;
    m->operationValue = 3;
    m->testValue = 17;
    m->whenTrue = 0;
    m->whenFalse = 1;

    for (size_t i = 0; i < 20; i++) {
        MonkeyList_playRound1(list);
    }
    for (size_t i = 0; i < 4; i++) {
        printf("Monkey %zu inspected %lu times.\n", i, list.monkeys[i].inspectCount);
    }
    printf("Monkey bussiness: %lu\n", MonkeyList_monkeyBussinessLevel(list));
    //MonkeyList_print(list);


    //RUN(Day11_solve, "noop\naddx 3\naddx -5\n", "0", "0");
}

