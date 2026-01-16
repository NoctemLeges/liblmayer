#include <stdio.h>
#include <stdlib.h>
#include "../includes/word.h"
#include "../includes/rule.h"
#include "../includes/errors.h"

//TODO: Add functionality to check whether NumRules is equal to Number of Rules
int searchChar(Word* arr, char key){
    for(int i = 0;i<arr->currSize;i++){
        if(arr->data[i]==key) return i;
    }
    return -1;
}

void checkConfigFieldPresence(FILE* fp){
    Word* initials = (Word*)malloc(sizeof(Word));
    initArr(initials,1);
    char line[1024];
    while(fgets(line,sizeof(line), fp) != NULL){
        append(initials,line[0]);
    }
    if(searchChar(initials,'A')==-1){
        printf("Error:%s\n",strError(LMAYER_AXIOM_MISSING));
        exit(LMAYER_AXIOM_MISSING);
    }
    else if(searchChar(initials,'N')==-1){
        printf("Error:%s\n",strError(LMAYER_NUMRULES_MISSING));
        exit(LMAYER_NUMRULES_MISSING);
    }
    else if(searchChar(initials,'R')==-1){
        printf("Error:%s\n",strError(LMAYER_RULE_MISSING));
        exit(LMAYER_RULE_MISSING);
    }
    else if(searchChar(initials,'D')==-1){
        printf("Error:%s\n",strError(LMAYER_DELTA_MISSING));
        exit(LMAYER_DELTA_MISSING);
    }
    else if(searchChar(initials,'L')==-1){
        printf("Error:%s\n",strError(LMAYER_LENGTH_MISSING));
        exit(LMAYER_LENGTH_MISSING);
    }
    rewind(fp);
}

void parseNumRules(int* numRules, FILE* fp) {
    if (fp == NULL) {
        printf("Error:%s\n",strError(LMAYER_CONF_FILE_OPENING_ERROR));
        exit(LMAYER_CONF_FILE_OPENING_ERROR);
    }
    //TODO: Check whether NumRules is present in the file
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[0] == 'N') {
            if((sscanf(line, "NumRules:%d", numRules)) != 1){
                printf("Error:%s\n",strError(LMAYER_EMPTY_NUMRULES));
                exit(LMAYER_EMPTY_NUMRULES);
            }
        }
    }
    rewind(fp);
}

void parseConfig(Word* Axiom, Rule* rules, int* length, int* delta, FILE* fp) {
    if (fp == NULL) {
        printf("Error:%s\n",strError(LMAYER_CONF_FILE_OPENING_ERROR));
        exit(LMAYER_CONF_FILE_OPENING_ERROR);
    }
    char line[256];
    int counter = 0;
    checkConfigFieldPresence(fp);
    while(fgets(line,sizeof(line),fp) !=NULL){
        if(line[0] == 'R'){
            char pred;
            Word* succ = (Word*)malloc(sizeof(Word));
            initArr(succ,50);
            int pred_parsing = 0;
            int succ_parsing = 0;
            for(int i = 0;line[i]!='\n';i++){
                if(line[i]==':'){
                    pred_parsing=1;
                    continue;
                }
                if(line[i]=='-' && !succ_parsing){
                    pred_parsing = 0;
                    continue;
                }
                if(line[i]==',' && succ_parsing){
                    succ_parsing = 0;
                    continue;
                }
                if(line[i]=='>'){
                    succ_parsing = 1;
                    continue;
                }
                if(pred_parsing){
                    pred = line[i];
                    
                }
                if(succ_parsing){
                    append(succ,line[i]);
                }
                
            }
            append(succ,'\0');
            if(pred==0){
                printf("Error:%s\n",strError(LMAYER_EMPTY_RULE_PRED));
                exit(LMAYER_EMPTY_RULE_PRED);
            }
            if(succ->data[0]==0){
                printf("Error:%s\n",strError(LMAYER_EMPTY_RULE_SUCC));
                exit(LMAYER_EMPTY_RULE_SUCC);
            }
            rules[counter].predecessor = pred;
            rules[counter].successor = succ->data;
            sscanf(line,"Rule:%*c->%*[^,],%f",&rules[counter].probability); //For now, every rule must be of the format %c->%s,%f
            if(rules[counter].probability == 0.0) rules[counter].probability = 100.0;
            counter++;
               
        }
        //
        else if(line[0]=='A'){
            int parsing = 0;
            for(int i = 0;line[i]!='\n';i++){
                if(parsing){
                    append(Axiom,line[i]);
                }
                if(line[i]==':') parsing = 1;
            }
            if(Axiom->data == NULL){
                printf("Error:%s\n",strError(LMAYER_EMPTY_AXIOM));
                exit(LMAYER_EMPTY_AXIOM);
            }
            
        }
        
        else if(line[0]=='L'){
            if((sscanf(line,"Length:%d",length)) != 1){
                printf("Error:%s\n",strError(LMAYER_EMPTY_LENGTH));
                exit(LMAYER_EMPTY_LENGTH);
            }
        }
        else if(line[0]=='D'){
            if((sscanf(line,"Delta:%d",delta)) != 1){
                printf("Error:%s\n",strError(LMAYER_EMPTY_DELTA));
                exit(LMAYER_EMPTY_DELTA);
            }
        }
        
    }
    rewind(fp);
    int numRules;
    parseNumRules(&numRules,fp);
    if(counter != numRules){
        printf("Error:%s\n",strError(LMAYER_NUMRULES_MISMATCH));
        exit(LMAYER_NUMRULES_MISMATCH);
    }
    
}
