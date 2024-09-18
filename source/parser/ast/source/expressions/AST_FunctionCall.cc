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
#include "parser/ast/include/nodes/AST_generate.hh"
#include "token/include/token_list.hh"

__AST_NODE_BEGIN {
PARSE_SIG(FunctionCall) {
    using namespace token;

    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return 0;
    }

    // FunctionCall ::= AnySeparatedID GenericAccess? '(' (ExpressionList)? ')'

    i32 len = 0;
    std::vector<Token*> balance;

    // we break down the function call into parts
    // 1. function path
    // 2. generic access
    // 3. arguments

    // 1. function path
    path = make_node<PathAccess>(*tokens);
    len += path->parse();

    // 2. generic access
    i32 generic_access_len = len;
    for (auto &tok : (*tokens).slice(len)) {
        if (tok->value() == "<") {
            print("Found generic access at: {}", generic_access_len);
            len++; // skip the '<'
            break;
        }

        generic_access_len++;
    }

    //generics = make_node<GenericAccess>((*tokens).slice(generic_access_len));
    //len += generics->parse();

    // 3. arguments
    i32 arguments_len = len;
    for (auto &tok : (*tokens).slice(len)) {
        if (tok->value() == "(") {
            print("Found arguments at: {}", arguments_len);
            len++; // skip the '('
            break;
        }

        arguments_len++;
    }

    arguments = make_node<ExpressionList>((*tokens).slice(arguments_len));
    len += arguments->parse();


    return len;
}

TEST_SIG(FunctionCall) {
    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return false;
    }
    return false;
}

VISITOR_IMPL(FunctionCall);
}  // namespace __AST_NODE_BEGIN
