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

__AST_NODE_BEGIN {
using namespace token;

// Control Flow
class ForLoop final : public Statement {
    AST_NODE_METHODS(ForLoop);
    NodePtr<> loopType;  // Either CStyleForLoop or PyStyleForLoop
    NodePtr<Suite> suite;
};

class WhileLoop final : public Statement {
    AST_NODE_METHODS(WhileLoop);
    NodePtr<Expression> condition;
    NodePtr<Suite> suite;
};

class IfStatement final : public Statement {
    AST_NODE_METHODS(IfStatement);
    NodePtr<Expression> condition;
    NodePtr<Suite> suite;
};

class ElseIfStatement final : public Statement {
    AST_NODE_METHODS(ElseIfStatement);
    NodePtr<Expression> condition;
    NodePtr<Suite> suite;
};

class ElseStatement final : public Statement {
    AST_NODE_METHODS(ElseStatement);
    NodePtr<Suite> suite;
};

class ContinueStatement final : public Statement {
    AST_NODE_METHODS(ContinueStatement);
};

class BreakStatement final : public Statement {
    AST_NODE_METHODS(BreakStatement);
};

class SwitchStatement final : public Statement {
    AST_NODE_METHODS(SwitchStatement);
    NodeList<NodePtr<>> cases;  // CaseStatement or DefaultCaseStatement
};

class CaseStatement final : public Statement {
    AST_NODE_METHODS(CaseStatement);
    NodePtr<Expression> condition;
    NodePtr<Suite> suite;
};

class DefaultCaseStatement final : public Statement {
    AST_NODE_METHODS(DefaultCaseStatement);
    NodePtr<Suite> suite;
};

// Statements
class Assignment final : public Statement {
    AST_NODE_METHODS(Assignment);
    NodePtr<AnySeparatedID> variable;
    NodePtr<Expression> expression;
};

class BlockStatement final : public Statement {
    AST_NODE_METHODS(BlockStatement);
    NodePtr<Suite> suite;
};
}  // namespace __AST_NODE_BEGIN

#endif  // __AST_STATE_NODES_HH__