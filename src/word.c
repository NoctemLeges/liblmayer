#include "../includes/word.h"
#include <stdlib.h>
#include <string.h>
void initArr(Word *arr,size_t initialCap){
    arr->data = (char*)malloc(initialCap*sizeof(char));
    arr->currSize = 0;
    arr->capacity = initialCap;
}

void append(Word* arr,char c){
    if(arr->currSize==arr->capacity){
        arr->capacity*=2;
        arr->data = realloc(arr->data,arr->capacity*sizeof(char));
    }
    arr->data[arr->currSize++] = c;
}

void printArrData(Word* arr){
    for(int i = 0;i<arr->currSize;i++){
        printf("%c",arr->data[i]);
    }
    printf("\n");
}

void printArrDetails(Word *arr){
    printf("Data: ");
    printArrData(arr);
    printf("Current Size: %ld\n",arr->currSize);
    printf("Capacity: %ld\n",arr->capacity);

}

void appendCharWise(Word* string, char* change){
    for(int i = 0;i<strlen(change);i++){
        append(string,change[i]);
    }
}
