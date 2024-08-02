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

void handle_invalid_abi_option(Preprocessor *self) {
    std::string abi_options;

    for (const std::string &abi : self->allowed_abi) {
        abi_options += abi + ", ";
    }

    if (!self->allowed_abi.empty()) {
        abi_options = abi_options.substr(0, abi_options.size() - 2);
    }

    auto bad_token = self->peek().value();
    error::Error(error::CodeError(&bad_token, 0.7004, std::vector<string>{abi_options}));
}

void parse_import(Preprocessor *self) {}

/*
ffi "c++" import "some.hh";
ffi "py"  import "sympy";
          ^
ffi "py" {
         ^ or
    import "sympy";
    }

    ffi "py" {

    }
}

*/
void parse_ffi(Preprocessor *self) {  // at the time of call current() is 'ffi'
    i32 brace_count = 0;
    bool jump_back = false;
    string goto_caller;

iter_body:
    switch (self->current().token_kind()) {  // at call time peek should be a string
        case tokens::KEYWORD_FFI:
            if (self->peek().value_or(Token()).token_kind() != tokens::LITERAL_STRING) {
                error::Error(error::CodeError(&self->current(), 0.7005));
            }

            self->advance(2);  // skip ffi and the string ident

            if (self->current().token_kind() == tokens::KEYWORD_IMPORT) {  // ffi "c" import <- this
                goto_caller = "ffi";
                goto abi_import;  // no loop back
            }

            jump_back = true;

            break;

        case tokens::PUNCTUATION_OPEN_BRACE:  // ffi "py" { <-- this opening brace
            brace_count++;

            if (brace_count <= 0) {  // if theres more }'s then opening ones
                throw error::Error(error::CodeError(&self->current(), 2.1002, {}, std::vector<string>{"closing brace"}));
            }

            self->advance();  // skip {
            jump_back = true;
            break;

        case tokens::PUNCTUATION_CLOSE_BRACE:  // } <-- this closing brace
            brace_count--;

            if (brace_count < 0) {  // if theres an additional closing brace
                throw error::Error(error::CodeError(&self->current(), 2.1002, {}, std::vector<string>{"opening brace"}));
            }

            if (brace_count == 0) {  // completed
                return;
            }

            self->advance();  // skip }
            jump_back = true;
            break;

        case tokens::KEYWORD_IMPORT:  // import <-- this "sympy";
        abi_import:
            // syntax: 'import' (string (',' string)*) ';'
            if (!self->peek().has_value()) {  // just 'import' no specifier
                auto bad_token = self->peek().value();
                throw error::Error(error::CodeError(&bad_token, 0.10001, {}, std::vector<string>{"opening brace"}));
            }

            if (self->peek().value().token_kind() != tokens::LITERAL_STRING) {
                // 0.10101
                auto bad_token = self->peek().value();
                throw error::Error(error::CodeError(&bad_token, 0.10101, std::vector<string>{"import \"" + self->peek().value().value() + "\""}));
            }

            self->advance(2);  // skip 'import' string | other
            // current should only be either ; or ,

            if (self->current().token_kind() == tokens::PUNCTUATION_COMMA) {  // (',' string)*
                // 0.10102
                error::Error(error::CodeError(&self->current(), 0.10102));
                // TODO: add parsing if needed (might not look cohesive)
                //       dont forget to advance after parsing out multiple
            }

            // ';' at this point it should only be a semicolon
            if (self->current().token_kind() != tokens::PUNCTUATION_SEMICOLON) {
                error::Error(error::CodeError(&self->current(), 4.0001, {}, {}, std::vector<std::pair<token::Token, i64>>{std::make_pair(Token(tokens::PUNCTUATION_SEMICOLON), static_cast<i64>(-1))}));
            }

            self->advance();  // skip ; or ,
            jump_back = true;

            if (goto_caller == "ffi") {
                return;  // import completed
            }

            break;

        case tokens::PUNCTUATION_SEMICOLON:
            self->advance();  // skip ;'s
            jump_back = true;
            break;

        default:
            if (brace_count > 0) {
                break;
                self->advance();  // skip ;
                jump_back = true;
                break;
            } else {
                error::Error(error::CodeError(&self->current(), 0.0001));
            }
    }

    if (jump_back) {
        jump_back = false;
        goto iter_body;
    }
}

void parse_define(Preprocessor *self) {}

void parse_macro(Preprocessor *self) {}

void parse_invocation(Preprocessor *self) {}

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
