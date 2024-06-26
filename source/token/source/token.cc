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

#include <include/colors_ansi.hh>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <token/include/token.hh>

#include "token/include/generate.hh"

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

// custom intrinsics constructor
Token::Token(tokens token_type, const std::string &filename, std::string value)
    : kind(token_type)
    , filename(filename) {
    
    if (value.empty()) {
        value = std::string(tokens_map.at(token_type).value());
    }

    len = value.length();
    val = std::move(value);
}

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

u64 Token::line_number() const { return line; }

u64 Token::column_number() const { return column; }

u64 Token::length() const { return len; }

u64 Token::offset() const { return _offset; }

tokens Token::token_kind() const { return kind; }

std::string Token::value() const { return val; }

std::string_view Token::token_kind_repr() const { return tokens_map.at(kind).value(); }

std::string_view Token::file_name() const { return filename; }

void Token::set_file_name(const std::string &file_name) { this->filename = std::string(file_name); }

TokenList::TokenList(std::string filename)
    : filename(std::move(filename))
    , it(this->begin()) {}

TokenList::TokenList(std::string filename, std::vector<Token>::const_iterator start,
                     std::vector<Token>::const_iterator end)
    : std::vector<Token>(start, end)
    , filename(std::move(filename)) {}

Token TokenList::next(u32 n) const {
    if (it == this->end()) {
        return {};
    }

    if (it + n >= this->end()) {
        return *(this->end() - 1);
    }

    return *(it + n++);
}

Token TokenList::peek(u32 n) const {
    if (it == this->end()) {
        return {};
    }

    if (it + n >= this->end()) {
        return *(this->end() - 1);
    }

    return *(it + n);
}

Token TokenList::current() const {
    if (it == this->begin()) {
        return {};
    }
    return *(it - 1);
}

Token TokenList::previous(u32 n) const {
    if (it == this->begin()) {
        return {};
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

    auto start_index = static_cast<std::vector<Token>::difference_type>(start);
    auto end_index = static_cast<std::vector<Token>::difference_type>(end);

    return {this->filename, this->begin() + start_index, this->begin() + end_index};
}

/**
 * @brief Replaces tokens in the list from start to end with the provided tokens.
 *
 * This function removes tokens from the specified start index up to, but not including,
 * the end index, and then inserts the tokens from the provided TokenList at the start index.
 *
 * @param tokens TokenList to insert.
 * @param start Start index of the range to remove.
 * @param end End index of the range to remove.
 */
void TokenList::insert_remove(TokenList &tokens, u64 start, u64 end) {
    if (start > end || end > this->size()) {
        throw std::out_of_range("Invalid start or end index");
    }

    auto start_it = this->begin() + static_cast<std::vector<Token>::difference_type>(start);
    auto end_it = this->begin() + static_cast<std::vector<Token>::difference_type>(end);

    this->erase(start_it, end_it);
    this->insert(start_it, tokens.begin(), tokens.end());
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
