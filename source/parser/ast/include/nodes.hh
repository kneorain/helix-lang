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

#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

#include "include/error/error.hh"
#include "parser/ast/include/ast.hh"
#include "token/include/token.hh"

#define AST_NODE_METHODS(name)               \
    virtual ~name() = default;               \
    explicit name(TokenListRef parse_tokens) \
        : tokens(parse_tokens){};            \
    name() = default;                        \
    name(name &&) = default;                 \
    name(const name &) = default;            \
    name &operator=(name &&) = default;      \
    name &operator=(const name &) = delete;  \
                                             \
  private:                                   \
    std::optional<TokenListRef> tokens;

namespace parser::ast {
using namespace token;

// TODO: Rename to StringLiteral

template <const char quote, const tokens toke_type>
struct Quoted : ASTBase<Quoted<quote, toke_type>> {
  public:
    enum class Format : char {
        Invalid,
        None = quote,
        Raw = 'r',
        Bytes = 'b',
        Unicode = 'u',
        Formatted = 'f',  // does not work for char....., but it could if someone really wanted too
    };

    AST_NODE_METHODS(Quoted);

public:
    ParseResult parse() override {
        // Do we have suffixes?
        Token &toke = tokens->get().front();

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

        // Remove the format specifier (if it is there) and quotes
        this->value.set_value(toke.value().substr(
            this->format == Format::None ?  // Check if the there is a format specifier
                1  // Remove the quotes only
                :
                2, // Remove the quotes and the format specifier
            toke.value().size() - 3));
        // - 1 is the actual length
        // - 2 is removing the \0
        // - 3 removes the quote

        print(this->value.value());

        // Check for format
        // TODO: make f"hi {name if !name.empty() else "john doe"}" -> string: "hi {}", fmt_args
        // (astExpr): name if !name.empty() else "john doe"

        return std::nullopt;
    };

    std::string to_string() const override {

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

        return format + quote + this->value.to_string() + quote;
    };

  private:
    Token value;
    Format format = Format::None;
};

struct BoolLiteral : ASTBase<BoolLiteral> {
  public:
    enum class BoolValue : std::uint8_t {
        True = 't',
        False = 'f',
    };

    AST_NODE_METHODS(BoolLiteral);
    ParseResult parse() override;
    std::string to_string() const override;

  private:
    Token value;
    // BoolValue value; // should this be a bool?
};

using StringLiteral = Quoted<'"', tokens::LITERAL_STRING>;
using CharLiteral = Quoted<'\'', tokens::LITERAL_CHAR>;


template < tokens StartToken, const char StartChar, typename Middle, const char EndChar, const tokens EndTokens>
struct Delimited:ASTBase<Delimited<StartToken, StartChar, Middle, EndChar, EndTokens>> {
  public:
    AST_NODE_METHODS(Delimited);
  public:

    Delimited(TokenList parse_tokens) : tokens(parse_tokens) {}

    // const char start = StartChar;
    // const char end = EndChar;
    

    ParseResult parse() {
        // Check if the first token is the start token
        if (tokens->get().front().token_kind() != StartToken) {
            error::Error(error::Line(tokens->get().front(), "Expected a start token"));
        }

        // construct the middle
        // make unique 

        this->value = Middle{tokens};
        
        // Parse the middle
        this->value.get().parse();
        
        // Check if the last token is the end token
        if (tokens->get().back().token_kind() != EndTokens) {
            error::Error(error::Line(tokens->get().back(), "Expected an end token"));
        }
        


        return std::nullopt;
    }

    std::string to_string() const {
        return StartChar + this->value.get().to_string() + EndChar;
    }
    
  private:
    std::optional<Middle> value = std::nullopt;
};

template <ASTNode T>
using Parentheses = Delimited<tokens::PUNCTUATION_OPEN_PAREN,'(', T, ')', tokens::PUNCTUATION_CLOSE_PAREN>;

template <ASTNode T>
using CurlyBraces = Delimited<tokens::PUNCTUATION_OPEN_BRACE, '{', T, '}', tokens::PUNCTUATION_CLOSE_BRACE>;

template <ASTNode T>
using SquareBrack = Delimited<tokens::PUNCTUATION_OPEN_BRACKET, '[', T, ']', tokens::PUNCTUATION_CLOSE_BRACKET>;

template <ASTNode T>
using AngleBrace  = Delimited<tokens::PUNCTUATION_OPEN_ANGLE, '<', T, '>', tokens::PUNCTUATION_CLOSE_ANGLE>;

template <ASTNode T>
using PipeDelimited = Delimited<tokens::OPERATOR_BITWISE_OR, '|', T, '|', tokens::OPERATOR_BITWISE_OR>;





/*
    the following parsed and translated:
        a: i16;                 // i16 a();
        a: i16 = 5;             // i16 a = 5;
        a: i16? = null;         // std::optional<i16> a = std::nullopt;
        a: ptr<i16>;            // i16* a = std::make_unique<i16>();
        b: i16 = ref<a>;        // i16 b = &a;
        c: i16 = ref<ref<a>>;   // i16 c = &&a;

        ref<a> parsed as:
            Generic(
                name: "ref",
                arguments: [
                    Identifier("a")
                ]
            )

        fn add<T: Addable>(a: T, b: T) -> T {
            return a + b;
        }



        add(5, 6) parsed as:
            FunctionCall(
                name: "add",
                arguments: [
                    Number(5),
                    Number(6)
                ]
            )

        fn add<T: Addable>(a: T, b: T) -> T parsed as:
            FunctionDeclaration(
                name: "add",
                arguments: [
                    Variable(name: "a", type: "T"),
                    Variable(name: "b", type: "T")
                ],
                return_type: "T",
                generics: [
                    Generic(
                        name: "add",
                        arguments: [
                            Variable(
                                name: "T",
                                type: "Addable"
                            )
                        ]
                    )
                ],
                body: [
                    Return(
                        value: BinaryOperation(
                            left: Variable("a"),
                            op: '+',
                            right: Variable("b")
                        )
                    )
                ]
            )

*/
}  // namespace parser::ast

#undef AST_NODE_METHODS

#endif  // __NODES_HH__