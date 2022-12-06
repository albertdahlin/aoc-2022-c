#include <stdio.h>
#include <stdlib.h>
#include <Day1.c>
#include "test.h"


int main()
{
    RUN(
        Day1_solve,
        "1000\n2000\n3000\n\n4000\n\n5000\n6000\n\n7000\n8000\n9000\n\n10000\n",
        "24000",
        "45000"
    );

    printf("%lu\n", 0x10);
    printf("%lu\n", 10 * 256 / 100);
}
