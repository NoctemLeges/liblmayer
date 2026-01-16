typedef enum{
    LMAYER_CONF_FILE_OPENING_ERROR, //parseconf.c 
    LMAYER_AXIOM_MISSING, //parseconf.c 
    LMAYER_NUMRULES_MISSING, //parseconf.c
    LMAYER_RULE_MISSING, //parseconf.c
    LMAYER_DELTA_MISSING, //parseconf.c
    LMAYER_LENGTH_MISSING, //parseconf.c
    LMAYER_NUMRULES_MISMATCH,
    LMAYER_EMPTY_AXIOM, //parseconf.c
    LMAYER_EMPTY_NUMRULES, //parseconf.c 
    LMAYER_EMPTY_RULE_PRED, //parseconf.c
    LMAYER_EMPTY_RULE_SUCC, //parseconf.c
    LMAYER_EMPTY_DELTA, //parseconf.c
    LMAYER_EMPTY_LENGTH, //parseconf.c
    LMAYER_TOTAL_PROB_NOT_100
}ErrorCodes;

const char* strError(ErrorCodes error);