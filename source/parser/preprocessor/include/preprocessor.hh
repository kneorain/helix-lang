// -*- C++ -*-
//===------------------------------------------------------------------------------------------===//
//
// Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
// You are allowed to use, modify, redistribute, and create derivative works, even for commercial
// purposes, provided that you give appropriate credit, and indicate if changes were made.
// For more information, please visit: https://creativecommons.org/licenses/by/4.0/
//
// SPDX-License-Identifier: CC-BY-4.0
// Copyright (c) 2024 (CC BY 4.0)
//
//===------------------------------------------------------------------------------------------===//

#ifndef __PRE_HH__
#define __PRE_HH__

#include <cstddef>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "core/utils/hx_print"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

namespace parser::preprocessor {
using namespace token;

struct ImportNode {
    std::string module_name;
    std::vector<std::shared_ptr<ImportNode>> children;
    std::weak_ptr<ImportNode> parent;

    explicit ImportNode(std::string name, std::shared_ptr<ImportNode> parent_node = nullptr)
        : module_name(std::move(name)), parent(parent_node) {}

    ~ImportNode() = default;
    ImportNode(ImportNode &&other) = default;
    ImportNode(const ImportNode &other) = delete;
    ImportNode& operator=(ImportNode &&other) = delete;
    ImportNode& operator=(const ImportNode &other) = delete;
};

class ImportTree {
  public:
    explicit ImportTree(std::string name)
        : root(std::make_shared<ImportNode>(std::move(name))) {}

    ~ImportTree() = default;
    ImportTree(ImportTree &&other) = default;
    ImportTree(const ImportTree &other) = delete;
    ImportTree& operator=(ImportTree &&other) = delete;
    ImportTree& operator=(const ImportTree &other) = delete;

    std::shared_ptr<ImportNode> add_import(const std::string &module_name, std::shared_ptr<ImportNode> parent = nullptr) {
        auto node = std::make_shared<ImportNode>(module_name, parent);
        if (parent != nullptr) {
            parent->children.push_back(node);
        } else {
            root->children.push_back(node);
        }
        return node;
    }

    void print_tree(const std::shared_ptr<ImportNode>& node, const std::string& prefix = "", bool is_last = true, int depth = 0) {
        if (node == nullptr) {
            return;
        }

        // Define ANSI color codes
        const std::string RESET = "\033[0m";
        const std::string CYAN = "\033[36m";
        const std::string MAGENTA = "\033[35m";
        const std::string BLUE = "\033[34m";
        const std::string YELLOW = "\033[33m";

        std::cout << prefix;

        if (depth != 0) {
            std::cout << (is_last ? "└── " : "├── ");
        }
        std::cout << (depth == 0 ? CYAN : (depth % 2 == 0 ? MAGENTA : BLUE)) << node->module_name << RESET << std::endl;

        std::string new_prefix = prefix + (is_last ? std::string(static_cast<int>(depth * 4), ' ') : "│   ");

        for (size_t i = 0; i < node->children.size(); ++i) {
            print_tree(node->children[i], new_prefix, i == node->children.size() - 1, depth + 1);
        }
    }

    std::shared_ptr<ImportNode> get_root() { return root; }

  private:
    std::shared_ptr<ImportNode> root;
};

/**
 * @brief helix handles imports in a slightly different manner then a language like c++ where
 * imports have to be linked. in helix imports are inplace replaced in place of an import statement,
 * thus having the source in place, making 1 giant helix file that would contain all the the
 * project, this would not only speed up ast gen, and clang compile times, it would also allow for
 * circular imports, BUT if a file still needs to be linked rather then this way an `extern import`
 * statement can always be used to allow for that functionality.
 *
 * The import_helix struct encapsulates information related to Helix imports,
 * detailing how and where a module is imported within the Helix source code.
 *
 * Members:
 * - filename: The path to the imported file relative to the project root (e.g.,
 * "src/foo/hello.hlx"). This indicates that the file is part of the "foo" module.
 * - module: The name of the module to which the file belongs (e.g., "foo").
 * - module_base: The base file of the module (e.g., "src/foo/foo.hlx").
 * - relative: The namespace under which the module should be included (e.g., "foo").
 * - source: A list of tokens representing the source code to be inserted in place of the import
 * statement.
 */
struct import_helix {
    std::filesystem::path filepath;           //> src/foo/hello.hlx - a part of the foo module
    std::filesystem::path module_base;        //> src/foo/foo.hlx
    TokenList module;                         //> foo
    TokenList relative;                       //> foo - the namespace to include it too
    TokenList source;                         //> source tokens to go in place
    std::vector<TokenList> explicit_imports;  //> if a specific part of the module is imported
    u32 start;                                //> the start of the import statement itself
    u32 end;                                  //> the end of the import statement

