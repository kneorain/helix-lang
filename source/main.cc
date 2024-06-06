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

#include <chrono>
#include <iostream>
#include <span>
#include "token/include/lexer.hh"
#include "parser/ast/ast.hh"
int main() {
    std::string source  = lexer::readfile("/Volumes/Container/Projects/Helix/helix-lang/tests/test_tokenize.hlx");
    
    auto lex = lexer::Lexer(source, "/Volumes/Container/Projects/Helix/helix-lang/tests/test_tokenize.hlx");
    auto start = std::chrono::high_resolution_clock::now();
    auto tokens = lex.tokenize();
    auto end   = std::chrono::high_resolution_clock::now();


    token::print_tokens(tokens);

    std::span<token::Token> slice{tokens};

    // constructs a new ast node
    AstFunctionHeader node;

    node.parse(slice);

    // print time in ns
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\n";

    return 0;
}

