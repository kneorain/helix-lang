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
//  This file defines the AST Expression Parser, which is used to parse expressions in the AST.   //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#include <cstdio>

#include "neo-panic/include/error.hh"
#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/AST.hh"
#include "parser/ast/include/case_types.def"
#include "token/include/generate.hh"
#include "token/include/token_list.hh"

/* IDEINTIFIED

break into 2 parts the compound expressions and the single expressions

single expressions are:
    [x] Literals
    [x] Identifier
    [x] UnaryOp
    [x] FunctionCall
    [x] ScopeAccess
    [x] Parenthesized

compound expressions are:
    [-] PathAccess
    [-] DotAccess

    [-] BinaryOp
    [-] ArrayAccess
    [-] Cast


TODO: add the following:
    [-] List
    [-] Set
    [-] Tuple
    [-] Map
    [-] Match
    [-] Range
    [-] Lambda
    [-] GenericAccess
    [-] TernaryOp
*/

namespace parser::ast {
NodeT<Expression> get_simple_Expression(token::TokenList &tokens) {
    // Parse any simple expression
    for (auto &tok : tokens) {

        auto peek     = tok.peek();
        bool has_peek = tok.peek().has_value();

        switch (tok->token_kind()) {
            case IS_LITERAL:
                return new node::Literal(tokens);

            case IS_IDENTIFIER: {

                if (has_peek) {
                    switch (peek->get().token_kind()) {
                        case token::OPERATOR_SCOPE:
                            return new node::ScopeAccess(tokens);
                        case token::PUNCTUATION_OPEN_PAREN:
                            return new node::FunctionCall(tokens);
                        default:
                            return new node::Identifier(tokens);
                    }
                }
                return new node::Identifier(tokens);
            }

            case IS_OPERATOR:
                return new node::UnaryOp(tokens);

            case token::PUNCTUATION_OPEN_PAREN:
                return new node::Parenthesized(tokens);

            default:
                break;
        }
    }

    return nullptr;
}

NodeT<Expression> get_Expression(token::TokenList &tokens) {
    /// Parse any expression
    /// Expression ::= Literal | AnySeparatedID | BinaryOperation | UnaryOperation | FunctionCall |
    /// ParenthesizedExpression | ArrayAccess | ObjectAccess | ConditionalExpression Parsing Order

    /// The order of operations is as follows: (is this correct?)
    // Operator      ::= UnaryOp   | BinaryOp
    // Identifier    ::= DotAccess | ScopeAccess | PathAccess | FunctionCall
    // Literal       ::= Literal   | BinaryOp    | UnaryOp    | Cast         | Conditional
    // Parenthesized ::= ( Expression )

    // we parse compound expressions here

    return get_simple_Expression(tokens);
}

Expression::Expression() = default;
Expression::Expression(token::TokenList &tokens)
    : Node(tokens)
    , tokens(&tokens) {}
}  // namespace parser::ast
