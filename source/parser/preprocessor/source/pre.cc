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
#include "parser/preprocessor/include/pre.hh"

#include <algorithm>
#include <iostream>
#include <string>

#include "include/error/error.hh"

namespace parser::preprocessor {
/* The AST parser dependents resolver would fail without knowing context such as imports,
 * macro expansions and such. thats why we have the preprocessor this would resolve all of that
 * and output a full context aware token list that would contain everything the ast dependents
 * resolver would need to work.
 */
void Preprocessor::parse() {
    /* things parsed here:
    - imports:
        - import xyz
        - import xyz::{class function or namespace, ...}
        - import xyz::class function or namespace
        - import xyz::abc as abc_source;
        - import xyz::future::Future as Future_Class;

        ~ not parsed here ~
        - using "c++ or c"    {
            import "xyzcpp.hpp";
            import "xyzcpp.cpp";
          }
        - using "c++ or c"    import <iostream>
        - using "python" import xyzpy

    - defines:

    - macros:

    - compiler directives:
        - #[no-entry]
    */
    tokens current_token_type{};

    bool in_using = false;
    bool is_using_block = false;  // using "..." { ... }

    while (not_end()) {
        const Token &current_token = current();
        current_token_type = current_token.token_kind();

        switch (current_token_type) {
            case tokens::KEYWORD_USING:
                parse_using();
                break;
            case tokens::KEYWORD_IMPORT:  // 2 possibles its in an using statement or its a helix
                                          // import
                parse_import();
                break;
            default:
                // std::cout << (peek().has_value() ? peek()->file_name() : "null") << "\n";
                break;
        }

        increment_pos();
    }
}

/*=====---------------------------------- private function ----------------------------------=====*/

void Preprocessor::parse_import() {}

void Preprocessor::parse_using() {
    auto next_token = peek();
    if (next_token.has_value()) {
        if (next_token->token_kind() == tokens::LITERAL_STRING &&
            std::find(allowed_abi.begin(), allowed_abi.end(), next_token->value()) !=
                allowed_abi.end()) {

        } else {
            std::string abi_options;

            for (const std::string &abi : allowed_abi) {
                abi_options += abi + ", ";
            }

            if (!allowed_abi.empty()) {
                abi_options = abi_options.substr(0, abi_options.size() - 2);
            }

            error::Error(error::Line(
                next_token.value(), "disallowed abi option, abi should only be a string.",
                error::ERR, "use one of allowed abi options [" + abi_options + "]"));
        }
    }
}

void Preprocessor::increment_pos(u32 n) { current_pos += n; }

token::Token Preprocessor::current() { return source_tokens[current_pos]; }

std::optional<token::Token> Preprocessor::peek(u32 n) {
    if (not_end(n)) {
        return source_tokens[current_pos + n];
    }

    return std::nullopt;
}

std::optional<token::Token> Preprocessor::peek_back(u32 n) {
    if (not_start(n)) {
        return source_tokens[current_pos - n];
    }

    return std::nullopt;
}

std::optional<token::Token> Preprocessor::advance(u32 n) {
    if (not_end(n)) {
        return source_tokens[current_pos += n];
    }

    return std::nullopt;
}

std::optional<token::Token> Preprocessor::reverse(u32 n) {
    if (not_start(n)) {
        return source_tokens[current_pos -= n];
    }

    return std::nullopt;
}

inline bool Preprocessor::not_end(u32 n) const { return (current_pos + n) < end; }

inline bool Preprocessor::not_start(u32 n) const { return current_pos >= n; }

}  // namespace parser::preprocessor
