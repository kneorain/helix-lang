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

#ifndef __TOKEN_LIST_HH__
#define __TOKEN_LIST_HH__

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "core/types/hx_ints"
#include "core/utils/josnify.hh"
#include "token/include/token.hh"

namespace token {
class TokenList : public std::vector<Token> {
  private:
    std::string filename;

  public:
    using TokenVec = std::vector<Token>;
    using TokenVec::vector;  // Inherit constructors
    using const_iterator = TokenVec::const_iterator;

    /*
    used for doing safe range based for loops while still being able to use iter methods.

    allowing for things like:
    for (auto &tok : tokenList) {
        switch (tok.current().token_kind()) {
            // ...
        }

        if (!tok.peek_back()->token_kind() != tokens::KEYWORD_FUNCTION) {}
    }
    */
    class TokenListIter {
      private:
        std::reference_wrapper<TokenList> tokens;
        u64                               cursor_position;
        u64                               end;

      public:
        explicit TokenListIter(TokenList &token_list, u64 pos = 0)
            : tokens(token_list)
            , cursor_position(pos)
            , end(token_list.size() - 1) {}

        bool           operator!=(const TokenListIter &other) const;
        bool           operator==(const TokenListIter &other) const;
        Token         *operator->();  // TODO: Change if a shared ptr is needed
        TokenListIter &operator*();
        std::reference_wrapper<TokenListIter>        operator--();
        std::reference_wrapper<TokenListIter>        operator++();
        std::reference_wrapper<Token>                advance(const std::int32_t n = 1);
        std::reference_wrapper<Token>                reverse(const std::int32_t n = 1);
        std::optional<std::reference_wrapper<Token>> peek(const std::int32_t n = 1) const;
        std::optional<std::reference_wrapper<Token>> peek_back(const std::int32_t n = 1) const;
        std::reference_wrapper<Token>                current() const;
        TokenList                                    remaining();
    };

    mutable const_iterator it;

    ~TokenList() = default;

    // Default constructor
    TokenList() = default;

    // Copy constructor
    TokenList(const TokenList &other)
        : TokenVec(other)
        , filename(other.filename) {}

    // Copy assignment operator
    TokenList &operator=(const TokenList &other) {
        if (this != &other) {
            TokenVec::operator=(other);
            filename = other.filename;
        }
        return *this;
    }

    // Move constructor
    TokenList(TokenList &&other) noexcept
        : TokenVec(std::move(other))
        , filename(std::move(other.filename)) {}

    // Move assignment operator
    TokenList &operator=(TokenList &&other) noexcept {
        if (this != &other) {
            TokenVec::operator=(std::move(other));
            filename = std::move(other.filename);
        }
        return *this;
    }

    explicit TokenList(std::string filename);
    TokenList(const std::string                 &filename,
              std::vector<Token>::const_iterator start,
              std::vector<Token>::const_iterator end);

    [[nodiscard]] TokenVec::const_iterator cbegin() const { return TokenVec::begin(); }
    [[nodiscard]] TokenVec::const_iterator cend() const { return TokenVec::end(); }

    [[nodiscard]] TokenVec::const_iterator begin() const { return TokenVec::begin(); }
    [[nodiscard]] TokenVec::const_iterator end() const { return TokenVec::end(); }

    inline TokenListIter begin() { return TokenListIter(*this); }
    inline TokenListIter end() { return TokenListIter(*this, this->size()); }

    TokenVec &as_vec() { return *this; };

    void      remove_left();
    void      reset();
    TokenList raw_slice(const std::uint64_t start, const std::int64_t end) const;
    TokenList slice(std::uint64_t start, std::int64_t end = -1);
    std::pair<TokenList, TokenList> split_at(const std::uint64_t i) const;
    TokenList                       pop(const std::uint64_t offset = 1);
    const Token                    &pop_front();
    TO_JSON_SIGNATURE {
        jsonify::Jsonify token_list_json("TokenList", depth);

        token_list_json.add("tokens", std::vector<Token>(*this));

        TO_JSON_RETURN(token_list_json);
    }

    [[nodiscard]] const std::string &file_name() const;
    void                             insert_remove(TokenList &tokens, u64 start, u64 end);

    bool operator==(const TokenList &rhs) const;
};

void print_tokens(token::TokenList &tokens);
}  // namespace token

#endif  // __TOKEN_LIST_HH__
