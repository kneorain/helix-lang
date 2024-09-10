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

#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/AST.hh"
#include "parser/ast/include/AST_interface.hh"
#include "token/include/token_list.hh"

namespace parser::ast::node {
ParseResult FunctionCall::parse() {
    if (tokens->empty()) [[unlikely]] {
        return 0;
    }

    // FunctionCall ::= AnySeparatedID GenericAccess? '(' (ExpressionList)? ')'
    // TODO: add support for generic access

    i32 len = 0;

    // Parse the function name
    callee = new PathAccess(*tokens);
    len += 1;

    i32 _len = 0;

    auto slice = tokens->slice(len);
    tokens = &slice;

    for (auto &tok : *tokens) {
        if (tok->token_kind() == token::tokens::PUNCTUATION_OPEN_PAREN) {
            len += 1;
            tok.advance();
            continue;
        }
        
        if (tok->token_kind() == token::tokens::PUNCTUATION_CLOSE_PAREN) {
            len += 1;
            tok.advance();
            break;
        }

        if (tok->token_kind() == token::tokens::PUNCTUATION_COMMA) {
            len += 1;
            tok.advance();
            continue;
        }

        token::TokenList slice = tokens->slice(len);
        token::print_tokens(slice);
        auto *expr_node        = get_Expression(slice);
        
        if (expr_node != nullptr) {
            args.push_back(expr_node);
            tok.advance(_len = expr_node->parse());
            len += _len;
        }
    }

    return len;
}

bool FunctionCall::test() {
    if (tokens->empty()) [[unlikely]] {
        return false;
    }
    return false;
}

void FunctionCall::accept(Visitor &visitor) const { visitor.visit(*this); }

}  // namespace parser::ast::node
