#include <stdio.h>
#include <String.h>
#include <Day07.c>
#include "test.h"


int main()
{
    char buffer[1024*32] = {0};
    String output = (String){
        buffer,
        sizeof(buffer)
    };

    RUN(Day7_solve, "mjqjpqmgbljsphdztnvjfqwrcgsmlb\n", "7", "19");
}
