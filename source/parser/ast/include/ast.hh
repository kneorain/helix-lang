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
#include "core/utils/josnify.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

#define AST_NODE_METHODS(name)                                                               \
  public:                                                                                    \
    explicit name(token::TokenList parse_tokens)                                             \
        : source_tokens(std::move(parse_tokens)){};                                          \
    explicit name(const token::Token &parse_token) { source_tokens.push_back(parse_token); } \
    ~name()                                       = default;                                 \
    name()                                        = default;                                 \
    name(name &&)                                 = default;                                 \
    name(const name &)                            = default;                                 \
    name                 &operator=(name &&)      = default;                                 \
    name                 &operator=(const name &) = delete;                                  \
    constexpr std::string node_repr() const { return #name; }                                \
    ParseResult           parse();                                                           \
                                                                                             \
  private:                                                                                   \
    token::TokenList source_tokens;                                                          \
                                                                                             \
  public:

#define BASE_NODE_TYPE(name)                                               \
    class name {                                                           \
      public:                                                              \
        name()                        = default;                           \
        name(name &&)                 = default;                           \
        name(const name &)            = default;                           \
        name &operator=(name &&)      = default;                           \
        name &operator=(const name &) = delete;                            \
        virtual ~name()               = default;                           \
                                                                           \
        [[nodiscard]] virtual ParseResult           parse()           = 0; \
        [[nodiscard]] virtual constexpr std::string node_repr() const = 0; \
        [[nodiscard]] virtual TO_JSON_SIGNATURE                       = 0; \
    }

#define DERIVED_NODE_TYPE(name)                                                                  \
    class name : public ASTBase {                                                                \
      public:                                                                                    \
        name()                        = default;                                                 \
        name(name &&)                 = default;                                                 \
        name(const name &)            = default;                                                 \
        name &operator=(name &&)      = default;                                                 \
        name &operator=(const name &) = delete;                                                  \
        virtual ~name()               = default;                                                 \
                                                                                                 \
        [[nodiscard]] virtual ParseResult           parse() override;                            \
        [[nodiscard]] virtual constexpr std::string node_repr() const override { return #name; } \
        [[nodiscard]] virtual TO_JSON_SIGNATURE     override;                                    \
    }

namespace parser::ast {
using namespace token;

struct ParseError {
    using fix_type   = std::vector<std::pair<Token, i64>>;
    using string_vec = std::vector<string>;

    ParseError(Token     &tok,
               float      error_code,
               string_vec fix_fmt_args = {},
               string_vec err_fmt_args = {},
               fix_type   opt_fixes    = {}) {
        error::Panic(error::create_old_CodeError(&tok,
                                                 error_code,
                                                 std::move(fix_fmt_args),
                                                 std::move(err_fmt_args),
                                                 std::move(opt_fixes)));
    };

    ParseError()          = default;
    virtual ~ParseError() = default;

    ParseError(const ParseError &other)                = default;
    ParseError(ParseError &&other) noexcept            = default;
    ParseError &operator=(const ParseError &other)     = default;
    ParseError &operator=(ParseError &&other) noexcept = default;
};

using ParseResult = std::expected<u64, ParseError>;  // len of tokens to skip | recoverable error

BASE_NODE_TYPE(ASTBase);
namespace node {
    DERIVED_NODE_TYPE(Statement);
    DERIVED_NODE_TYPE(Expression);
    DERIVED_NODE_TYPE(Declaration);
    DERIVED_NODE_TYPE(Type);
}  // namespace node

template <typename T = ASTBase>
using NodePtr = std::shared_ptr<T>;

template <typename T = ASTBase>
using NodeList = std::vector<NodePtr<T>>;

template <typename T = ASTBase>
using Slice = const std::reference_wrapper<NodeList<T>>;

template <typename T, typename U>
constexpr std::shared_ptr<T> make_node(U tokens) {
    static_assert(std::is_base_of_v<ASTBase, T>, "T must be derived from ASTBase");
    return std::make_shared<T>(tokens);
}

namespace node {

    /**
     * @brief Retrieves a single expression node from the given token list.
     *
     * This function returns a single expression node such as a Literal or Function Call.
     * It will never return a more complex node like a BinaryOp.
     *
     * @param tokens The list of tokens to parse.
     * @return NodePtr<Expression> A pointer to the expression node parsed from the tokens.
     */
    std::pair<NodePtr<Expression>, u64> get_expr(token::TokenList tokens);

    /**
     * @brief Parses a valid expression from the given token list up to the specified term.
     *
     * This function attempts to parse a valid expression from the token list until it encounters
     * the specified terminating token or reaches the starting depth.
     *
     * @param tokens The list of tokens to parse.
     * @param start_depth The starting depth to maintain while parsing.
     * @param term The terminating token to stop parsing.
     * @return NodePtr<Expression> A pointer to the parsed expression node.
     */
    std::pair<NodePtr<Expression>, u64> parse_expr(token::TokenList &tokens, u64 start_depth, token::tokens term);

    /**
     * @brief Parses a statement from the given token list.
     *
     * This function parses a single statement from the token list, which could be a control flow
     * statement, assignment, or any other type of statement.
     *
     * @param tokens The list of tokens to parse.
     * @return NodePtr<Statement> A pointer to the parsed statement node.
     */
    std::pair<NodePtr<Statement>, u64> parse_statement(token::TokenList &tokens);

    /**
     * @brief Parses a declaration from the given token list.
     *
     * This function parses a declaration, such as a variable or function declaration, from the
     * token list.
     *
     * @param tokens The list of tokens to parse.
     * @return NodePtr<Declaration> A pointer to the parsed declaration node.
     */
    std::pair<NodePtr<Declaration>, u64> parse_declaration(token::TokenList &tokens);

    /**
     * @brief Parses a type from the given token list.
     *
     * This function parses a type definition or usage from the token list, which could be a
     * primitive type, custom type, or complex type like a function pointer.
     *
     * @param tokens The list of tokens to parse.
     * @return NodePtr<Type> A pointer to the parsed type node.
     */
    std::pair<NodePtr<Type>, u64> parse_type(token::TokenList &tokens);

}  // namespace node

}  // namespace parser::ast

#endif  // __AST_HH__