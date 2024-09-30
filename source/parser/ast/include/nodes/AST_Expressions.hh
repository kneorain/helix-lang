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
    class LiteralExpr final : public Node {  // := LITERAL
        BASE_CORE_METHODS(LiteralExpr);

        enum class LiteralType {
            Integer,
            Float,
            String,
            Char,
            Boolean,
            Null,
        };

        LiteralExpr(token::Token value, LiteralType type)
            : value(std::move(value))
            , type(type) {}

        token::Token value;
        LiteralType  type;
    };

    class BinaryExpr final : public Node {  // := E op E
        BASE_CORE_METHODS(BinaryExpr);

        BinaryExpr(NodeT<> lhs, NodeT<> rhs, token::Token op)
            : lhs(std::move(lhs))
            , op(std::move(op))
            , rhs(std::move(rhs)) {}

        NodeT<>      lhs;
        token::Token op;
        NodeT<>      rhs;
    };

    class UnaryExpr final : public Node {  // := op E
        BASE_CORE_METHODS(UnaryExpr);

        enum class PosType { PreFix, PostFix };

        UnaryExpr(NodeT<> opd, token::Token op, PosType type)
            : opd(std::move(opd))
            , op(std::move(op))
            , type(type) {}

        NodeT<>      opd;
        token::Token op;
        PosType      type = PosType::PreFix;
    };

    class IdentExpr final : public Node {  // := T
        BASE_CORE_METHODS(IdentExpr);

        explicit IdentExpr(token::Token name, bool is_reserved_primitive = false)
            : name(std::move(name))
            , is_reserved_primitive(is_reserved_primitive) {}

        token::Token name;
        bool         is_reserved_primitive = false;
    };

    class NamedArgumentExpr final : public Node {  // := IdentExpr '=' E
        BASE_CORE_METHODS(NamedArgumentExpr);

        NamedArgumentExpr(NodeT<IdentExpr> name, NodeT<> value)
            : name(std::move(name))
            , value(std::move(value)) {}

        NodeT<IdentExpr> name;
        NodeT<>          value;
    };

    class ArgumentExpr final : public Node {  // := PositionalArgumentExpr | NamedArgumentExpr
        BASE_CORE_METHODS(ArgumentExpr);

        explicit ArgumentExpr(NodeT<> value)
            : value(std::move(value))
            , type(ArgumentType::Positional){};

        enum class ArgumentType {
            Positional,
            Keyword,
        };

        NodeT<>      value;
        ArgumentType type;
    };

    class ArgumentListExpr final : public Node {  // := '(' ArgumentExpr (',' ArgumentExpr)* ')'
        BASE_CORE_METHODS(ArgumentListExpr);

        explicit ArgumentListExpr(NodeT<> args) {
            if (args != nullptr) {
                (this->args).emplace_back(std::move(args));
            }
        }

        NodeV<> args;
    };

    class GenericArgumentExpr final : public Node {  // := GenericPositionalArgumentExpr
                                                     // | GenericNamedArgumentExprExpr
        BASE_CORE_METHODS(GenericArgumentExpr);

        explicit GenericArgumentExpr(NodeT<> value);

        enum class ArgumentType {
            Positional,
            Keyword,
        };

        NodeT<> value;
    };

    class GenericInvokeExpr final
        : public Node {  // := '<' GenericArgumentExpr ((',' GenericArgumentExpr)*)? '>'
        BASE_CORE_METHODS(GenericInvokeExpr);

        explicit GenericInvokeExpr(NodeT<> args) {
            if (args != nullptr) {
                (this->args).emplace_back(std::move(args));
            }
        }

        NodeV<> args;
    };

    class GenericInvokePathExpr final : public Node {  // := E GenericInvokeExpr
        BASE_CORE_METHODS(GenericInvokePathExpr);

        GenericInvokePathExpr(NodeT<> path, NodeT<> generic);

        NodeT<> path;
        NodeT<> generic;
    };

    class ScopePathExpr final : public Node {  // := E '::' E
        BASE_CORE_METHODS(ScopePathExpr);

        ScopePathExpr(NodeT<> lhs, NodeT<> rhs)
            : lhs(std::move(lhs))
            , rhs(std::move(rhs)) {}

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class DotPathExpr final : public Node {  // := E '.' E
        BASE_CORE_METHODS(DotPathExpr);

        DotPathExpr(NodeT<> lhs, NodeT<> rhs)
            : lhs(std::move(lhs))
            , rhs(std::move(rhs)) {}

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class ArrayAccessExpr final : public Node {  // := E '[' E ']'
        BASE_CORE_METHODS(ArrayAccessExpr);

        ArrayAccessExpr(NodeT<> lhs, NodeT<> rhs)
            : lhs(std::move(lhs))
            , rhs(std::move(rhs)) {}

        NodeT<> lhs;
        NodeT<> rhs;
    };

    class PathExpr final : public Node {  // := ScopePathExpr | DotPathExpr
        BASE_CORE_METHODS(PathExpr);

        explicit PathExpr(NodeT<> path)
            : path(std::move(path))
            , type(PathType::Identifier) {}

        enum class PathType {
            Scope,
            Dot,
            Identifier,
        };

        NodeT<>  path;
        PathType type;
    };

    class FunctionCallExpr final : public Node {  // := PathExpr GenericInvokeExpr? ArgumentListExpr
        BASE_CORE_METHODS(FunctionCallExpr);

        FunctionCallExpr(NodeT<PathExpr>          path,
                         NodeT<ArgumentListExpr>  args,
                         NodeT<GenericInvokeExpr> generic = nullptr)
            : path(std::move(path))
            , args(std::move(args))
            , generic(std::move(generic)) {}

        NodeT<PathExpr>          path;
        NodeT<ArgumentListExpr>  args;
        NodeT<GenericInvokeExpr> generic;
    };

    class ArrayLiteralExpr final : public Node {  // := '[' E (',' E)* ']'
        BASE_CORE_METHODS(ArrayLiteralExpr);

        explicit ArrayLiteralExpr(NodeT<> value) { values.emplace_back(std::move(value)); }

        NodeV<> values;
    };

    class TupleLiteralExpr final : public Node {  // := '(' E (',' E)* ')'
        BASE_CORE_METHODS(TupleLiteralExpr);

        explicit TupleLiteralExpr(NodeT<> value) { values.emplace_back(std::move(value)); }

        NodeV<> values;
    };

    class SetLiteralExpr final : public Node {  // := '{' E (',' E)* '}'
        BASE_CORE_METHODS(SetLiteralExpr);

        explicit SetLiteralExpr(NodeT<> value) { values.emplace_back(std::move(value)); }

        NodeV<> values;
    };

    class MapPairExpr final : public Node {  // := E ':' E
        BASE_CORE_METHODS(MapPairExpr);

        MapPairExpr(NodeT<> key, NodeT<> value)
            : key(std::move(key))
            , value(std::move(value)) {}

        NodeT<> key;
        NodeT<> value;
    };

    class MapLiteralExpr final : public Node {
        BASE_CORE_METHODS(MapLiteralExpr);

        explicit MapLiteralExpr(NodeT<MapPairExpr> value) { values.emplace_back(std::move(value)); }

        NodeV<MapPairExpr> values;
    };

    class ObjInitExpr final
        : public Node {  // := '{' (NamedArgumentExpr (',' NamedArgumentExpr)*)? '}'
        BASE_CORE_METHODS(ObjInitExpr);

        explicit ObjInitExpr(NodeT<NamedArgumentExpr> args) {
            this->kwargs.emplace_back(std::move(args));
        }

        NodeV<NamedArgumentExpr> kwargs;
        NodeT<>          path;
    };

    class LambdaExpr final : public Node {  // TODO
        BASE_CORE_METHODS(LambdaExpr);

        explicit LambdaExpr(token::Token marker)
            : marker(std::move(marker)) {}

        NodeV<>      args;
        NodeT<>      body;
        NodeT<>      ret;
        token::Token marker;
    };

    class TernaryExpr final : public Node {  // := (E '?' E ':' E) | (E 'if' E 'else' E)
        BASE_CORE_METHODS(TernaryExpr);

        TernaryExpr(NodeT<> condition, NodeT<> if_true, NodeT<> if_false)
            : condition(std::move(condition))
            , if_true(std::move(if_true))
            , if_false(std::move(if_false)) {}

        NodeT<> condition;
        NodeT<> if_true;
        NodeT<> if_false;
    };

    class ParenthesizedExpr final : public Node {  // := '(' E ')'
        BASE_CORE_METHODS(ParenthesizedExpr);

        explicit ParenthesizedExpr(NodeT<> value)
            : value(std::move(value)) {}

        NodeT<> value;
    };

    class CastExpr final : public Node {  // := E 'as' E
        BASE_CORE_METHODS(CastExpr);

        CastExpr(NodeT<> value, NodeT<> type)
            : value(std::move(value))
            , type(std::move(type)) {}

        NodeT<> value;
        NodeT<> type;
    };

    class InstOfExpr final : public Node {  // := E ('has' | 'derives') E
        BASE_CORE_METHODS(InstOfExpr);

        enum class InstanceType {
            Has,
            Derives,
        };

        InstOfExpr(NodeT<> value, NodeT<> type, InstanceType op)
            : value(std::move(value))
            , type(std::move(type))
            , op(op) {}

        NodeT<>      value;
        NodeT<>      type;
        InstanceType op;
    };

    /* DEPRECATED */
    class Type final : public Node {  // := IdentExpr
        BASE_CORE_METHODS(Type);

        enum class TypeType {
            Identifier,
            Pointer,
            Reference,
            Lambda,
        };

        explicit Type(NodeT<> value)
            : value(std::move(value))
            , type(TypeType::Identifier) {}
        explicit Type(NodeT<LambdaExpr> value)
            : value(std::move(value))
            , type(TypeType::Lambda) {}

        NodeT<>  value;
        TypeType type;
    };

    class AsyncThreading final : public Node {  // := IdentExpr
        BASE_CORE_METHODS(AsyncThreading);

        enum class AsyncThreadingType { Await, Spawn, Thread, Other };

        explicit AsyncThreading(NodeT<> value, const token::Token &type)
            : value(std::move(value)) {
            switch (type.token_kind()) {
                case token::KEYWORD_AWAIT:
                    this->type = AsyncThreadingType::Await;
                    break;
                case token::KEYWORD_SPAWN:
                    this->type = AsyncThreadingType::Spawn;
                    break;
                case token::KEYWORD_THREAD:
                    this->type = AsyncThreadingType::Thread;
                    break;
                default:
                    this->type = AsyncThreadingType::Other;
                    break;
            }
        }

        NodeT<>            value;
        AsyncThreadingType type;
    };
}

#endif  // __AST_EXPRESSIONS_H__