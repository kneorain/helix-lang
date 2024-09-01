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
//                                                                                                //
//  This file defines the interface to the AST classes.                                           //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_INTERFACE_H__
#define __AST_INTERFACE_H__

#include "core/utils/josnify.hh"
#include "parser/ast/include/AST_types.hh"
#include "token/include/token_list.hh"

namespace parser::ast {
enum class NodeTypes {
    // Expressions
    BinaryExpr,
    UnaryExpr,
    LiteralExpr,
    IdentifierExpr,
    CallExpr,
    GroupingExpr,
    // Statements
    BlockStmt,
    ExpressionStmt,
    PrintStmt,
    VarStmt,
    // Declarations
    FunctionDecl,
    VarDecl,
    // Types
    BoolType,
    IntType,
    FloatType,
    StringType,
    VoidType,
};

class Node {
  public:
    virtual ~Node()                                          = default;
    virtual ParseResult<Node> parse()                        = 0;
    virtual ParseResult<Node> test()                         = 0;
    virtual void              accept(Visitor &visitor) const = 0;

    Node(const Node &)            = default;
    Node &operator=(const Node &) = default;
    Node(Node &&)                 = default;
    Node &operator=(Node &&)      = default;
};

class Expr : public Node {
public:
    Expr();
    explicit Expr(token::TokenList &tokens);
};
class Stmt : public Node {};
class Decl : public Node {};
class Type : public Node {};

class Literal : public Expr {
  protected:
    token::TokenList *tokens;
  public:
    explicit Literal(token::TokenList &tokens) : tokens(&tokens) {}
    virtual ~Literal() = default;
    virtual ParseResult<Node> parse() override = 0;
    virtual ParseResult<Node> test() override  = 0;
    virtual void              accept(Visitor &visitor) const override = 0;
};

}  // namespace parser::ast

#endif  // __AST_INTERFACE_H__