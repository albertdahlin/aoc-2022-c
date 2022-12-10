#include <stdio.h>
#include <String.h>
#include <Ocr.c>
#include "test.h"



int main()
{
    //TEST_INIT();

    Ocr_Glyph fromRows = 0;
    fromRows = Ocr_parseRow("####", fromRows);
    fromRows = Ocr_parseRow("#...", fromRows);
    fromRows = Ocr_parseRow("###.", fromRows);
    fromRows = Ocr_parseRow("#...", fromRows);
    fromRows = Ocr_parseRow("#...", fromRows);
    fromRows = Ocr_parseRow("####", fromRows);
    fromRows = Ocr_parseFinalize(fromRows);

    char columns = 9;

    for (char c = 'A';  c <= 'Z'; c += columns) {
        for (char letter = 0; letter <  columns; letter++) {
            if (c + letter > 'Z') continue;
            printf("%c    ", c + letter);
        }
        printf("\n");
        for (size_t row = 0; row < 6; row++) {
            for (int64_t letter = 0; letter < columns; letter++) {
                if (c + letter > 'Z') continue;
                Ocr_printRow(Ocr_fromChar(c + letter), row);
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
}


