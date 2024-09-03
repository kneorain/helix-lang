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

#include "parser/ast/include/AST.hh"

#include "parser/ast/include/case_types.def"
#include "token/include/token_list.hh"

namespace parser::ast {
enum class ExpressionType {
    //< once we can confirm its a unary operator we know there cant be:
    //  DotAccess | ScopeAccess | PathAccess | FunctionCall | Literal | Parenthesized
    UnaryOp,

    //< once we can confirm its a binary operator we know there cant be:
    //  DotAccess | ScopeAccess | PathAccess | FunctionCall | Literal | Parenthesized
    BinaryOp,

    //< once we can confirm its an dot path we know there cant be:
    //  UnaryOp | Literal | Parenthesized
    DotAccess,

    //< once we can confirm its an scope path we know there cant be:
    //  UnaryOp | Literal | Parenthesized
    ScopeAccess,

    //< once we can confirm its an path we know there cant be:
    //  UnaryOp | Literal | Parenthesized | DotAccess | ScopeAccess
    PathAccess,

    //< once we can confirm its a function call we know there cant be:
    //  UnaryOp | Literal
    FunctionCall,

    //< once we can confirm its a literal we know there can be anything
    Literal,

    //< we can confirm its a cast if we see an 'as' keyword
    Cast,

    //< we can confirm its a conditional if we see an 'if' keyword
    Conditional,

    //< we can confirm its a parenthesized expression if we see an '('
    Parenthesized
};




bool is_termination_token(token::tokens kind, std::map<char, u32> &depth_map) {
    switch (kind) {
        case token::PUNCTUATION_SEMICOLON:
            return true;

        case token::PUNCTUATION_CLOSE_PAREN:
            if (depth_map['('] == 0) {
                return true;
            }

            --depth_map['('];
            break;

        case token::PUNCTUATION_CLOSE_BRACE:
            if (depth_map['{'] == 0) {
                return true;
            }

            --depth_map['{'];
            break;

        case token::PUNCTUATION_CLOSE_BRACKET:
            if (depth_map['['] == 0) {
                return true;
            }

            --depth_map['['];
            break;

        case token::PUNCTUATION_CLOSE_ANGLE:
            if (depth_map['<'] == 0) {
                return true;
            }

            --depth_map['<'];
            break;

        case token::PUNCTUATION_COMMA:
            return true;

        case token::PUNCTUATION_OPEN_PAREN:
            ++depth_map['('];
            break;

        case token::PUNCTUATION_OPEN_BRACE:
            ++depth_map['{'];
            break;

        case token::PUNCTUATION_OPEN_BRACKET:
            ++depth_map['['];
            break;

        case token::PUNCTUATION_OPEN_ANGLE:
            ++depth_map['<'];
            break;

        default:
            return false;
    }

    return false;
}

/*
 *  get_Expression is a recursive reverse descent parser that parses an expression from a
 *  list of tokens. It returns a NodeT<Expression> which is a shared pointer to an Expression node.
 *
 */
NodeT<Expression> get_Expression(token::TokenList &tokens) {
    /// Parse any expression
    /// Expression ::= Literal | AnySeparatedID | BinaryOperation | UnaryOperation | FunctionCall |
    /// ParenthesizedExpression | ArrayAccess | ObjectAccess | ConditionalExpression Parsing Order

    /// The order of operations is as follows: (is this correct?)
    // Operator      ::= UnaryOp   | BinaryOp
    // Identifier    ::= DotAccess | ScopeAccess | PathAccess | FunctionCall
    // Literal       ::= Literal   | BinaryOp    | UnaryOp    | Cast         | Conditional
    // Parenthesized ::= ( Expression )

    /// The order of operations is as follows:
    // UnaryOp       ::= op ... | ... op
    // BinaryOp      ::= ... op ...
    // DotAccess     ::= ... . ...
    // ScopeAccess   ::= ... :: ...
    // PathAccess    ::= ... :: ... | ... . ...
    // FunctionCall  ::= ... ( ... )
    // Literal       ::= Literal
    // Cast          ::= ... as ...
    // Conditional   ::= ... if ... else ...
    // Parenthesized ::= ( Expression )

    // osmehting like:

    // -1
    // -1 + 2 < this is the unary -1 and binary + 2 but is still a binary operation
    // -1 + 2 * 3 < this is the unary -1 and binary + 2 and binary * 3
    // (((-1) '+' (2)) '*' 3)

    // a termination of a expression is:
    // a semicolon,
    // a closing parenthesis,
    // a closing brace,
    // a closing bracket
    // a closing angle bracket,
    // a comma,


    /// this only contains single len expressions
    /// compound expressions are handled by the parent expression
    std::vector<std::unique_ptr<Expression>> expr_stack;

    std::map<char, u32> depth_map = {
        {'(', 0},
        {'{', 0},
        {'[', 0},
        {'<', 0},
    };

    i32 consumed = 0;

    ExpressionType current_expr_type;

    // once we know the type of expression it cant be we remove
    std::vector<ExpressionType> possible_expr_types = {
        ExpressionType::UnaryOp,
        ExpressionType::BinaryOp,
        ExpressionType::DotAccess,
        ExpressionType::ScopeAccess,
        ExpressionType::PathAccess,
        ExpressionType::FunctionCall,
        ExpressionType::Literal,
        ExpressionType::Cast,
        ExpressionType::Conditional,
        ExpressionType::Parenthesized
    };

    for (auto &token : tokens) {
        if (is_termination_token(token->token_kind(), depth_map)) {
            
            return expr_stack.back().get();
        }

        switch (token->token_kind()) {
            case IS_IDENTIFIER:
                expr_stack.push_back(std::make_unique<node::Identifier>(tokens));
                consumed = expr_stack.back()->parse();

                if (consumed > 1 && ((static_cast<i32>(consumed) - 1) > 0)) {
                    token.advance(consumed - 1);
                }

                continue;

            case IS_LITERAL:
                expr_stack.push_back(std::make_unique<node::Literal>(tokens));
                consumed = expr_stack.back()->parse();

                if (consumed > 1 && ((static_cast<i32>(consumed) - 1) > 0)) {
                    token.advance(consumed - 1);
                }

                continue;
            
            case token::tokens::PUNCTUATION_DOT:
                [&](){
                    auto slice = tokens;
                
                    expr_stack.push_back(std::make_unique<node::DotAccess>(slice));
                    consumed = expr_stack.back()->parse();

                    if (consumed > 1 && ((static_cast<i32>(consumed) - 1) > 0)) {
                        token.advance(consumed - 1);
                    }

                }();
                continue;

            case token::tokens::OPERATOR_SCOPE:
                [&](){
                    auto slice = tokens;
                
                    expr_stack.push_back(std::make_unique<node::ScopeAccess>(slice));
                    consumed = expr_stack.back()->parse();

                    if (consumed > 1 && ((static_cast<i32>(consumed) - 1) > 0)) {
                        token.advance(consumed - 1);
                    }

                }();
                continue;
        }
    }

    return nullptr;
}

Expression::Expression() = default;
Expression::Expression(token::TokenList &tokens)
    : Node(tokens)
    , tokens(&tokens) {}
}  // namespace parser::ast