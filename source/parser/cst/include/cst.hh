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
#ifndef __CST_HH__
#define __CST_HH__

#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <expected>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "token/include/token.hh"
#include "token/include/token_list.hh"

/*
something like: 2 * (3 + 4) / 5

would break down to:
BinaryOperation(
    left: BinaryOperation(
        left: Number(2),
        op: '*',
        right: BinaryOperation(
            left: Number(3),
            op: '+',
            right: Number(4)
        )
    ),
    op: '/',
    right: Number(5)
)

or something like: let a: i32 = some_function(5, 6);

would break down to:
VariableDeclaration(
    name: "a",
    type: "i32",
    value: FunctionCall(
        name: "some_function",
        arguments: [
            Number(5),
            Number(6)
        ]
    )
)

or something like: "Hello, world!" if true else "Goodbye, world!"

would break down to:
TernaryOperation(
    condition: Boolean(true),
    if_true: String("Hello, world!"),
    if_false: String("Goodbye, world!")
)

or something like: print("Hello, world!")

would break down to:
FunctionCall(
    name: "print",
    arguments: [
        String("Hello, world!")
    ]
)

or something like:
```
fn this_adds_two_numbers(a: i32, b: i32) -> i32 {
    return a + b;
}

let result: i32 = this_adds_two_numbers(5, 6);
```

would break down to:
FunctionDeclaration(
    name: "this_adds_two_numbers",
    arguments: [
        Argument(name: "a", type: "i32"),
        Argument(name: "b", type: "i32")
    ],
    return_type: "i32",
    body: [
        Return(
            value: BinaryOperation(
                left: Variable("a"),
                op: '+',
                right: Variable("b")
            )
        )
    ]
),
VariableDeclaration(
    name: "result",
    type: "i32",
    value: FunctionCall(
        name: "this_adds_two_numbers",
        arguments: [
            Number(5),
            Number(6)
        ]
    )
)

root node for
```
let a: i32 = 5;
let b: i32 = 6;
print("Hello, world!");
```
is as so:

Program(
    body: [
        VariableDeclaration(
            name: "a",
            type: "i32",
            value: Number(5)
        ),
        VariableDeclaration(
            name: "b",
            type: "i32",
            value: Number(6)
        ),
        FunctionCall(
            name: "print",
            arguments: [
                String("Hello, world!")
            ]
        )
    ],
    file: "example.hlx",
    comments: [
        ...
    ]
)

each node would also contain location information (line, column, etc.) for error reporting and
comments

*/

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

namespace parser::cst {
inline string get_indent(u16 depth) noexcept { return string(static_cast<u16>(depth * 4), ' '); };

struct ParseError {};

// concept AstBase = requires(T t) {
//     { t.parse(token::TokenList) } -> std::expected<std::weak_ptr<ASTBase>, ParseError>;
//     { t.to_string() } -> std::string;
// };

using TokenListRef = std::shared_ptr<token::TokenList>;
using ParseResult = std::expected<TokenListRef, ParseError>;

template <typename T>
struct CSTBase;

template <>
struct CSTBase<void> {
    //     virtual std::expected<std::span<Token>,AstError> parse(std::span<Token> tokens) = 0;
    virtual ~CSTBase() = default;
    CSTBase() = default;
    CSTBase(CSTBase &&) = default;
    CSTBase(const CSTBase &) = default;
    CSTBase &operator=(CSTBase &&) = default;
    CSTBase &operator=(const CSTBase &) = delete;

    [[nodiscard]] virtual ParseResult parse() = 0;
    [[nodiscard]] virtual std::string to_string(u32 depth = 0) const = 0;
};

template <typename T>
struct CSTBase {
    virtual ~CSTBase() = default;
    CSTBase() = default;
    explicit CSTBase(TokenListRef parse_tokens);
    CSTBase(CSTBase &&) = default;
    CSTBase(const CSTBase &) = default;
    CSTBase &operator=(CSTBase &&) = default;
    CSTBase &operator=(const CSTBase &) = delete;

    [[nodiscard]] virtual ParseResult parse() = 0;
    [[nodiscard]] virtual std::string to_string(u32 depth = 0) const = 0;
};

template <typename T>
concept CSTNode = std::derived_from<T, CSTBase<T>>;

template <typename T = void>
using CSTNodePtr = std::unique_ptr<CSTBase<T>>;

template <typename T = void>
using CSTNodeList = std::vector<CSTNodePtr<T>>;

template <typename T = void>
using CSTNodeRef = std::reference_wrapper<CSTBase<T>>;

template <typename T = void>
using CSTSlice = const std::reference_wrapper<CSTNodeList<T>>;

}  // namespace parser::cst
#endif  // __CST_HH__