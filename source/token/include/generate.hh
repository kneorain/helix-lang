/**
 * @author Dhruvan Kartik
 * @copyright Copyright (c) 2024 (CC BY 4.0)
 *
 * @note This code is part of the Helix Language Project and is licensed under the Attribution 4.0
 * International license (CC BY 4.0). You are allowed to use, modify, redistribute, and create
 * derivative works, even for commercial purposes, provided that you give appropriate credit,
 * provide a link to the license, and indicate if changes were made. For more information, please
 * visit: https://creativecommons.org/licenses/by/4.0/ SPDX-License-Identifier: CC-BY-4.0
 *
 * @note This code is provided by the creators of Helix. Visit our website at:
 * https://helix-lang.com/ for more information.
 */

#ifndef __TOKENS_H__
#define __TOKENS_H__

#include "../enums/delimiters.def"
#include "../enums/keywords.def"
#include "../enums/literals.def"
#include "../enums/operators.def"
#include "../enums/others.def"
#include "../enums/primitives.def"
#include "../enums/punctuation.def"
#include "../types/mapping.hh"

#define MAKE_TOKEN(name, string) name,
#define MAKE_TOKEN_PAIR(name, string) std::pair{name, string},
#define MAKE_TOKEN_CLASS(name, string)                            \
    class name {                                                  \
      public:                                                     \
        constexpr std::string_view make_view() { return string; } \
    };

#define TOKENS_COUNT                \
    KEYWORD_TOKENS_COUNT            \
        + DELIMITER_TOKENS_COUNT    \
        + LITERAL_TOKENS_COUNT      \
        + OPERATOR_TOKENS_COUNT     \
        + OTHER_TOKENS_COUNT        \
        + PRIMITIVE_TOKENS_COUNT    \
        + PUNCTUATION_TOKENS_COUNT

#define TOKENS(MACRO)       \
    KEYWORD_TOKENS(MACRO)   \
    DELIMITER_TOKENS(MACRO) \
    LITERAL_TOKENS(MACRO)   \
    OPERATOR_TOKENS(MACRO)  \
    OTHER_TOKENS(MACRO)     \
    PRIMITIVE_TOKENS(MACRO) \
    PUNCTUATION_TOKENS(MACRO)

// The enum inside of the struct removes the naming conflict with the token classes.

#define GENERATE_TOKENS_ENUM_AND_MAPPING()                                         \
                                                                                   \
    enum tokens {TOKENS(MAKE_TOKEN) };                                             \
                                                                                   \
                                                                                   \
    constexpr Mapping<tokens, TOKENS_COUNT> tokens_map{{TOKENS(MAKE_TOKEN_PAIR)}}; \
                                                                                   \
    namespace token_classes { TOKENS(MAKE_TOKEN_CLASS) }

namespace token {
    GENERATE_TOKENS_ENUM_AND_MAPPING()  // generate enum and maps for all tokens

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
}  // namespace token

#endif  // __TOKENS_H__