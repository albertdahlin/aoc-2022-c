#include <inttypes.h>
#include "String.h"


uint64_t Day3_prio(uint8_t c)
{
    /*
    if c is lower case (c >= 'a')
    c - 'a' + 1 = c - 97 + 1 = c - 96

    else
    c - 'A' + 27 = c - 65 + 27 = c - 38

    diff = 96 - 38 = 58

    */
    return c - 38 - (c >= 'a')*58;
}

uint64_t Day3_countZeroBitsRight(uint64_t powerOf2)
{
#if __GNUC__
    // Use Bit Scan Forward instructions if gcc is used.
    return __builtin_ctzl(powerOf2);
#else

    // Fallback solution
    uint64_t n = 0;

    while (powerOf2 > 1) {
        powerOf2 >>= 1;
        n++;
    }

    return n;
#endif
}

void Day3_solve(String input)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    uint8_t c;

    // Since prio is between 1-52 we can use a 64bit mask to
    // store which items we have seen in each compartment.
    // We can fit the whole thing in a register instead of an array in memory.
    uint64_t firstHalfMask = 0;
    uint64_t secondHalfMask = 0;

    uint64_t groupMask[3] = {0};
    uint64_t elfIdx = 0;

    // Rucksack start index
    size_t rsStart = 0;
    // Rucksack length
    size_t rsLength = 0;

    while (rsStart < input.length) {
        size_t i;

        // Loop through first half.
        for (i = 0; i < input.length; i++) {
            // We can assume rucksack string length to be an even number.
            // If char at pos i * 2 is not a letter it must be the end of the line.
            if (input.data[rsStart+i*2] < 'A') {
                // Set length for next loop.
                rsLength = i * 2;
                break;
            }
            c = input.data[rsStart+i];
            // Set the Nth bit from right where N = prio
            firstHalfMask |= 1UL << Day3_prio(c);
        }

        // i fallthough from previous loop, we continue with the second half.
        for (; i < rsLength; i++) {
            c = input.data[rsStart+i];
            secondHalfMask |= 1UL << Day3_prio(c);
        }

        // Set group mask as a union of first and second half.
        groupMask[elfIdx] = firstHalfMask | secondHalfMask;

        // prio = number of zeros to the right of the set bit.
        part1 += Day3_countZeroBitsRight(firstHalfMask & secondHalfMask);

        // If we are at Elf no 3 in our group.
        if (elfIdx == 2) {
            // Only common bits will be 1. Assume only 1 bit is common between groups.
            groupMask[0] &= groupMask[1] & groupMask[2];

            // prio = number of zeros to the right of the set bit.
            part2 += Day3_countZeroBitsRight(groupMask[0]);
            groupMask[0] = 0;
            groupMask[1] = 0;
            groupMask[2] = 0;
        }

        // ternary operator assignment results in fewer instructions than (n+1) % 3
        elfIdx = elfIdx == 2 ? 0 : elfIdx + 1;
        firstHalfMask = 0;
        secondHalfMask = 0;
        rsStart += rsLength + 1;
        rsLength = 0;
    }

    printf("%10lu %10lu", part1, part2);
}

