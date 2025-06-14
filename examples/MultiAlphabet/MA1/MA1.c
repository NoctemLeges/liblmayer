#include <stdio.h>
#include <stdlib.h>
#include "../../../includes/parseconf.h"
#include "../../../includes/render.h"
#include "../../../includes/rule.h"
#include "../../../includes/strexp.h"
#include "../../../includes/word.h"

int main(){
    FILE* fp = fopen("MA1_conf","r");
    Word* Axiom = (Word*)malloc(sizeof(Word));
    initArr(Axiom,50);
    Rule rule;
    int length;
    int delta;
    parseConfig(Axiom,&rule,&length,&delta,fp);
    Word* string = strexp(Axiom,rule,length);
    drawLSystem(string,delta,5.0,"MA1.svg");

}