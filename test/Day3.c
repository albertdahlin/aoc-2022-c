#include <stdio.h>
#include <String.h>
#include <Day3.c>
#include "test.h"


int main()
{
    TEST_INIT();

    RUN(
        Day3_solve,
        "vJrwpWtwJgWrhcsFMMfFFhFp\njqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\nPmmdzqPrVvPwwTWBwg\nwMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\nttgJtRGJQctTZtZT\nCrZsJsPPZsGzwwsLwLmpwMDw\n",
        "157",
        "70"
    );

    EXPECT(prio('a') == 1, "");
    EXPECT(prio('z') == 26, "");
    EXPECT(prio('A') == 27, "");
    EXPECT(prio('Z') == 52, "");

    EXPECT(countZeroBitsRight(0x0) == 0, "");
    EXPECT(countZeroBitsRight(0x10) == 4, "");
    EXPECT(countZeroBitsRight(0x100) == 8, "");
}
