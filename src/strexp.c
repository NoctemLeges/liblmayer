#include "../includes/word.h"
#include "../includes/rule.h"
#include "../includes/errors.h"
#include <time.h>
#include <stdlib.h>

void checkTotalProbability(Rule* rules, int numRules){
    Word* allPreds = (Word*)malloc(sizeof(Word));
    initArr(allPreds,10);
    for(int i = 0;i<numRules;i++){
        int alreadyChecked = 0;
        char pred = rules[i].predecessor;
        for(int i = 0;i<allPreds->currSize;i++){
            if(pred==allPreds->data[i]) alreadyChecked = 1;
        }
        if(alreadyChecked==1) continue;
        float total = rules[i].probability;
        for(int j = i+1;j<numRules;j++){
            if(rules[j].predecessor==pred) total += rules[j].probability;
        }
        if(total != 100.0){
            printf("Error:%s\n",strError(LMAYER_TOTAL_PROB_NOT_100));
            exit(LMAYER_TOTAL_PROB_NOT_100);
        }
        append(allPreds,pred);
    }
}

Word* strexp(Word* Axiom, Rule* rules,int numRules,int length){
    checkTotalProbability(rules,numRules);
    srand(time(NULL));
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
                    float random = 1 + ((float)rand()/(float)RAND_MAX)*(100 - 1);
                    if(random <= rules[k].probability) appendCharWise(temp,rules[k].successor);
                    else continue;
                }
            }
            if(!matched) append(temp,string->data[j]);
        }
        string = temp;
    }
    return string;
}