#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include "String.h"


extern void Day1_solve(String input, String buffer);
extern void Day2_solve(String input, String buffer);
extern void Day3_solve(String input, String buffer);
extern void Day4_solve(String input, String buffer);
extern void Day5_solve(String input, String buffer);
extern void Day6_solve(String input, String buffer);
extern void Day7_solve(String input, String buffer);
extern void Day8_solve(String input, String buffer);
extern void Day9_solve(String input, String buffer);
extern void Day10_solve(String input, String buffer);
extern void Day11_solve(String input, String buffer);

typedef struct {
    int onlyDay;
    int repeat;
    int error;
    char *errorv;
    bool asMarkdown;
} Args;

enum Args_Expected {
    NOTHING,
    SHOULD_BE_DAY,
    SHOULD_BE_REPEAT
};

enum Args_Error {
    ERR_NONE,
    ERR_ARG_UNKNOWN,
    ERR_ARG_MISSING,
    ERR_DAY,
    ERR_REPEAT
};


static char tmpBuffer[1024*32];

static String loadInput(int day)
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

static float runDay(int day, String input, String output, Args args)
{
    struct timeval start, stop;
    memset(output.data, 0, output.length);

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

        case 9:
            gettimeofday(&start, NULL);
            Day9_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 10:
            gettimeofday(&start, NULL);
            Day10_solve(input, output);
            gettimeofday(&stop, NULL);
            break;

        case 11:
            gettimeofday(&start, NULL);
            Day11_solve(input, output);
            gettimeofday(&stop, NULL);
            break;


        default:
            printf("- not implemented -");
    }

    float elapsedTimeMicroSec = (float)(stop.tv_sec - start.tv_sec) * 1e6;
    elapsedTimeMicroSec += (float)stop.tv_usec - (float)start.tv_usec;

    return elapsedTimeMicroSec;

}


static Args parseArgs(int argc, char *argv[])
{
    Args args = {0};

    args.onlyDay    = 0;
    args.repeat     = 1;
    args.error      = ERR_NONE;
    args.asMarkdown = false;

    enum Args_Expected expected = NOTHING;

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        args.errorv = arg;

        if (arg[0] == '-') {
            switch (arg[1]) {
                case 'd':
                    expected = SHOULD_BE_DAY;
                    break;

                case 'r':
                    expected = SHOULD_BE_REPEAT;
                    break;

                case 'm':
                    args.asMarkdown = true;
                    break;

                default:
                    args.error = ERR_ARG_UNKNOWN;
            }
        } else {
            switch (expected) {
                case NOTHING:
                    args.error = ERR_ARG_UNKNOWN;
                    break;

                case SHOULD_BE_DAY:
                    int day = atoi(arg);
                    if (day > 0 && day <= 25) {
                        args.onlyDay = day;
                    } else {
                        args.error = ERR_DAY;
                    }
                    expected = NOTHING;

                    break;

                case SHOULD_BE_REPEAT:
                    int repeat = atoi(arg);
                    if (repeat > 0) {
                        args.repeat = repeat;
                    } else {
                        args.error = ERR_REPEAT;
                    }
                    expected = NOTHING;

                    break;
                    break;
            }
        }
    }

    if (expected) {
        args.error = ERR_ARG_MISSING;
    }

    return args;
}

static void printError(Args args)
{
    switch (args.error) {
        case ERR_NONE:
            printf("WTF, this should never happen.\n");
            break;

        case ERR_ARG_UNKNOWN:
            printf("Unknown arg: %s\n", args.errorv);
            break;

        case ERR_ARG_MISSING:
            printf("Missing value for: %s\n", args.errorv);
            break;

        case ERR_DAY:
            printf("Invalid value for day: %s\n", args.errorv);
            break;

        case ERR_REPEAT:
            printf("Invalid value for repeat: %s\n", args.errorv);
            break;
    }
}
static void printHeader(Args args)
{
    if (args.asMarkdown) {
        printf("|  Day |    Time |\n");
        printf("| ---: | ------: |\n");
    }
}

static void printFooter(Args args, float elapsedTimeMicroSec)
{
    if (args.asMarkdown) {
        printf("|  Sum |  %.0fµs |\n", elapsedTimeMicroSec);
        return;
    } else {
        if (elapsedTimeMicroSec < 1000) {
            printf("\nTotal time: %.0fµs", elapsedTimeMicroSec);
        } else {
            printf("\nTotal time: %.1fms", elapsedTimeMicroSec / 1000);
        }
    }

    if (args.repeat > 1) {
        printf(" (average from %d runs)", args.repeat);
    }
    printf("\n");
}

static void printDay(Args args, int day, String output, float elapsedTimeMicroSec)
{
    if (args.asMarkdown) {
        if (day > 9) {
            printf("| [%d] | %5.0fµs |\n", day, elapsedTimeMicroSec);
        } else {
            printf("|  [%d] | %5.0fµs |\n", day, elapsedTimeMicroSec);
        }
    } else {
        printf("Day %2d: %.30s %10.0fµs\n", day, output.data, elapsedTimeMicroSec);
    }
}

static float repeatDay(int day, String input, Args args)
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

    for (size_t i = 0; i < args.repeat; i++) {
        elapsedTimeMicroSec += runDay(day, input, output, args);
    }

    elapsedTimeMicroSec /= args.repeat;

    printDay(args, day, output, elapsedTimeMicroSec);

    return elapsedTimeMicroSec;
}

int main(int argc, char *argv[])
{
    Args args = parseArgs(argc, argv);

    if (args.error) {
        printError(args);
        return 1;
    }

    if (args.onlyDay > 0) {
        repeatDay(args.onlyDay, loadInput(args.onlyDay), args);

        return 0;
    }


    float elapsedTimeMicroSec = 0;

    printHeader(args);

    for (size_t day = 1; day <= 25; day++) {
        elapsedTimeMicroSec += repeatDay(day, loadInput(day), args);
    }


    printFooter(args, elapsedTimeMicroSec);

    return 0;
}
