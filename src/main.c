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
#include "Day7.c"
#include "Day8.c"

char tmpBuffer[1024*32];

String Main_loadInput(int day)
{
    String string = {0};

    sprintf(tmpBuffer, "input/day%d.txt", day);

    FILE *file = fopen(tmpBuffer, "r");

    if (file == NULL) {
        return string;
    }

    fseek(file, 0, SEEK_END);
    string.length = ftell(file);
    assert(string.length < sizeof(tmpBuffer));
    fseek(file, 0, SEEK_SET);
    string.data = tmpBuffer;

    if (fread(tmpBuffer, sizeof(char), string.length, file) != string.length) {
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

float Main_runDay(int day, String input, String output)
{
    struct timeval start, stop;

    switch (day) {
        case 1:
            gettimeofday(&start, NULL);
            Day1_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 2:
            gettimeofday(&start, NULL);
            Day2_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 3:
            gettimeofday(&start, NULL);
            Day3_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 4:
            gettimeofday(&start, NULL);
            Day4_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 5:
            gettimeofday(&start, NULL);
            Day5_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 6:
            gettimeofday(&start, NULL);
            Day6_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 7:
            gettimeofday(&start, NULL);
            Day7_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 8:
            gettimeofday(&start, NULL);
            Day8_solve(input, output);
            gettimeofday(&stop, NULL);
            break;


        default:
            printf("- not implemented -");
    }

    float elapsedTimeMicroSec = (float)(stop.tv_sec - start.tv_sec) * 1e6;
    elapsedTimeMicroSec += (float)stop.tv_usec - (float)start.tv_usec;

    return elapsedTimeMicroSec;

}

float Main_repeatDay(int day, String input, size_t repeat)
{
    if (input.length == 0) {
        return 0;
    }

    char *alignedAddress = tmpBuffer + input.length;

    size_t offset = (size_t)alignedAddress % 64;

    if (offset > 0) {
        alignedAddress += 64 - offset;
    }

    String output = (String){
        alignedAddress,
        sizeof(tmpBuffer) - (alignedAddress - tmpBuffer)
    };

    float elapsedTimeMicroSec = 0;

    for (size_t i = 0; i < repeat; i++) {
        elapsedTimeMicroSec += Main_runDay(day, input, output);
    }

    elapsedTimeMicroSec /= repeat;
    printf("Day %d: %.30s %10.0fµs\n", day, output.data, elapsedTimeMicroSec);

    return elapsedTimeMicroSec;
}

int main(int argc, char *argv[])
{
    String input;
    size_t repeat = 1;

    if (argc == 2) {
        int day = Main_dayFromArgs(argv);
        Main_repeatDay(day, Main_loadInput(day), repeat);

        return 0;
    } else if (argc == 3) {
        int day = Main_dayFromArgs(argv);
        input = (String){ argv[2], strlen(argv[2])};
        Main_repeatDay(day, input, repeat);

        return 0;
    }

    float elapsedTimeMicroSec = 0;

    for (size_t day = 1; day <= 25; day++) {
        elapsedTimeMicroSec += Main_repeatDay(day, Main_loadInput(day), repeat);
    }

    if (elapsedTimeMicroSec < 1000) {
        printf("\nTotal time: %.0fµs\n", elapsedTimeMicroSec);
    } else {
        printf("\nTotal time: %.1fms\n", elapsedTimeMicroSec / 1000);
    }

    return 0;
}
