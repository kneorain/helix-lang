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
#include "token/include/generate.hh"
#include "token/include/token.hh"

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


    /* order of parsing (first to last)
    imports - working on now
    defines - working on now
    macros
    */
    while (not_end()) {
        const Token &current_token = current();
        current_token_type = current_token.token_kind();

        switch (current_token_type) {
            case tokens::KEYWORD_USING:
                parse_using();
                break;
            case tokens::KEYWORD_IMPORT:
                parse_import();
                break;
            default:
                // std::cout << (peek().has_value() ? peek()->file_name() : "null") << "\n";
                break;
        }

        increment_pos();
    }

    print_tokens(source_tokens);
}

/*=====---------------------------------- private function ----------------------------------=====*/

void Preprocessor::parse_import() {
    // helix imports are relative to the base file, or module file.
    /* example while compiling src/hello.hlx

    src/hello.hlx:
    ```helix
    import helper // this is excepted to be at src/helper.hlx
    import foo::bar // excepted to be at src/foo/helper.hlx
    ```

    src/zam/zam.hlx:
    ```
    import zoom::far // excepted to be at src/zam/zoom/far.hlx
    // another way of writing this import would be import zam::zoom::far
    ```

    src/zam/zoom/far.hlx:
    ```
    import helper // excepted at src/zam/helper.hlx not src/helper.hlx,
                  // since making a src/zam/zam.hlx is a module declaration
                  // and src/zam is considered as its own standalone module.
    ```
    */

    
}

void Preprocessor::parse_using() { // FIXME: Refactor and fix the code QL
    auto next_token = peek();
    if (next_token.has_value()) {
        if (next_token->token_kind() == tokens::LITERAL_STRING &&
            std::find(allowed_abi.begin(), allowed_abi.end(), next_token->value()) !=
                allowed_abi.end()) {
            advance();

            if (peek().has_value() && (peek()->token_kind() == tokens::KEYWORD_IMPORT ||
                                       peek()->token_kind() == tokens::PUNCTUATION_OPEN_BRACE)) {
                u32 brace_count = 0;

                if (peek()->token_kind() == tokens::PUNCTUATION_OPEN_BRACE) {
                    ++brace_count;
                }

                advance();
                bool ended = false;
                while (!ended && not_end()) {
                    advance();
                    if (peek().has_value()) {
                        switch (peek()->token_kind()) {
                            case tokens::PUNCTUATION_OPEN_BRACE:
                                ++brace_count;
                                break;
                            case tokens::PUNCTUATION_CLOSE_BRACE:
                                --brace_count;
                                if (brace_count == 0) {
                                    ended = true;
                                }
                                break;
                            case KEYWORD_IMPORT:
                                if (brace_count == 0) {
                                    [this] {
                                        bool end_of_import = false;
                                        while (!end_of_import && not_end()) {
                                            if (peek().has_value() &&
                                                peek()->token_kind() ==
                                                    tokens::PUNCTUATION_SEMICOLON) {
                                                end_of_import = true;
                                            }

                                            advance();
                                        }
                                    }();
                                }
                            default:
                        }
                    }
                }
            }
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

Token Preprocessor::current() { return source_tokens[current_pos]; }

std::optional<Token> Preprocessor::peek(u32 n) {
    if (not_end(n)) {
        return source_tokens[current_pos + n];
    }

    return std::nullopt;
}

std::optional<Token> Preprocessor::peek_back(u32 n) {
    if (not_start(n)) {
        return source_tokens[current_pos - n];
    }

    return std::nullopt;
}

std::optional<Token> Preprocessor::advance(u32 n) {
    if (not_end(n)) {
        return source_tokens[current_pos += n];
    }

    return std::nullopt;
}

std::optional<Token> Preprocessor::reverse(u32 n) {
    if (not_start(n)) {
        return source_tokens[current_pos -= n];
    }

    return std::nullopt;
}

inline bool Preprocessor::not_end(u32 n) const { return (current_pos + n) < end; }

inline bool Preprocessor::not_start(u32 n) const { return current_pos >= n; }

}  // namespace parser::preprocessor
