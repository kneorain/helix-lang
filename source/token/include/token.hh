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

#ifndef __TOKEN_HH__
#define __TOKEN_HH__

#include <iostream>
#include <string>
#include <string_view>

#include "core/types/hx_ints"
#include "core/utils/josnify.hh"
#include "token/include/generate.hh"

namespace token {
/*
Token(u64 line, u64 column, u64 length, u64 offset, std::string_view value,
          const std::string &filename, std::string_view token_kind = "");
*/
struct Token {
  private:
    u32         line{};     ///< Line number where the token is located
    u32         column{};   ///< Column number where the token starts
    u32         len{};      ///< Length of the token
    u32         _offset{};  ///< Offset from the beginning of the file
    tokens      kind{};     ///< Kind of the token
    std::string val;        ///< String value of the token
    std::string filename;   ///< Name of the file

  public:
    Token(u64                line,
          u64                column,
          u64                length,
          u64                offset,
          std::string_view   value,
          const std::string &filename,
          std::string_view   token_kind = "");
    Token(const Token &other);
    Token &operator=(const Token &other);
    Token(Token &&other) noexcept;
    Token &operator=(Token &&other) noexcept;
    Token &operator=(const std::string &other);
    Token();

    explicit Token(tokens token_type, const std::string &filename, std::string value = "");
    ~Token();

    /* ====-------------------------- getters ---------------------------==== */
    u32         line_number() const;
    u32         column_number() const;
    u32         length() const;
    u32         offset() const;
    tokens      token_kind() const;
    std::string value() const;
    std::string token_kind_repr() const;
    std::string file_name() const;
    std::string to_string() const;
    TO_JSON_SIGNATURE {
        jsonify::Jsonify token_json("Token", depth);

        token_json.add("length", len)
                .add("kind", token_kind_repr())
                .add("value", val);
            
        token_json.create_sub("loc")
                .add("filename", filename)
                .add("line_number", line)
                .add("column_number", column)
                .add("offset", _offset);

        TO_JSON_RETURN(token_json);
    }

    bool          operator==(const Token &rhs) const;
    bool          operator==(const tokens &rhs) const;
    std::ostream &operator<<(std::ostream &os) const;
    auto          operator+(const string &str) {
        this->val += str;
        return *this;
    }

    /* ====-------------------------- setters ---------------------------==== */

    void set_file_name(const std::string &file_name);
    void set_value(const std::string &other);
};

inline auto bare_token(tokens token_type, std::string value = "") {
    return Token(token_type,
                 "",
                 value.empty() ? std::string(tokens_map.at(token_type).value()) : std::move(value));
}

}  // namespace token

inline token::Token operator+(const std::string &lhs, token::Token rhs) {
    rhs.set_value(lhs + rhs.value());
    return rhs;
}

inline token::Token operator+(token::Token &lhs, const std::string &rhs) {
    lhs.set_value(lhs.value() + rhs);
    return lhs;
}

#endif  // __TOKEN_HH__