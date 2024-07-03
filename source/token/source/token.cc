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

#include "token/include/token.hh"

#include <mutex>
#include <shared_mutex>

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
Token::Token(const Token &other)
    : line(other.line)
    , column(other.column)
    , len(other.len)
    , _offset(other._offset)
    , kind(other.kind)
    , val(other.val)
    , filename(other.filename) {}

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
    , filename(std::move(other.filename)) {}

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

std::string Token::to_string() const {
    return std::string("Token(") + std::string("line: ") + std::to_string(line) +
           std::string(", column: ") + std::to_string(column) + std::string(", len: ") +
           std::to_string(len) + std::string(", offset: ") + std::to_string(_offset) +
           std::string(", kind: ") + std::string(token_kind_repr()) + std::string(", val: ") +
           std::string(val) + ")";
}

bool Token::operator==(const Token &rhs) const {
    return (line == rhs.line && column == rhs.column && len == rhs.len && _offset == rhs._offset &&
            kind == rhs.kind && val == rhs.val && filename == rhs.filename);
}

std::ostream &Token::operator<<(std::ostream &os) const { return os << to_string(); }
}  // namespace token
