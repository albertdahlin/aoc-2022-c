#include <inttypes.h>
#include <stdio.h>
#include "String.h"

void Day2_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    uint64_t a, b, i;

    // Assume input is correct. We can skip over some characters since we
    // know our instructions will be at col 0 and 2
    for (size_t pos = 2; pos < input.length; pos += 4) {
        a = input.data[pos - 2];
        b = input.data[pos];

        // Values should be between 0-2 instead of ASCII
        a -= 'A';
        b -= 'X';

        /*
        Since there are only 9 combinations of a and b we can look up
        the result from an array of precaluclated values.

        Instead of using an array like this:

            int array[3] = { 1, 2, 3 };
            score = array[i];

        the same result can be achieved by storing the digits as an uint64 and shifting
        them into the lower 4 bits. Then we clear all other bits to get our answer.

        Our array example above can be rewritten as

            score = 0x321 >> (4*i) & 0xF;

        This lets us keep the whole array in one 64bit register.
        */

        i = 3*a + b;

        part1 += 0x627951384 >> 4*i & 0xF;
        part2 += 0x762951843 >> 4*i & 0xF;
    }

    sprintf(buffer.data, "%10lu %10lu", part1, part2);
}

