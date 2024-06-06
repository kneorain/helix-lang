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
#include <unordered_map>

#include "token.hh"


namespace lexer {
std::string readfile(std::string &filename);
std::string readfile(const std::string &filename);

class Lexer {
  public:
    Lexer(std::string source, const std::string &filename);
    Lexer(const Lexer &lexer) = delete;
    Lexer(Lexer &&lexer) = delete;
    Lexer &operator=(const Lexer &lexer) = delete;
    Lexer &operator=(Lexer &&lexer) = delete;
    ~Lexer() = default;

    token::TokenList tokenize();

  private:
    inline token::Token next_token();
    inline token::Token parse_alpha_numeric();
    inline token::Token parse_compiler_directive();
    inline token::Token process_single_line_comment();
    inline token::Token process_multi_line_comment();
    inline token::Token parse_numeric();
    inline token::Token parse_string();
    inline token::Token parse_operator();
    inline token::Token parse_other();
    inline token::Token parse_punctuation();
    inline token::Token process_whitespace();

    inline char next();
    [[nodiscard]] inline char peek() const;

    token::TokenList    tokens;       //> list of tokens
    std::string  source;       //> source code
    std::string  file_name;    //> file name
    u64          currentPos;   //> current position in the source
    
    u64 line;   //> line number
    u64 column; //> position in the line
    u64 offset; //> position of the end of the token
    u64 end;    //> end of the source

};
}  // namespace lexer

#endif  // __LEXER_H__