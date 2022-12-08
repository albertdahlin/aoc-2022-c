#include <stdio.h>
#include <String.h>
#include <Day5.c>
#include "test.h"


int main()
{
    TEST_INIT();

    char input[] = "    [D]    \n[N] [C]    \n[Z] [M] [P]\n 1   2   3 \n\nmove 1 from 2 to 1\nmove 3 from 1 to 3\nmove 2 from 2 to 1\nmove 1 from 1 to 2\n";
    RUN(Day5_solve, input, "CMZ", "MCD");
}
