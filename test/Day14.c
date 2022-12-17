#include <stdio.h>
#include <String.h>
#include <Day14.c>
#include "test.h"



int main()
{
    TEST_INIT();
    char in[] = 
"498,4 -> 498,6 -> 496,6\n"
"503,4 -> 502,4 -> 502,9 -> 494,9\n";


/*
L5 (E1 E1 E3 E1 E1)

[5, [6, 7], 8]

L3 (E5 L2 (E6 E7) E8)
*/

    RUN(Day14_solve, in, "", "");
}

