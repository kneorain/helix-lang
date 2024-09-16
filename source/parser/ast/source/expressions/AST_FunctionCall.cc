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

__AST_NODE_BEGIN {
PARSE_SIG(FunctionCall) {
    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return 0;
    }

    // FunctionCall ::= AnySeparatedID GenericAccess? '(' (ExpressionList)? ')'
    // TODO: add support for generic access

    i32 len = 0;

    // Parse the function name
    callee = make_node<PathAccess>(*tokens);
    len += callee->parse();

    print("len: ", len);

    /*
    0x1 : open paren
    0x2 : close paren
    0x3 : generic access
    0x4 : comma
    0x5 : expression

    */

    auto slice = tokens->slice(len); // starting at ()

    token::print_tokens(slice);


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
