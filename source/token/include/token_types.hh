/*
 * token_types.hh
 *
 * This file contains the header for the token types in the Helix programming language.
 * It includes various header files that define the enums for delimiters, keywords, literals,
 * operators, others, primitives, and punctuations.
 */

#ifndef __TOKEN_TYPES_H__
#define __TOKEN_TYPES_H__

#include "./tokens.def"

namespace token {
    GENERATE_TOKENS_ENUM_AND_MAPPING() // generate enum and maps for all tokens

    // undefine the macros to prevent global namespace pollution
    #undef MAKE_TOKEN
    #undef MAKE_TOKEN_PAIR
    #undef GENERATE_TOKENS_ENUM_AND_MAPPING
    
    #undef KEYWORD_TOKENS_COUNT
    #undef DELIMITER_TOKENS_COUNT
    #undef LITERAL_TOKENS_COUNT
    #undef OPERATOR_TOKENS_COUNT
    #undef OTHER_TOKENS_COUNT
    #undef PRIMITIVE_TOKENS_COUNT
    #undef PUNCTUATION_TOKENS_COUNT
    
    #undef TOKENS
    #undef KEYWORD_TOKENS
    #undef DELIMITER_TOKENS
    #undef LITERAL_TOKENS
    #undef OPERATOR_TOKENS
    #undef OTHER_TOKENS
    #undef PRIMITIVE_TOKENS
    #undef PUNCTUATION_TOKENS
}

#endif  // __TOKEN_TYPES_H__