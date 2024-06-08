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
#include <expected>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../../token/include/token.hh"

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

namespace parser::ast {
using std::string;
using std::string_view;
using namespace token;

string get_indent(u16 depth) noexcept {
    return string(static_cast<u16>(depth * 4), ' ');
};

template <typename T>
struct AstNode;

struct ParseError {
    // TODO: Add more information
};

template <typename T>
using AstNodePtr = std::unique_ptr<AstNode<T>>;

template <typename T>
using ParseResult = std::expected<AstNodePtr<T>, ParseError>;

template <typename T>
using AstNodeList = std::vector<AstNodePtr<T>>;

template <typename T>
struct AstNode {
    AstNode() = default;
    AstNode(const AstNode &) = default;
    AstNode &operator=(const AstNode &) = default;
    AstNode(AstNode &&) = default;
    AstNode &operator=(AstNode &&) = default;
    virtual ~AstNode() = default;

    [[nodiscard]] virtual string to_string(u16 depth = 1) const = 0;
    [[nodiscard]] virtual string node_name() const = 0;

    virtual ParseResult<T> parse(TokenList tokens) = 0;
    virtual void accept(class Visitor &visitor) = 0;
};

struct Location {
    u64 line;
    u64 column;
    u64 offset;
    u64 length;
    string_view file;

    explicit Location(const Token &token) noexcept
        : line(token.line_number())
        , column(token.column_number())
        , offset(token.offset())
        , length(token.length())
        , file(token.file_name()) {}

    // returns a readable string representation of the location
    [[nodiscard]] string to_string(u16 depth = 1) const noexcept {
        // file_name:line:column[offset|length]
        return get_indent(depth)
             + string(file)
             + ":" + std::to_string(line)
             + ":" + std::to_string(column)
             + "[" + std::to_string(offset)
             + "|" + std::to_string(length)
             + "]";
    }
};

// 1, 1.0, 1.0f, 0x1, 0b1, 0o1
struct Number : AstNode<Number> {
    Location loc;
    string value;
    tokens type;  // int | float

    explicit Number(const Token &token)
        : loc(token)
        , value(token.value())
        , type(token.token_kind()) {}
};

struct String : AstNode<String> {
    Location loc;
    string value;
};

struct Boolean : AstNode<Boolean> {
    Location loc;
    string value;
};

}  // namespace parser::ast
#endif  // __AST_HH__