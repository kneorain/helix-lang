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

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "../../include/colors_ansi.hh"
#include "../../include/inttypes.hh"
#include "./generate.hh"

namespace token {
/**
 * @brief Structure representing a token in the source code.
 */
struct Token {
  public:
    u64 line{};         ///< Line number where the token is located
    u64 column{};       ///< Column number where the token starts
    u64 length{};       ///< Length of the token
    u64 offset{};       ///< Offset from the beginning of the file
    tokens kind{};      ///< Kind of the token
    std::string value;  ///< String value of the token

    /**
     * @brief Constructs a Token with the specified attributes.
     *
     * @param line Line number where the token is located.
     * @param column Column number where the token starts.
     * @param length Length of the token.
     * @param offset Offset from the beginning of the file.
     * @param value String value of the token.
     */
    Token(u64 line, u64 column, u64 length, u64 offset, std::string_view value,
          std::string_view token_kind = "")
        : line(line)
        , column(column)
        , length(length)
        , offset(offset)
        , value(value) {

        std::optional<tokens> token_enum;

        if (token_kind.empty()) {
            token_enum = tokens_map.at(value);
        } else {
            token_enum = tokens_map.at(token_kind);
        }

        if (token_enum.has_value()) {
            this->kind = token_enum.value();
        } else {
            this->kind = tokens::OTHERS;
        }
    }

    Token()
        : kind(tokens::WHITESPACE)
        , value("<<WHITE_SPACE>>") {}
};

class TokenList : public std::vector<token::Token> {
  private:
    std::string filename;

  public:
    std::vector<token::Token>::iterator it;

    explicit TokenList(std::string filename)
        : filename(std::move(filename))
        , it(this->begin()) {}

    token::Token next() {
        if (it == this->end()) {
            return token::Token{};
        }

        return *it++;
    }

    token::Token peek() {
        if (it == this->end()) {
            return token::Token{};
        }

        return *it;
    }

    token::Token current() {
        if (it == this->begin()) {
            return token::Token{};
        }

        return *(it - 1);
    }

    token::Token previous() {
        if (it == this->begin()) {
            return token::Token{};
        }

        return *(it - 1);
    }

    void remove_left() {
        this->erase(this->begin(), it);
        it = this->begin();
    }

    void reset() { it = this->begin(); }

    void append(const token::Token &token) { this->push_back(token); }

    std::vector<token::Token>::iterator begin() { return std::vector<token::Token>::begin(); }
    std::vector<token::Token>::iterator end()   { return std::vector<token::Token>::end(); }
};

inline void print_tokens(token::TokenList &tokens) {
    u16 indent = 0;

    for (const auto &tok : tokens) {
        if (tok.value == "{") {
            indent++;
        } else if (tok.value == "}") {
            indent--;
        }
        if (tok.kind == token::tokens::SEMICOLON || tok.kind == token::tokens::OPEN_BRACE ||
            tok.kind == token::tokens::CLOSE_BRACE ||
            tok.kind == token::tokens::SINGLE_LINE_COMMENT) {
            if (tok.kind != token::tokens::CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red << token::tokens_map.at(tok.kind).value()
                          << colors::reset << ", " << colors::fg16::green << tok.value
                          << colors::reset << ") ";
            }

            std::cout << "\n";
            std::cout << std::string(static_cast<u16>(indent * 4), ' ');

            if (tok.kind == token::tokens::CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red << token::tokens_map.at(tok.kind).value()
                          << colors::reset << ", " << colors::fg16::green << tok.value
                          << colors::reset << ") ";
            }

            continue;
        }
        std::cout << "(" << colors::fg16::red << token::tokens_map.at(tok.kind).value()
                  << colors::reset << ", " << colors::fg16::green << tok.value << colors::reset
                  << ") ";
    }

    std::cout << "\n";
}
}  // namespace token

#endif  // __TOKEN_H__
