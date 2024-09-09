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

    for (auto &tok : *tokens) {
        if (tok->token_kind() == token::PUNCTUATION_CLOSE_PAREN) {
            len++;
            break;
        }

        if (tok->token_kind() == token::PUNCTUATION_COMMA) {
            len++;
            continue;
        }

        auto  slice = tokens->slice(len);
        auto *arg   = get_Expression(slice);
        len += arg->parse();

        args.push_back(arg);
    }

    for (auto &arg : args) {
        print(arg);
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
