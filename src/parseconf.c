#include <stdio.h>
#include <stdlib.h>
#include "../includes/word.h"
#include "../includes/rule.h"

//Add functionality to check whether NumRules is equal to Number of Rules


void parseNumRules(int* numRules, FILE* fp) {
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[0] == 'N') {
            sscanf(line, "NumRules:%d", numRules);
        }
    }
    rewind(fp);
}

void parseConfig(Word* Axiom, Rule* rules, int* length, int* delta, FILE* fp) {
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char line[256];
    int counter = 0;
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
                if(line[i]=='>'){
                    succ_parsing = 1;
                    continue;
                }
                if(pred_parsing){
                    //printf("1%c",line[i]);
                    pred = line[i];
                    
                }
                if(succ_parsing){
                    //printf("2%c",line[i]);
                    append(succ,line[i]);
                }
                
            }
            rules[counter].predecessor = pred;
            rules[counter].successor = succ->data;
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
            
        }
        
        else if(line[0]=='L'){
            sscanf(line,"Length:%d",length);
        }
        else if(line[0]=='D'){
            sscanf(line,"Delta:%d",delta);
        }
    }

    rewind(fp);
}
