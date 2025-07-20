#ifndef RENDER_H
#define RENDER_H
#include <stdio.h>
#include "rule.h"
#include "word.h"
void drawLSystem(Word* instructions, double angleDelta, double step, const char* filename,int isTree);
#endif