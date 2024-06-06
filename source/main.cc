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

#include "token/include/lexer.hh"

int main() {
    std::string source = lexer::readfile("source/main.cc");
    auto start = std::chrono::high_resolution_clock::now();
    auto tokens = lexer::Lexer(source).tokenize();
    auto end = std::chrono::high_resolution_clock::now();

    // print time in ns
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\n";

    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << " Line: " << token.line << " Column: " << token.column << " Offset: " << token.offset << "\n";
    }
    return 0;
}