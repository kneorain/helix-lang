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

#include "parser/preprocessor/include/preprocessor.hh"

#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "controllers/include/file_system.hh"
#include "core/error/error.hh"
#include "core/utils/colors_ansi.hh"
#include "lexer/include/lexer.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"

namespace parser {
Preprocessor::Preprocessor(TokenList &tokens, const std::string &name,
                           const std::vector<string> &custom_include_dirs)
    : source_tokens(tokens)
    , end((tokens.size() > 0) ? (tokens.size() - 1) : 0) {

    if (!(tokens.size() > 0) || end == 0) [[unlikely]] {
        return;  // in the case that there are no tokens (physically impossible)
    }

    include_dirs.emplace_back(std::filesystem::path(tokens[0].file_name()).parent_path());

    for (const auto &path_str : custom_include_dirs) {
        include_dirs.emplace_back(path_str);
    }

    transform(abi::reserved.begin(), abi::reserved.end(), allowed_abi.begin(),
              [](const auto &pair) { return string(pair.second); });

    if (!name.empty() || name == "main") {
        preprocessor::import_tree = make_unique<preprocessor::ImportTree>(tokens[0].file_name());
    }
}

void handle_invalid_abi_option(Preprocessor* self) {
    std::string abi_options;

    for (const std::string &abi : self->allowed_abi) {
        abi_options += abi + ", ";
    }

    if (!self->allowed_abi.empty()) {
        abi_options = abi_options.substr(0, abi_options.size() - 2);
    }

    error::Error(error::Line(self->peek().value(),
                             "disallowed abi option, abi should only be a string.", error::ERR,
                             "use one of allowed abi options [" + abi_options + "]"));
}

void parse_import(Preprocessor* self) {

}

void parse_ffi(Preprocessor* self) {

}

void parse_define(Preprocessor* self) {

}

void parse_macro(Preprocessor* self) {

}

void parse_invocation(Preprocessor* self) {

}

TokenList Preprocessor::parse(std::shared_ptr<preprocessor::ImportNode> parent_node) {
    /* order of parsing (first to last)
        imports - working on now
        defines
        macros
        directives
    */

    for (auto tok_iter : source_tokens) {
        if (!is_source_iter_set()) {
            source_iter = &tok_iter;
        }

        switch (current().token_kind()) {
            case tokens::KEYWORD_IMPORT:
                parse_import(this);
                break;
            case tokens::KEYWORD_FFI:
                parse_ffi(this);
                break;
            case tokens::KEYWORD_DEFINE:
                parse_define(this);
                break;
            case tokens::KEYWORD_MACRO:
                parse_macro(this);
                break;
            case tokens::OPERATOR_LOGICAL_NOT:
                parse_invocation(this);
                break;
            default:
                break;
        }
    }

    return source_tokens;
}

}  // namespace parser
