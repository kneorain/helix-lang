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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include "../../include/error/error.hh"
#include "../include/cases.def"
#include "../types/file_cache.hh"

using namespace token;

namespace lexer {
std::string _internal_read_file(const std::string &filename) {
    auto cached_file = file_sys::FileCache::get_file(filename);
    if (cached_file.has_value()) {
        return cached_file.value();
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file) {
        error::Error(error::Compiler{filename, "file not found."});
        return "";
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string source(size, '\0');
    if (!file.read(source.data(), size)) {
        error::Error(error::Compiler{filename, "failed to read file."});
        return "";
    }

    file_sys::FileCache::add_file(filename, source);

    return source;
}

std::string readfile(std::string &filename) {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path abs_path = std::filesystem::absolute(cwd / filename);
    filename = abs_path.string();

    return _internal_read_file(filename);
}

// TODO: make all readfiles after the first one be relative to the first one
/// Example: readfile("file1.hlx") -> /path/to/file1.hlx
///          readfile("test/file2.hlx") -> /path/to/test/file2.hlx
///          readfile("../file3.hlx") -> /path/to/file3.hlx

std::string readfile(const std::string &filename) {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path abs_path = std::filesystem::absolute(cwd / filename);

    return _internal_read_file(abs_path.string());
}

std::string getline(const std::string &filename, u64 line) {
    std::string source = readfile(filename);

    u64 current_line = 1;
    u64 start = 0;
    u64 end = 0;

    for (u64 i = 0; i < source.size(); ++i) {
        if (source[i] == '\n') {
            ++current_line;
            if (current_line == line) {
                start = i + 1;
            } else if (current_line == line + 1) {
                end = i;
                break;
            }
        }

        if (i == source.size() - 1) {
            end = source.size();
        }
    }

    return source.substr(start, end - start);
}

Lexer::Lexer(std::string source, const std::string &filename)
    : tokens(filename)
    , source(std::move(source))
    , file_name(filename)
    , currentChar('\0')
    , cachePos(0)
    , currentPos(0)
    , line(1)
    , column(0)
    , offset(0)
    , end(this->source.size()) {}

TokenList Lexer::tokenize() {
    while ((currentPos + 1) <= end) {
        auto token = next_token();

        if (token.token_kind() == tokens::WHITESPACE) {
            continue;
        }
        tokens.append(token);
    }

    tokens.append({line, column, 1, offset, "", file_name, "<eof>"});
    tokens.reset();
    return tokens;
}

inline Token Lexer::process_single_line_comment() {
    auto start = currentPos;

    while (current() != '\n' && !is_eof()) {
        bare_advance();
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name,
            "//"};
}

inline Token Lexer::process_multi_line_comment() {
    auto start = currentPos;
    u32 comment_depth = 0;

    while (!is_eof()) {
        switch (current()) {
            case '/':
            case '*':
                switch (peek_forward()) {
                    case '*':
                        ++comment_depth;
                        break;
                    case '/':
                        --comment_depth;
                        break;
                }
                break;
            case '\n':
                ++line;
                column = 0;
                break;
        }

        if (comment_depth == 0) {
            bare_advance(2);
            break;
        }

        bare_advance();
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name,
            "/*"};
}

inline Token Lexer::next_token() {
    switch (source[currentPos]) {
        case WHITE_SPACE:
            bare_advance();
            return Token{};
        case '/':
            switch (peek_forward()) {
                case '/':
                    return process_single_line_comment();
                case '*':
                    return process_multi_line_comment();
            }
            return parse_operator();
        case STRING:
            return parse_string();
        case _0_9:
            return parse_numeric();
        case STRING_BYPASS:
            switch (peek_forward()) {
                case STRING:
                    return parse_string();
            }
        case '_':
        case A_Z:
        case a_z_EXCLUDE_rbuf:  // removed the following cases since they are already
                                // covered by the STRING_BYPASS: (r, b, f, u)
            return parse_alpha_numeric();
        case '#':  // so things like #[...] are compiler directives and are 1 token but # [...] is
                   // a NOT compiler directive and is # token + everything else
            return parse_compiler_directive();
        case OPERATORS:
            return parse_operator();
        case PUNCTUATION:
            return parse_punctuation();
    }

    throw error::Error(error::Compiler{std::string(1, current()), "unknown token"});
}

inline Token Lexer::parse_compiler_directive() {
    auto start = currentPos;
    auto end_loop = false;
    u32 brace_level = 0;

    if (peek_forward() != '[') {
        bare_advance();
        return {line, column, 1, offset, source.substr(start, 1), file_name};
    }

    while (!end_loop && !is_eof()) {
        switch (current()) {
            case '[':
                ++brace_level;
                break;
            case ']':
                --brace_level;
                end_loop = brace_level == 0;
                break;
            case '\n':
                end_loop = true;
                break;
        }

        bare_advance();
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name,
            "<complier_directive>"};
}

   inline Token Lexer::process_whitespace() {
    auto result = Token{line, column, 1, offset, source.substr(currentPos, 1), file_name, "< >"};
    bare_advance();
    return result;
}

   inline Token Lexer::parse_alpha_numeric() {
    auto start = currentPos;

    bool end_loop = false;

    while (!end_loop && !is_eof()) {
        switch (peek_forward()) {
            case '_':
            case A_Z:
            case a_z:
            case _0_9:
                break;
            default:
                end_loop = true;
                break;
        }
        bare_advance();
    }

    auto result = Token{line,
                        column - (currentPos - start),
                        currentPos - start,
                        offset,
                        source.substr(start, currentPos - start),
                        file_name};

    if (result.token_kind() != tokens::OTHERS) {
        return result;
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name,
            "<id>"};
}

   inline Token Lexer::parse_numeric() {
    // all the data within 0-9 is a number
    // a number can have the following chars after the first digit:
    // 0-9, ., F, f, U, u, o, x, b, e, E, A-F, a-f, _
    auto start = currentPos;

    bool is_float = false;
    bool end_loop = false;

    while (!end_loop && !is_eof()) {
        switch (peek_forward()) {
            case '.':
                is_float = true;
            case _non_float_numeric:
                break;
            default:
                end_loop = true;
                break;
        }
        bare_advance();
    }

    // if theres a . then it is a float
    if (is_float) {
        return {line,
                column - (currentPos - start),
                currentPos - start,
                offset,
                source.substr(start, currentPos - start),
                file_name,
                "<float>"};
    }
    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name,
            "<int>"};
}

