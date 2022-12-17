#include <stdio.h>
#include <String.h>
#include <Day12.c>
#include "test.h"



int main()
{
    TEST_INIT();
    char in[] = 
        "Sabqponm\n"
        "abcryxxl\n"
        "accszExk\n"
        "acctuvwj\n"
        "abdefghi\n";

    char in2[] = 
        "Saaaaaaabcd\n"
        "aaddddddddd\n"
        "bcdefghijkl\n"
        "abcuxwghijm\n"
        "abcyzvghijn\n"
        "abcxEutsrqo\n"
        "abcwvutsrqp\n";

    //RUN(Day12_solve,in, "", "");

    RUN(Day12_solve, in, "", "");

    /*
    */
}

