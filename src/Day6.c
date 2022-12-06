#include <inttypes.h>
#include "String.h"

static inline uint64_t Day6_mask(char c)
{
    return 1UL << (c - 'a');
}

static inline uint64_t Day6_countBitsOne(uint64_t n)
{
    uint64_t c = 0;

    for (; n; ++c) {
        n &= n - 1;
    }

    return c;
}

void Day6_solve(String input)
{
    uint64_t part1 = 0;
    uint64_t part2 = 0;

    uint64_t mask = 0;
    char *str = input.data;

    // Assume input is long and part1 answer is not found in the first 14 bytes.
    // Assume input is only lower case.
    for (size_t i = 13; i < input.length; i++) {
        mask |= Day6_mask(str[i]);
        mask |= Day6_mask(str[i-1]);
        mask |= Day6_mask(str[i-2]);
        mask |= Day6_mask(str[i-3]);

        if (part1 == 0 && Day6_countBitsOne(mask) == 4) {
            part1 = i + 1;
        }

        mask |= Day6_mask(str[i-4]);
        mask |= Day6_mask(str[i-5]);
        mask |= Day6_mask(str[i-6]);
        mask |= Day6_mask(str[i-7]);
        mask |= Day6_mask(str[i-8]);
        mask |= Day6_mask(str[i-9]);
        mask |= Day6_mask(str[i-10]);
        mask |= Day6_mask(str[i-11]);
        mask |= Day6_mask(str[i-12]);
        mask |= Day6_mask(str[i-13]);

        if (part2 == 0 && Day6_countBitsOne(mask) == 14) {
            part2 = i + 1;
        }

        mask = 0;
    }

    printf("%10lu %10lu", part1, part2);
}

