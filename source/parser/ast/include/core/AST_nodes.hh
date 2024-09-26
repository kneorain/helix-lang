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

#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/config/AST_generate.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "parser/ast/include/types/AST_visitor.hh"
#include "token/include/token_list.hh"

#define null nullptr

__AST_NODE_BEGIN {
    class Node {  // base node
      public:
        Node()                                                                          = default;
        virtual ~Node()                                                                 = default;
        virtual void                      accept(__AST_VISITOR::Visitor &visitor) const = 0;
        [[nodiscard]] virtual nodes       getNodeType() const                           = 0;
        [[nodiscard]] virtual std::string getNodeName() const                           = 0;

        Node(const Node &)            = default;
        Node &operator=(const Node &) = default;
        Node(Node &&)                 = default;
        Node &operator=(Node &&)      = default;
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
        template <typename T = Node>
        using p_r = parser::ast::ParseResult<T>;

      public:
        explicit Expression(token::TokenList::TokenListIter &iter)
            : iter(iter) {}
        Expression()                              = delete;
        Expression(const Expression &)            = default;
        Expression &operator=(const Expression &) = default;
        Expression(Expression &&)                 = default;
        Expression &operator=(Expression &&)      = default;
        virtual ~Expression()                     = default;

        p_r<NamedArgumentExpr>     parse_NamedArgumentExpr();
        p_r<PathExpr>              parse_PathExpr(p_r<> simple_path);
        p_r<UnaryExpr>             parse_UnaryExpr();
        p_r<BinaryExpr>            parse_BinaryExpr(p_r<> lhs, int min_precedence);
        p_r<LiteralExpr>           parse_LiteralExpr();
        p_r<ArgumentExpr>          parse_ArgumentExpr();
        p_r<DotPathExpr>           parse_DotPathExpr(p_r<> lhs = null);
        p_r<IdentExpr>             parse_IdentExpr();
        p_r<ScopePathExpr>         parse_ScopePathExpr(p_r<> lhs = null);
        p_r<ArrayAccessExpr>       parse_ArrayAccessExpr(p_r<> lhs = null);
        p_r<ArgumentListExpr>      parse_ArgumentListExpr();
        p_r<GenericArgumentExpr>   parse_GenericArgumentExpr();
        p_r<GenericInvokeExpr>     parse_GenericInvokeExpr();
        p_r<GenericInvokePathExpr> parse_GenericInvokePathExpr();
        p_r<ArrayLiteralExpr>      parse_ArrayLiteralExpr();
        p_r<TupleLiteralExpr>      parse_TupleLiteralExpr(p_r<> starting_element = null);
        p_r<SetLiteralExpr>        parse_SetLiteralExpr(p_r<> starting_value);
        p_r<MapPairExpr>           parse_MapPairExpr();
        p_r<MapLiteralExpr>        parse_MapLiteralExpr(p_r<> starting_value);
        p_r<ObjInitExpr>           parse_ObjInitExpr(bool skip_start_brace = false);
        p_r<LambdaExpr>            parse_LambdaExpr();
        p_r<TernaryExpr>           parse_TernaryExpr(p_r<> lhs = null);
        p_r<ParenthesizedExpr>     parse_ParenthesizedExpr(p_r<> expr = null);
        p_r<CastExpr>              parse_CastExpr(p_r<> lhs);
        p_r<InstOfExpr>            parse_InstOfExpr(p_r<> lhs = null);
        p_r<Type>                  parse_Type();
        p_r<FunctionCallExpr>      parse_FunctionCallExpr(p_r<> lhs = null, p_r<> gens = null);

        template <typename T>
        p_r<T> parse() {
            return std::dynamic_pointer_cast<T>(parse());
        }

        p_r<> parse();
        p_r<> parse_primary();

      private:
        token::TokenList::TokenListIter &iter;
        std::vector<ParseResult<>>       parse_stack;
    };
}  // namespace __AST_BEGIN

#undef null

#endif  // __AST_NODES_H__