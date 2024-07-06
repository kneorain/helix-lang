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

#include "token/include/token_list.hh"

namespace parser::ast {
struct ParseError {};

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

struct Declarations : public ASTBase<Declarations> {};
struct Expressions  : public ASTBase<Expressions>  {};
struct Annotations  : public ASTBase<Annotations>  {};
struct Statements   : public ASTBase<Statements>   {};
struct Types        : public ASTBase<Types>        {};

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