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
#include <shared_mutex>
#include <string>
#include <string_view>

#include "core/types/hx_ints"
#include "core/utils/josnify.hh"
#include "token/include/generate.hh"

namespace token {
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
    Token &operator=(const std::string &other);
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
    std::string file_name() const;
    std::string to_string() const;
    TO_JSON_SIGNATURE;

    bool operator==(const Token &rhs) const;
    std::ostream &operator<<(std::ostream &os) const;

    /* ====-------------------------- setters ---------------------------==== */

    void set_file_name(const std::string &file_name);
    void set_value(const std::string &other);
};
}  // namespace token

#endif  // __TOKEN_HH__