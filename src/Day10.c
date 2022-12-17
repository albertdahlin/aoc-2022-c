#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "Ocr.h"

#define SKIP(n) i += n;
#define CURRENT_CHAR str[i]

void Day10_solve(String input, String buffer)
{
    uint64_t part1 = 0;

    char *str = input.data;
    char display[6][40] = {0};

    int64_t addxPending[2] = {0};
    int64_t xReg = 1;
    int64_t cyclesPending = 0;
    int64_t cycle = 1;

    for (int64_t i = 0; i < input.length; i++) {
        int64_t num = 0;
        int64_t sign = 1;

        // Instruction addx <num>
        if (CURRENT_CHAR == 'a') {
            SKIP(5);
            if (CURRENT_CHAR == '-') {
                sign = -1;
                SKIP(1);
            }

            if (CURRENT_CHAR >= '0') {
                num = num * 10 + CURRENT_CHAR - '0';
                SKIP(1);
            }
            if (CURRENT_CHAR >= '0') {
                num = num * 10 + CURRENT_CHAR - '0';
                SKIP(1);
            }
            cyclesPending = 2;
            num *= sign;
            addxPending[(cycle + 2) % 2] = num;
        }

        // Instruction noop
        if (CURRENT_CHAR == 'n') {
            SKIP(4);
            cyclesPending = 1;
        }

        // Run cycles 1 or 2 times depending on instruction.
        while (cyclesPending > 0) {
            int64_t col = (cycle - 1) % 40;
            int64_t row = (cycle - 1) / 40;

            // Set diplay pixels
            if (labs(xReg - col) <= 1) {
                display[row][col] = '#';
            } else {
                display[row][col] = '.';
            }

            // Execute pending instructions.
            cycle += 1;
            xReg  += addxPending[cycle % 2];
            addxPending[cycle % 2] = 0;
            cyclesPending -= 1;

            if ((cycle + 20) % 40 == 0) {
                part1 += cycle * xReg;
            }
        }
    }

    // Parse display pixes into Glyphs.
    Ocr_Glyph glyphs[8] = {0};

    for (size_t row = 0; row < 6; row++) {
        for (size_t letterIdx = 0; letterIdx < 8; letterIdx++) {
            size_t col = letterIdx*5;
            glyphs[letterIdx] = Ocr_parseRow(&display[row][col] , glyphs[letterIdx]);
        }
    }

    // Convert Glyph into char and store them in an array (part2),
    // effectively creating a string.
    char part2[8] = {0};

    for (size_t i = 0; i < 8; i++) {
        glyphs[i] = Ocr_parseFinalize(glyphs[i]);
        char result = Ocr_fromGlyph(glyphs[i]);
        part2[i] = result;
    }

    sprintf(buffer.data, "%14lu %14.8s", part1, part2);
}

