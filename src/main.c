#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <sys/time.h>
#include <String.h>
#include <Array.h>
#include "Day1.c"
#include "Day2.c"
#include "Day3.c"


String_Buffer Input_load(int day)
{
    char filename[100];

    sprintf(filename, "input/day%d.txt", day + 1);

    String_Buffer str = String_fromFile(filename);

    return str;
}

String_Buffer *Input_loadAll(int argc, char *argv[])
{
    String_Buffer *inputs = Array_alloc(sizeof(String_Buffer), 25);

    for (int day = 0; day < 25; day++) {
        Array_push(inputs, Input_load(day));
    }

    return inputs;
}

void Input_freeAll(String_Buffer *inputs)
{
    Array_for(inputs, day) {
        String_free(inputs[day]);
    }

    Array_free(inputs);
}

int dayFromArgs(char *argv[])
{
    char *opt = argv[1];
    int day;

    if (opt[0] != '-') {
        return 0;
    }

    day = atoi(&opt[1]);

    if (day > 0 && day <= 25) {
        return day;
    }

    return 0;
}

void runDay(int day, String input)
{
    printf("Day %d: ", day);
    struct timeval start, stop;

    gettimeofday(&start, NULL);
    switch (day) {
        case 1:
            Day1_solve(input);
            break;

        case 2:
            Day2_solve(input);
            break;

        case 3:
            Day3_solve(input);
            break;

        default:
            printf("- not implemented -");
    }
    gettimeofday(&stop, NULL);

    float time = (float)(stop.tv_sec - start.tv_sec) * 1e6;
    time += (float)stop.tv_usec - (float)start.tv_usec;
    printf(" %10.0fµs\n", time);
}

int main(int argc, char *argv[])
{
    String input;

    if (argc == 3) {
        int day = dayFromArgs(argv);
        input = (String){ argv[2], strlen(argv[2])};
        runDay(day, input);

        return 0;
    }

    String_Buffer *inputs = Input_loadAll(argc, argv);

    Array_for(inputs, day) {
        input = String_fromBuffer(inputs[day]);
        if (input.length == 0) {
            continue;
        }

        runDay(day + 1, input);
    }

    Input_freeAll(inputs);

    return 0;
}
