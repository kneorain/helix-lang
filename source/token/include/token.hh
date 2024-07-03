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

#ifndef __TOKEN_HH__
#define __TOKEN_HH__
#include <iostream>
#include <memory>
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <vector>

#include "include/inttypes.hh"
#include "token/include/generate.hh"

namespace token {

/**
 * @brief Structure representing a token in the source code.
 */
struct Token {
  private:
    u32 line{};                     ///< Line number where the token is located
    u32 column{};                   ///< Column number where the token starts
    u32 len{};                      ///< Length of the token
    u32 _offset{};                  ///< Offset from the beginning of the file
    tokens kind{};                  ///< Kind of the token
    std::string val;                ///< String value of the token
    std::string filename;           ///< Name of the file
    mutable std::shared_mutex mtx;  ///< Mutex for thread safety

  public:
    Token(u64 line, u64 column, u64 length, u64 offset, std::string_view value,
          const std::string &filename, std::string_view token_kind = "");
    Token(const Token &other);
    Token &operator=(const Token &other);
    Token(Token &&other) noexcept;
    Token &operator=(Token &&other) noexcept;
    Token();

    explicit Token(tokens token_type, const std::string &filename, std::string value = "");
    ~Token();

    /* ====-------------------------- getters ---------------------------==== */
    u64 line_number() const;
    u64 column_number() const;
    u64 length() const;
    u64 offset() const;
    tokens token_kind() const;
    std::string value() const;
    std::string_view token_kind_repr() const;
    std::string_view file_name() const;

    std::string to_string() const;
    bool operator==(const Token &rhs) const;
    std::ostream &operator<<(std::ostream &os) const;

    /* ====-------------------------- setters ---------------------------==== */

    void set_file_name(const std::string &file_name);
};

/**
 * @brief Class representing a list of tokens.
 */
class TokenList : public std::vector<Token> {
  private:
    std::string filename;
    TokenList(std::string filename, std::vector<Token>::const_iterator start,
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
        std::unique_ptr<Token> operator->();  // TODO: change if a shared ptr is needed
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
    std::optional<Token> yes();
    TokenList() = default;
    explicit TokenList(std::string filename);
    Token next(u32 n = 1) const;
    [[nodiscard]] Token peek(u32 n = 1) const;
    [[nodiscard]] Token current() const;
    TokenListIter begin() { return TokenListIter(*this); }
    TokenListIter end() { return TokenListIter(*this, this->size() - 1); }

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

    [[nodiscard]] Token previous(u32 n = 1) const;
    void remove_left();
    void reset();
    void append(const Token &token);
    TokenList slice(u64 start, u64 end);

    [[nodiscard]] bool reached_end() const;
    [[nodiscard]] std::string file_name() const;
    void insert_remove(TokenList &tokens, u64 start, u64 end);

    bool operator==(const TokenList &rhs) const;
};

/**
 * @brief Prints the tokens in the provided token list.
 *
 * @param tokens Token list to be printed.
 */
void print_tokens(token::TokenList &tokens);

}  // namespace token

#endif  // __TOKEN_HH__