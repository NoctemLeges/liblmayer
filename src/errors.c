#include "../includes/errors.h"

const char* strError(ErrorCodes error){
    switch(error){
        case LMAYER_CONF_FILE_OPENING_ERROR: return "Configuration File not Found.";
        case LMAYER_AXIOM_MISSING: return "No Axiom found in config file.";
        case LMAYER_NUMRULES_MISSING: return "Number of Rules not specified in config file.";
        case LMAYER_RULE_MISSING: return "No production rule specified in config file.";
        case LMAYER_DELTA_MISSING: return "No delta specified in config file.";
        case LMAYER_LENGTH_MISSING: return "No expansion depth (Length) specified in config file.";
        case LMAYER_NUMRULES_MISMATCH: return "NumRules does not match number of Rules in config file.";
        case LMAYER_EMPTY_AXIOM: return "Axiom empty in config file.";
        case LMAYER_EMPTY_NUMRULES: return "NumRules empty in config file.";
        case LMAYER_EMPTY_RULE_PRED: return "Production rule missing predecessor in config file.";
        case LMAYER_EMPTY_RULE_SUCC: return "Production rule missing successor in config file.";
        case LMAYER_EMPTY_DELTA: return "Delta empty in config file.";
        case LMAYER_EMPTY_LENGTH: return "Expansion depth (Length) empty in config file.";
        default: return "Unknown Error.";
        
    }
}