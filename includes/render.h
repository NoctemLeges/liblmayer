#ifndef RENDER_H
#define RENDER_H
#include <stdio.h>
#include "rule.h"
#include "word.h"
void svgHeader(FILE *f, int width, int height);

void svgFooter(FILE *f);

void drawLSystem(Word* instructions, double angleDelta, double step, const char* filename);
#endif