    std::string get_module() {
        std::string mod;

        for (auto &tok : module) {
            mod += tok->value();
        }

        return mod;
    }

    std::string get_namespace() {
        std::string name_space;

        for (auto &tok : relative) {
            name_space += tok->value();
        }

        return name_space;
    }

    static void print_data(import_helix data) {
        std::cout << std::string(120, '-') << '\n';
        std::cout << "filepath: " << data.filepath << "\n";
        std::cout << "module_base: " << data.module_base << "\n";
        std::cout << "module: ";
        print_tokens(data.module);
        std::cout << "relative: ";
        print_tokens(data.relative);
        std::cout << "source: ";
        print_tokens(data.source);
        std::cout << "explicit_imports: ["
                  << "\n";
        for (auto token_list : data.explicit_imports) {
            print_tokens(token_list);
        }
        std::cout << "]" << '\n' << '\n';
    }
};

inline std::unique_ptr<ImportTree> import_tree;
inline std::vector<import_helix>   imports;

} //  namespace parser::preprocessor

namespace parser {
using namespace token;
/**
 * The Preprocessor class is responsible for handling context-dependent elements in the source code,
 * such as imports and macro expansions. It processes the source tokens to produce a fully
 * context-aware token list. This token list provides all necessary information for subsequent
 * stages of the compiler, such as the AST dependency resolver, ensuring accurate parsing and code
 * analysis.
 *
 * Members:
 * - allowed_abi: An array of allowed ABI (Application Binary Interface) strings.
 * - imports: A vector of import_helix structures that represent the imports found in the source
 * code.
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
 * - handle_open_brace_in_import: Processes tokens when an open brace is encountered in an import
 * statement.
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
 * - Preprocessor(TokenList &tokens): Initializes the Preprocessor with a list of source tokens and
 * sets up allowed ABI options.
 *
 * Public Method:
 * - parse: Main method to start the preprocessing of the source tokens.
 */
class Preprocessor {
  private:
    std::array<std::string, abi::reserved_map.size()> allowed_abi;
    std::vector<std::filesystem::path>
        rel_path;  // if importing a module that would be the current rel path

    TokenList &source_tokens;

    std::vector<string> pkg_paths;
    u32 current_pos{};
    u32 end;

    std::optional<preprocessor::import_helix> parse_import(std::unique_ptr<preprocessor::ImportTree> &import_tree, std::shared_ptr<preprocessor::ImportNode> parent_node = nullptr);

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

    static void process_import_path(TokenList &import_path,
                                    std::vector<TokenList> &explicit_imports, bool &module_import);
    static std::string resolve_import_path(const TokenList &import_path);
    static std::string resolve_import_path_with_namespace(const TokenList &import_path);
    bool if_missing_relative_parent(std::string &string_import_path,
                                    std::optional<std::filesystem::path> &temp_path,
                                    TokenList &explicit_imports, TokenList &import_path, u32 depth);

    void parse_using();
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

    [[nodiscard]] inline bool not_end(u32 n = 0) const { return (current_pos + n) <= end; }

    [[nodiscard]] inline bool not_start(u32 n = 0) const { return current_pos >= n; }

  public:
    explicit Preprocessor(TokenList &tokens, const std::string& name = "", const std::vector<string>& _pkg_paths = {})
        : source_tokens(tokens)
        , pkg_paths(_pkg_paths)
        , end(tokens.size() - 2) { // accounting the eof token
        pkg_paths.push_back(std::filesystem::path(tokens[0].file_name()).parent_path().string());
        rel_path.push_back(std::filesystem::path(tokens[0].file_name()).parent_path());
        std::transform(abi::reserved_map.begin(), abi::reserved_map.end(), allowed_abi.begin(),
                       [](const auto &pair) { return std::string(pair.second); });
        
        if (!name.empty() || name == "main") {
            preprocessor::import_tree = std::make_unique<preprocessor::ImportTree>(std::string(tokens[0].file_name()));
        }
    }

    ~Preprocessor() = default;

    Preprocessor(Preprocessor &&other) = default;
    Preprocessor(const Preprocessor &other) = default;
    Preprocessor& operator=(const Preprocessor &other) = delete;
    Preprocessor& operator=(Preprocessor &&other) = delete;

    TokenList parse(std::shared_ptr<preprocessor::ImportNode> parent_node = nullptr);
    
    static void finalize() {
        preprocessor::import_tree.reset();
    };
};

}  // namespace parser::preprocessor

#endif  // __PRE_HH__