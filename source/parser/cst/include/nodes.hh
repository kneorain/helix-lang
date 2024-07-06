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
#ifndef __CST_NODES_HH__
#define __CST_NODES_HH__

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

#include "core/error/error.hh"
#include "core/utils/hx_print"
#include "core/utils/josnify.hh"
#include "parser/cst/include/cst.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"
#include "lexer/include/lexer.hh"

#define CST_NODE_METHODS(name)               \
    ~name() = default;                       \
    explicit name(TokenListRef parse_tokens) \
        : tokens(std::move(parse_tokens)){}; \
    name() = default;                        \
    name(name &&) = default;                 \
    name(const name &) = default;            \
    name &operator=(name &&) = default;      \
    name &operator=(const name &) = delete;  \
                                             \
  private:                                   \
    TokenListRef tokens;

namespace parser::cst {
using namespace token;

template <const char quote, const tokens toke_type>
struct Quoted final : CSTBase<Quoted<quote, toke_type>> {
  public:
    enum class Format : char {
        Invalid,
        None = quote,
        Raw = 'r',
        Bytes = 'b',
        Unicode = 'u',
        Formatted = 'f',  // does not work for char....., but it could if someone really wanted too
    };

    CST_NODE_METHODS(Quoted);

  public:
    ParseResult parse() final {
        // Do we have suffixes?
        Token &toke = tokens->front();
        auto toks = tokens;

        if (toke.token_kind() != toke_type) {
            error::Error(error::Line(toke, "Expected a quote literal"));
        };

        // There in no need to check for the token kind as the value of this
        this->format = static_cast<Format>(toke.value().at(0));

        if (format == Format::Invalid) {
            error::Error(error::Line(toke.file_name(), toke.line_number(), toke.column_number(), 1,
                                     "Invalid format specifier"));
        }

        this->value = toke;
        auto siz = this->format == Format::None ? 1 : 2;
        // Remove the format specifier (if it is there) and quotes
        this->value.set_value(toke.value().substr(siz, toke.value().size() - (siz + 1)));
        // - 1 is the actual length
        // - 2 is removing the \0
        // - 3 removes the quote

        auto new_tokens = std::make_shared<TokenList>(this->tokens->slice(0, 1));
        this->tokens.swap(new_tokens);

        // Check for format
        // TODO: make f"hi {name if !name.empty() else "john doe"}" -> string: "hi {}", fmt_args
        // (astExpr): name if !name.empty() else "john doe"
        
        /*Sure, here are the formatting types with examples for both Rust and C++:

### Rust Formatting Types with Examples

#### Alignment
- `:<`  - Left aligns the result
  ```rust
  format!("{:<10}", "left") // "left      "
  ```
- `:>`  - Right aligns the result
  ```rust
  format!("{:>10}", "right") // "     right"
  ```
- `:^`  - Center aligns the result
  ```rust
  format!("{:^10}", "center") // "  center  "
  ```

#### Sign and Space
- `:=`  - Places the sign to the left most position
  ```rust
  format!("{:=+10}", 42) // "+      42"
  ```
- `:+`  - Use a plus sign to indicate if the result is positive or negative
  ```rust
  format!("{:+}", 42) // "+42"
  ```
- `:-`  - Use a minus sign for negative values only
  ```rust
  format!("{:-}", -42) // "-42"
  ```
- `: `  - Use a space to insert an extra space before positive numbers (and a minus sign before negative numbers)
  ```rust
  format!("{: }", 42) // " 42"
  ```

#### Separator
- `:,`  - Use a comma as a thousand separator
  ```rust
  format!("{:,}", 1000000) // "1,000,000"
  ```
- `:_`  - Use an underscore as a thousand separator
  ```rust
  format!("{:_}", 1000000) // "1_000_000"
  ```

#### Base
- `:b`  - Binary format
  ```rust
  format!("{:b}", 42) // "101010"
  ```
- `:o`  - Octal format
  ```rust
  format!("{:o}", 42) // "52"
  ```
- `:x`  - Hex format, lower case
  ```rust
  format!("{:x}", 42) // "2a"
  ```
- `:X`  - Hex format, upper case
  ```rust
  format!("{:X}", 42) // "2A"
  ```

#### Number
- `:d`  - Decimal format
  ```rust
  format!("{:d}", 42) // "42"
  ```
- `:e`  - Scientific format, with a lower case e
  ```rust
  format!("{:e}", 12345.6789) // "1.234568e4"
  ```
- `:E`  - Scientific format, with an upper case E
  ```rust
  format!("{:E}", 12345.6789) // "1.234568E4"
  ```
- `:f`  - Fix point number format
  ```rust
  format!("{:f}", 3.14159) // "3.141590"
  ```
- `:F`  - Fix point number format, in uppercase format (show inf and nan as INF and NAN)
  ```rust
  format!("{:F}", 3.14159) // "3.141590"
  ```
- `:g`  - General format
  ```rust
  format!("{:g}", 12345.6789) // "12345.7"
  ```
- `:G`  - General format (using an upper case E for scientific notations)
  ```rust
  format!("{:G}", 12345.6789) // "12345.7"
  ```
- `:n`  - Number format
  ```rust
  format!("{:n}", 1234567890) // "1234567890"
  ```
- `:%`  - Percentage format
  ```rust
  format!("{:.2%}", 0.1234) // "12.34%"
  ```

#### Other
- `:c`  - Converts the value into the corresponding Unicode character
  ```rust
  format!("{:c}", 65) // "A"
  ```

### C++ Formatting Types with Examples (using `std::format` from C++20)

#### Alignment
- `<`  - Left aligns the result
  ```cpp
  std::format("{:<10}", "left") // "left      "
  ```
- `>`  - Right aligns the result
  ```cpp
  std::format("{:>10}", "right") // "     right"
  ```
- `^`  - Center aligns the result
  ```cpp
  std::format("{:^10}", "center") // "  center  "
  ```

#### Sign and Space
- `=`  - Places the sign to the left most position
  ```cpp
  std::format("{:=+10}", 42) // "+      42"
  ```
- `+`  - Use a plus sign to indicate if the result is positive or negative
  ```cpp
  std::format("{:+}", 42) // "+42"
  ```
- `-`  - Use a minus sign for negative values only
  ```cpp
  std::format("{:-}", -42) // "-42"
  ```
- ` `  - Use a space to insert an extra space before positive numbers (and a minus sign before negative numbers)
  ```cpp
  std::format("{: }", 42) // " 42"
  ```

#### Separator
- `,`  - Use a comma as a thousand separator
  ```cpp
  std::format("{:,}", 1000000) // "1,000,000"
  ```
- `_`  - Use an underscore as a thousand separator
  ```cpp
  std::format("{:_}", 1000000) // "1_000_000"
  ```

#### Base
- `b`  - Binary format
  ```cpp
  std::format("{:b}", 42) // "101010"
  ```
- `o`  - Octal format
  ```cpp
  std::format("{:o}", 42) // "52"
  ```
- `x`  - Hex format, lower case
  ```cpp
  std::format("{:x}", 42) // "2a"
  ```
- `X`  - Hex format, upper case
  ```cpp
  std::format("{:X}", 42) // "2A"
  ```

#### Number
- `d`  - Decimal format
  ```cpp
  std::format("{:d}", 42) // "42"
  ```
- `e`  - Scientific format, with a lower case e
  ```cpp
  std::format("{:e}", 12345.6789) // "1.234568e4"
  ```
- `E`  - Scientific format, with an upper case E
  ```cpp
  std::format("{:E}", 12345.6789) // "1.234568E4"
  ```
- `f`  - Fix point number format
  ```cpp
  std::format("{:f}", 3.14159) // "3.141590"
  ```
- `F`  - Fix point number format, in uppercase format (show inf and nan as INF and NAN)
  ```cpp
  std::format("{:F}", 3.14159) // "3.141590"
  ```
- `g`  - General format
  ```cpp
  std::format("{:g}", 12345.6789) // "12345.7"
  ```
- `G`  - General format (using an upper case E for scientific notations)
  ```cpp
  std::format("{:G}", 12345.6789) // "12345.7"
  ```
- `n`  - Number format
  ```cpp
  std::format("{:n}", 1234567890) // "1234567890"
  ```
- `%`  - Percentage format
  ```cpp
  std::format("{:.2%}", 0.1234) // "12.34%"
  ```

#### Other
- `c`  - Converts the value into the corresponding Unicode character
  ```cpp
  std::format("{:c}", 65) // "A"
  ```

These examples illustrate how to use various formatting options in Rust and C++.
        */


        if (this->format == Format::Formatted) {
            // {var=} // var = value
            // {function_name(var)} // "___value"
            auto tokenized_string = lexer::Lexer(toke).tokenize();
            

            





        }
        

        return std::make_shared<TokenList>(toks->slice(0));
    };

