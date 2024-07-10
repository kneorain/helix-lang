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

#include "parser/ast/include/ast.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

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

class ASTParser {
    explicit ASTParser(token::TokenList tokens);
};
}  // namespace parser

#endif  // __PARSER_HH__