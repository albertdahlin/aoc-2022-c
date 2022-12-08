#include <stdio.h>
#include <String.h>
#include <Day4.c>
#include "test.h"


int main()
{
    TEST_INIT();

    RUN(Day4_solve, "2-4,6-8\n2-3,4-5\n5-7,7-9\n2-8,3-7\n6-6,4-6\n2-6,4-8\n", "2", "4");

    EXPECT(isOverlap(4, 6, 1, 3) == 0, "");
    EXPECT(isOverlap(4, 6, 7, 9) == 0, "");
    EXPECT(isOverlap(1, 3, 4, 6) == 0, "");
    EXPECT(isOverlap(7, 9, 4, 6) == 0, "");

    EXPECT(isOverlap(4, 6, 1, 4) == 1, "");
    EXPECT(isOverlap(4, 6, 6, 9) == 1, "");
    EXPECT(isOverlap(1, 4, 4, 6) == 1, "");
    EXPECT(isOverlap(6, 9, 4, 6) == 1, "");

    EXPECT(isOverlap(4, 6, 5, 5) == 1, "");
    EXPECT(isOverlap(5, 5, 4, 6) == 1, "");

}
