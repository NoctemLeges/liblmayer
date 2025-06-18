#include "../includes/word.h"
#include "../includes/rule.h"
#include <stdlib.h>
Word* strexp(Word* Axiom, Rule* rules,int numRules,int length){
    Word* string = (Word*)malloc(sizeof(Word));
    initArr(string,50);
    appendCharWise(string,Axiom->data);
    for(int i = 0;i<length;i++){
        Word* temp = (Word*)malloc(sizeof(Word));
        initArr(temp,50);
        for(int j = 0;j<string->currSize;j++){
            int matched = 0;
            for(int k = 0;k<numRules;k++){
                if(string->data[j]==rules[k].predecessor){
                    matched = 1;
                    appendCharWise(temp,rules[k].successor);
                }
            }
            if(!matched) append(temp,string->data[j]);
        }
        string = temp;
    }
    return string;
}