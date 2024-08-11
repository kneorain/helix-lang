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

#ifndef __AST_HH__
#define __AST_HH__

#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <expected>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "core/error/error.hh"
#include "core/error/error_codes.def"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

#define AST_NODE_METHODS(name)                      \
    ~name() = default;                              \
    explicit name(TokenListRef parse_tokens)        \
        : source_tokens(std::move(parse_tokens)){}; \
    name() = default;                               \
    name(name &&) = default;                        \
    name(const name &) = default;                   \
    name &operator=(name &&) = default;             \
    name &operator=(const name &) = delete;         \
    ParseResult parse();                            \
    std::string to_json(u32 depth = 0) const;       \
                                                    \
  private:                                          \
    TokenListRef source_tokens;                     \
                                                    \
  public:

#define make_ast_node(node_type, tokens) std::make_shared<node_type>(std::make_shared<TokenList>(tokens))
// make_ast_node(Literal, make_ast_node())

namespace parser::ast {

struct ParseError {
    ParseError(token::Token& tok, float error_code, std::vector<string> fix_fmt_args = {}, std::vector<string> err_fmt_args = {}, std::vector<std::pair<token::Token, i64>> opt_fixes = {}) {
        error::Error(error::create_old_CodeError(&tok, error_code, std::move(fix_fmt_args), std::move(err_fmt_args),  std::move(opt_fixes)));
    };

    virtual ~ParseError()                  = default;
};

using TokenListRef = std::shared_ptr<token::TokenList>;
using ParseResult  = std::expected<u64, ParseError>; // len of tokens to skip | recoverable error

template <typename T>
struct ASTBase;

template <>
struct ASTBase<void> {
    ASTBase()                           = default;
    ASTBase(ASTBase &&)                 = default;
    ASTBase(const ASTBase &)            = default;
    ASTBase &operator=(ASTBase &&)      = default;
    ASTBase &operator=(const ASTBase &) = delete;
    virtual ~ASTBase()                  = default;

    [[nodiscard]] virtual ParseResult parse() = 0;
    [[nodiscard]] virtual std::string to_json(u32 depth = 0) const = 0;
};

template <typename T>
struct ASTBase : public ASTBase<void> {
    explicit ASTBase(TokenListRef parse_tokens);
    ASTBase()                           = default;
    ASTBase(ASTBase &&)                 = default;
    ASTBase(const ASTBase &)            = default;
    ASTBase &operator=(ASTBase &&)      = default;
    ASTBase &operator=(const ASTBase &) = delete;
   ~ASTBase()                           = default;
};

namespace node {
    template <typename T>
    struct Statement   : public ASTBase<Statement<T>>   {};
    
    template <typename T>
    struct Expression  : public ASTBase<Expression<T>>  {};
    
    template <typename T>
    struct Declaration : public ASTBase<Declaration<T>> {};
    
    template <typename T>
    struct Type        : public ASTBase<Type<T>>        {};
    
    template <typename T>
    struct Annotation  : public ASTBase<Annotation<T>>  {};
}

template <class T>
concept ASTNode =
    std::derived_from<T, ASTBase<T>>          || std::derived_from<T, node::Statement<T>>   ||
    std::derived_from<T, node::Expression<T>> || std::derived_from<T, node::Declaration<T>> ||
    std::derived_from<T, node::Type<T>>       || std::derived_from<T, node::Annotation<T>>;

template <typename T = ASTBase<void>>
using NodePtr        = std::shared_ptr<T>;

template <typename T = void>
using NodeList       = std::vector<NodePtr<T>>;

template <typename T = void>
using Slice          = const std::reference_wrapper<NodeList<T>>;

template <ASTNode T>
constexpr std::shared_ptr<T> make_node(const token::TokenList& tokens) {
    return std::make_shared<T>(std::make_shared<token::TokenList>(tokens));
}
}  // namespace parser::ast

#endif  // __AST_HH__