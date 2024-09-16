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
#include "parser/ast/include/AST_types.hh"
#include "parser/ast/include/nodes/AST_generate.hh"

// PathAccess := (DotAccess | ScopeAccess)*

__AST_NODE_BEGIN {
PARSE_SIG(PathAccess) {
    ParseResult len = 0;

    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return 0;
    }

    auto tmp = make_node<ScopeAccess>(*tokens);

    len += tmp->parse();

    paths = tmp->paths;

    return len;
}

TEST_SIG(PathAccess) {
    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return false;
    }

    return false;
}

VISITOR_IMPL(PathAccess);
}  // namespace __AST_NODE_BEGIN
