#include <Day2.c>
#include <stdio.h>
#include "test.h"


int main()
{
    EXPECT(Day2_outcomeOf(D2_ROCK, D2_ROCK) == D2_DRAW, "fail");
    EXPECT(Day2_outcomeOf(D2_ROCK, D2_PAPER) == D2_LOSE, "fail");
    EXPECT(Day2_outcomeOf(D2_ROCK, D2_SCISSOR) == D2_WIN, "fail");

    EXPECT(Day2_outcomeOf(D2_PAPER, D2_ROCK) == D2_WIN, "fail");
    EXPECT(Day2_outcomeOf(D2_PAPER, D2_PAPER) == D2_DRAW, "fail");
    EXPECT(Day2_outcomeOf(D2_PAPER, D2_SCISSOR) == D2_LOSE, "fail");

    EXPECT(Day2_outcomeOf(D2_SCISSOR, D2_ROCK) == D2_LOSE, "fail");
    EXPECT(Day2_outcomeOf(D2_SCISSOR, D2_PAPER) == D2_WIN, "fail");
    EXPECT(Day2_outcomeOf(D2_SCISSOR, D2_SCISSOR) == D2_DRAW, "fail");

    EXPECT(Day2_toOutcome(0) == D2_LOSE, "fail");
    EXPECT(Day2_toOutcome(1) == D2_DRAW, "fail");
    EXPECT(Day2_toOutcome(2) == D2_WIN, "fail");

    EXPECT(Day2_myHand(D2_ROCK, D2_WIN) == D2_PAPER, "fail");
    EXPECT(Day2_myHand(D2_ROCK, D2_DRAW) == D2_ROCK, "fail");
    EXPECT(Day2_myHand(D2_ROCK, D2_LOSE) == D2_SCISSOR, "fail");

    EXPECT(Day2_myHand(D2_PAPER, D2_WIN) == D2_SCISSOR, "fail");
    EXPECT(Day2_myHand(D2_PAPER, D2_DRAW) == D2_PAPER, "fail");
    EXPECT(Day2_myHand(D2_PAPER, D2_LOSE) == D2_ROCK, "fail");

    EXPECT(Day2_myHand(D2_SCISSOR, D2_WIN) == D2_ROCK, "fail");
    EXPECT(Day2_myHand(D2_SCISSOR, D2_DRAW) == D2_SCISSOR, "fail");
    EXPECT(Day2_myHand(D2_SCISSOR, D2_LOSE) == D2_PAPER, "fail");
}
