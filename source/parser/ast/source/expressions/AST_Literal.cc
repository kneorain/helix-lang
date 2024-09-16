//===------------------------------------------ C++ ------------------------------------------====//
//                                                                                                //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).       //
//  You are allowed to use, modify, redistribute, and create derivative works, even for           //
//  commercial purposes, provided that you give appropriate credit, and indicate if changes       //
//   were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/  //
//                                                                                                //
//  SPDX-License-Identifier: CC-BY-4.0                                                            //
//  Copyright (c) 2024 (CC BY 4.0)                                                                //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//

#include "parser/ast/include/AST.hh"

__AST_NODE_BEGIN {
PARSE_SIG(Literal) {
    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return 0;
    }

    switch (tokens->front().token_kind()) {
        case token::LITERAL_STRING:
            [[fallthrough]];
            // string concat but handle edge cases like a mix or
            // r|b|u|f strings too, while maintaining the correct order and locational metadata
        case token::LITERAL_TRUE:
            [[fallthrough]];
        case token::LITERAL_FALSE:
            [[fallthrough]];
        case token::LITERAL_INTEGER:
            [[fallthrough]];
        case token::LITERAL_FLOATING_POINT:
            [[fallthrough]];
        case token::LITERAL_CHAR:
            [[fallthrough]];
        case token::LITERAL_NULL:
            value = tokens->front();
            return 1;
        default:
            break;
    }

    return 0;
}

TEST_SIG(Literal) {
    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return false;
    }

    switch (tokens->front().token_kind()) {
        case token::LITERAL_STRING:
            [[fallthrough]];
        case token::LITERAL_TRUE:
            [[fallthrough]];
        case token::LITERAL_FALSE:
            [[fallthrough]];
        case token::LITERAL_INTEGER:
            [[fallthrough]];
        case token::LITERAL_FLOATING_POINT:
            [[fallthrough]];
        case token::LITERAL_CHAR:
            [[fallthrough]];
        case token::LITERAL_NULL:
            return true;
        default:
            break;
    }

    return false;
}

VISITOR_IMPL(Literal);
}  // namespace __AST_NODE_BEGIN
