#include <inttypes.h>
#include <stdio.h>
#include "String.h"

static inline uint64_t leftBy(char c)
{
    return 1UL << (c & 0x1F);
}

static inline uint64_t countBitsOne(uint64_t n)
{
    uint64_t c = 0;

    for (; n; ++c) {
        n &= n - 1;
    }

    return c;
}

void Day6_solve(String input, String buffer)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    uint64_t mask = 0;
    char *str = input.data;

    // start at index 4.
    size_t i = 4;

    // Assume input is only lower case characters.
    // Part 1 will always be found before part 2. If a character is repeated
    // within the last 4 it is also repeated in the last 14.

    // First we find the start-of-packet marker (part 1).
    while (i < input.length) {
        mask  = leftBy(str[i]);
        mask |= leftBy(str[i-1]);
        mask |= leftBy(str[i-2]);
        mask |= leftBy(str[i-3]);

        if (countBitsOne(mask) == 4) {
            part1 = i + 1;
            break;
        }
        i++;
    }

    // We can skip ahead 10 since part 2 will check 14 previous characters.
    i += 10;

    // i fallthrugh from previous loop.
    // Look for the start-of-message marker (part 2).
    while (i < input.length) {
        // Small performance improvement.
        // If two adjacent characters are the same we can skip ahead by 13.
        // On my input that is quite common so this made a noticable difference.
        if (str[i] == str[i-1]) {
            i += 13;
            continue;
        }

        mask  = leftBy(str[i]);
        mask |= leftBy(str[i-1]);
        mask |= leftBy(str[i-2]);
        mask |= leftBy(str[i-3]);
        mask |= leftBy(str[i-4]);
        mask |= leftBy(str[i-5]);
        mask |= leftBy(str[i-6]);
        mask |= leftBy(str[i-7]);
        mask |= leftBy(str[i-8]);
        mask |= leftBy(str[i-9]);
        mask |= leftBy(str[i-10]);
        mask |= leftBy(str[i-11]);
        mask |= leftBy(str[i-12]);
        mask |= leftBy(str[i-13]);

        if (countBitsOne(mask) == 14) {
            part2 = i + 1;
            break;
        }
        i++;
    }

    snprintf(buffer.data, buffer.length, "%10lu %10lu", part1, part2);
}

