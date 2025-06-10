#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/word.h"
#include "../includes/rule.h"
#include "../includes/parseconf.h"
#include "../includes/strexp.h"
#include "../includes/render.h"

int main(){
    Word* Axiom = (Word*)malloc(sizeof(Word));
    initArr(Axiom,50);
    Rule rule;
    int length;
    int delta;
    parseConfig(Axiom,&rule,&length,&delta);
    Word *string = Axiom;
    for(int i = 0;i<length;i++){
        string = applyRule(string,rule);
        
    }
    //printArrData(string);
    drawLSystem(string, delta,5.0, "example.svg");
}