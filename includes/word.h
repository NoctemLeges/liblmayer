#ifndef WORD_H
#define WORD_H
#include <stdio.h>

typedef struct Word{
    char* data;
    size_t currSize;
    size_t capacity;
}Word;

void initArr(Word *arr,size_t initialCap);
void append(Word* arr,char c);
void printArrData(Word* arr);
void printArrDetails(Word *arr);
void appendCharWise(Word* string, char* change);
#endif