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

#ifndef __AST_HH__
#define __AST_HH__

#include <cstddef>
#include <cstdlib>
#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "include/error/error.hh"
#include "token/include/token.hh"

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

#define AST_NODE_METHODS(name)                                 \
    inline string to_string(u16 depth = 1) const override;     \
    inline string node_name() const override { return #name; } \
    ParseResult<name> validate(TokenList tokens) override;     \
    void accept(class Visitor &visitor) override

namespace parser::ast {
using std::string;
using std::string_view;
using namespace token;

inline string get_indent(u16 depth) noexcept {
    return string(static_cast<u16>(depth * 4), ' ');
};

template <typename T>
struct AstNode;

struct ParseError {
    ParseError() = default;
    explicit ParseError(const error::Compiler &diagnostic) {
        (error::Error(diagnostic));
        std::exit(1);
    }
};

using AstNodePtr = std::unique_ptr<AstNode<void>>;

template <typename T>
using AstNodeRef = std::shared_ptr<AstNode<T>>;

template <typename T>
using ParseResult = std::expected<AstNodeRef<T>, ParseError>;

template <typename T = void>
using AstNodeList = std::vector<AstNodeRef<T>>;

template <>
struct AstNode<void> {
    AstNode() = default;
    AstNode(const AstNode &) = default;
    AstNode &operator=(const AstNode &) = default;
    AstNode &operator=(AstNode &&) = default;
    AstNode(AstNode &&) = default;
    virtual ~AstNode() = default;

    [[nodiscard]] virtual string to_string(u16 depth = 1) const = 0;
    [[nodiscard]] virtual string node_name() const = 0;

    virtual void accept(class Visitor &visitor) = 0;
    [[noreturn]] void validate(TokenList tokens) {
        ParseError(error::Compiler{
            .file_name = "unknown",
            .message = "void ast node pointer called",
            .fix = "this message would never or should never be seen if it is, report it"});

        std::exit(1);
    };
};

template <typename T>
struct AstNode : public AstNode<void> {
    AstNode() = default;
    AstNode(const AstNode &) = default;
    AstNode &operator=(const AstNode &) = default;
    AstNode &operator=(AstNode &&) = default;
    AstNode(AstNode &&) = default;
    virtual ~AstNode() = default;

    [[nodiscard]] virtual string to_string(u16 depth = 1) const override = 0;
    [[nodiscard]] virtual string node_name() const override = 0;

    virtual ParseResult<T> validate(TokenList tokens) = 0;
    virtual void accept(class Visitor &visitor) override = 0;
};

// struct Variable : AstNode<Variable> { // a | _a | a1 | _a1
//     Location loc;
//     string name;
//
//     explicit Variable(const Token &token)
//         : loc(token)
//         , name(token.value()) {}
//
//     [[nodiscard]] string to_string(u16 depth = 1) const override {
//         return get_indent(depth) + "Variable(" + name + ")";
//     }
//
//     [[nodiscard]] string node_name() const override {
//         return "Variable";
//     }
//
//     ParseResult<Variable> parse(TokenList tokens) override {
//         // Implement parsing logic for Variable node
//         return std::make_unique<Variable>(tokens.current());
//     }
//
//     void accept(Visitor &visitor) override {
//         // Implement visitor pattern logic
//     }
// };

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
#endif  // __AST_HH__