#include <String.h>
#include <inttypes.h>

void Day2_solve(String input)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    int a, b;

    // Assume input is correct.
    for (size_t i = 2; i < input.length; i += 4) {
        a = input.data[i-2];
        b = input.data[i];

        // Values should be between 0-2 instead of ASCII
        a -= 'A';
        b -= 'X';

        /*
        Since there are only 9 combinations of a and b we can look up
        the result from an array.

        Instead of using an array like this:
        int array[3] = { 1, 2, 3 };
        a = array[i];

        the same result can be achieved by storing digits as an uint64 and shifting
        them into the lower 4 bits. We also have to clear all higher bits
        using &0xF.

        a = 0x321 >> (4*i) & 0xF;

        First, convert to index 0, 1 ... 8
        */
        a = 3*a + b;

        part1 += 0x627951384 >> 4*a & 0xF;
        part2 += 0x762951843 >> 4*a & 0xF;
    }

    printf("%10lu %10lu", part1, part2);
}

