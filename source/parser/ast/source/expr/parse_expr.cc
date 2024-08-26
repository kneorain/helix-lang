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
#include <stdexcept>
#include <string>

#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/expr_nodes.hh"
#include "parser/ast/source/expr/helpers.def"
#include "token/include/generate.hh"

namespace parser::ast::node {
ParseResult Expression::parse() {
    throw std::runtime_error("This should never be called since its a base node");
}

std::string Expression::to_json(u32 depth) const {
    return R"("Expression": { "value": "This is a Base Expr" },)";
}

std::pair<NodePtr<Expression>, u64> parse_expr(token::TokenList &tokens, u64 start_depth, token::tokens term) {
    // depth only matters for pair tokens
    // when term is reached and the depth is what it should be
    // identify what kind of expr we are trying to parse.
    // Expression  ::= Literal
    //              |  AnySeparatedID
    //              |  BinaryOperation
    //              |  UnaryOperation
    //              |  FunctionCal
    //              |  ParenthesizedExpression
    //              |  ArrayAccess
    //              |  ObjectAccess
    //              |  ConditionalExpression

    NodePtr<AnySeparatedID> any_sep_path = make_node<AnySeparatedID>(tokens);
    u32 len = 0;
    auto expr = get_expr(tokens);
    any_sep_path->identifiers.push_back(expr.first);
    len += expr.second;

    expr = get_expr(tokens.slice(expr.second));
    any_sep_path->identifiers.push_back(expr.first);
    len += expr.second;

    if (!any_sep_path->identifiers.empty()) {
        return {any_sep_path, len};
    }

    return {nullptr, 0};
}

#undef LITERALS
#undef OPERATORS
}  // namespace parser::ast::node
