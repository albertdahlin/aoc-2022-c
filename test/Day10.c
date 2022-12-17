#include <stdio.h>
#include <String.h>
#include <Day10.c>
#include "test.h"
#include <Ocr.c>



int main()
{
    TEST_INIT();
    RUN(Day10_solve, "noop\naddx 3\naddx -5\n", "0", "0");
}

