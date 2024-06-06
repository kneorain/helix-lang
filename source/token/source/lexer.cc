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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

#include "../../include/error/error.hh"
#include "../include/cases.def"

namespace lexer {
std::unordered_map<std::string, std::string> FILE_CACHE;

std::string _internal_read_file(const std::string &filename) {
    auto cache_it = FILE_CACHE.find(filename);
    if (cache_it != FILE_CACHE.end()) {
        return cache_it->second;
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

    FILE_CACHE[filename] = source;

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

    for (u64 i = 0; i < source.size(); i++) {
        if (source[i] == '\n') {
            current_line++;
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
    , currentPos(0)
    , line(1)
    , column(0)
    , offset(0)
    , end(this->source.size()) {}

token::TokenList Lexer::tokenize() {
    while ((currentPos + 1) <= end) {
        auto start = std::chrono::high_resolution_clock::now();
        auto token = next_token();
        auto end = std::chrono::high_resolution_clock::now();
        if (token.value == "<<WHITE_SPACE>>") {
            continue;
        }
        tokens.append(token);
        std::cout << "Time taken: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
                  << "ns\n";
    }

    return tokens;
}

inline token::Token Lexer::process_single_line_comment() {
    auto start = currentPos;
    while (source[currentPos] != '\n' && currentPos < end) {
        next();
    }
    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            "//"};
}

inline token::Token Lexer::process_multi_line_comment() {
    auto start = currentPos;
    u32 brace_level = 0;
    while (currentPos < end) {
        if (source[currentPos] == '/' && source[currentPos + 1] == '*') {
            brace_level++;
        } else if (source[currentPos] == '*' && source[currentPos + 1] == '/') {
            brace_level--;
        }

        if (source[currentPos] == '\n') {
            line++;
            column = 0;
        }

        if (brace_level == 0) {
            next();
            next();
            break;
        }

        next();
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            "/*"};
}

inline token::Token Lexer::next_token() {
    switch (source[currentPos]) {
        case WHITESPACE:
            next();
            return token::Token{};
        case '/':
            switch (peek()) {
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
            break;
        case STRING_BYPASS:
            switch (peek()) {
                case '"':
                case '\'':
                    return parse_string();
            }
        case '_':
        case A_Z:
        case a_z_EXCLUDE_rbuf:  // removed the following cases since they are already
                                // covered by the STRING_BYPASS: (r, b, f, u)
            return parse_alpha_numeric();
        case '#':  // so things like #[...] or # [...] are compiler directives and are 1 token
            return parse_compiler_directive();
        case OPERATORS:
            return parse_operator();
        case PUNCTUATION:
            return parse_punctuation();
    }

    throw error::Error(error::Compiler{std::string(1, source[currentPos]), "unknown token"});
}

inline token::Token Lexer::parse_compiler_directive() {
    auto start = currentPos;
    auto end_loop = false;
    u32 brace_level = 0;
    while (!end_loop && currentPos < end) {
        if (source[currentPos] == '[') {
            brace_level++;
        } else if (source[currentPos] == ']') {
            brace_level--;
        }

        if (source[currentPos] == '\n' || (source[currentPos] == ']' && brace_level == 0)) {
            next();
            end_loop = true;
        }

        next();
    }
    if (currentPos - start == 1) {  // if just a #
        return {line, column, 1, offset, source.substr(start, 1)};
    }
    return {line, column - (currentPos - start), currentPos - start, offset,
            source.substr(start, currentPos - start)};
}

inline token::Token Lexer::process_whitespace() {
    auto result = token::Token{line, column, 1, offset, source.substr(currentPos, 1), "< >"};
    next();
    return result;
}

inline token::Token Lexer::parse_alpha_numeric() {
    auto start = currentPos;
    bool end_loop = false;

    while (!end_loop && currentPos < end) {
        switch (peek()) {
            case '_':
            case A_Z:
            case a_z:
            case _0_9:
                next();
                break;
            default:
                next();
                end_loop = true;
                break;
        }
    }

    auto result = token::Token{line, column - (currentPos - start), currentPos - start, offset,
                               source.substr(start, currentPos - start)};

    if (result.kind != token::tokens::OTHERS) {
        return result;
    }

    if (result.value == "true" || result.value == "false") {
        return {line,
                column - (currentPos - start),
                currentPos - start,
                offset,
                source.substr(start, currentPos - start),
                "bool"};
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            "<id>"};
}

inline token::Token Lexer::parse_numeric() {
    // all the data within 0-9 is a number
    // a number can have the following chars after the first digit:
    // 0-9, ., F, f, U, u, o, x, b, e, E, A-F, a-f, _
    auto start = currentPos;

    bool is_float = false;
    bool end_loop = false;

    while (!end_loop && currentPos < end) {
        switch (peek()) {
            case '.':
                is_float = true;
            case _non_float_numeric:
                next();
                break;
            default:
                next();
                end_loop = true;
                break;
        }
    }

    // if theres a . then it is a float
    if (is_float) {
        return {line,
                column - (currentPos - start),
                currentPos - start,
                offset,
                source.substr(start, currentPos - start),
                "<float>"};
    }
    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            "<int>"};
}

inline token::Token Lexer::parse_string() {
    // all the data within " (<string>) or ' (<char>) is a string
    auto start = currentPos;
    auto start_line = line;
    auto start_column = column;

    bool end_loop = false;
    char quote = source[currentPos];

    switch (source[currentPos]) {
        case STRING_BYPASS:
            quote = next();
            break;
    }

    // if the quote is followed by a \ then ignore the quote
    while (!end_loop && currentPos < end) {
        switch (peek()) {
            case '\\':
                next();
                next();
                break;
            case STRING:
                next();
                end_loop = source[currentPos] == quote;
                next();
                break;
            default:
                next();
                break;
        }
    }

    if (currentPos >= end) {
        throw error::Error(
            error::Line(file_name, start_line, start_column, 1, "unterminated string"),
            getline(file_name, start_line));
    }

    std::string token_type;

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
            token_type};
}

inline token::Token Lexer::parse_operator() {
    auto start = currentPos;
    bool end_loop = false;

    while (!end_loop && currentPos < end) {
        switch (peek()) {
            case OPERATORS:
                next();
                break;
            default:
                next();
                end_loop = true;
                break;
        }
    }

    return {line, column - (currentPos - start), currentPos - start, offset,
            source.substr(start, currentPos - start)};
}

inline token::Token Lexer::parse_other() {}

inline token::Token Lexer::parse_punctuation() {
    auto result = token::Token{line, column, 1, offset, source.substr(currentPos, 1)};
    next();
    return result;
}

inline char Lexer::next() {
    if (currentPos + 1 > end) {
        return '\0';
    }

    currentPos++;

    switch (source[currentPos]) {
        case '\n':
            line++;
            column = 0;
            break;
        default:
            column++;
            offset++;
            break;
    }

    return source[currentPos];  // FIXME: remove this if not needed
}

[[nodiscard]] inline char Lexer::peek() const {
    if (currentPos + 1 >= end) {
        return '\0';
    }

    return source[currentPos + 1];
}
}  // namespace lexer