    std::string to_json(u32 depth = 0) const final {

        std::string format;

        switch (this->format) {
            case Format::Raw:
                format = "r";
                break;
            case Format::Bytes:
                format = "b";
                break;
            case Format::Unicode:
                format = "u";
                break;
            case Format::Formatted:
                format = "f";
                break;
            case Format::None:
                break;
        }

        /*
        "Quoted" : {
            "value" : ...

        },
        */

        return jsonify::indent(depth) + "\"Quoted\" : {\n" +
               jsonify::to_json(jsonify::escape(std::string(1, quote)), depth + 1, "openSymbol") +
               ",\n" + jsonify::indent(depth + 1) +
               "\"value\" : " + this->value.to_json(depth + 1, false) + ",\n" +
               jsonify::to_json(jsonify::escape(std::string(1, quote)), depth + 1, "closeSymbol") +
               "\n" + jsonify::indent(depth) + "}\n";
    };

  private:
    Token value;
    Format format = Format::None;
};

struct BoolLiteral final : CSTBase<BoolLiteral> {
  public:
    enum class BoolValue : u8 {
        True = 't',
        False = 'f',
    };

    CST_NODE_METHODS(BoolLiteral);
    ParseResult parse() final;
    std::string to_json(u32 depth = 0) const final;

  private:
    Token value;
    // BoolValue value; // should this be a bool?
};

using StringLiteral = Quoted<'"', tokens::LITERAL_STRING>;
using CharLiteral = Quoted<'\'', tokens::LITERAL_CHAR>;

template <const tokens StartToken, const char StartChar, typename Middle, const char EndChar,
          const tokens EndTokens>
struct Delimited final : CSTBase<Delimited<StartToken, StartChar, Middle, EndChar, EndTokens>> {
  public:
    CST_NODE_METHODS(Delimited);

