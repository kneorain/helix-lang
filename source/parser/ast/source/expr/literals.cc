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

namespace parser::ast::node {
parser::ast::ParseResult parser::ast::node::Literal::parse() {
    // linearly parse out any literal
    for (auto &tok : source_tokens) {
        switch (tok->token_kind()) {
            case tokens::LITERAL_FALSE:
            case tokens::LITERAL_TRUE:
                type = LiteralType::BOOL;
                break;

            case tokens::LITERAL_CHAR:
                type = LiteralType::CHAR;

                if ((tok->value().size() - 3) > 1) {
                    return std::unexpected(ParseError(tok.current().get(), 1.020));
                }
                break;

            case tokens::LITERAL_STRING:
                type = LiteralType::STRING;
                break;

            case tokens::LITERAL_NULL:
                type = LiteralType::NONE;
                break;

            case tokens::LITERAL_FLOATING_POINT:
                type = LiteralType::FLOAT;
                break;

                if ((tok->value().contains('e') || tok->value().contains('E')) &&
                    (tok->value().contains('-') || tok->value().contains('+'))) {
                    type = LiteralType::SCIENTIFIC;
                }
                break;

            case tokens::LITERAL_INTEGER:
                type = LiteralType::INTEGER;

                if ((tok->value().contains('e') || tok->value().contains('E')) &&
                    (tok->value().contains('-') || tok->value().contains('+'))) {
                    type = LiteralType::SCIENTIFIC;
                }
                break;

            default:
                return std::unexpected(ParseError(tok.current().get(), 0.0001));
        }

        if (type != LiteralType::INVALID) {
            value = tok.current().get();
            break;
        }
    }

    return 1;  // since the size would never be greater then 1.
}
}  // end namespace parser::ast::node