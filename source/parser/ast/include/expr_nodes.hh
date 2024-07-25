/**
 * @author Dhruvan Kartik
 * @copyright Copyright (c) 2024 (CC BY 4.0)
 *
 * @note This code is part of the Helix Language Project and is licensed under the Attribution 4.0
 * International license (CC BY 4.0). You are allowed to use, modify, redistribute, and create
 * derivative works, even for commercial purposes, provided that you give appropriate credit,
 * provide a link to the license, and indicate if changes were made. For more information, please
 * visit: https://creativecommons.org/licenses/by/4.0/ SPDX-License-Identifier: CC-BY-4.0
 *
 * @note This code is provided by the creators of Helix. Visit our website at:
 * https://helix-lang.com/ for more information.
 */
#ifndef __AST_NODES_HH__
#define __AST_NODES_HH__

#include "parser/ast/include/ast.hh"

namespace parser::ast::node {
using namespace token;

struct Literals final : Expression<Literals> {
    enum class LiteralType : u8 {
        INVALID,
        BOOL,
        CHAR,
        FLOAT,
        STRING,
        INTEGER,
        SCIENTIFIC,
        NONE  // null
    };

    AST_NODE_METHODS(Literals);

    LiteralType type = LiteralType::INVALID;
    Token value;
};

struct BinaryOp final : Expression<BinaryOp> { // 1 + 2
    AST_NODE_METHODS(BinaryOp);
    
    Token op;
    NodePtr<Expression<void>> left;
    NodePtr<Expression<void>> right;
};

struct UnaryOp final : Expression<UnaryOp> { // -1
    AST_NODE_METHODS(UnaryOp);
    
    Token op; // -
    NodePtr<Expression<void>> right; // 1
};

struct SuffixOp final : Expression<SuffixOp> { // foo[...] | foo|...|
    AST_NODE_METHODS(SuffixOp);

    NodePtr<Expression<void>> index; // of type Identifier or ScopeAccess
    NodePtr<Expression<void>> right;
    std::pair<Token, Token> op;
};

struct Identifier final : Expression<Identifier> {
    AST_NODE_METHODS(Identifier);

    Token value;
};

struct ScopeAccess final : Expression<ScopeAccess> { // a->b | foo::bar
    enum class ScopeType : u8 {
        INVALID,     // invalid access
        POINTER,  // ->
        MEMBER,   // .
        NAMESPACE // ::
    };

    AST_NODE_METHODS(ScopeAccess);

    ScopeType type = ScopeType::INVALID;
    Token     parent; // foo
    Token     child;  // bar
};

struct FunctionCall final : Expression<FunctionCall> { // std::print("yoo", end=" ");
    AST_NODE_METHODS(FunctionCall);

    NodeList<ScopeAccess> function; // std::print
    NodeList<> arguments;           // "yoo"
    NodeList<> typed_arguments;     // end=" "

};

struct InlineControlFlow final : Expression<InlineControlFlow> { // 10 if i == 1 else 5
    AST_NODE_METHODS(InlineControlFlow);

    NodePtr<Expression<void>> condition; // i == 1
    NodePtr<Expression<void>> pass;      // 10
    NodePtr<Expression<void>> fail;      // 5
};

struct InlineLambda final : Expression<InlineLambda> { // lambda[this] x, y { return x+y; };
    AST_NODE_METHODS(InlineLambda);

    // TODO
};

struct InlineListComprehension final : Expression<InlineListComprehension> {
    AST_NODE_METHODS(InlineListComprehension);

    // TODO
};

Expression<void> parse_expr(TokenListRef tokens);
}  // namespace parser::ast::node

#endif  // __AST_NODES_HH__