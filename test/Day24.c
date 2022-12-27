#include <stdio.h>
#include <String.h>
#include <Day24.c>
#include "test.h"



int main()
{
    TEST_INIT();
    char in[] = 
"#.######\n"
"#>>.<^<#\n"
"#.<..<<#\n"
"#>v.><>#\n"
"#<^v^^>#\n"
"######.#\n";

/*
    char in2[] = 
"#.######\n"
"#......#\n"
"#^.....#\n"
"#......#\n"
"#......#\n"
"######.#\n";
*/

/*

 +18 18
 +23 41
 +13 54


    grid.endX = 1;
    grid.endY = 1;
    State state = {
        .time = 0,
        .x = 120,
        .y = 26
    };
*/

    // 896, to high
    // 825, to low
    //
    //printf("score %ld\n", stateScore(&state));

    RUN(Day24_solve, in, "", "");
}


