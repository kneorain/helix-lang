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

string get_indent(u16 depth) noexcept { return string(static_cast<u16>(depth * 4), ' '); };

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
    AstNode &operator=(AstNode &&) = default;
    AstNode(AstNode &&) = default;
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
        return get_indent(depth) + string(file) + ":" + std::to_string(line) + ":" +
               std::to_string(column) + "[" + std::to_string(offset) + "|" +
               std::to_string(length) + "]";
    }
};

struct Number : AstNode<Number> {  // 1 | 1.0 | 1.0d | 0x1 | 0b1 | 0o1
    Location loc;
    string value;
    tokens type;  // int | float | decimal | hex | binary | octal

    explicit Number(const Token &token)
        : loc(token)
        , value(token.value())
        , type(token.token_kind()) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "Number(" + value + ")";
    }

    [[nodiscard]] string node_name() const override { return "Number"; }

    ParseResult<Number> parse(TokenList tokens) override {
        // Implement parsing logic for Number node
        return std::make_unique<Number>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct Identifier : AstNode<Identifier> {  // a | _a | a1 | _a1
    Location loc;
    string value;

    explicit Identifier(const Token &token)
        : loc(token)
        , value(token.value()) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "Identifier(" + value + ")";
    }

    [[nodiscard]] string node_name() const override { return "Identifier"; }

    ParseResult<Identifier> parse(TokenList tokens) override {
        // Implement parsing logic for Identifier node
        return std::make_unique<Identifier>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct String : AstNode<String> {  // "Hello, world!" | 'H'
    Location loc;
    string value;

    explicit String(const Token &token)
        : loc(token)
        , value(token.value()) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "String(" + value + ")";
    }

    [[nodiscard]] string node_name() const override { return "String"; }

    ParseResult<String> parse(TokenList tokens) override {
        // Implement parsing logic for String node
        return std::make_unique<String>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct Boolean : AstNode<Boolean> {  // true | false
    Location loc;
    string value;

    explicit Boolean(const Token &token)
        : loc(token)
        , value(token.value()) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "Boolean(" + value + ")";
    }

    [[nodiscard]] string node_name() const override { return "Boolean"; }

    ParseResult<Boolean> parse(TokenList tokens) override {
        // Implement parsing logic for Boolean node
        return std::make_unique<Boolean>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct Null : AstNode<Null> {  // null
    Location loc;

    explicit Null(const Token &token)
        : loc(token) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "NULL";
    }

    [[nodiscard]] string node_name() const override { return "Null"; }

    ParseResult<Null> parse(TokenList tokens) override {
        // Implement parsing logic for Null node
        return std::make_unique<Null>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
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

struct Generic : AstNode<Generic> {  // ref<i32> | ptr<i32>
    Location loc;
    string   name;
    AstNodeList<AstNode> arguments;

    explicit Generic(const Token &token)
        : loc(token)
        , name(token.value()) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        string args_str;
        for (const auto &arg : arguments) {
            if (!args_str.empty()) {
                args_str += ", ";
            }
            args_str += arg->to_string(depth + 1);
        }
        return get_indent(depth) + "Generic(" + name + "<" + args_str + ">)";
    }

    [[nodiscard]] string node_name() const override { return "Generic"; }

    ParseResult<Generic> parse(TokenList tokens) override {
        // Implement parsing logic for Generic node
        return std::make_unique<Generic>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct Variable : AstNode<Variable> {  // a: int<8> | a: i32 = 5 | a: i32? = null
    Location loc;
    string   name;
    string   type;
    bool     has_value   = false;
    bool     is_nullable = false;
    AstNodePtr<AstNode> value;
    AstNodePtr<Generic> generics;

    explicit Variable(const Token &token)
        : loc(token)
        , name(token.value()) {
            
        }

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "Variable(" + name + ": " + type + ")";
    }

    [[nodiscard]] string node_name() const override { return "Variable"; }

    ParseResult<Variable> parse(TokenList tokens) override {
        // Implement parsing logic for Variable node
        return std::make_unique<Variable>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct Return : AstNode<Return> {  // return 5 | return null
    Location loc;
    AstNodePtr<AstNode> value;

    explicit Return(const Token &token)
        : loc(token) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "Return(" + (value ? value->to_string(depth + 1) : "null") + ")";
    }

    [[nodiscard]] string node_name() const override { return "Return"; }

    ParseResult<Return> parse(TokenList tokens) override {
        // Implement parsing logic for Return node
        return std::make_unique<Return>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct BinaryOperation : AstNode<BinaryOperation> {  // 2 * (3 + 4) / 5
    Location loc;
    AstNodePtr<AstNode> left;
    string op;
    AstNodePtr<AstNode> right;

    explicit BinaryOperation(const Token &token)
        : loc(token) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "BinaryOperation(" +
               (left ? left->to_string(depth + 1) : "null") + " " + op + " " +
               (right ? right->to_string(depth + 1) : "null") + ")";
    }

    [[nodiscard]] string node_name() const override { return "BinaryOperation"; }

    ParseResult<BinaryOperation> parse(TokenList tokens) override {
        // Implement parsing logic for BinaryOperation node
        return std::make_unique<BinaryOperation>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

struct FunctionCall
    : AstNode<FunctionCall> {  // print("Hello, world!") | print("Hello, world!", end=" ")
    Location loc;
    string name;
    AstNodeList<Argument> arguments;
    AstNodeList<DefaultArgument> default_arguments;

    explicit FunctionCall(const Token &token)
        : loc(token)
        , name(token.value()) {}

    [[nodiscard]] string to_string(u16 depth = 1) const override {
        string args_str;
        for (const auto &arg : arguments) {
            if (!args_str.empty()) {
                args_str += ", ";
            }
            args_str += arg->to_string(depth + 1);
        }
        string defaults_str;
        for (const auto &def_arg : default_arguments) {
            if (!defaults_str.empty()) {
                defaults_str += ", ";
            }
            defaults_str += def_arg->to_string(depth + 1);
        }
        return get_indent(depth) + "FunctionCall(" + name + "(" + args_str + ") defaults(" +
               defaults_str + "))";
    }

    [[nodiscard]] string node_name() const override { return "FunctionCall"; }

    ParseResult<FunctionCall> parse(TokenList tokens) override {
        // Implement parsing logic for FunctionCall node
        return std::make_unique<FunctionCall>(tokens.current());
    }

    void accept(Visitor &visitor) override {
        // Implement visitor pattern logic
    }
};

}  // namespace parser::ast
#endif  // __AST_HH__