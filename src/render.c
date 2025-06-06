#include <stdio.h>
#include <stdlib.h>
#include "../includes/word.h"
#include "../includes/rule.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void svgHeader(FILE *f, int width, int height) {
    fprintf(f, "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d' viewBox='0 0 %d %d'>\n",
            width, height, width, height);
    fprintf(f, "<g stroke='black' stroke-width='1' fill='none'>\n");
}

void svgFooter(FILE *f) {
    fprintf(f, "</g>\n</svg>\n");
}

void drawLSystem(Word* instructions, double angleDelta, double step, const char* filename) {
    double x = 0.0, y = 0.0, angle = 90.0;
    double minX = x, minY = y, maxX = x, maxY = y;

    for (size_t i = 0; i < instructions->currSize; i++) {
        char c = instructions->data[i];
        if (c == 'F') {
            double newX = x + step * cos(angle * M_PI / 180.0);
            double newY = y + step * sin(angle * M_PI / 180.0);
            if (newX < minX) minX = newX;
            if (newX > maxX) maxX = newX;
            if (newY < minY) minY = newY;
            if (newY > maxY) maxY = newY;
            x = newX;
            y = newY;
        } else if (c == '+') {
            angle += angleDelta;
        } else if (c == '-') {
            angle -= angleDelta;
        }
    }

    double width = maxX - minX + 10.0;
    double height = maxY - minY + 10.0;
    double offsetX = -minX + 5.0;
    double offsetY = -minY + 5.0;

    FILE* svg = fopen(filename, "w");
    if (!svg) {
        perror("Error opening SVG file");
        return;
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%f\" height=\"%f\" viewBox=\"0 0 %f %f\">\n",
            width, height, width, height);
    fprintf(svg, "<polyline points=\"");

    x = 0.0;
    y = 0.0;
    angle = 90.0;

    fprintf(svg, "%f,%f ", x + offsetX, height - (y + offsetY));  // Initial point

    for (size_t i = 0; i < instructions->currSize; i++) {
        char c = instructions->data[i];
        if (c == 'F') {
            double newX = x + step * cos(angle * M_PI / 180.0);
            double newY = y + step * sin(angle * M_PI / 180.0);
            fprintf(svg, "%f,%f ", newX + offsetX, height - (newY + offsetY));
            x = newX;
            y = newY;
        } else if (c == '+') {
            angle += angleDelta;
        } else if (c == '-') {
            angle -= angleDelta;
        }
    }

    fprintf(svg, "\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(svg, "</svg>\n");
    fclose(svg);
}