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

#include "../include/token.hh"

#include <iostream>
#include <shared_mutex>
#include <mutex>

#include "../../include/colors_ansi.hh"

namespace token {

Token::Token(u64 line, u64 column, u64 length, u64 offset, std::string_view value,
             const std::string &filename, std::string_view token_kind)
    : line(line)
    , column(column)
    , len(length)
    , _offset(offset)
    , val(value)
    , filename(filename) {
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

// Default Constructor
Token::Token()
    : kind(tokens::WHITESPACE)
    , val("<<WHITE_SPACE>>") {}

// Copy Constructor
Token::Token(const Token &other) {
    line = other.line;
    column = other.column;
    len = other.len;
    _offset = other._offset;
    kind = other.kind;
    val = other.val;
    filename = other.filename;
}

// Copy Assignment Operator
Token &Token::operator=(const Token &other) {
    if (this == &other) {
        return *this;
    }
    std::unique_lock<std::shared_mutex> lock1(mtx, std::defer_lock);
    std::shared_lock<std::shared_mutex> lock2(other.mtx, std::defer_lock);
    std::lock(lock1, lock2);

    line = other.line;
    column = other.column;
    len = other.len;
    _offset = other._offset;
    kind = other.kind;
    val = other.val;
    filename = other.filename;

    return *this;
}

// Move Constructor
Token::Token(Token &&other) noexcept
    : line(other.line)
    , column(other.column)
    , len(other.len)
    , _offset(other._offset)
    , kind(other.kind)
    , val(std::move(other.val))
    , filename(other.filename) {}

// Move Assignment Operator
Token &Token::operator=(Token &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    line = other.line;
    column = other.column;
    len = other.len;
    _offset = other._offset;
    kind = other.kind;
    val = std::move(other.val);
    filename = other.filename;
    return *this;
}

// Destructor
Token::~Token() = default;

u64 Token::line_number() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return line;
}

u64 Token::column_number() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return column;
}

u64 Token::length() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return len;
}

u64 Token::offset() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return _offset;
}

tokens Token::token_kind() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return kind;
}

std::string Token::value() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return val;
}

std::string_view Token::token_kind_repr() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return tokens_map.at(kind).value();
}

std::string_view Token::file_name() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return filename;
}

void Token::set_line_number(u64 line) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    this->line = line;
}

void Token::set_column_number(u64 column) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    this->column = column;
}

void Token::set_length(u64 length) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    this->len = length;
}

void Token::set_offset(u64 offset) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    this->_offset = offset;
}

void Token::set_token_kind(tokens kind) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    this->kind = kind;
}

void Token::set_value(std::string value) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    this->val = std::move(value);
}

TokenList::TokenList(std::string filename)
    : filename(std::move(filename))
    , it(this->begin()) {}

TokenList::TokenList(std::string filename, std::vector<Token>::iterator start,
                     std::vector<Token>::iterator end)
    : std::vector<Token>(start, end)
    , filename(std::move(filename))
    , it(this->begin()) {}

Token TokenList::next(u32 n) {
    if (it == this->end()) {
        return Token();
    }

    if (it + n >= this->end()) {
        return *(this->end() - 1);
    }

    return *(it + n++);
}

Token TokenList::peek(u32 n) const {
    if (it == this->end()) {
        return Token();
    }

    if (it + n >= this->end()) {
        return *(this->end() - 1);
    }

    return *(it + n);
}

Token TokenList::current() const {
    if (it == this->begin()) {
        return Token();
    }
    return *(it - 1);
}

Token TokenList::previous(u32 n) const {
    if (it == this->begin()) {
        return Token();
    }

    if (it - n < this->begin()) {
        return *(this->begin());
    }

    return *(it - n);
}

void TokenList::remove_left() {
    this->erase(this->begin(), it);
    it = this->begin();
}

void TokenList::reset() { it = this->begin(); }

void TokenList::append(const Token &token) { this->push_back(token); }

std::string TokenList::file_name() const { return filename; }

TokenList TokenList::slice(u64 start, u64 end) {
    if (end > this->size()) {
        end = this->size();
    }
    return TokenList(/*this->filename, this->begin() + start, this->begin() + end*/);
}

bool TokenList::reached_end() const { return it == this->end(); }

void print_tokens(token::TokenList &tokens) {
    u16 indent = 0;

    for (const auto &tok : tokens) {
        if (tok.value() == "{") {
            indent++;
        } else if (tok.value() == "}") {
            indent--;
        }
        if (tok.token_kind() == token::tokens::PUNCTUATION_SEMICOLON ||
            tok.token_kind() == token::tokens::PUNCTUATION_OPEN_BRACE ||
            tok.token_kind() == token::tokens::PUNCTUATION_CLOSE_BRACE ||
            tok.token_kind() == token::tokens::PUNCTUATION_SINGLE_LINE_COMMENT) {
            if (tok.token_kind() != token::tokens::PUNCTUATION_CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red
                          << token::tokens_map.at(tok.token_kind()).value() << colors::reset << ", "
                          << colors::fg16::green << tok.value() << colors::reset << ") ";
            }

            std::cout << "\n";
            std::cout << std::string(static_cast<u16>(indent * 4), ' ');

            if (tok.token_kind() == token::tokens::PUNCTUATION_CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red
                          << token::tokens_map.at(tok.token_kind()).value() << colors::reset << ", "
                          << colors::fg16::green << tok.value() << colors::reset << ") ";
            }

            continue;
        }
        std::cout << "(" << colors::fg16::red << token::tokens_map.at(tok.token_kind()).value()
                  << colors::reset << ", " << colors::fg16::green << tok.value() << colors::reset
                  << ") ";
    }

    std::cout << "\n";
}

}  // namespace token
