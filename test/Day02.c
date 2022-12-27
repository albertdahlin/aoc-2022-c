#include <stdio.h>
#include "test.h"
#include <Day02.c>


int main()
{
    TEST_INIT();

    RUN(
        Day2_solve,
        "A Y B X C Z ",
        "15",
        "12"
    );
}
