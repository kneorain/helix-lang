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

#ifndef __AST_EXPR_NODES_HH__
#define __AST_EXPR_NODES_HH__

#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/nodes.hh"

namespace parser::ast::node {
using namespace token;
// Control Flow
struct MatchExpression final : Expression<MatchExpression> {
    AST_NODE_METHODS(MatchExpression);
    NodeList<std::pair<NodePtr<Expression<void>>, NodePtr<>>>
        cases;  // (Expression | '_') -> (CodeBlock | (':' Expression))
};

// Functions and Methods
struct ReturnExpression final : Expression<ReturnExpression> {
    AST_NODE_METHODS(ReturnExpression);
    NodePtr<Expression<void>> expression;
};

struct YieldExpression final : Expression<YieldExpression> {
    AST_NODE_METHODS(YieldExpression);
    NodePtr<Expression<void>> expression;
};

// Operators
struct BinaryOperation final : Expression<BinaryOperation> {
    AST_NODE_METHODS(BinaryOperation);
    NodePtr<Expression<void>> left;
    NodePtr<Operator> op;
    NodePtr<Expression<void>> right;
};

struct UnaryOperation final : Expression<UnaryOperation> {
    AST_NODE_METHODS(UnaryOperation);
    NodePtr<Operator> op;
    NodePtr<Expression<void>> expression;
};

// Expressions
struct FunctionCall final : Expression<FunctionCall> {
    AST_NODE_METHODS(FunctionCall);
    NodePtr<AnySeparatedID> function;
    NodePtr<GenericAccess> genericAccess;
    NodeList<Expression<void>> arguments;
};

struct ParenthesizedExpression final : Expression<ParenthesizedExpression> {
    AST_NODE_METHODS(ParenthesizedExpression);
    NodePtr<Expression<void>> expression;
};

struct ArrayAccess final : Expression<ArrayAccess> {
    AST_NODE_METHODS(ArrayAccess);
    NodePtr<AnySeparatedID> array;
    NodePtr<Expression<void>> index;
};

struct ObjectAccess final : Expression<ObjectAccess> {
    AST_NODE_METHODS(ObjectAccess);
    NodePtr<AnySeparatedID> object;
    NodePtr<Identifier> member;
};

struct ConditionalExpression final : Expression<ConditionalExpression> {
    AST_NODE_METHODS(ConditionalExpression);
    NodePtr<Expression<void>> condition;
    NodePtr<Expression<void>> trueExpression;
    NodePtr<Expression<void>> falseExpression;
};

// Base Elements
struct Literal final : Expression<Literal> {
    enum class LiteralType : u8 { INVALID, BOOL, CHAR, FLOAT, STRING, INTEGER, SCIENTIFIC, NONE };

    AST_NODE_METHODS(Literal);
    LiteralType type = LiteralType::INVALID;
    Token value;
};
}  // namespace parser::ast::node

#endif  // __AST_EXPR_NODES_HH__