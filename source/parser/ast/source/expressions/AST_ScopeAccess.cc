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
#include "parser/ast/include/nodes/AST_generate.hh"
#include <memory>


// ScopeAccess := Ident ('::' Ident)*

__AST_NODE_BEGIN {
PARSE_SIG(ScopeAccess) {
    ParseResult len = 0;

    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return 0;
    }
    
    if ((*tokens).front().token_kind() != token::tokens::IDENTIFIER) {
        return 0;
    }

    if (tokens->size() == 1) {
        paths.push_back(make_node<Identifier>(tokens->front()));
        return 1;
    }

    // at this point our checks have passed for the pre, and now we can move on to the post iter

    int next = 0x2; // ident

    for (auto &tok : *tokens) {
        switch (next) {
            case 0x1:
                if (tok->token_kind() == token::tokens::OPERATOR_SCOPE) {
                    ++len;
                    next = 0x2; // ident
                    continue;
                }
                
                break;
            case 0x2:
                if (tok->token_kind() == token::tokens::IDENTIFIER) {
                    paths.push_back(make_node<Identifier>(tok.current().get()));
                    len += 1;
                    next = 0x1; // scope op
                    continue;
                }
                
                break;
            default:
                // TODO: Error handling
                // something went horribly wrong
                print("something went horribly wrong");
                return 0;
        }

        if (tok->token_kind() !=  token::tokens::OPERATOR_SCOPE
            && tok->token_kind() != token::tokens::IDENTIFIER) {
                break;
        }
    }

    return len;
}

TEST_SIG(ScopeAccess) {
    if (tokens == nullptr || tokens->empty()) [[unlikely]] {
        return false;
    }
    return false;
}

VISITOR_IMPL(ScopeAccess);
}  // namespace __AST_NODE_BEGIN
