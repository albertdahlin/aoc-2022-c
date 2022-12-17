#include <stdio.h>
#include <String.h>
#include <Day9.c>
#include "test.h"


#define tmove(X, Y) \
    tmp = moveTail(point((X), (Y)), point(0, 0)); \
    printf("%2d,%2d  ->  %2d,%2d\n", (X), (Y), tmp.x, tmp.y)


Point point(int32_t x, int32_t y)
{
    return (Point){ x, y };
}

int main()
{
    //TEST_INIT();


    Point tmp;

}

/*

R  5  ->   0  0
U  8  ->   0  0
L  8  ->   1  3
D  3  ->   1  3
R 17  ->   5  5
D 10  ->  10  0
L 25  ->  -2 -5
U 20  -> -11  6

*/
