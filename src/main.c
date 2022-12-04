#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>

#include "String.h"
#include "Day1.c"
#include "Day2.c"
#include "Day3.c"
#include "Day4.c"


String Input_load(int day)
{
    char filename[100];
    String string = {0};

    sprintf(filename, "input/day%d.txt", day + 1);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return string;
    }

    fseek(file, 0, SEEK_END);
    string.length = ftell(file);
    fseek(file, 0, SEEK_SET);

    string.data = malloc(string.length);
    assert(string.data != NULL);

    if (fread(string.data, sizeof(char), string.length, file) != string.length) {
        free(string.data);
        string.length = 0;
    }

    fclose(file);

    return string;
}

String *Input_loadAll(int argc, char *argv[])
{
    String *inputs = malloc(sizeof(String) * 25);

    for (int day = 0; day < 25; day++) {
        inputs[day] = Input_load(day);
    }

    return inputs;
}

void Input_freeAll(String *inputs)
{
    for (size_t i = 0; i < 25; i++) {
        free(inputs[i].data);
    }

    free(inputs);
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

float runDay(int day, String input)
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

        case 4:
            Day4_solve(input);
            break;

        default:
            printf("- not implemented -");
    }
    gettimeofday(&stop, NULL);

    float time = (float)(stop.tv_sec - start.tv_sec) * 1e6;
    time += (float)stop.tv_usec - (float)start.tv_usec;
    printf(" %10.0fµs\n", time);

    return time;
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

    String *inputs = Input_loadAll(argc, argv);
    float time = 0;

    for(size_t day = 0; day < 25; day++) {
        input = inputs[day];
        if (input.length == 0) {
            continue;
        }

        time += runDay(day + 1, input);
    }

    if (time < 1000) {
        printf("\nTotal time: %.0fµs\n", time);
    } else {
        printf("\nTotal time: %.1fms\n", time / 1000);
    }

    Input_freeAll(inputs);

    return 0;
}
