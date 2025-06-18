#ifndef PARSECONF_H
#define PARSECONF_H
#include "rule.h"
#include "word.h"
#include <stdio.h>
void parseNumRules(int* numRules,FILE* fp);
void parseConfig(Word* Axiom,Rule* rules,int* length, int* delta,FILE* fp);
#endif