#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../includes/rule.h"
#include "../../../includes/word.h"
#include "../../../includes/parseconf.h"
#include "../../../includes/strexp.h"
#include "../../../includes/render.h"

int main(){
    
    FILE* fp = fopen("MA2_conf","r");
    if(fp==NULL){
        perror("Error opening MA2_conf");
        exit(1);
    }
    int NumRules;
    Word* Axiom = (Word*)malloc(sizeof(Word));
    initArr(Axiom,50);
    int Delta;
    int Length;
    parseNumRules(&NumRules,fp);
    Rule* rules = (Rule*)malloc(sizeof(Rule)*NumRules);
    parseConfig(Axiom,rules,&Length,&Delta,fp);
    //Expand the Axiom with the Rules
    Word* string = (Word*)malloc(sizeof(Word));
    initArr(string,50);
    string = strexp(Axiom,rules,NumRules,Length);
    drawLSystem(string,Delta,5.0,"MA2.svg");
}