#include <Day4.c>
#include <stdio.h>
#include <String.h>
#include "test.h"


int main()
{
    RUN(Day4_solve, "2-4,6-8 2-3,4-5 5-7,7-9 2-8,3-7 6-6,4-6 2-6,4-8 ", "2", "4");

    EXPECT(Day4_isOverlap(4, 6, 1, 3) == 0, "");
    EXPECT(Day4_isOverlap(4, 6, 7, 9) == 0, "");
    EXPECT(Day4_isOverlap(1, 3, 4, 6) == 0, "");
    EXPECT(Day4_isOverlap(7, 9, 4, 6) == 0, "");

    EXPECT(Day4_isOverlap(4, 6, 1, 4) == 1, "");
    EXPECT(Day4_isOverlap(4, 6, 6, 9) == 1, "");
    EXPECT(Day4_isOverlap(1, 4, 4, 6) == 1, "");
    EXPECT(Day4_isOverlap(6, 9, 4, 6) == 1, "");

    EXPECT(Day4_isOverlap(4, 6, 5, 5) == 1, "");
    EXPECT(Day4_isOverlap(5, 5, 4, 6) == 1, "");

}
