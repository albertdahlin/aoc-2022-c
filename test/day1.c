#include <stdio.h>
#include <stdlib.h>
#include <Day1.c>
#include "test.h"


int main()
{
    RUN(
        Day1_solve,
        "1000 2000 3000  4000  5000 6000  7000 8000 9000  10000 ",
        "24000",
        "45000"
    );
}
