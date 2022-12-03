#include <String.h>

void Day1_solve(String input)
{
    uint64_t cal = 0;
    uint64_t elf = 0;
    uint64_t sm = 0;
    uint64_t md = 0;
    uint64_t lg = 0;
    uint8_t c;

    for (size_t i = 0; i < input.length; i++) {
        c = input.data[i];

        if ('0' <= c && c <= '9') {
            cal = cal * 10 + c - '0';
        } else if (cal == 0) {
            if (elf <= sm) {
                elf = 0;
                continue;
            } else if (elf > lg) {
                lg = elf;
            } else if (elf > md) {
                sm = md;
                md = elf;
            } else {
                sm = elf;
            }
            elf = 0;
        } else {
            elf += cal;
            cal = 0;
        }
    }

    printf("%10lu %10lu", lg, sm + md + lg);
}
