//===------------------------------------------ C++ ------------------------------------------====//
//                                                                                                //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).       //
//  You are allowed to use, modify, redistribute, and create derivative works, even for           //
//  commercial purposes, provided that you give appropriate credit, and indicate if changes       //
//   were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/  //
//                                                                                                //
//  SPDX-License-Identifier: CC-BY-4.0                                                            //
//  Copyright (c) 2024 (CC BY 4.0)                                                                //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//
//                                                                                                //
//  This file contains the AST nodes used by the parser and lexer.                                //
//  All the code here is subject to change with refactoring.                                      //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_NODES_H__
#define __AST_NODES_H__

#include <utility>

#include "parser/ast/include/core/AST_core.def"
#include "parser/ast/include/core/AST_types.hh"
#include "token/include/token_list.hh"

// helper macros to generate the correct node structures

#define FORWARD_DECL(name) class name;
#define DECL_PARSE_FUNC(name) ParseResult<name> parse_##name();
#define NODE_ENUM(name) name,
#define VISIT_FUNC(name) virtual void visit(const name &) = 0;

#define GENERATE_MACRO_HELPER(MACRO) EXPRS(MACRO)

#define GENERATE_NODES_ENUM enum class nodes { GENERATE_MACRO_HELPER(NODE_ENUM) };
#define GENERATE_NODES GENERATE_MACRO_HELPER(FORWARD_DECL)
#define GENERATE_PARSE_FUNCS GENERATE_MACRO_HELPER(DECL_PARSE_FUNC)
#define GENERATE_VISIT_FUNCS GENERATE_MACRO_HELPER(VISIT_FUNC)

#define BASE_CORE_METHODS(name)                                                           \
  public:                                                                                 \
    name()                                 = delete;                                      \
    ~name() override                       = default;                                     \
    name(const name &)                     = default;                                     \
    name &operator=(const name &)          = default;                                     \
    name(name &&)                          = default;                                     \
    name               &operator=(name &&) = default;                                     \
    void                accept(Visitor &visitor) const override { visitor.visit(*this); } \
    [[nodiscard]] nodes getNodeType() const override { return nodes::name; }

#define EXPRS(MACRO)                           \
    MACRO(LiteralExpression)                   \
    MACRO(BinaryExpression)                    \
    MACRO(UnaryExpression)                     \
    MACRO(IdentifierExpression)                \
    MACRO(KeywordArgument)                     \
    MACRO(PositionalArgumentExpression)        \
    MACRO(ArgumentExpression)                  \
    MACRO(ArgumentListExpression)              \
    MACRO(GenericPositionalArgumentExpression) \
    MACRO(GenericKeywordArgumentExpression)    \
    MACRO(GenericArgumentExpression)           \
    MACRO(GenericInvocationExpression)         \
    MACRO(PathGenericInvocationExpression)     \
    MACRO(ScopeAccessExpression)               \
    MACRO(DotAccessExpression)                 \
    MACRO(ArrayAccessExpression)               \
    MACRO(PathExpression)                      \
    MACRO(FunctionCallExpression)              \
    MACRO(ArrayLiteralExpression)              \
    MACRO(TupleLiteralExpression)              \
    MACRO(SetLiteralExpression)                \
    MACRO(MapPairExpression)                   \
    MACRO(MapLiteralExpression)                \
    MACRO(ObjectInitializerExpression)         \
    MACRO(LambdaExpression)                    \
    MACRO(TernaryExpression)                   \
    MACRO(ParenthesizedExpression)             \
    MACRO(CastExpression)                      \
    MACRO(InstanceOfExpression)                \
    MACRO(PtrType)                             \
    MACRO(Type)

