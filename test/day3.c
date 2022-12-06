#include <stdio.h>
#include <String.h>
#include <Day3.c>
#include "test.h"


int main()
{
    RUN(
        Day3_solve,
        "vJrwpWtwJgWrhcsFMMfFFhFp\njqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\nPmmdzqPrVvPwwTWBwg\nwMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\nttgJtRGJQctTZtZT\nCrZsJsPPZsGzwwsLwLmpwMDw\n",
        "157",
        "70"
    );

    EXPECT(Day3_prio('a') == 1, "");
    EXPECT(Day3_prio('z') == 26, "");
    EXPECT(Day3_prio('A') == 27, "");
    EXPECT(Day3_prio('Z') == 52, "");

    EXPECT(Day3_countZeroBitsRight(0x0) == 0, "");
    EXPECT(Day3_countZeroBitsRight(0x10) == 4, "");
    EXPECT(Day3_countZeroBitsRight(0x100) == 8, "");
}
