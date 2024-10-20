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

#ifndef __AST_BASE_EXPRESSION_H__
#define __AST_BASE_EXPRESSION_H__

#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/private/AST_generate.hh"
#include "parser/ast/include/types/AST_types.hh"

__AST_NODE_BEGIN {
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
        AST_CLASS_BASE(Expression, EXPRS) {};

        ParseResult<> parse_primary();
        template <typename T, typename... Args>
        ParseResult<T> parse(Args &&...args) { /* NOLINT */
            if constexpr (std ::is_same_v<T, LiteralExpr>) {
                return parse_LiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, BinaryExpr>) {
                return parse_BinaryExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, UnaryExpr>) {
                return parse_UnaryExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, IdentExpr>) {
                return parse_IdentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, NamedArgumentExpr>) {
                return parse_NamedArgumentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArgumentExpr>) {
                return parse_ArgumentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArgumentListExpr>) {
                return parse_ArgumentListExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, GenericInvokeExpr>) {
                return parse_GenericInvokeExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, GenericInvokePathExpr>) {
                return parse_GenericInvokePathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ScopePathExpr>) {
                return parse_ScopePathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, DotPathExpr>) {
                return parse_DotPathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArrayAccessExpr>) {
                return parse_ArrayAccessExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, PathExpr>) {
                return parse_PathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, FunctionCallExpr>) {
                return parse_FunctionCallExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArrayLiteralExpr>) {
                return parse_ArrayLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TupleLiteralExpr>) {
                return parse_TupleLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, SetLiteralExpr>) {
                return parse_SetLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, MapPairExpr>) {
                return parse_MapPairExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, MapLiteralExpr>) {
                return parse_MapLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ObjInitExpr>) {
                return parse_ObjInitExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, LambdaExpr>) {
                return parse_LambdaExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TernaryExpr>) {
                return parse_TernaryExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ParenthesizedExpr>) {
                return parse_ParenthesizedExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, CastExpr>) {
                return parse_CastExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, InstOfExpr>) {
                return parse_InstOfExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, Type>) {
                return parse_Type(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, AsyncThreading>) {
                return parse_AsyncThreading(std ::forward<Args>(args)...);
            }
        };

      private:
        ParseResult<NamedArgumentExpr>     parse_NamedArgumentExpr(bool is_anonymous = false);
        ParseResult<PathExpr>              parse_PathExpr(ParseResult<> simple_path = nullptr);
        ParseResult<UnaryExpr>             parse_UnaryExpr(ParseResult<> lhs = nullptr, bool in_type = false);
        ParseResult<BinaryExpr>            parse_BinaryExpr(ParseResult<> lhs, int min_precedence);
        ParseResult<LiteralExpr>           parse_LiteralExpr(ParseResult<> str_concat = nullptr);
        ParseResult<ArgumentExpr>          parse_ArgumentExpr();
        ParseResult<DotPathExpr>           parse_DotPathExpr(ParseResult<> lhs = nullptr);
        ParseResult<IdentExpr>             parse_IdentExpr();
        ParseResult<ScopePathExpr>         parse_ScopePathExpr(ParseResult<> lhs = nullptr, bool global_scope = false);
        ParseResult<ArrayAccessExpr>       parse_ArrayAccessExpr(ParseResult<> lhs = nullptr);
        ParseResult<ArgumentListExpr>      parse_ArgumentListExpr();
        ParseResult<GenericInvokeExpr>     parse_GenericInvokeExpr();
        ParseResult<GenericInvokePathExpr> parse_GenericInvokePathExpr();
        ParseResult<ArrayLiteralExpr>      parse_ArrayLiteralExpr();
        ParseResult<TupleLiteralExpr>
        parse_TupleLiteralExpr(ParseResult<> starting_element = nullptr);
        ParseResult<SetLiteralExpr>    parse_SetLiteralExpr(ParseResult<> starting_value);
        ParseResult<MapPairExpr>       parse_MapPairExpr();
        ParseResult<MapLiteralExpr>    parse_MapLiteralExpr(ParseResult<> starting_value);
        ParseResult<ObjInitExpr>       parse_ObjInitExpr(bool          skip_start_brace = false,
                                                         ParseResult<> obj_path         = nullptr);
        ParseResult<LambdaExpr>        parse_LambdaExpr();
        ParseResult<TernaryExpr>       parse_TernaryExpr(ParseResult<> lhs = nullptr);
        ParseResult<ParenthesizedExpr> parse_ParenthesizedExpr(ParseResult<> expr = nullptr);
        ParseResult<CastExpr>          parse_CastExpr(ParseResult<> lhs);
        ParseResult<InstOfExpr>        parse_InstOfExpr(ParseResult<> lhs = nullptr);
        ParseResult<Type>              parse_Type();
        ParseResult<AsyncThreading>    parse_AsyncThreading();
        ParseResult<FunctionCallExpr>  parse_FunctionCallExpr(ParseResult<> lhs = nullptr, NodeT<GenericInvokeExpr> generic_invoke = nullptr);
    };
}  //  namespace __AST_NODE_BEGIN

#endif  // __AST_BASE_EXPRESSION_H__