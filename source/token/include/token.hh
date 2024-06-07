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
#include <shared_mutex>

#include "../../include/colors_ansi.hh"
#include "../../include/inttypes.hh"
#include "./generate.hh"

namespace token {
/**
 * @brief Structure representing a token in the source code.
 */
struct Token {
    u64        line{}; ///< Line number where the token is located
    u64      column{}; ///< Column number where the token starts
    u64      length{}; ///< Length of the token
    u64      offset{}; ///< Offset from the beginning of the file
    tokens     kind{}; ///< Kind of the token
    std::string value; ///< String value of the token
    mutable std::shared_mutex mtx; ///< Mutex for thread safety
  public:
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

    Token(const Token& other) : line(other.line), column(other.column), length(other.length), offset(other.offset), kind(other.kind), value(other.value) {
        std::shared_lock<std::shared_mutex> lock(other.mtx);
    }

    // Manually implement the copy assignment operator
    Token& operator=(const Token& other) {
        if (this == &other) {
            return *this;
        }
        std::unique_lock<std::shared_mutex> lock1(mtx, std::defer_lock);
        std::shared_lock<std::shared_mutex> lock2(other.mtx, std::defer_lock);
        std::lock(lock1, lock2);

        line = other.line;
        column = other.column;
        length = other.length;
        offset = other.offset;
        kind = other.kind;
        value = other.value;

        return *this;
    }
    
    ~Token() = default;

    u64 getLineNumber() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return line;
    }

    u64 getColumnNumber() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return column;
    }

    u64 getLength() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return length;
    }

    u64 getOffset() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return offset;
    }

    tokens getTokenKind() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return kind;
    }

    std::string getValue() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return value;
    }

    void setLineNumber(u64 line) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        this->line = line;
    }

    void setColumnNumber(u64 column) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        this->column = column;
    }

    void setLength(u64 length) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        this->length = length;
    }

    void setOffset(u64 offset) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        this->offset = offset;
    }

    void setTokenKind(tokens kind) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        this->kind = kind;
    }

    void setValue(std::string value) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        this->value = std::move(value);
    }
};

class TokenList : public std::vector<Token> {
private:
    std::string filename;

public:
    std::vector<Token>::iterator it;

    explicit TokenList(std::string filename)
        : filename(std::move(filename))
        , it(this->begin()) {}

    Token next() {
        if (it == this->end()) {
            return Token{};
        }
        return *it++;
    }

    Token peek() const {
        if (it == this->end()) {
            return Token{};
        }
        return *it;
    }

    Token current() const {
        if (it == this->begin()) {
            return Token{};
        }
        return *(it - 1);
    }

    std::vector<Token>::const_iterator begin() const {
        return std::vector<Token>::begin();
    }

    std::vector<Token>::const_iterator end() const {
        return std::vector<Token>::end();
    }

    Token previous() const {
        if (it == this->begin()) {
            return Token{};
        }
        return *(it - 1);
    }

    void remove_left() {
        this->erase(this->begin(), it);
        it = this->begin();
    }

    void reset() {
        it = this->begin();
    }

    void append(const Token& token) {
        this->push_back(token);
    }

    std::vector<Token>::iterator begin() {
        return std::vector<Token>::begin();
    }

    std::vector<Token>::iterator end() {
        return std::vector<Token>::end();
    }
};

inline void print_tokens(token::TokenList &tokens) {
    u16 indent = 0;

    for (const auto &tok : tokens) {
        if (tok.value == "{") {
            indent++;
        } else if (tok.value == "}") {
            indent--;
        }
        if (tok.kind == token::tokens::PUNCTUATION_SEMICOLON ||
            tok.kind == token::tokens::PUNCTUATION_OPEN_BRACE ||
            tok.kind == token::tokens::PUNCTUATION_CLOSE_BRACE ||
            tok.kind == token::tokens::PUNCTUATION_SINGLE_LINE_COMMENT) {
            if (tok.kind != token::tokens::PUNCTUATION_CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red << token::tokens_map.at(tok.kind).value()
                          << colors::reset << ", " << colors::fg16::green << tok.value
                          << colors::reset << ") ";
            }

            std::cout << "\n";
            std::cout << std::string(static_cast<u16>(indent * 4), ' ');

            if (tok.kind == token::tokens::PUNCTUATION_CLOSE_BRACE) {
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
