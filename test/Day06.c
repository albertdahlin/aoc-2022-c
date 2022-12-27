#include <stdio.h>
#include <String.h>
#include <Day06.c>
#include "test.h"


int main()
{
    TEST_INIT();

    RUN(Day6_solve, "mjqjpqmgbljsphdztnvjfqwrcgsmlb\n", "7", "19");
    RUN(Day6_solve, "bvwbjplbgvbhsrlpgdmjqwftvncz\n", "5", "23");
    RUN(Day6_solve, "nppdvjthqldpwncqszvftbrmjlhg\n", "6", "23");
    RUN(Day6_solve, "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg\n", "10", "29");
    RUN(Day6_solve, "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", "11", "26");
}
