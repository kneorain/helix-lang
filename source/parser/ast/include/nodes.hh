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

#include <memory>
#include <utility>

#include <parser/ast/include/ast.hh>

namespace parser::ast {
/*                                            Literals                                           */
struct StringLiteral : AstNode<StringLiteral> {  // "Hello, world!" | 'H'
    Token value;
    explicit StringLiteral(Token token);
    AST_NODE_METHODS(StringLiteral);
};

struct BooleanLiteral : AstNode<BooleanLiteral> {  // true | false
    Token value;
    explicit BooleanLiteral(Token token);
    AST_NODE_METHODS(BooleanLiteral);
};

struct NullLiteral : AstNode<NullLiteral> {  // null
    Token value;
    explicit NullLiteral(Token token);
    AST_NODE_METHODS(NullLiteral);
};

struct NumericLiteral : AstNode<NumericLiteral> {  // 1 | 1.0 | 1.0d | 0x1 | 0b1 | 0o1
    Token value;
    explicit NumericLiteral(Token token);
    AST_NODE_METHODS(NumericLiteral);
};

struct GenericArgument : AstNode<GenericArgument> {  // <i32> | <i32, i32>
    AstNodeList<> arguments;
    explicit GenericArgument(AstNodeList<> arguments);
    AST_NODE_METHODS(GenericArgument);
};

struct GenericInvocation
    : AstNode<GenericInvocation> {           // ref<i32> | ptr<i32> | SomeGeneric<i32, i32>
    Token value;                             // ref | ptr | SomeGeneric
    AstNodeList<GenericArgument> arguments;  // <i32> | <i32, i32>
    explicit GenericInvocation(Token token, AstNodeList<GenericArgument> arguments);
    AST_NODE_METHODS(GenericInvocation);
};

/*                                            Statements */
struct Identifier : AstNode<Identifier> {  // a | _a | a1 | _a1
    Token value;
    explicit Identifier(Token token);
    AST_NODE_METHODS(Identifier);
};

struct Variable : AstNode<Variable> {  // a: int<8> | a: i32 = 5 | a: i32? = null
    AstNodeRef<Identifier> name;       // a
    AstNodeRef<GenericArgument> type;  // int<8> | i32
    AstNodePtr value;                  // 5 | null
    bool is_nullable;
    Token reference;  // & | &&
    Token pointer;    // * | *
    explicit Variable(AstNodeRef<Identifier> name, AstNodeRef<GenericArgument> type,
                      AstNodePtr value, bool is_nullable = false, Token reference = Token(),
                      Token pointer = Token());
    AST_NODE_METHODS(Variable);
};

struct Return : AstNode<Return> {  // return 5 | return null
    AstNodePtr value;              // 5 | null
    explicit Return(AstNodePtr value);
    AST_NODE_METHODS(Return);
};

/*                                            Expressions */
struct BinaryOperation : AstNode<BinaryOperation> {  // 2 * (3 + 4) / 5
    Token op;                                        // *
    AstNodePtr left;                                 // 2
    AstNodePtr right;                                // (3 + 4) / 5
    explicit BinaryOperation(Token op, AstNodePtr left, AstNodePtr right);
    AST_NODE_METHODS(BinaryOperation);
};

struct ObjectInvocation
    : AstNode<ObjectInvocation> {  // print("Hello, world!") | print("Hello, world!", end=" ")
                                   // print<str>("Hello, world!")
    Token name;                    // print
    AstNodeList<> arguments;       // ("Hello, world!")
    AstNodeList<GenericArgument> generics;  // <str>
    AstNodeList<> named_arguments;          // (end=" ")
    explicit ObjectInvocation(Token name, AstNodeList<> arguments,
                              AstNodeList<GenericArgument> generics, AstNodeList<> named_arguments);
    AST_NODE_METHODS(ObjectInvocation);
};

struct StructureInvocation
    : AstNode<StructureInvocation> {        // SomeStruct { a: 5, b: 6 } | SomeStruct<i32> { a, b }
    Token name;                             // SomeStruct
    AstNodeList<> arguments;                // { a: 5, b: 6 } | { a, b } - shorthand
    AstNodeList<GenericArgument> generics;  // <i32>
    explicit StructureInvocation(Token name, AstNodeList<> arguments,
                                 AstNodeList<GenericArgument> generics,
                                 AstNodeList<> named_arguments);
    AST_NODE_METHODS(StructureInvocation);
};

struct CommentNode : AstNode<CommentNode> {  // // hello this is a comment
    Token value;                             // "hello this is a comment"
    AstNodePtr owner;  // if this is on top of a function decl this would be the function
    explicit CommentNode(Token value, AstNodePtr owner)
        : value(std::move(value))
        , owner(std::move(owner)) {}

    explicit CommentNode(Token value)
        : value(std::move(value))
        , owner(nullptr) {}

    inline string to_string(u16 depth = 1) const override {
        return get_indent(depth) + "CommentNode(" + '\n' + get_indent(depth + 1) +
               "value: " + value.value() + ",\n" + get_indent(depth + 1) +
               "owner: " + (owner ? owner->to_string(depth + 1) : "nullptr") + '\n' +
               get_indent(depth) + ")";
    }

    inline string node_name() const override { return "CommentNode"; }
    
    ParseResult<CommentNode> validate(TokenList tokens) override {
        // validate
        return std::unexpected(ParseError());
    }
    
    void accept(class Visitor &visitor) override {
        // accepct
    }
};

struct ProgramNode : AstNode<ProgramNode> {
    Token entry_point;  // main | WinMain | wWinMain | DllMain
                        // mainCRTStartup | wmain | kernel_main
    string filename;    // example.hlx - any file (imported) not just the root file in the compile
                        // command
    std::unique_ptr<CommentNode> comment;  // a file comment on the first few lines or after imports
    AstNodeList<> body;                    // all the sub ast nodes
    explicit ProgramNode(Token entry_point, string filename, AstNodeList<> body,
                         std::unique_ptr<CommentNode> comment)
        : entry_point(std::move(entry_point))
        , filename(std::move(filename))
        , comment(std::move(comment))
        , body(std::move(body)) {}

    inline string to_string(u16 depth = 1) const override {
        std::string result = get_indent(depth) + "Program("+ '\n'
                               + get_indent(depth + 1) + "entry_point: " + entry_point.value() + ", " + '\n'
                               + get_indent(depth + 1) + "filename: " + filename + ", " + '\n'
                               + get_indent(depth + 1) + "comment: " + comment->to_string() + ", " + '\n'
                               + get_indent(depth + 1) + "body: [" + '\n';

        for (auto node : body) {
            result += node->to_string(depth + 2) + ",\n";
        }

        if (!body.empty()) {
            result = result.substr(0, result.size() - 2) + "\n";
        }

        result += get_indent(depth + 1) + "]\n" + get_indent(depth) + ")";

        return result;
    }

    inline string node_name() const override { return "ProgramNode"; }
    
    ParseResult<ProgramNode> validate(TokenList tokens) override {
        // validate
        return std::unexpected(ParseError());
    }
    
    void accept(class Visitor &visitor) override {
        // accepct
    }
};
}  // namespace parser::ast

#endif  // __NODES_HH__