#include <stdio.h>
#include <String.h>
#include <Day08.c>
#include "test.h"


int main()
{
    TEST_INIT();

    char input[] = "30373\n25512\n65332\n33549\n35390\n";

    RUN(Day8_solve, input, "21", "8");
}

