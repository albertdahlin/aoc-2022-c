#pragma once
#include <inttypes.h>

#define Ocr_literal(r1,r2,r3,r4,r5,r6) 0b##r1##r2##r3##r4##r5##r6##00000000

typedef uint32_t Ocr_Glyph;

Ocr_Glyph Ocr_parseRow(char *input, Ocr_Glyph glyph);

Ocr_Glyph Ocr_parseFinalize(Ocr_Glyph);

Ocr_Glyph Ocr_fromChar(char);

char Ocr_fromGlyph(Ocr_Glyph);

void Ocr_print(Ocr_Glyph);

void Ocr_printRow(Ocr_Glyph glyph, int64_t row);
