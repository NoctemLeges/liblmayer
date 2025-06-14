#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "../includes/word.h"
#include "../includes/rule.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double x, y, angle;
} TurtleState;

typedef struct {
    TurtleState* data;
    int top;
    int capacity;
} Stack;

void initStack(Stack* s, int capacity) {
    s->data = (TurtleState*)malloc(sizeof(TurtleState) * capacity);
    s->top = -1;
    s->capacity = capacity;
}

void push(Stack* s, TurtleState value) {
    if (s->top + 1 >= s->capacity) {
        s->capacity *= 2;
        s->data = (TurtleState*)realloc(s->data, sizeof(TurtleState) * s->capacity);
    }
    s->data[++s->top] = value;
}

TurtleState pop(Stack* s) {
    if (s->top >= 0) {
        return s->data[s->top--];
    }
    TurtleState empty = {0, 0, 0};
    return empty;
}

void freeStack(Stack* s) {
    free(s->data);
}

void drawLSystem(Word* instructions, double angleDelta, double step, const char* filename) {
    double x = 0.0, y = 0.0, angle = 90.0;
    double minX = x, minY = y, maxX = x, maxY = y;

    Stack stack;
    initStack(&stack, 100);
    
    for (size_t i = 0; i < instructions->currSize; i++) {
        char c = instructions->data[i];
        if (isalpha(c)) {
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
        } else if (c == '[') {
            TurtleState current = {x, y, angle};
            push(&stack, current);
        } else if (c == ']') {
            TurtleState state = pop(&stack);
            x = state.x;
            y = state.y;
            angle = state.angle;
        }
    }

    double width = maxX - minX + 10.0;
    double height = maxY - minY + 10.0;
    double offsetX = -minX + 5.0;
    double offsetY = -minY + 5.0;

    FILE* svg = fopen(filename, "w");
    if (!svg) {
        perror("Error opening SVG file");
        freeStack(&stack);
        return;
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%f\" height=\"%f\" viewBox=\"0 0 %f %f\">\n",
            width, height, width, height);
    fprintf(svg, "<rect width=\"100%%\" height=\"100%%\" fill=\"black\" />\n");
    fprintf(svg, "<g stroke=\"white\" stroke-width=\"1\" fill=\"none\">\n");

    x = 0.0;
    y = 0.0;
    angle = 90.0;
    initStack(&stack, 100);

    for (size_t i = 0; i < instructions->currSize; i++) {
        char c = instructions->data[i];
        if (isalpha(c)) {
            double newX = x + step * cos(angle * M_PI / 180.0);
            double newY = y + step * sin(angle * M_PI / 180.0);
            fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />\n",
                    x + offsetX, height - (y + offsetY),
                    newX + offsetX, height - (newY + offsetY));
            x = newX;
            y = newY;
        } else if (c == '+') {
            angle += angleDelta;
        } else if (c == '-') {
            angle -= angleDelta;
        } else if (c == '[') {
            TurtleState current = {x, y, angle};
            push(&stack, current);
        } else if (c == ']') {
            TurtleState state = pop(&stack);
            x = state.x;
            y = state.y;
            angle = state.angle;
        }
    }

    fprintf(svg, "</g>\n</svg>\n");
    fclose(svg);
    freeStack(&stack);
}
