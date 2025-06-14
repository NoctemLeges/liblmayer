#ifndef PARSECONF_H
#define PARSECONF_H
#include "rule.h"
#include "word.h"
#include <stdio.h>
void parseConfig(Word* Axiom,Rule* rule,int* length, int* delta,FILE* fp);
#endif