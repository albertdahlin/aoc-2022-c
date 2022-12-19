#include <stdio.h>
#include <String.h>
#include <Day19.c>
#include "test.h"



int main()
{
    TEST_INIT();
    char in[] = 
"Blueprint 1:\n"
"  Each ore robot costs 4 ore.\n"
"  Each clay robot costs 2 ore.\n"
"  Each obsidian robot costs 3 ore and 14 clay.\n"
"  Each geode robot costs 2 ore and 7 obsidian.\n"

"Blueprint 2:\n"
"  Each ore robot costs 2 ore.\n"
"  Each clay robot costs 3 ore.\n"
"  Each obsidian robot costs 3 ore and 8 clay.\n"
"  Each geode robot costs 3 ore and 12 obsidian\n";



    RUN(Day19_solve, in, "", "");
}

