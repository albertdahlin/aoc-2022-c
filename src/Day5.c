#include <stdio.h>
#include <inttypes.h>
#include "String.h"


typedef struct {
    uint8_t crates[64];
    size_t size;
} Stack;


void Day5_push(Stack *stack, uint8_t c)
{
    stack->crates[stack->size] = c;
    stack->size++;
}


uint8_t Day5_pop(Stack *stack)
{
    stack->size--;

    return stack->crates[stack->size];
}


void Day5_moveOneByOne(Stack *from, Stack *to, size_t count)
{
    char c;
    while (count != 0) {
        c = Day5_pop(from);
        Day5_push(to, c);
        count--;
    }
}


void Day5_moveMultiple(Stack *from, Stack *to, size_t count)
{
    size_t n = count;
    char c;
    while (n != 0) {
        c = from->crates[from->size - n];
        Day5_push(to, c);
        n--;
    }
    from->size -= count;
}

void Day5_parseInitialStack(Stack *stack, int i, size_t rowLen, char *str)
{
    uint8_t c;

    // Move up the column and push to the stack.
    // Assume i is at the first create.
    while (i > 0) {
        c = str[i];

        if (c == ' ') {
            break;
        }
        Day5_push(stack, c);
        i -= rowLen + 1;
    }
}

char *Day5_printTopOfStacks(char *buffer, Stack *stacks, size_t stackCount)
{
    buffer += sprintf(buffer, "%*.s", 10 - (int)stackCount, "");
    for (size_t j = 0; j < stackCount; j++) {
        Stack stack = stacks[j];
        buffer += sprintf(buffer, "%c", stack.crates[stack.size - 1]);
    }

    return buffer;
}

void Day5_solve(String input, String buffer)
{
    uint8_t c;

    // Assume there will never be no more than 9 stacks.
    Stack part1[9] = {0};
    Stack part2[9] = {0};

    size_t i = 0;
    size_t rowLen = 0;
    size_t stackCount = 0;

    // Find the row length of the initial stack configuration.
    while (i < input.length) {
        c = input.data[i];
        if (c == '\n') {
            rowLen = i;
            break;
        }
        i++;
    }

    // The example data only has 3 stacks.
    // Each stack column takes up 4 characters.
    stackCount = rowLen / 4 + 1;

    // Increment i to the first "1" found.
    // This is below the column of the first stack's initial values.
    while (i < input.length) {
        c = input.data[i];
        if (c == '1') {
            break;
        }
        i++;
    }


    // Fill stacks with their initial values.
    for (size_t stackIdx = 0; stackIdx < stackCount; stackIdx++) {
        Day5_parseInitialStack(&part1[stackIdx], i - rowLen - 1, rowLen, input.data);
        part2[stackIdx] = part1[stackIdx];
        i += 4;
    }

    // Move i to the first m found.
    // It should now be at the beginning of move
    while (input.data[i] != 'm') {
        i++;
    }

    // Skip over "move ", should now be at the first number.
    i += 5;

    uint64_t count = 0;
    uint64_t from = 0;
    uint64_t to = 0;

    // Run through all move instructions.
    while (i < input.length) {
        // Parse the first number on the row, count.
        while (input.data[i] != ' ') {
            count = count *10 + input.data[i] - '0';
            i++;
        }
        // skip over " from "
        i += 6;

        // parse the second number, from.
        while (input.data[i] != ' ') {
            from = from *10 + input.data[i] - '0';
            i++;
        }
        // skip over " to "
        i += 4;

        // parse the third number, to.
        while (input.data[i] != '\n') {
            to = to *10 + input.data[i] - '0';
            i++;
        }
        // skip over "\nmove "
        i += 6;

        // Indexes are zero based.
        from -= 1;
        to -= 1;

        Day5_moveOneByOne(&part1[from], &part1[to], count);
        Day5_moveMultiple(&part2[from], &part2[to], count);

        count = 0;
        from = 0;
        to = 0;
    }

    char *output = buffer.data;
    output = Day5_printTopOfStacks(output, part1, stackCount);
    output += sprintf(output, " ");
    output = Day5_printTopOfStacks(output, part2, stackCount);
}

