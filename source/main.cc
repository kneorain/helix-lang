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
#include <parser/ast/include/parser.hh>
#include <parser/preprocessor/include/pre.hh>
#include <token/include/lexer.hh>
#include <tools/controllers/include/file_system.hh>
#include <token/include/token.hh>

int main() {
    std::string file_name = "tests/main.hlx";
    
    auto start = std::chrono::high_resolution_clock::now();
    auto tokens = lexer::Lexer(file_system::read_file(file_name), file_name).tokenize();
    auto end   = std::chrono::high_resolution_clock::now();

    //std::cout << "time taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "\n";
    
    // token::print_tokens(tokens);
    //for (token::Token _token : tokens) {
    //    std::cout << _token.to_string() << "\n";
    //}

    auto preprocessor = parser::preprocessor::Preprocessor(tokens);

    preprocessor.parse();

    std::string rootPath = "../";
    file_system::SourceTree tree(rootPath);

    std::cout << "Source Tree for .hlx files:\n";
    tree.print();

    //auto _parser = parser::Parser(tokens);

    //std::unique_ptr<parser::ast::ProgramNode> _ast = _parser.parse();
    
    //std::cout << _ast->to_string(0) << "\n";



    
    return 0;
}

