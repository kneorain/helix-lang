//===------------------------------------------ C++ ------------------------------------------====//
//                                                                                                //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).       //
//  You are allowed to use, modify, redistribute, and create derivative works, even for           //
//  commercial purposes, provided that you give appropriate credit, and indicate if changes       //
//   were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/  //
//                                                                                                //
//  SPDX-License-Identifier: CC-BY-4.0                                                            //
//  Copyright (c) 2024 (CC BY 4.0)                                                                //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//

#ifndef __LEXER_HH__
#define __LEXER_HH__

#include <string>

#include "token/include/Token.hh"

namespace parser::lexer {
class Lexer {
  public:
    // TODO: Investigate if we can make this string not a copy
    Lexer(std::string source, const std::string &filename);
    explicit Lexer(const __TOKEN_N::Token &token);
    Lexer(const Lexer &lexer)            = delete;
    Lexer(Lexer &&lexer)                 = delete;
    Lexer &operator=(const Lexer &lexer) = delete;
    Lexer &operator=(Lexer &&lexer)      = delete;
    ~Lexer()                             = default;

    __TOKEN_N::TokenList tokenize();

  private:
    inline __TOKEN_N::Token next_token();
    inline __TOKEN_N::Token parse_alpha_numeric();
    inline __TOKEN_N::Token parse_compiler_directive();
    inline __TOKEN_N::Token process_single_line_comment();
    inline __TOKEN_N::Token process_multi_line_comment();
    inline __TOKEN_N::Token parse_numeric();
    inline __TOKEN_N::Token parse_string();
    inline __TOKEN_N::Token parse_operator();
    inline __TOKEN_N::Token parse_other();
    inline __TOKEN_N::Token parse_punctuation();
    inline __TOKEN_N::Token process_whitespace();
    inline __TOKEN_N::Token get_eof();

    inline char advance(u16 n = 1);
    inline char current();
    inline void bare_advance(u16 n = 1);

    [[nodiscard]] inline char peek_forward() const;
    [[nodiscard]] inline char peek_back() const;
    [[nodiscard]] inline bool is_eof() const;

    __TOKEN_N::TokenList tokens;     //> list of tokens
    std::string          source;     //> source code
    std::string          file_name;  //> file name

    char currentChar;  //> current character
    u64  cachePos;     //> cache position
    u64  currentPos;   //> current position in the source
    u64  line;         //> line number
    u64  column;       //> position in the line
    u64  offset;       //> position of the end of the token
    u64  end;          //> end of the source
};

// prevent global namespace pollution
#undef A_Z
#undef STRING_BYPASS
#undef a_z_EXCLUDE_rbuf
#undef a_z
#undef _0_9
#undef _non_float_numeric
#undef WHITE_SPACE
#undef STRING
#undef PUNCTUATION
#undef OPERATORS

}  // namespace parser::lexer

#endif  // __LEXER_HH__