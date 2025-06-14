#include "../includes/word.h"
#include "../includes/rule.h"
#include <stdlib.h>
Word* applyRule(Word* string,Rule rule){
    Word *temp = (Word*)malloc(sizeof(Word));
    initArr(temp,string->capacity);
    for(int i = 0;i<string->currSize;i++){
        if(string->data[i]==rule.predecessor){
            appendCharWise(temp,rule.successor);
        }
        else{
            append(temp,string->data[i]);
        }
    }
    return temp;
}

Word* strexp(Word* Axiom, Rule rule,int length){
    Word *string = Axiom;
    for(int i = 0;i<length;i++){
        string = applyRule(string,rule);
    }
    return string;
}