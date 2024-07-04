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
#ifndef __TOKEN_LIST_HH__
#define __TOKEN_LIST_HH__

#include <optional>
#include <string>
#include <vector>

#include "core/types/hx_ints"
#include "token/include/token.hh"

namespace token {
class TokenList : public std::vector<Token> {
  private:
    std::string filename;
    TokenList(const std::string &filename, std::vector<Token>::const_iterator start,
              std::vector<Token>::const_iterator end);

    class TokenListIter {
      private:
        std::reference_wrapper<TokenList> tokens;
        u64 cursor_position;
        u64 end;

      public:
        explicit TokenListIter(TokenList &token_list, u64 pos = 0)
            : tokens(token_list)
            , cursor_position(pos)
            , end(token_list.size() - 1) {}

        bool operator!=(const TokenListIter &other) const;
        bool operator==(const TokenListIter &other) const;
        Token *operator->();  // TODO: change if a shared ptr is needed
        TokenListIter &operator*();
        std::reference_wrapper<TokenListIter> operator--();
        std::reference_wrapper<TokenListIter> operator++();
        std::reference_wrapper<Token> advance(int n = 1);
        std::reference_wrapper<Token> reverse(int n = 1);
        std::optional<std::reference_wrapper<Token>> peek(int n = 1);
        std::optional<std::reference_wrapper<Token>> peek_back(int n = 1);
        std::reference_wrapper<Token> current();
    };

  public:
    using std::vector<Token>::vector;  // Inherit constructors
    using const_iterator = std::vector<Token>::const_iterator;

    mutable const_iterator it;

    ~TokenList() = default;

    // Default constructor
    TokenList() = default;

    // Copy constructor
    TokenList(const TokenList &other)
        : std::vector<Token>(other)
        , filename(other.filename) {}

    // Copy assignment operator
    TokenList &operator=(const TokenList &other) {
        if (this != &other) {
            std::vector<Token>::operator=(other);
            filename = other.filename;
        }
        return *this;
    }

    // Move constructor
    TokenList(TokenList &&other) noexcept
        : std::vector<Token>(std::move(other))
        , filename(std::move(other.filename)) {}

    // Move assignment operator
    TokenList &operator=(TokenList &&other) noexcept {
        if (this != &other) {
            std::vector<Token>::operator=(std::move(other));
            filename = std::move(other.filename);
        }
        return *this;
    }

    explicit TokenList(std::string filename);

    [[nodiscard]] std::vector<Token>::const_iterator cbegin() const {
        return std::vector<Token>::begin();
    }
    [[nodiscard]] std::vector<Token>::const_iterator cend() const {
        return std::vector<Token>::end();
    }

    [[nodiscard]] std::vector<Token>::const_iterator begin() const {
        return std::vector<Token>::begin();
    }
    [[nodiscard]] std::vector<Token>::const_iterator end() const {
        return std::vector<Token>::end();
    }

    TokenListIter begin() { return TokenListIter(*this); }
    TokenListIter end() { return TokenListIter(*this, this->size() - 1); }

    void remove_left();
    void reset();
    TokenList slice(u64 start, i64 end = -1);

    [[nodiscard]] const std::string &file_name() const;
    void insert_remove(TokenList &tokens, u64 start, u64 end);

    bool operator==(const TokenList &rhs) const;
};

void print_tokens(token::TokenList &tokens);
}  // namespace token

#endif  // __TOKEN_LIST_HH__
