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

#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <vector>

#include "token.hh"


namespace lexer {
    
const std::string readfile(const std::string &filename);

class Lexer {
  public:
    explicit Lexer(const std::string &source);
    std::vector<token::Token> tokenize();

  private:
    inline token::Token nextToken();
    inline token::Token parseKeyword();
    inline token::Token parseDelimiter();
    inline token::Token parseLiteral();
    inline token::Token parseOperator();
    inline token::Token parseOther();
    inline token::Token parsePrimitive();
    inline token::Token parsePunctuation();

    inline void skipWhitespace();
    inline char next();
    [[nodiscard]] inline char peek() const;

    std::string  source;
    char*  currentToken;
    u64 currentPosition;
};
}  // namespace lexer

#endif  // __LEXER_H__