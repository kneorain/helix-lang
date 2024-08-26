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

#include <__expected/unexpected.h>
#include <cstddef>
#include <expected>
#include <string>

#include "core/utils/hx_print"
#include "core/utils/josnify.hh"
#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/expr_nodes.hh"
#include "token/include/generate.hh"

namespace parser::ast::node {
parser::ast::ParseResult parser::ast::node::Identifier::parse() {
    if (source_tokens.empty()) {
        // TODO: handle error
        return 0;
    }

    for (auto &tok : source_tokens) {
        if (tok.current().get() == tokens::IDENTIFIER) {
            this->value = tok.current().get();
            return 1;
        }

        // else handle error
    }

    return 0;
}
}  // end namespace parser::ast::node