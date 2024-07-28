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
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "parser/preprocessor/include/dependency_tree.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

namespace parser {
using namespace token;
/**
 * The Preprocessor class is responsible for handling context-dependent elements in the source code,
 * such as imports and macro expansions. It processes the source tokens to produce a fully
 * context-aware token list. This token list provides all necessary information for subsequent
 * stages of the compiler, such as the AST dependency resolver, ensuring accurate parsing and code
 * analysis.
 */
class Preprocessor {
  private:
    TokenList source_tokens;
    std::list<std::filesystem::path> include_dirs;
    std::array<string, abi::reserved.size()> allowed_abi;
    TokenList::TokenListIter *source_iter = nullptr;

    u32 current_pos{};
    u32 end{};

    friend void handle_invalid_abi_option(Preprocessor*);
    friend void parse_import(Preprocessor*);
    friend void parse_ffi(Preprocessor*);
    friend void parse_define(Preprocessor*);
    friend void parse_macro(Preprocessor*);
    friend void parse_invocation(Preprocessor*);

    //===------------------------------------ iter helpers ------------------------------------===//

    inline bool is_source_iter_set() { return source_iter != nullptr; }

    inline Token &current() { return source_iter->current().get(); }

    inline Token &advance(const std::int32_t n = 1) { return source_iter->advance(n).get(); }

    inline Token &reverse(const std::int32_t n = 1) { return source_iter->reverse(n).get(); }

    std::optional<Token> peek(const std::int32_t n = 1) const {
        return source_iter->peek(n)->get();
    };

    std::optional<Token> peek_back(const std::int32_t n = 1) const {
        return source_iter->peek_back(n)->get();
    };

    //===--------------------------------------------------------------------------------------===//

  public:
    explicit Preprocessor(TokenList &tokens, const std::string &name = "",
                          const std::vector<string> &custom_include_dirs = {});

    ~Preprocessor() = default;

    Preprocessor(Preprocessor &&other) = default;
    Preprocessor(const Preprocessor &other) = default;
    Preprocessor &operator=(const Preprocessor &other) = delete;
    Preprocessor &operator=(Preprocessor &&other) = delete;

    TokenList parse(std::shared_ptr<preprocessor::ImportNode> parent_node = nullptr);

    static void finalize() { preprocessor::import_tree.reset(); };
};

}  // namespace parser

#endif  // __PRE_HH__