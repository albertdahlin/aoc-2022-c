#include <stdio.h>
#include <String.h>
#include <Day8.c>
#include "test.h"


int main()
{
    /*
    */
    char buffer[1024*32] = {0};
    String output = (String){
        buffer,
        sizeof(buffer)
    };

    char input[] = "30373\n25512\n65332\n33549\n35390\n";
    Grid grid = {
        input,
        5,
        5,
        6
    };

    RUN(Day8_solve, input, "21", "8");


    EXPECT(distanceUp(2, 0, grid) == -1, "");
    EXPECT(distanceUp(2, 1, grid) == -1, "");
    EXPECT(distanceUp(3, 1, grid) == 1, "");
    EXPECT(distanceDown(4, 3, grid) == -1, "");
    EXPECT(distanceDown(3, 3, grid) == 1, "");
}

