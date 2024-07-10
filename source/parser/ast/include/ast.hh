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
#ifndef __AST_HH__
#define __AST_HH__

#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <expected>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "core/error/error.hh"
#include "parser/error_codes.def"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

namespace parser::ast {
struct ParseError {
    ParseError(token::Token tok, float error_code) {
        const auto &error_state = ERROR_MAP.at(error_code);
        error::Error(error::Line(tok, error_state.message, error_state.level, error_state.fix));
    };
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
    struct Declaration : public ASTBase<Declaration<T>> {};
    template <typename T>
    struct Expression  : public ASTBase<Expression<T>>  {};
    template <typename T>
    struct Annotation  : public ASTBase<Annotation<T>>  {};
    template <typename T>
    struct Statement   : public ASTBase<Statement<T>>   {};
    template <typename T>
    struct Type        : public ASTBase<Type<T>>        {};

    struct Program : ASTBase<Program> {};
}

template <typename T = void>
concept ASTNode      = std::derived_from<T, ASTBase<T>>;

template <typename T = void>
using NodePtr        = std::shared_ptr<ASTBase<T>>;

template <typename T = void>
using NodeList       = std::vector<NodePtr<T>>;

template <typename T = void>
using Slice          = const std::reference_wrapper<NodeList<T>>;
}  // namespace parser::ast
#endif  // __AST_HH__