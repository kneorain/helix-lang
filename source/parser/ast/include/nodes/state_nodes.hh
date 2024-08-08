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

#ifndef __AST_STATE_NODES_HH__
#define __AST_STATE_NODES_HH__

#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/nodes.hh"

namespace parser::ast::node {
using namespace token;

// Control Flow
struct ForLoop final : Statement<ForLoop> {
    AST_NODE_METHODS(ForLoop);
    NodePtr<> loopType;  // Either CStyleForLoop or PyStyleForLoop
    NodePtr<Suite> suite;
};

struct WhileLoop final : Statement<WhileLoop> {
    AST_NODE_METHODS(WhileLoop);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct IfStatement final : Statement<IfStatement> {
    AST_NODE_METHODS(IfStatement);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct ElseIfStatement final : Statement<ElseIfStatement> {
    AST_NODE_METHODS(ElseIfStatement);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct ElseStatement final : Statement<ElseStatement> {
    AST_NODE_METHODS(ElseStatement);
    NodePtr<Suite> suite;
};

struct ContinueStatement final : Statement<ContinueStatement> {
    AST_NODE_METHODS(ContinueStatement);
};

struct BreakStatement final : Statement<BreakStatement> {
    AST_NODE_METHODS(BreakStatement);
};

struct SwitchStatement final : Statement<SwitchStatement> {
    AST_NODE_METHODS(SwitchStatement);
    NodeList<NodePtr<>> cases;  // CaseStatement or DefaultCaseStatement
};

struct CaseStatement final : Statement<CaseStatement> {
    AST_NODE_METHODS(CaseStatement);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct DefaultCaseStatement final : Statement<DefaultCaseStatement> {
    AST_NODE_METHODS(DefaultCaseStatement);
    NodePtr<Suite> suite;
};

// Statements
struct Assignment final : Statement<Assignment> {
    AST_NODE_METHODS(Assignment);
    NodePtr<AnySeparatedID> variable;
    NodePtr<Expression<void>> expression;
};

struct BlockStatement final : Statement<BlockStatement> {
    AST_NODE_METHODS(BlockStatement);
    NodePtr<Suite> suite;
};
}  // namespace parser::ast::node

#endif  // __AST_STATE_NODES_HH__