   inline Token Lexer::parse_string() {
    // all the data within " (<string>) or ' (<char>) is a string
    auto start = currentPos;
    auto start_line = line;
    auto start_column = column;

    std::string token_type;

    bool end_loop = false;
    char quote = current();

    switch (current()) {
        case STRING_BYPASS:
            quote = advance();
            break;
    }

    // if the quote is followed by a \ then ignore the quote
    while (!end_loop && !is_eof()) {
        switch (peek_forward()) {
            case '\\':
                bare_advance();
                break;
            case STRING:
                end_loop = advance() == quote;
                break;
            default:
                break;
        }
        bare_advance();
    }

    if (is_eof()) {
        throw error::Error(
            error::Line(file_name, start_line, start_column, 1, "unterminated string"),
            getline(file_name, start_line));
    }

    switch (quote) {
        case '"':
            token_type = "<string>";
            break;
        case '\'':
            token_type = "<char>";
            break;
    }

    return {start_line,
            start_column,
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name,
            token_type};
}

   inline Token Lexer::parse_operator() {
    auto start = currentPos;
    bool end_loop = false;

    while (!end_loop && !is_eof()) {
        switch (peek_forward()) {
            case OPERATORS:
                break;
            default:
                end_loop = true;
                break;
        }
        bare_advance();
    }

    return {line,      column - (currentPos - start),           currentPos - start, offset,
            file_name, source.substr(start, currentPos - start)};
}

   inline Token Lexer::parse_punctuation() {
    auto result = Token{line, column, 1, offset, source.substr(currentPos, 1), file_name};
    bare_advance();
    return result;
}

   inline char Lexer::advance(u16 n) {
    if (currentPos + 1 > end) {
        return '\0';
    }

    ++currentPos;

    switch (current()) {
        case '\n':
            ++line;
            column = 0;
            break;
        default:
            ++column;
            ++offset;
            break;
    }

    if (n > 1) {
        return advance(n - 1);
    }

    return current();
}

   inline void Lexer::bare_advance(u16 n) {
    ++currentPos;

    switch (current()) {
        case '\n':
            ++line;
            column = 0;
            break;
        default:
            ++column;
            ++offset;
            break;
    }

    if (n > 1) {
        return bare_advance(n - 1);
    }
}

   inline char Lexer::current() {
    if (is_eof()) {
        return '\0';
    }

    if (currentPos == cachePos) {
        return currentChar;
    }

    cachePos = currentPos;
    currentChar = source[currentPos];

    return currentChar;
}

   inline char Lexer::peek_back() const {
    if (currentPos - 1 < 0) {
        return '\0';
    }

    return source[currentPos - 1];
}

   inline char Lexer::peek_forward() const {
    if (currentPos + 1 >= end) {
        return '\0';
    }

    return source[currentPos + 1];
}

   inline bool Lexer::is_eof() const { return currentPos >= end; }
}  // namespace lexer