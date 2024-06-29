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
#include <parser/preprocessor/include/preprocessor.hh>
#include <token/include/lexer.hh>
#include <tools/controllers/include/file_system.hh>
#include <token/include/token.hh>

int main() {
    // start the timer to measure execution time
    auto start = std::chrono::high_resolution_clock::now();

    // define the input file name
    std::string file_name = "tests/main.hlx";

    // read the file and tokenize its contents
    auto tokens = lexer::Lexer(file_system::read_file(file_name), file_name).tokenize();

    // preprocess the tokens
    tokens = parser::preprocessor::Preprocessor(tokens, "main").parse();

    // print the import tree
    parser::preprocessor::import_tree->print_tree(parser::preprocessor::import_tree->get_root());

    // print the preprocessed tokens
    // token::print_tokens(tokens);

    // end the timer and calculate the duration
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    // Print the time taken in nanoseconds and milliseconds
    std::cout << "time taken: " << diff.count() * 1e+9 << " ns\n";
    std::cout << "            " << diff.count() * 1000 << " ms\n";

    return 0;
}

