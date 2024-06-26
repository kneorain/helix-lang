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
#ifndef __PRE_H__
#define __PRE_H__

#include <optional>
#include <string>
#include <vector>

#include <token/include/token.hh>

namespace parser::preprocessor {
using namespace token;

/**
 * The import_helix struct encapsulates information related to Helix imports,
 * detailing how and where a module is imported within the Helix source code.
 *
 * Members:
 * - filename: The path to the imported file relative to the project root (e.g., "src/foo/hello.hlx").
 *   This indicates that the file is part of the "foo" module.
 * - module: The name of the module to which the file belongs (e.g., "foo").
 * - module_base: The base file of the module (e.g., "src/foo/foo.hlx").
 * - relative: The namespace under which the module should be included (e.g., "foo").
 * - source: A list of tokens representing the source code to be inserted in place of the import statement.
 */
struct import_helix {
    std::string filename;     //> src/foo/hello.hlx - a part of the foo module
    std::string module;       //> foo
    std::string module_base;  //> src/foo/foo.hlx
    std::string relative;     //> foo - the namespace to include it too
    TokenList   source;       //> source tokens to go in place
};

/**
 * The Preprocessor class is responsible for handling context-dependent elements in the source code,
 * such as imports and macro expansions. It processes the source tokens to produce a fully context-aware
 * token list. This token list provides all necessary information for subsequent stages of the compiler,
 * such as the AST dependency resolver, ensuring accurate parsing and code analysis.
 *
 * Members:
 * - allowed_abi: An array of allowed ABI (Application Binary Interface) strings.
 * - imports: A vector of import_helix structures that represent the imports found in the source code.
 * - rel_path: A vector of strings representing the relative path for imported modules.
 * - source_tokens: A list of tokens representing the source code to be processed.
 * - current_pos: The current position in the token list being processed.
 * - end: The position of the last token in the token list.
 *
 * Methods:
 * - parse_import: Handles the parsing of import statements in the source code.
 * - parse_using: Handles the parsing of using statements related to ABI in the source code.
 * - parse_import_alias: Parses the alias part of an import statement.
 * - handle_import_tokens: Processes tokens within an import statement.
 * - handle_open_brace_in_import: Processes tokens when an open brace is encountered in an import statement.
 * - handle_using_abi_imports: Handles ABI-specific imports within a using statement.
 * - parse_import_within_using: Parses imports found within a using statement.
 * - handle_invalid_abi_option: Handles invalid ABI options in a using statement.
 * - increment_pos: Increments the current position in the token list by a specified amount.
 * - current: Returns the current token being processed.
 * - peek: Returns the token at a specified position ahead of the current position.
 * - peek_back: Returns the token at a specified position behind the current position.
 * - advance: Advances the current position in the token list by a specified amount.
 * - reverse: Reverses the current position in the token list by a specified amount.
 * - not_end: Checks if the specified position is not beyond the end of the token list.
 * - not_start: Checks if the specified position is not before the start of the token list.
 *
 * Constructor:
 * - Preprocessor(TokenList &tokens): Initializes the Preprocessor with a list of source tokens and sets up allowed ABI options.
 *
 * Public Method:
 * - parse: Main method to start the preprocessing of the source tokens.
 */
class Preprocessor {
  private:
    std::array<std::string, abi::reserved_map.size()> allowed_abi;
    
    std::vector<import_helix> imports;
    std::vector<std::string>  rel_path;  // if importing a module that would be the current rel path

    TokenList source_tokens;
    u32       current_pos{};
    u32       end;

    void parse_import();
    void parse_using();

    void parse_import_alias(TokenList &alias, const std::vector<TokenList> &explicit_imports);
    void handle_import_tokens(u32 &brace_level, bool &captured_import, bool &captured_specific,
                                std::vector<TokenList> &explicit_imports, TokenList &import_path,
                                TokenList &current_feature, TokenList &alias, u32 &import_end);
    void handle_open_brace_in_import(u32 &brace_level, bool &captured_specific,
                                     std::vector<TokenList> &explicit_imports,
                                     TokenList &current_feature);
    void handle_using_abi_imports();
    void parse_import_within_using();
    void handle_invalid_abi_option(const std::optional<Token> &next_token);

    void increment_pos(u32 n = 1) { current_pos += n; }

    Token current() { return source_tokens[current_pos]; }

    std::optional<Token> peek(u32 n = 1) {
        if (not_end(n)) {
            return source_tokens[current_pos + n];
        }

        return std::nullopt;
    }

    std::optional<Token> peek_back(u32 n = 1) {
        if (not_start(n)) {
            return source_tokens[current_pos - n];
        }

        return std::nullopt;
    }

    std::optional<Token> advance(u32 n = 1) {
        if (not_end(n)) {
            return source_tokens[current_pos += n];
        }

        return std::nullopt;
    }

    std::optional<Token> reverse(u32 n = 1) {
        if (not_start(n)) {
            return source_tokens[current_pos -= n];
        }

        return std::nullopt;
    }

    inline bool not_end(u32 n = 0) const { return (current_pos + n) < end; }

    inline bool not_start(u32 n = 0) const { return current_pos >= n; }

  public:
    explicit Preprocessor(TokenList &tokens)
        : source_tokens(tokens)
        , end(tokens.size() - 1) {
        std::transform(abi::reserved_map.begin(), abi::reserved_map.end(), allowed_abi.begin(),
                       [](const auto &pair) { return std::string(pair.second); });
    }

    void parse();
};

}  // namespace parser::preprocessor

#endif  // __PRE_H__