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
#ifndef __NODES_HH__
#define __NODES_HH__

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

#include "core/error/error.hh"
#include "core/utils/hx_print"
#include "parser/cst/include/cst.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

#define CST_NODE_METHODS(name)               \
    virtual ~name() = default;               \
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
inline std::string indent(u32 depth = 0) { return std::string(static_cast<u32>(depth * 4), ' '); }

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
    ParseResult parse() override {
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

        return std::make_shared<TokenList>(toks->slice(0));
    };

    std::string to_string(u32 depth = 0) const override {

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

        return indent(depth) + "\"Quoted\" : {\n" + indent(depth + 1) + R"("openSymbol" : ')" +
               std::string(1, quote) + "\',\n" + indent(depth + 1) + "\"value\" : {\n" +
               indent(depth + 2) + "\"token\" : {\n" + indent(depth + 3) + R"("filename" : ")" +
               this->value.file_name() + "\",\n" + indent(depth + 3) +
               "\"line_number\" : " + std::to_string(this->value.line_number()) + ",\n" +
               indent(depth + 3) +
               "\"column_number\" : " + std::to_string(this->value.column_number()) + ",\n" +
               indent(depth + 3) + "\"length\" : " + std::to_string(this->value.length()) + ",\n" +
               indent(depth + 3) + "\"offset\" : " + std::to_string(this->value.offset()) + ",\n" +
               indent(depth + 3) + R"("token_kind" : ")" +
               std::string(this->value.token_kind_repr()) + "\",\n" + indent(depth + 3) +
               R"("value" : ")" + this->value.value() + "\"\n" + indent(depth + 2) + "}\n" +
               indent(depth + 1) + "},\n" + indent(depth + 1) + R"("closeSymbol" : ')" +
               std::string(1, quote) + "\'\n" + indent(depth) + "}\n";
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
    ParseResult parse() override;
    std::string to_string(u32 depth = 0) const override;

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

    virtual ParseResult parse() override final {

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

    std::string to_string(u32 depth = 0) const override {
        /*
        "Delimited" : {
            "value" : ...

        },
        */

        return indent(depth) + "\"Delimited\" : {\n" + indent(depth + 1) + R"("openSymbol" : ')" +
               std::string(1, StartChar) + "\',\n" + indent(depth + 1) + "\"value\" : {\n" +
               this->value.value()->to_string(depth + 2) + indent(depth + 1) + "},\n" +
               indent(depth + 1) + R"("closeSymbol" : ')" + std::string(1, EndChar) + "\'\n" +
               "},\n";
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
#endif  // __NODES_HH__