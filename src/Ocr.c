#include <stdio.h>
#include "Ocr.h"


Ocr_Glyph Ocr_parseRow(char *input, Ocr_Glyph glyph)
{
    for (size_t i = 0; i < 4; i++) {
        if (input[i] == '#') {
            glyph |= 1;
        }
        glyph <<= 1;
    }

    return glyph;
}

Ocr_Glyph Ocr_parseFinalize(Ocr_Glyph glyph)
{
    glyph <<= 7;

    return glyph;
}

void Ocr_print(Ocr_Glyph glyph)
{
    for (size_t i = 0; i < 24; i++) {
        if (glyph & 0x80000000) {
            printf("#");
        } else {
            printf(".");
        }
        if ((i+1) % 4 == 0) {
            printf("\n");
        }
        glyph <<= 1;
    }
}

void Ocr_printRow(Ocr_Glyph glyph, int64_t row)
{
    glyph <<= row * 4;
    for (size_t i = 0; i < 4; i++) {
        if (glyph & 0x80000000) {
            printf("#");
        } else {
            printf(".");
        }
        glyph <<= 1;
    }
}

void Ocr_setRowPixes(Ocr_Glyph glyph, int64_t row, char *buffer)
{
    glyph <<= row * 4;
    for (size_t i = 0; i < 4; i++) {
        if (glyph & 0x80000000) {
            buffer[i] = '#';
        } else {
            buffer[i] = '.';
        }
        glyph <<= 1;
    }
}


static Ocr_Glyph alphabet[26] = {
    // A
    Ocr_literal(
        0110,
        1001,
        1001,
        1111,
        1001,
        1001
    ),
    // B
    Ocr_literal(
        1110,
        1001,
        1110,
        1001,
        1001,
        1110
    ),
    // C
    Ocr_literal(
        0110,
        1001,
        1000,
        1000,
        1001,
        0110
    ),
    // D
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // E
    Ocr_literal(
        1111,
        1000,
        1110,
        1000,
        1000,
        1111
    ),
    // F
    Ocr_literal(
        1111,
        1000,
        1110,
        1000,
        1000,
        1000
    ),
    // G
    Ocr_literal(
        0110,
        1001,
        1000,
        1011,
        1001,
        0111
    ),
    // H
    Ocr_literal(
        1001,
        1001,
        1111,
        1001,
        1001,
        1001
    ),
    // I
    Ocr_literal(
        0111,
        0010,
        0010,
        0010,
        0010,
        0111
    ),
    // J
    Ocr_literal(
        0011,
        0001,
        0001,
        0001,
        1001,
        0110
    ),
    // K
    Ocr_literal(
        1001,
        1010,
        1100,
        1010,
        1010,
        1001
    ),
    // L
    Ocr_literal(
        1000,
        1000,
        1000,
        1000,
        1000,
        1111
    ),
    // M
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // N
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // O
    Ocr_literal(
        0110,
        1001,
        1001,
        1001,
        1001,
        0110
    ),
    // P
    Ocr_literal(
        1110,
        1001,
        1001,
        1110,
        1000,
        1000
    ),
    // Q
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // R
    Ocr_literal(
        1110,
        1001,
        1001,
        1110,
        1010,
        1001
    ),
    // S
    Ocr_literal(
        0111,
        1000,
        1000,
        0110,
        0001,
        1110
    ),
    // T
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // U
    Ocr_literal(
        1001,
        1001,
        1001,
        1001,
        1001,
        0110
    ),
    // v
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // W
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // X
    Ocr_literal(
        0000,
        0000,
        0000,
        0000,
        0000,
        0000
    ),
    // Y
    Ocr_literal(
        1000,
        1000,
        0101,
        0010,
        0010,
        0010
    ),
    // Z
    Ocr_literal(
        1111,
        0001,
        0010,
        0100,
        1000,
        1111
    ),
};


Ocr_Glyph Ocr_fromChar(char c)
{
    return alphabet[c - 'A'];
}

char Ocr_fromGlyph(Ocr_Glyph glyph)
{
    for (size_t i = 0; i < 26; i++) {
        if (alphabet[i] == glyph) {
            return i + 'A';
        }
    }

    return '-';
}
