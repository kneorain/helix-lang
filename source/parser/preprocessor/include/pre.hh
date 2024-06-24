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
#include <vector>

#include "token/include/token.hh"

namespace parser::preprocessor {
using namespace token;
/* The AST parser dependents resolver would fail without knowing context such as imports,
 * macro expansions and such. thats why we have the preprocessor this would resolve all of that
 * and output a full context aware token list that would contain everything the ast dependents
 * resolver would need to work.
 */
struct processed {
    u32 start{};
    u32 end{};
    token::TokenList tokens;
};

class Preprocessor {
  private:
    std::array<std::string, abi::reserved_map.size()> allowed_abi;
    token::TokenList source_tokens;
    processed processor;
    u32 current_pos{};
    u32 end;

    void parse_import();
    void parse_using();

    void increment_pos(u32 n = 1);

    token::Token current();

    std::optional<token::Token> peek(u32 n = 1);

    std::optional<token::Token> peek_back(u32 n = 1);

    std::optional<token::Token> advance(u32 n = 1);

    std::optional<token::Token> reverse(u32 n = 1);

    inline bool not_end(u32 n = 0) const;

    inline bool not_start(u32 n = 0) const;

  public:
    explicit Preprocessor(token::TokenList &tokens)
        : source_tokens(tokens)
        , end(tokens.size() - 1) {
        std::transform(abi::reserved_map.begin(), abi::reserved_map.end(), allowed_abi.begin(),
                       [](const auto &pair) { return std::string(pair.second); });
    }

    void parse();
};

}  // namespace parser::preprocessor

#endif  // __PRE_H__