// -*- C++ -*-
//===------------------------------------------------------------------------------------------===//
//
// Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
// You are allowed to use, modify, redistribute, and create derivative works, even for commercial
// purposes, provided that you give appropriate credit, and indicate if changes were made.
// For more information, please visit: https://creativecommons.org/licenses/by/4.0/
//
// SPDX-License-Identifier: CC-BY-4.0
// Copyright (c) 2024 (CC BY 4.0)
//
//===------------------------------------------------------------------------------------------===//

#include <expected>
#include <string>

#include "core/utils/hx_print"
#include "core/utils/josnify.hh"
#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/expr_nodes.hh"
#include "token/include/generate.hh"
#include "token/include/token_list.hh"

namespace parser::ast::node {
parser::ast::ParseResult parser::ast::node::QualifiedNamespaceID::parse() {
    NodePtr<node::Identifier> _node;
    u64 length = 0;

    if (source_tokens.empty()) [[unlikely]] {
        return 0; // TODO: error out
    }

    // QualifiedNamespaceID ::= Identifier ('::' Identifier)*

    if (source_tokens[0] != tokens::IDENTIFIER) {
        return 0; // TODO: error out
    }

    identifiers.push_back(make_node<node::Identifier>(source_tokens[0]));

    if (source_tokens.size() < 1) {
        return 0; // TODO: error out
    }

    if (source_tokens[1] != tokens::OPERATOR_SCOPE) {
        return 0; // TODO: error out
    }

    // at this point we has satisfied 1/3;

    auto tokena = source_tokens.slice(1);

    for (auto &tok : source_tokens.slice(1)) {
        if (tok.current().get() != tokens::OPERATOR_SCOPE) {
            break;
        } // pass dont add the :: to the list but add the len

        length += 1;
        tok.advance(); // Worth

        if (tok.current().get() != tokens::IDENTIFIER) {
            break;
        } // pass

        identifiers.push_back(make_node<node::Identifier>(tok.current().get())); // Worth
    }

    for (auto &_node : identifiers) {
        length += _node->parse().value_or(0);
    }

    return length-1; // remove the len of the last thing
}
}  // end namespace parser::ast::node