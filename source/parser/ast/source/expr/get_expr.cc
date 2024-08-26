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
#include <utility>
#include <vector>

#include "core/error/error.hh"
#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/expr_nodes.hh"
#include "parser/ast/include/nodes/nodes.hh"
#include "parser/ast/source/expr/helpers.def"

namespace parser::ast::node {
std::pair<NodePtr<Expression>, u64> get_expr(TokenList tokens) {
    // identify what kind of expr we are trying to parse.
    // Expression  ::= Literal
    //              |  AnySeparatedID
    //              |  UnaryOperation
    //              |  FunctionCal
    //              |  ParenthesizedExpression
    //              |  ArrayAccess
    //              |  ObjectAccess
    //              |  ConditionalExpression
    // TODO: missing:
    //                 Match

    NodePtr<Expression> result;
    u64                 result_len = 0;

    // attempt the following, just parse single expr if the return value is greater then 0
    // return the new node thats pre parsed or else continue parsing
    // this has the possibility to reduce time complexity to O(n) - where n is number of nodes
    // this change would also significantly reduce the memory footprint of the ast parser.

    if (tokens.empty()) [[unlikely]] {
        is_tokens_empty();
    }

    result     = make_node<node::Literal>(tokens[0]);
    result_len = result->parse().value_or(0);
    if (result_len > 0) {
        return {result, result_len};
    }

    // if (is_op(tokens[0])) {
    //     if (tokens.size() > 0) {
    //         // return make_node<node::UnaryOperation>(tokens);
    //     }

    //     throw error::Panic(error::CodeError{.pof = &tokens[0], .err_code = 0.100112});
    // }

    result     = make_node<node::QualifiedNamespaceID>(tokens);
    result_len = result->parse().value_or(0);
    if (result_len > 0) {
        return {result, result_len};
    }

    result     = make_node<node::DotSeparatedID>(tokens);
    result_len = result->parse().value_or(0);
    if (result_len > 0) {
        return {result, result_len};
    }

    return {nullptr, 0};
}
}  // namespace parser::ast::node

#undef LITERALS
#undef OPERATORS