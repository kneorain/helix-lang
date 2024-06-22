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
#include "parser/ast/classes/parser.hh"
#include "token/include/lexer.hh"
#include "parser/ast/classes/ast.hh"

int main() {
    std::string file_name = "/Volumes/Container/Projects/Helix/helix-lang/tests/test_tokenize.hlx";
    
    auto start = std::chrono::high_resolution_clock::now();
    auto tokens = lexer::Lexer(lexer::readfile(file_name), file_name).tokenize();
    auto end   = std::chrono::high_resolution_clock::now();
    
    for (token::Token _token : tokens) {
        std::cout << _token.to_string() << "\n";
    }

    // parser::ast::Generator generator(tokens);
    // auto ast = generator.generate_ast();

    // parser::ast::print_ast(ast);

    auto _parser = parser::Parser(tokens);

    std::unique_ptr<parser::ast::ProgramNode> _ast = _parser.parse();
    
    std::cout << _ast->to_string(0) << "\n";



    
    return 0;
}

