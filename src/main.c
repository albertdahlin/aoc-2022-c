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
#include "Day5.c"
#include "Day6.c"

char tmp_buffer[1024*16];

String Main_loadInput(int day)
{
    String string = {0};

    sprintf(tmp_buffer, "input/day%d.txt", day);

    FILE *file = fopen(tmp_buffer, "r");

    if (file == NULL) {
        return string;
    }

    fseek(file, 0, SEEK_END);
    string.length = ftell(file);
    assert(string.length < sizeof(tmp_buffer));
    fseek(file, 0, SEEK_SET);
    string.data = tmp_buffer;

    if (fread(tmp_buffer, sizeof(char), string.length, file) != string.length) {
        string.length = 0;
    }

    fclose(file);

    return string;
}

int Main_dayFromArgs(char *argv[])
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

float Main_runDay(int day, String input)
{
    if (input.length == 0) {
        return 0;
    }
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

        case 5:
            Day5_solve(input);
            break;

        case 6:
            Day6_solve(input);
            break;

        default:
            printf("- not implemented -");
    }
    gettimeofday(&stop, NULL);

    float elapsedTimeMicroSec = (float)(stop.tv_sec - start.tv_sec) * 1e6;
    elapsedTimeMicroSec += (float)stop.tv_usec - (float)start.tv_usec;
    printf(" %10.0fµs\n", elapsedTimeMicroSec);

    return elapsedTimeMicroSec;
}

int main(int argc, char *argv[])
{
    String input;

    if (argc == 2) {
        int day = Main_dayFromArgs(argv);
        Main_runDay(day, Main_loadInput(day));

        return 0;
    } else if (argc == 3) {
        int day = Main_dayFromArgs(argv);
        input = (String){ argv[2], strlen(argv[2])};
        Main_runDay(day, input);

        return 0;
    }

    float elapsedTimeMicroSec = 0;

    for (size_t day = 1; day <= 25; day++) {
        elapsedTimeMicroSec += Main_runDay(day, Main_loadInput(day));
    }

    if (elapsedTimeMicroSec < 1000) {
        printf("\nTotal time: %.0fµs\n", elapsedTimeMicroSec);
    } else {
        printf("\nTotal time: %.1fms\n", elapsedTimeMicroSec / 1000);
    }

    return 0;
}
