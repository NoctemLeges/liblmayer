#ifndef STREXP_H
#define STREXP_H
#include "word.h"
#include "rule.h"
Word* applyRule(Word*,Rule);
Word* strexp(Word*,Rule,int);
#endif