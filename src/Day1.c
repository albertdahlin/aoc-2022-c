#include <String.h>
#include <Parser.h>
#include <Array.h>

uint64_t *Day1_parseInput(Parser *parser, uint64_t *caloriesPerElf)
{
    uint64_t calories = 0;

    while (!Parser_isDone(parser)) {
        calories += Parser_toU64(parser);

        if (parser->error > 0) {
            printf("Expecting int");
            return caloriesPerElf;
        }

        Parser_skipChar('\n', parser);

        if (Parser_current(parser) == '\n' || Parser_isDone(parser)) {
            Parser_skipChar('\n', parser);
            Array_push(caloriesPerElf, calories);
            calories = 0;
        }
    }

    return caloriesPerElf;
}

void Day1_solve(String input)
{
    Parser parser = Parser_fromString(input);

    uint64_t *caloriesPerElf = Array_alloc(sizeof(uint64_t), 256);

    caloriesPerElf = Day1_parseInput(&parser, caloriesPerElf);

    if (parser.error > 0) {
        printf("Parser error end");
        goto abort;
    }
    if (Array_length(caloriesPerElf) < 3) {
        printf("need at least 3 elves");
        goto abort;
    }

    Array_qsort_u64(caloriesPerElf);

    size_t lastIdx = Array_length(caloriesPerElf) - 1;
    uint64_t part1 = caloriesPerElf[lastIdx];
    uint64_t part2 =
        caloriesPerElf[lastIdx]
        + caloriesPerElf[lastIdx - 1]
        + caloriesPerElf[lastIdx - 2];

    printf("%10lu %10lu", part1, part2);

    abort:
    Array_free(caloriesPerElf);
}

