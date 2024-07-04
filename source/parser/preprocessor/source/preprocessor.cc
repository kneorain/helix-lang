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
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "core/utils/colors_ansi.hh"
#include "core/error/error.hh"
#include "token/include/generate.hh"
#include "lexer/include/lexer.hh"
#include "token/include/token.hh"
#include "controllers/include/file_system.hh"

namespace parser {
/**
 * The AST parser's dependency resolver requires context information, such as imports
 * and macro expansions, to function correctly. The Preprocessor handles this by resolving
 * all such context dependencies and producing a fully context-aware token list. This token
 * list includes all necessary information for the AST dependency resolver to operate effectively.
 */
TokenList Preprocessor::parse(std::shared_ptr<preprocessor::ImportNode> parent_node) {
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

    /* order of parsing (first to last)
        imports - working on now
        defines - working on now
        macros
    */
    preprocessor::import_helix _import;

    while (not_end()) {
        switch (current().token_kind()) {
            case tokens::KEYWORD_USING:  // abi import
                parse_using();
                break;
            case tokens::KEYWORD_IMPORT:  // module import
                _import = parse_import(preprocessor::import_tree, parent_node);
                break;
            case tokens::OPERATOR_LOGICAL_NOT:  // define invocation
                if (peek_back()->token_kind() == tokens::IDENTIFIER) {
                    error::Error(error::Line(source_tokens.slice(current_pos - 1, current_pos + 1),
                                             "undefined macro invocation", error::FATAL,
                                             std::string(colors::fg16::red) +
                                                 "marcos are not yet implemented." +
                                                 colors::reset));
                    std::exit(1);
                }
            case tokens::KEYWORD_DEFINE:
            case tokens::KEYWORD_MACRO:  // TODO: implement proc macros and defines into the
                                         // preprocessor
                error::Error(error::Line(current(), "macro behaviour unknown", error::FATAL,
                                         std::string(colors::fg16::red) +
                                             "marcos are not yet implemented." + colors::reset));
                std::exit(1);
            default:
                break;
        }

        if (!_import.source.empty()) {
            source_tokens.insert_remove(_import.source, _import.start, _import.end + 1);
            current_pos += _import.source.size() - ((_import.end + 1) - _import.start);
            end += _import.source.size();
            _import.source.clear();
        }

        increment_pos();
    }

    return source_tokens;

    /// print_tokens(source_tokens);
    /// std::cout << std::string(60, '-') << "\n";
}

inline void print_debug(auto explicit_imports, auto import_path, auto alias, auto current_feature,
                        auto import_start, auto import_end, auto source_tokens);

/*=====---------------------------------- private function ----------------------------------=====*/

bool is_circular_import(const std::shared_ptr<preprocessor::ImportNode> &node) {
    std::unordered_set<std::string> visited;
    std::shared_ptr<preprocessor::ImportNode> current = node;

    while (current != nullptr) {
        if (visited.find(current->module_name) != visited.cend()) {
            return true;  // Circular import detected
        }
        visited.insert(current->module_name);
        current = current->parent.lock();
    }
    return false;
}

preprocessor::import_helix
Preprocessor::parse_import(std::unique_ptr<preprocessor::ImportTree> &import_tree,
                           std::shared_ptr<preprocessor::ImportNode> parent_node) {
    std::vector<TokenList> explicit_imports;
    TokenList import_path;
    TokenList alias;
    TokenList current_feature;
    preprocessor::import_helix complete_import;

    u32 import_start = current_pos;
    u32 import_end = current_pos;
    u32 brace_level = 0;

    bool captured_import = false;
    bool captured_specific = false;

    if (peek().has_value() && peek()->token_kind() != tokens::IDENTIFIER) {
        error::Error(error::Line(peek().value(), "expected an identifier but got a string",
                                 error::ERR, "change the string import to a direct import."));
    }

    while (!captured_import && not_end()) {
        if (!advance().has_value()) {
            throw error::Error(error::Line(current(), "invalid syntax, maybe missing a semicolon"));
        }

        handle_import_tokens(brace_level, captured_import, captured_specific, explicit_imports,
                             import_path, current_feature, alias, import_end);
    }

    if (!current_feature.empty()) {
        error::Error(error::Line(current_feature, "incomplete import statement", error::FATAL,
                                 "complete the import statement."));
        std::exit(1);
    }

    std::string string_import_path = resolve_import_path(import_path);

    std::optional<std::filesystem::path> temp_path =
        file_system::resolve_path(string_import_path + ".hlx", rel_path.back().string());

    if (!temp_path.has_value()) {
        string_import_path = resolve_import_path(import_path.slice(0, import_path.size() - 2));
        temp_path =
            file_system::resolve_path(string_import_path + ".hlx", rel_path.back().string());
        explicit_imports.push_back(import_path.slice(import_path.size() - 1, import_path.size()));
    }

    if (!temp_path.has_value()) {
        string_import_path = resolve_import_path_with_namespace(import_path);
        temp_path =
            file_system::resolve_path(string_import_path + ".hlx", rel_path.back().string());

        if (!temp_path.has_value()) {
            TokenList tmp;
            if_missing_relative_parent(string_import_path, temp_path, tmp, import_path, 1);
        }
    }

    // TODO: handle module imports from PATH and manually included dirs.

    if (!temp_path.has_value()) {
        error::Error(error::Line(import_path, "import path not found", error::FATAL,
                                 "validate the import path provided. if you meant to do an "
                                 "explicit import, use import ..::{...} syntax."));
    }

    string_import_path = temp_path->string();

    // add the import to the import tree
    std::shared_ptr<preprocessor::ImportNode> current_node =
        import_tree->add_import(string_import_path, std::move(parent_node));
    // check for circular imports
    if (is_circular_import(current_node)) {
        error::Error(error::Line(import_path, "circular import detected", error::FATAL,
                                 "the module is already imported earlier in the import chain."));
    }

    if (error::HAS_ERRORED) {
        std::exit(1);
    }

    TokenList namespace_name = alias.empty() ? import_path : alias;
    TokenList parsed_source =
        lexer::Lexer(file_system::read_file(string_import_path), string_import_path).tokenize();

    parsed_source = Preprocessor(parsed_source).parse(current_node);
    parsed_source.pop_back();
    parsed_source.insert(parsed_source.cbegin(),
                         Token(tokens::PUNCTUATION_OPEN_BRACE, string_import_path));

    for (auto it = namespace_name.rbegin(); it != namespace_name.rend(); ++it) {
        parsed_source.insert(parsed_source.cbegin(), *it);
    }

    parsed_source.insert(parsed_source.cbegin(),
                         Token(tokens::KEYWORD_NAMESPACE, string_import_path));
    parsed_source.insert(parsed_source.cend(),
                         Token(tokens::PUNCTUATION_CLOSE_BRACE, string_import_path));

    complete_import = {
        .filepath = temp_path.value(),
        .module_base = rel_path.back(),
        .module = import_path,
        .relative = namespace_name,
        .source = parsed_source,
        .explicit_imports = explicit_imports,
        .start = import_start,
        .end = import_end,
    };

    preprocessor::imports.push_back(complete_import);

    return complete_import;
}

bool Preprocessor::if_missing_relative_parent(std::string &string_import_path,
                                              std::optional<std::filesystem::path> &temp_path,
                                              TokenList &explicit_imports, TokenList &import_path,
                                              u32 depth) {
    if (depth > u32(import_path.size() / 2)) {
        return false;
    }

    // try resolving with namespace and without last token
    string_import_path =
        resolve_import_path_with_namespace(import_path.slice(0, import_path.size() - (depth + 1)));

    temp_path = file_system::resolve_path(string_import_path + ".hlx", rel_path.back().string());

    // add the last token back as explicit import
    explicit_imports.push_back(
        import_path.slice(import_path.size() - depth, import_path.size())[0]);

    import_path = import_path.slice(0, import_path.size() - (depth + 1));

    return true;
}

// void Preprocessor::process_import_path(TokenList &import_path,
//                                        std::vector<TokenList> &explicit_imports,
//                                        bool &module_import) {
//     if (explicit_imports.size() == 1) {  // handle single explicit import
//         Token temp = explicit_imports[0][0];
//         import_path.push_back(Token(temp.line_number(), temp.column_number(), temp.length(),
//                                     temp.offset(), "::", std::string(temp.file_name())));
//
//         for (const auto &tok_list : explicit_imports) {
//             for (const auto &tok : tok_list) {
//                 import_path.push_back(Token(tok.line_number(), tok.column_number(), tok.length(),
//                                             tok.offset(), tok.value(),
//                                             std::string(tok.file_name()),
//                                             tok.token_kind_repr()));
//             }
//         }
//
//         explicit_imports.clear();  // clear explicit imports after processing
//     }
// }

std::string Preprocessor::resolve_import_path(const TokenList &import_path) {
    std::string string_import_path;
    for (const auto &tok : import_path) {
        switch (tok.token_kind()) {
            case tokens::IDENTIFIER:
                string_import_path += tok.value();  // append identifier to path
                break;
            case tokens::OPERATOR_SCOPE:
                string_import_path += "/";  // replace scope operator with path separator
                break;
            default:
                break;
        }
    }
    return string_import_path;  // return the resolved path as a string
}

std::string Preprocessor::resolve_import_path_with_namespace(const TokenList &import_path) {
    std::string string_import_path;
    Token _tok;

    for (const auto &tok : import_path) {
        switch (tok.token_kind()) {
            case tokens::IDENTIFIER:
                string_import_path += tok.value();  // append identifier to path
                _tok = tok;
                break;
            case tokens::OPERATOR_SCOPE:
                string_import_path += "/";  // replace scope operator with path separator
                break;
            default:
                break;
        }
    }

    string_import_path += "/";           // add a path separator before the last token
    string_import_path += _tok.value();  // append the last token value to the path
    return string_import_path;           // return the resolved path with namespace as a string
}

/*=====----------------------------------- debug functions ----------------------------------=====*/
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
}  // namespace parser
