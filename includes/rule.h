#ifndef RULE_H
#define RULE_H

typedef struct Rule{
    char predecessor;
    char* successor;
    float probability;
}Rule;
#endif