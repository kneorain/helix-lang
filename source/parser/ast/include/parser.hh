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
#ifndef __PARSER_HH__
#define __PARSER_HH__

#include <iostream>
#include <memory>

#include <parser/ast/include/ast.hh>
#include <parser/ast/include/nodes.hh>

namespace parser {
// generate an ast from a list of tokens
/*
all possiblities to parse:
- [] basic
    - [] true | false
    - [] int | float
    - [] string | char
    - [] null

- [] vars
    - [] let a = b
    - [] a = b
    - [] let a: int = b
    - [] let a: int
    - [] let b: int<5> = 10
    - [] let b: int = 10 if a == 5 else 8
    - [] b = 10 if a == 5 else 8
    - [] all variants without type (auto)

- [] primitives
    - [] [..., ...]
    - [] (..., ...)
    - [] {...: ..., ...}
    - [] {..., ...}

- [] invocations
    - [] Struct {a, b}
    - [] Struct {a: 10, b: 2}
    - [] Class(a, b)
    - [] Class(a, c=10)
    - [] function(a, b)
    - [] function(a, c=10)

- [] unary and binary
    - [] 1 + 2
    - [] 1 + (2 + 5)
    - [] 1 + ((3 if a == 5 else 2) + 3)
    - [] a += 2
    - [] a += 3 if a == 5 else 2

- [] defs
    - [] class a {...}
    - [] class a : b {...}
    - [] class a derives c {...}
    - [] class a derives (e + f) : (b + d) {...}
    - [] class a<T> {...}
    - [] class a<T: Stringable> {...}
    - [] fn yes() {...}
    - [] fn yes(): ...
    - [] fn yes() -> int {...}
    - [] fn yes<T>() -> int {...}
*/

class Parser {
  private:
    ast::AstNodeList<> body;
    ast::AstNodeList<> stack;
    token::TokenList  &tokens;

    /*
    StringLiteral
    BooleanLiteral
    NullLiteral
    NumericLiteral
    */
    inline void parse_literal(token::tokens type, std::vector<token::Token>::const_iterator &it) {
        switch (type) {
            case token::tokens::LITERAL_TRUE:
            case token::tokens::LITERAL_FALSE:
                body.push_back(std::make_unique<ast::BooleanLiteral>(*it));
                ++it;  // Advance the iterator
                break;
            case token::tokens::LITERAL_INTEGER:
            case token::tokens::LITERAL_FLOATING_POINT:
                body.push_back(std::make_unique<ast::NumericLiteral>(*it));
                ++it;  // Advance the iterator
                break;
            case token::tokens::LITERAL_STRING:
            case token::tokens::LITERAL_CHAR:
                body.push_back(std::make_unique<ast::StringLiteral>(*it));
                ++it;  // Advance the iterator
                break;
            case token::tokens::LITERAL_NULL:
                body.push_back(std::make_unique<ast::NullLiteral>(*it));
                ++it;  // Advance the iterator
                break;
            case token::tokens::EOF_TOKEN:
                std::cout << "end of file"
                          << "\n";
                break;
            default:
                break;
        }
    }

  public:
    explicit Parser(token::TokenList &tokens)
        : tokens(tokens) {};

    std::unique_ptr<ast::ProgramNode> parse() {
        token::tokens current_token_type{};

        for (auto it = tokens.begin(); it != tokens.end();) {
            const token::Token &current_token = *it;
            current_token_type = current_token.token_kind();

            switch (current_token_type) {
                case token::tokens::LITERAL_TRUE:
                case token::tokens::LITERAL_FALSE:
                case token::tokens::LITERAL_INTEGER:
                case token::tokens::LITERAL_FLOATING_POINT:
                case token::tokens::LITERAL_STRING:
                case token::tokens::LITERAL_CHAR:
                    parse_literal(current_token_type, it);
                    break;
                default:
                    ++it;  // Manually advance the iterator if not handled by parse_literal
                    break;
            }
        }

        return std::make_unique<ast::ProgramNode>(
            // Token entry_point, string filename, AstNodeList<> body, std::unique_ptr<CommentNode> comment
            token::Token(), tokens.file_name(), body, std::make_unique<ast::CommentNode>(
                token::Token(
                    0, 0, 0, 0, "// this is a file comment", tokens.file_name(), "//"
                )
            )
        );
    }
};
}  // namespace parser

#endif  // __PARSER_HH__