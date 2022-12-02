#include <String.h>
#include <Parser.h>
#include <inttypes.h>

typedef enum {
    D2_DRAW,
    D2_WIN,
    D2_LOSE
} Day2_Outcome;

typedef enum {
    D2_ROCK,
    D2_PAPER,
    D2_SCISSOR
} Day2_Hand;


Day2_Outcome Day2_outcomeOf(Day2_Hand me, Day2_Hand oponent)
{
    return ((me - oponent + 3) % 3);
}


int Day2_outcomeScore(Day2_Outcome outcome)
{
    return (outcome == D2_LOSE) ? 0 : 3 * outcome + 3;
}


int Day2_handScore(Day2_Hand hand)
{
    return hand + 1;
}


int Day2_toOutcome(uint8_t n)
{
    return ((n + 2) % 3);
}


Day2_Hand Day2_myHand(Day2_Hand oponent, Day2_Outcome outcome)
{
    return (outcome + oponent) % 3;
}


void Day2_solve(String input)
{
    Parser parser = Parser_fromString(input);
    uint8_t oponent, me;
    uint64_t part1 = 0;
    uint64_t part2 = 0;
    Day2_Outcome outcome;
    Day2_Hand myHand;

    while (!Parser_isDone(&parser)) {
        oponent = Parser_getChar(&parser);
        Parser_skipChar(' ', &parser);
        me = Parser_getChar(&parser);
        Parser_skipChar('\n', &parser);

        if (parser.error > 0) {
            printf("Invalid input");
            return;
        }

        if (oponent < 'A' || oponent > 'C') {
            printf("Col 1 must be A,B,C");
            return;
        }

        if (me < 'X' || me > 'Z') {
            printf("Col 3 must be X,Y,Z");
            return;
        }

        // Values should be between 0-2 instead of ASCII
        oponent -= 'A';
        me -= 'X';

        part1 += Day2_handScore(me);
        part1 += Day2_outcomeScore(Day2_outcomeOf(me, oponent));

        outcome = Day2_toOutcome(me);
        myHand = Day2_myHand(oponent, outcome);
        part2 += Day2_outcomeScore(outcome);
        part2 += Day2_handScore(myHand);
    }

    printf("%10lu %10lu", part1, part2);
}