__AST_BEGIN {
    class Visitor;

    GENERATE_NODES_ENUM;

    class Node {  // ----------------------------------- base node
                  // ----------------------------------- //
      public:
        Node()                                                     = default;
        virtual ~Node()                                            = default;
        virtual void                accept(Visitor &visitor) const = 0;
        [[nodiscard]] virtual nodes getNodeType() const            = 0;

        Node(const Node &)            = default;
        Node &operator=(const Node &) = default;
        Node(Node &&)                 = default;
        Node &operator=(Node &&)      = default;
    };

    GENERATE_NODES;

    class Visitor {
      public:
        Visitor()                           = default;
        Visitor(const Visitor &)            = default;
        Visitor &operator=(const Visitor &) = default;
        Visitor(Visitor &&)                 = default;
        Visitor &operator=(Visitor &&)      = default;
        virtual ~Visitor()                  = default;

        GENERATE_VISIT_FUNCS;
    };

    class LiteralExpression final : public Node {  // := LITERAL
        BASE_CORE_METHODS(LiteralExpression);

        enum class LiteralType {
            Integer,
            Float,
            String,
            Char,
            Boolean,
            Null,
        };

        LiteralExpression(token::Token value, LiteralType type) : value(std::move(value)), type(type) {}

        token::Token value;
        LiteralType  type;
    };

    class BinaryExpression final : public Node {  // := E op E
        BASE_CORE_METHODS(BinaryExpression);

        BinaryExpression(NodeT<> lhs, NodeT<> rhs, token::Token op);

        NodeT<>      lhs;
        token::Token op;
        NodeT<>      rhs;
    };

    class UnaryExpression final : public Node {  // := op E
        BASE_CORE_METHODS(UnaryExpression);

        UnaryExpression(NodeT<> rhs, token::Token op);

        NodeT<>      rhs;
        token::Token op;
    };

    class IdentifierExpression final : public Node {  // := T
        BASE_CORE_METHODS(IdentifierExpression);

        explicit IdentifierExpression(token::Token name);

        token::Token name;
    };

    class KeywordArgument final : public Node {  // := IdentifierExpression '=' E
        BASE_CORE_METHODS(KeywordArgument);

        KeywordArgument(NodeT<IdentifierExpression> name, NodeT<> value);

        NodeT<IdentifierExpression> name;
        NodeT<>                     value;
    };

    class PositionalArgumentExpression final : public Node {  // := E
        BASE_CORE_METHODS(PositionalArgumentExpression);

        explicit PositionalArgumentExpression(NodeT<> value);

        NodeT<> value;
    };

    class ArgumentExpression final
        : public Node {  // := PositionalArgumentExpression | KeywordArgument
        BASE_CORE_METHODS(ArgumentExpression);

        explicit ArgumentExpression(NodeT<> value);

        enum class ArgumentType {
            Positional,
            Keyword,
        };

        NodeT<>      value;
        ArgumentType type;
    };

    class ArgumentListExpression final
        : public Node {  // := '(' ArgumentExpression (',' ArgumentExpression)* ')'
        BASE_CORE_METHODS(ArgumentListExpression);

        explicit ArgumentListExpression(NodeT<> args);
        ArgumentListExpression(NodeT<ArgumentListExpression> args, NodeT<> next);

        NodeV<> args;
    };

    class GenericPositionalArgumentExpression final : public Node {  // := E
        BASE_CORE_METHODS(GenericPositionalArgumentExpression);

        explicit GenericPositionalArgumentExpression(NodeT<> value);

        NodeT<> value;
    };

    class GenericKeywordArgumentExpression final : public Node {  // := IdentifierExpression '=' E
        BASE_CORE_METHODS(GenericKeywordArgumentExpression);

        GenericKeywordArgumentExpression(NodeT<IdentifierExpression> name, NodeT<> value);

        NodeT<IdentifierExpression> name;
        NodeT<>                     value;
    };

    class GenericArgumentExpression final : public Node {  // := GenericPositionalArgumentExpression
                                                           // | GenericKeywordArgumentExpression
        BASE_CORE_METHODS(GenericArgumentExpression);

        explicit GenericArgumentExpression(NodeT<> value);

        enum class ArgumentType {
            Positional,
            Keyword,
        };

        NodeT<> value;
    };

    class GenericInvocationExpression final
        : public Node {  // := '<' GenericArgumentExpression ((',' GenericArgumentExpression)*)? '>'
        BASE_CORE_METHODS(GenericInvocationExpression);

        explicit GenericInvocationExpression(NodeT<> args);
        GenericInvocationExpression(NodeT<GenericInvocationExpression> args, NodeT<> next);

        NodeV<> args;
    };

    class PathGenericInvocationExpression final : public Node {  // := E GenericInvocationExpression
        BASE_CORE_METHODS(PathGenericInvocationExpression);

        PathGenericInvocationExpression(NodeT<> path, NodeT<> generic);

        NodeT<> path;
        NodeT<> generic;
    };

    class ScopeAccessExpression final : public Node {  // := E '::' E
        BASE_CORE_METHODS(ScopeAccessExpression);

        ScopeAccessExpression(NodeT<> lhs, NodeT<> rhs);

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class DotAccessExpression final : public Node {  // := E '.' E
        BASE_CORE_METHODS(DotAccessExpression);

        DotAccessExpression(NodeT<> lhs, NodeT<> rhs);

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class ArrayAccessExpression final : public Node {  // := E '[' E ']'
        BASE_CORE_METHODS(ArrayAccessExpression);

        ArrayAccessExpression(NodeT<> lhs, NodeT<> rhs);

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class PathExpression final : public Node {  // := ScopeAccessExpression | DotAccessExpression
        BASE_CORE_METHODS(PathExpression);

        explicit PathExpression(NodeT<> path);

        enum class PathType {
            Scope,
            Dot,
        };

        NodeT<> path;
    };

    class FunctionCallExpression final
        : public Node {  // := PathExpression GenericInvocationExpression? ArgumentListExpression
        BASE_CORE_METHODS(FunctionCallExpression);

        FunctionCallExpression(NodeT<PathExpression>              path,
                               NodeT<ArgumentListExpression>      args,
                               NodeT<GenericInvocationExpression> generic = nullptr);

        NodeT<PathExpression>              path;
        NodeT<ArgumentListExpression>      args;
        NodeT<GenericInvocationExpression> generic;
    };

    class ArrayLiteralExpression final : public Node {  // := '[' E (',' E)* ']'
        BASE_CORE_METHODS(ArrayLiteralExpression);

        explicit ArrayLiteralExpression(NodeT<> value);
        ArrayLiteralExpression(NodeT<ArrayLiteralExpression> values, NodeT<> next);

        NodeV<> values;
    };

    class TupleLiteralExpression final : public Node {  // := '(' E (',' E)* ')'
        BASE_CORE_METHODS(TupleLiteralExpression);

        explicit TupleLiteralExpression(NodeT<> value);
        TupleLiteralExpression(NodeT<TupleLiteralExpression> values, NodeT<> next);

        NodeV<> values;
    };

    class SetLiteralExpression final : public Node {  // := '{' E (',' E)* '}'
        BASE_CORE_METHODS(SetLiteralExpression);

        explicit SetLiteralExpression(NodeT<> value);
        SetLiteralExpression(NodeT<SetLiteralExpression> values, NodeT<> next);

        NodeV<> values;
    };

    class MapPairExpression final : public Node {  // := E ':' E
        BASE_CORE_METHODS(MapPairExpression);

        MapPairExpression(NodeT<> key, NodeT<> value);

        NodeT<> key;
        NodeT<> value;
    };

    class MapLiteralExpression final : public Node {
        BASE_CORE_METHODS(MapLiteralExpression);

        explicit MapLiteralExpression(NodeT<MapPairExpression> value);
        MapLiteralExpression(NodeT<MapLiteralExpression> values, NodeT<MapPairExpression> next);

        NodeV<MapPairExpression> values;
    };

    class ObjectInitializerExpression final
        : public Node {  // := '{' (KeywordArgument (',' KeywordArgument)*)? '}'
        BASE_CORE_METHODS(ObjectInitializerExpression);

        explicit ObjectInitializerExpression(NodeT<KeywordArgument> args);
        ObjectInitializerExpression(NodeT<ObjectInitializerExpression> args,
                                    NodeT<KeywordArgument>             next);

        NodeV<KeywordArgument> args;
    };

    class LambdaExpression final : public Node {  // TODO
        BASE_CORE_METHODS(LambdaExpression);
    };

    class TernaryExpression final : public Node {  // := (E '?' E ':' E) | (E 'if' E 'else' E)
        BASE_CORE_METHODS(TernaryExpression);

        TernaryExpression(NodeT<> condition, NodeT<> if_true, NodeT<> if_false);

        NodeT<> condition;
        NodeT<> if_true;
        NodeT<> if_false;
    };

    class ParenthesizedExpression final : public Node {  // := '(' E ')'
        BASE_CORE_METHODS(ParenthesizedExpression);

        explicit ParenthesizedExpression(NodeT<> value);

        NodeT<> value;
    };

    class CastExpression final : public Node {  // := E 'as' E
        BASE_CORE_METHODS(CastExpression);

        CastExpression(NodeT<> value, NodeT<> type);

        NodeT<> value;
    };

    class InstanceOfExpression final : public Node {  // := E ('has' | 'derives') E
        BASE_CORE_METHODS(InstanceOfExpression);

        InstanceOfExpression(NodeT<> value, NodeT<> type, token::Token op);

        enum class InstanceType {
            Has,
            Derives,
        };

        NodeT<>      value;
        NodeT<>      type;
        InstanceType op;
    };

    class PtrType final : public Node {  // := ((E '*') | (('*' E)) | ((E '&') | ('&' E))
        BASE_CORE_METHODS(PtrType);

        PtrType(NodeT<> value, token::Token op);

        enum class PtrTypeType {
            Pointer,
            Reference,
        };

        NodeT<>     value;
        PtrTypeType type;
    };

    class Type final : public Node {  // := IdentifierExpression | PtrType
        BASE_CORE_METHODS(Type);

        explicit Type(NodeT<> value);

        NodeT<> value;

        enum class TypeType {
            Identifier,
            Pointer,
            Reference,
        };
    };

    /*
     *  Expression class
     *
     *  This class is responsible for parsing the expression grammar.
     *  It is a recursive descent parser that uses the token list
     *  to parse the expression grammar.
     *
     *  (its very bad quality but will be improved when written in helix)
     *
     *  usage:
     *     Expression expr(tokens);
     *     NodeT<> node = expr.parse();
     *
     *     // or
     *
     *     NodeT<...> node = expr.parse<...>();
     */
    class Expression {  // THIS IS NOT A NODE
      public:
        explicit Expression(token::TokenList *tokens)
            : tokens(tokens){};
        Expression()                              = default;
        Expression(const Expression &)            = default;
        Expression &operator=(const Expression &) = default;
        Expression(Expression &&)                 = default;
        Expression &operator=(Expression &&)      = default;
        virtual ~Expression()                     = default;

        ParseResult<LiteralExpression>            parse_LiteralExpression();
        ParseResult<BinaryExpression>             parse_BinaryExpression();
        ParseResult<UnaryExpression>              parse_UnaryExpression();
        ParseResult<IdentifierExpression>         parse_IdentifierExpression();
        ParseResult<KeywordArgument>              parse_KeywordArgument();
        ParseResult<PositionalArgumentExpression> parse_PositionalArgumentExpression();
        ParseResult<ArgumentExpression>           parse_ArgumentExpression();
        ParseResult<ArgumentListExpression>       parse_ArgumentListExpression();
        ParseResult<GenericPositionalArgumentExpression>
                                                      parse_GenericPositionalArgumentExpression();
        ParseResult<GenericKeywordArgumentExpression> parse_GenericKeywordArgumentExpression();
        ParseResult<GenericArgumentExpression>        parse_GenericArgumentExpression();
        ParseResult<GenericInvocationExpression>      parse_GenericInvocationExpression();
        ParseResult<PathGenericInvocationExpression>  parse_PathGenericInvocationExpression();
        ParseResult<ScopeAccessExpression>            parse_ScopeAccessExpression();
        ParseResult<DotAccessExpression>              parse_DotAccessExpression();
        ParseResult<ArrayAccessExpression>            parse_ArrayAccessExpression();
        ParseResult<PathExpression>                   parse_PathExpression();
        ParseResult<FunctionCallExpression>           parse_FunctionCallExpression();
        ParseResult<ArrayLiteralExpression>           parse_ArrayLiteralExpression();
        ParseResult<TupleLiteralExpression>           parse_TupleLiteralExpression();
        ParseResult<SetLiteralExpression>             parse_SetLiteralExpression();
        ParseResult<MapPairExpression>                parse_MapPairExpression();
        ParseResult<MapLiteralExpression>             parse_MapLiteralExpression();
        ParseResult<ObjectInitializerExpression>      parse_ObjectInitializerExpression();
        ParseResult<LambdaExpression>                 parse_LambdaExpression();
        ParseResult<TernaryExpression>                parse_TernaryExpression();
        ParseResult<ParenthesizedExpression>          parse_ParenthesizedExpression();
        ParseResult<CastExpression>                   parse_CastExpression();
        ParseResult<InstanceOfExpression>             parse_InstanceOfExpression();
        ParseResult<PtrType>                          parse_PtrType();
        ParseResult<Type>                             parse_Type();

        template <typename T>
        NodeT<T> parse() {
            return std::dynamic_pointer_cast<T>(parse());
        }
        NodeT<> parse();

      private:
        token::TokenList *tokens = nullptr;
    };

    // class CreateIdentifiers_HelperNode;
    // class ForPyStatementCore;
    // class ForCStatementCore;
    // class ForStatement;
    // class WhileStatement;
    // class ElseStatement;
    // class IfStatement;
    // class SwitchCaseStatement;
    // class SwitchStatement;
    // class YieldStatement;
    // class AliasStatement;
    // class SingleImportStatement;
    // class GroupedStatement;
    // class ImportStatement;
    // class ReturnStatement;
    // class BreakStatement;
    // class ContinueStatement;
    // class ExpressionStatement;
    // class Statement;

}  // namespace __AST_BEGIN

#endif  // __AST_NODES_H__