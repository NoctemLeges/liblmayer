#include <stdio.h>
#include <stdlib.h>
#include "../includes/word.h"
#include "../includes/rule.h"
void parseConfig(Word* Axiom,Rule* rule,int* length, int* delta,FILE* fp){
    //FILE *fp = fopen("start_conf","r"); //There is a pathing issue here. Only workd when invoked from the ignore directory.
    if (fp == NULL) {
        perror("Error opening file");
    }
    char line[256];
    
    while(fgets(line,sizeof(line),fp) !=NULL){
        if (line[0] == 'A') {
            int parsing = 0;
            for (int i = 0; line[i] != '\n'; i++) {
                char c = line[i];
                if (parsing) {
                    if (c != '\n' && c != '\r')
                        append(Axiom, c);
                }
                if (c == ':') {
                    parsing = 1;
                }
            }
        }
 
        else if(line[0]=='R'){
            rule->predecessor = 'F';
            Word* succ = (Word*)malloc(sizeof(Word));
            initArr(succ,2);
            int parsing = 0;
            for (int i = 0; line[i] != '\n'; i++) {
                char c = line[i];
                if (parsing) {
                    if (c != '\n' && c != '\r')
                        append(succ, c);
                }
                if (c == '>') {
                    parsing = 1;
                }
            }
            rule->successor = succ->data;
            
        } 
        else if(line[0]=='L'){
            sscanf(line,"Length:%d",length);
        } 
        else if(line[0]=='D'){
            sscanf(line,"Delta:%d",delta);
        } 
    }
}