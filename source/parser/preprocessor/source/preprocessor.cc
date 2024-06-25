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
#include "parser/preprocessor/include/preprocessor.hh"

#include <iostream>
#include <string>
#include <vector>

#include "include/error/error.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"

namespace parser::preprocessor {
/**
 * The AST parser's dependency resolver requires context information, such as imports
 * and macro expansions, to function correctly. The Preprocessor handles this by resolving
 * all such context dependencies and producing a fully context-aware token list. This token
 * list includes all necessary information for the AST dependency resolver to operate effectively.
 */
void Preprocessor::parse() {
    /// print_tokens(source_tokens);
    /// std::cout << std::string(60, '-') << "\n";
    
    /* things parsed here:
        - imports:
            - import xyz
            - import xyz::{class function or namespace, ...}
            - import xyz::class function or namespace
            - import xyz::abc as abc_source;
            - import xyz::future::Future as Future_Class;

            ~ not parsed here ~
            - using "c++ or c" {
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

        imports
        rel_path
        source_tokens
        current_pos
        end
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



    /// print_tokens(source_tokens);
    /// std::cout << std::string(60, '-') << "\n";
}

inline void print_debug(auto explicit_imports, auto import_path, auto alias, auto current_feature,
                        auto import_start, auto import_end, auto source_tokens) {
    std::cout << "explicit_imports: "
              << "\n";
    for (auto token_list : explicit_imports) {
        print_tokens(token_list);
    }
    std::cout << "import_path: "
              << "\n";
    print_tokens(import_path);
    std::cout << "alias: "
              << "\n";
    print_tokens(alias);
    std::cout << "current_feature: "
              << "\n";
    print_tokens(current_feature);
    std::cout << "start: " << std::to_string(import_start) << "\n";
    std::cout << "end: " << std::to_string(import_end) << "\n";
    TokenList temp_sec = source_tokens.slice(u64(import_start), u64(import_end));
    std::cout << "slice: "
              << "\n";
    print_tokens(temp_sec);
    std::cout << std::string(60, '-') << "\n";
}

/*=====---------------------------------- private function ----------------------------------=====*/

void Preprocessor::parse_import() {
    // helix imports are relative to the base file, or module file.
    /*
    example while compiling src/hello.hlx

    src/hello.hlx:
    ```helix
    import helper // this is expected to be at src/helper.hlx
    import foo::bar // expected to be at src/foo/helper.hlx
    ```

    src/zam/zam.hlx:
    ```
    import zoom::far // expected to be at src/zam/zoom/far.hlx
    // another way of writing this import would be import zam::zoom::far
    ```

    src/zam/zoom/far.hlx:
    ```
    import helper // expected at src/zam/helper.hlx not src/helper.hlx,
                  // since making a src/zam/zam.hlx is a module declaration
                  // and src/zam is considered as its own standalone module.
    ```
    */

    std::vector<TokenList> explicit_imports;
    TokenList import_path;
    TokenList alias;
    TokenList current_feature;
    import_helix complete_import;

    u32 import_start = current_pos;
    u32 import_end = current_pos;
    u32 brace_level = 0;

    bool captured_import = false;
    bool captured_specific = false;

    if (peek().has_value() && peek()->token_kind() != tokens::IDENTIFIER) {
        error::Error(error::Line(peek().value(), "got string instead of identifier", error::ERR,
                                 "change the string import to a direct import."));
    }

    while (!captured_import && not_end()) {
        advance();
        handle_import_tokens(brace_level, captured_import, captured_specific, explicit_imports,
                             import_path, current_feature, alias, import_end);
    }

    // print_debug(explicit_imports, import_path, alias, current_feature, import_start, import_end,
    // source_tokens);
}
}  // namespace parser::preprocessor