  public:
    // const char start = StartChar;
    // const char end = EndChar;

    virtual ParseResult parse() final {

        auto toks = tokens;

        // Check if the first token is the start token
        if (tokens->front().token_kind() != StartToken) {
            error::Error(error::Line(tokens->front(), "Expected a start token"));
        };

        toks = std::make_shared<TokenList>(toks->slice(1));

        this->value.emplace(std::make_unique<Middle>(toks));

        ParseResult foo = this->value.value()->parse();

        if (foo.has_value()) {
        } else {
            // TODO: ERROR
        }
        toks = foo.value();

        // Check if the last token is the end token
        if (toks->back().token_kind() != EndTokens) {
            error::Error(error::Line(toks->front(), "Expected an end token"));
        }

        toks = std::make_shared<TokenList>(toks->slice(1));
        auto new_tokens = std::make_shared<TokenList>(this->tokens->slice(0));
        this->tokens.swap(new_tokens);
        return toks;
    }

    std::string to_json(u32 depth = 0) const final {
        /*
        "Delimited" : {
            "value" : ...

        },
        */

        return jsonify::indent(depth) + "\"Delimited\" : {\n" +
               jsonify::to_json(jsonify::escape(std::string(1, StartChar)), depth + 1,
                                "openSymbol") +
               ",\n" + jsonify::indent(depth + 1) + "\"value\" : {\n" +
               this->value.value()->to_json(depth + 2) + jsonify::indent(depth + 1) + "},\n" +
               jsonify::to_json(jsonify::escape(std::string(1, EndChar)), depth + 1,
                                "closeSymbol") +
               "\n" + jsonify::indent(depth) + "}\n";
    }

  private:
    std::optional<std::unique_ptr<Middle>> value;
};

template <CSTNode T>
using Parentheses =
    Delimited<tokens::PUNCTUATION_OPEN_PAREN, '(', T, ')', tokens::PUNCTUATION_CLOSE_PAREN>;

template <CSTNode T>
using CurlyBraces =
    Delimited<tokens::PUNCTUATION_OPEN_BRACE, '{', T, '}', tokens::PUNCTUATION_CLOSE_BRACE>;

template <CSTNode T>
using SquareBrack =
    Delimited<tokens::PUNCTUATION_OPEN_BRACKET, '[', T, ']', tokens::PUNCTUATION_CLOSE_BRACKET>;

template <CSTNode T>
using AngleBrace =
    Delimited<tokens::PUNCTUATION_OPEN_ANGLE, '<', T, '>', tokens::PUNCTUATION_CLOSE_ANGLE>;

template <CSTNode T>
using PipeDelimited =
    Delimited<tokens::OPERATOR_BITWISE_OR, '|', T, '|', tokens::OPERATOR_BITWISE_OR>;

}  // namespace parser::cst

#undef CST_NODE_METHODS
#endif  // __CST_NODES_HH__