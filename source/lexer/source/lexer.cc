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
#include "lexer/include/lexer.hh"

#include <string>

#include "core/error/error.hh"
#include "lexer/include/cases.def"

namespace lexer {
using namespace token;

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

Lexer::Lexer(const token::Token& token)
    : tokens(token.file_name())
    , source(token.value())
    , file_name(token.file_name())
    , currentChar('\0')
    , cachePos(0)
    , currentPos(0)
    , line(token.line_number())
    , column(token.column_number())
    , offset(token.offset())
    , end(this->source.size()) {}

TokenList Lexer::tokenize() {
    token::Token token;

    while ((currentPos + 1) <= end) {
        token = next_token();

        if (token.token_kind() == tokens::WHITESPACE) {
            continue;
        }

        token.set_file_name(file_name);
        tokens.push_back(token);
    }

    token = get_eof();
    token.set_file_name(file_name);
    tokens.push_back(token);

    tokens.reset();
    return tokens;
}

inline Token Lexer::get_eof() { return {line, column, 1, offset, "\0", file_name, "<eof>"}; }

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

    u32 start_line = line;
    u32 start_col = column;

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
                column = 0;
                break;
        }

        if (comment_depth == 0) {
            bare_advance(2);
            break;
        }

        bare_advance();
    }

    if (comment_depth != 0) {
        throw error::Error(
            error::Line(file_name, start_line, start_col, 2, "unterminated block comment"));
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
        case PUNCTUATION:
            return parse_punctuation();
        case OPERATORS:
            return parse_operator();
    }

    throw error::Error(error::Line(file_name, line, column, 1,
                                   "unknown token '" + std::string(1, current()) + "'"));
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
                end_loop = brace_level == 0;
                break;
        }

        bare_advance();
    }

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start + 2, (currentPos - start) - 3),
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
    // TODO: add sci notation
    auto start = currentPos;

    u32 dot_count = 0;
    bool is_float = false;
    bool end_loop = false;
    bool sci_notation = false;

    while (!end_loop && !is_eof()) {
        switch (peek_forward()) {
            case '.':
                ++dot_count;
                is_float = true;
            case _non_float_numeric:
                if (peek_forward() == 'e') {
                    sci_notation = true;
                }
                break;
            default:
                if (sci_notation && (peek_forward() == '-' || peek_forward() == '+')) {
                    break;
                }
                end_loop = true;
                break;
        }
        bare_advance();
    }

    // if theres a . then it is a float
    if (is_float) {
        if (dot_count > 1) {
            throw error::Error(error::Line(file_name, line, column - (currentPos - start),
                                           currentPos - start, "invalid float"));
        }
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
            error::Line(file_name, start_line, start_column, 1, "unterminated string"));
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

    return {line,
            column - (currentPos - start),
            currentPos - start,
            offset,
            source.substr(start, currentPos - start),
            file_name};
}

inline Token Lexer::parse_punctuation() {  // gets here bacause of something like . | :
    Token result;

    switch (peek_forward()) {
        case '.':  // ..
            bare_advance();
            if (peek_forward() == '.') {  //...
                result =
                    Token{line, column, 3, offset, source.substr(currentPos - 1, 3), file_name};
                bare_advance(2);  // advance by 3 before return
                return result;
            }
        case ':':
            result = Token{line, column, 2, offset, source.substr(currentPos, 2), file_name};
            bare_advance(2);
            return result;
        default:
            result = Token{line, column, 1, offset, source.substr(currentPos, 1), file_name};
            bare_advance();
            return result;
    }
}

inline char Lexer::advance(u16 n) {
    if (currentPos + 1 > end) {
        return '\0';
    }

    switch (source[currentPos]) {
        case '\n':
            ++line;
            column = 0;
            break;
        default:
            ++column;
            ++offset;
            break;
    }

    ++currentPos;

    if (n > 1) {
        return advance(n - 1);
    }

    return current();
}

inline void Lexer::bare_advance(u16 n) {
    switch (source[currentPos]) {
        case '\n':
            ++line;
            column = 0;
            break;
        default:
            ++column;
            ++offset;
            break;
    }

    ++currentPos;

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