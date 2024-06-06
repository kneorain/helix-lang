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

#include "../include/lexer.hh"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>

namespace lexer {
const std::string readfile(const std::string &filename) {
    std::ifstream file(filename);
    
}

Lexer::Lexer(const std::string &source) {

}
std::vector<token::Token> Lexer::tokenize() {

}

inline token::Token Lexer::nextToken() {

}

inline token::Token Lexer::parseKeyword() {

}

inline token::Token Lexer::parseDelimiter() {

}

inline token::Token Lexer::parseLiteral() {

}

inline token::Token Lexer::parseOperator() {

}

inline token::Token Lexer::parseOther() {

}

inline token::Token Lexer::parsePrimitive() {

}

inline token::Token Lexer::parsePunctuation() {

}

inline void Lexer::skipWhitespace() {

}

inline char Lexer::next() {

}

[[nodiscard]] inline char Lexer::peek() const {

}
}  // namespace lexer