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
#ifndef __AST_NODES_HH__
#define __AST_NODES_HH__

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
    TokenListRef source_tokens;

#include "parser/ast/include/ast.hh"

namespace parser::ast::node {
struct Literals final : parser::ast::node::Expression<Literals> {
  public:
    enum class LiteralType : u8 {
        INTEGER,
        SCIENTIFIC,
        FLOAT,
        STRING,
        BOOL,
        CHAR,
        NONE  // null
    };
    AST_NODE_METHODS(Literals)
};

struct BinaryOp final : parser::ast::node::Expression<BinaryOp> { // 1 + 1
    AST_NODE_METHODS(BinaryOp)
};

struct UnaryOp final : parser::ast::node::Expression<UnaryOp> { // -1
    AST_NODE_METHODS(UnaryOp)
};

struct SuffixOp final : parser::ast::node::Expression<SuffixOp> { // arr[...] | arr|...|
    AST_NODE_METHODS(SuffixOp)
};

struct FunctionCall final : parser::ast::node::Expression<FunctionCall> {
    AST_NODE_METHODS(FunctionCall)
};

struct MemberAccess final : parser::ast::node::Expression<MemberAccess> {
    AST_NODE_METHODS(MemberAccess)
};

struct PtrAccess final : parser::ast::node::Expression<PtrAccess> {
    AST_NODE_METHODS(PtrAccess)
};

struct ScopeAccess final : parser::ast::node::Expression<ScopeAccess> {
    AST_NODE_METHODS(ScopeAccess)
};

struct InlineStatement final : parser::ast::node::Expression<InlineStatement> {
    AST_NODE_METHODS(InlineStatement)
};

parser::ast::node::Expression<void> parse_expr(TokenListRef tokens);
}  // namespace parser::ast::node

#endif  // __AST_NODES_HH__