#include <stdio.h>
#include <String.h>
#include <Day12.c>
#include <AStar.c>
#include <Heap.c>
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
    //
    printf("pack %d\n", pack(166, 40));
    printf("unpack x %d\n", 6846 % 167);
    printf("unpack y %d\n", 6846 / 167);

    RUN(Day12_solve, in, "", "");

    /*
    */
}

