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

#ifndef __AST_EXPRESSIONS_H__
#define __AST_EXPRESSIONS_H__


#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/types/AST_types.hh"

__AST_NODE_BEGIN {
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

        BinaryExpression(NodeT<> lhs, NodeT<> rhs, token::Token op) : lhs(std::move(lhs)), op(std::move(op)), rhs(std::move(rhs)) {}

        NodeT<>      lhs;
        token::Token op;
        NodeT<>      rhs;
    };

    class UnaryExpression final : public Node {  // := op E
        BASE_CORE_METHODS(UnaryExpression);

        UnaryExpression(NodeT<> rhs, token::Token op) : rhs(std::move(rhs)), op(std::move(op)) {}

        NodeT<>      rhs;
        token::Token op;
    };

    class IdentifierExpression final : public Node {  // := T
        BASE_CORE_METHODS(IdentifierExpression);

        explicit IdentifierExpression(token::Token name) : name(std::move(name)) {}

        token::Token name;
    };

    class KeywordArgument final : public Node {  // := IdentifierExpression '=' E
        BASE_CORE_METHODS(KeywordArgument);

        KeywordArgument(NodeT<IdentifierExpression> name, NodeT<> value) : name(std::move(name)), value(std::move(value)) {}

        NodeT<IdentifierExpression> name;
        NodeT<>                     value;
    };

    class ArgumentExpression final
        : public Node {  // := PositionalArgumentExpression | KeywordArgument
        BASE_CORE_METHODS(ArgumentExpression);

        explicit ArgumentExpression(NodeT<> value) : value(std::move(value)), type(ArgumentType::Positional) {};

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

        explicit ArgumentListExpression(NodeT<> args) { if (args != nullptr) {(this->args).emplace_back(std::move(args));} }

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

        ScopeAccessExpression(NodeT<> lhs, NodeT<> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class DotAccessExpression final : public Node {  // := E '.' E
        BASE_CORE_METHODS(DotAccessExpression);

        DotAccessExpression(NodeT<> lhs, NodeT<> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class ArrayAccessExpression final : public Node {  // := E '[' E ']'
        BASE_CORE_METHODS(ArrayAccessExpression);

        ArrayAccessExpression(NodeT<> lhs, NodeT<> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class PathExpression final : public Node {  // := ScopeAccessExpression | DotAccessExpression
        BASE_CORE_METHODS(PathExpression);

        explicit PathExpression(NodeT<> path) : path(std::move(path)), type(PathType::Identifier) {}

        enum class PathType {
            Scope,
            Dot,
            Identifier,
        };

        NodeT<>  path;
        PathType type;
    };

    class FunctionCallExpression final
        : public Node {  // := PathExpression GenericInvocationExpression? ArgumentListExpression
        BASE_CORE_METHODS(FunctionCallExpression);

        FunctionCallExpression(NodeT<PathExpression>              path,
                               NodeT<ArgumentListExpression>      args,
                               NodeT<GenericInvocationExpression> generic = nullptr) : path(std::move(path)), args(std::move(args)), generic(std::move(generic)) {}

        NodeT<PathExpression>              path;
        NodeT<ArgumentListExpression>      args;
        NodeT<GenericInvocationExpression> generic;
    };

    class ArrayLiteralExpression final : public Node {  // := '[' E (',' E)* ']'
        BASE_CORE_METHODS(ArrayLiteralExpression);

        explicit ArrayLiteralExpression(NodeT<> value) { values.emplace_back(std::move(value)); }

        NodeV<> values;
    };

    class TupleLiteralExpression final : public Node {  // := '(' E (',' E)* ')'
        BASE_CORE_METHODS(TupleLiteralExpression);

        explicit TupleLiteralExpression(NodeT<> value) { values.emplace_back(std::move(value)); }

        NodeV<> values;
    };

    class SetLiteralExpression final : public Node {  // := '{' E (',' E)* '}'
        BASE_CORE_METHODS(SetLiteralExpression);

        explicit SetLiteralExpression(NodeT<> value) { values.emplace_back(std::move(value)); }

        NodeV<> values;
    };

    class MapPairExpression final : public Node {  // := E ':' E
        BASE_CORE_METHODS(MapPairExpression);

        MapPairExpression(NodeT<> key, NodeT<> value) : key(std::move(key)), value(std::move(value)) {}

        NodeT<> key;
        NodeT<> value;
    };

    class MapLiteralExpression final : public Node {
        BASE_CORE_METHODS(MapLiteralExpression);

        explicit MapLiteralExpression(NodeT<MapPairExpression> value) { values.emplace_back(std::move(value)); }

        NodeV<MapPairExpression> values;
    };

    class ObjectInitializerExpression final
        : public Node {  // := '{' (KeywordArgument (',' KeywordArgument)*)? '}'
        BASE_CORE_METHODS(ObjectInitializerExpression);

        explicit ObjectInitializerExpression(NodeT<KeywordArgument> args) { this->kwargs.emplace_back(std::move(args)); }

        NodeV<KeywordArgument> kwargs;
    };

    class LambdaExpression final : public Node {  // TODO
        BASE_CORE_METHODS(LambdaExpression);
    };

    class TernaryExpression final : public Node {  // := (E '?' E ':' E) | (E 'if' E 'else' E)
        BASE_CORE_METHODS(TernaryExpression);

        TernaryExpression(NodeT<> condition, NodeT<> if_true, NodeT<> if_false) : condition(std::move(condition)), if_true(std::move(if_true)), if_false(std::move(if_false)) {}

        NodeT<> condition;
        NodeT<> if_true;
        NodeT<> if_false;
    };

    class ParenthesizedExpression final : public Node {  // := '(' E ')'
        BASE_CORE_METHODS(ParenthesizedExpression);

        explicit ParenthesizedExpression(NodeT<> value) : value(std::move(value)) {}

        NodeT<> value;
    };

    class CastExpression final : public Node {  // := E 'as' E
        BASE_CORE_METHODS(CastExpression);

        CastExpression(NodeT<> value, NodeT<> type) : value(std::move(value)), type(std::move(type)) {}

        NodeT<> value;
        NodeT<> type;
    };

    
    class InstanceOfExpression final : public Node {  // := E ('has' | 'derives') E
        BASE_CORE_METHODS(InstanceOfExpression);

        enum class InstanceType {
            Has,
            Derives,
        };

        InstanceOfExpression(NodeT<> value, NodeT<> type, InstanceType op) : value(std::move(value)), type(std::move(type)), op(op) {}

        NodeT<>      value;
        NodeT<>      type;
        InstanceType op;
    };


    /* DEPRECATED */
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

    /* DEPRECATED */
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
}

#endif // __AST_EXPRESSIONS_H__