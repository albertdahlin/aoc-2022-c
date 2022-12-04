#include <inttypes.h>
#include "String.h"


void Day1_solve(String input)
{
    uint64_t calories = 0;
    uint64_t inventory = 0;

    // Keep the top 3 largest calorie countes here.
    uint64_t large = 0;
    uint64_t larger = 0;
    uint64_t largest = 0;

    uint8_t c;


    for (size_t i = 0; i < input.length; i++) {
        // Collect the calorie inventory for an Elf.
        while (i < input.length) {
            c = input.data[i];

            // Assume c is only digits or whitespace.
            if (c >= '0') {
                // c must be a digit, collect digits into an integer value.
                calories = calories * 10 + c - '0';
            } else if (calories == 0) {
                // If calories is zero we have seen 2 whitespace after each other.
                break;
            } else {
                // c is a whitespace
                inventory += calories;
                calories = 0;
            }
            i += 1;
        }

        // Store the 3 largest values.
        if (inventory > largest) {
            large   = larger;
            larger  = largest;
            largest = inventory;
        } else if (inventory > larger) {
            large = larger;
            larger = inventory;
        } else if (inventory > large) {
            large = inventory;
        }

        inventory = 0;
    }

    printf("%10lu %10lu", largest, large + larger + largest);
}
