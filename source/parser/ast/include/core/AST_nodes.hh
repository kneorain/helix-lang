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

__AST_NODE_BEGIN {
    class Node {  // base node
      public:
        Node()                                                                    = default;
        virtual ~Node()                                                           = default;
        virtual void                accept(__AST_VISITOR::Visitor &visitor) const = 0;
        [[nodiscard]] virtual nodes getNodeType() const                           = 0;
        [[nodiscard]] virtual std::string getNodeName() const                     = 0;

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
      public:
        explicit Expression(token::TokenList *tokens)
            : tokens(tokens), iter(tokens->begin()) {}
        Expression()                              = default;
        Expression(const Expression &)            = default;
        Expression &operator=(const Expression &) = default;
        Expression(Expression &&)                 = default;
        Expression &operator=(Expression &&)      = default;
        virtual ~Expression()                     = default;

        ParseResult<LiteralExpression>            parse_LiteralExpression();
        ParseResult<BinaryExpression>             parse_BinaryExpression(ParseResult<> lhs, int min_precedence);
        ParseResult<UnaryExpression>              parse_UnaryExpression();
        ParseResult<IdentifierExpression>         parse_IdentifierExpression();
        ParseResult<KeywordArgument>              parse_KeywordArgument();
        ParseResult<ArgumentExpression>           parse_ArgumentExpression();
        ParseResult<ArgumentListExpression>       parse_ArgumentListExpression();
        ParseResult<GenericPositionalArgumentExpression>
                                                      parse_GenericPositionalArgumentExpression();
        ParseResult<GenericKeywordArgumentExpression> parse_GenericKeywordArgumentExpression();
        ParseResult<GenericArgumentExpression>        parse_GenericArgumentExpression();
        ParseResult<GenericInvocationExpression>      parse_GenericInvocationExpression();
        ParseResult<PathGenericInvocationExpression>  parse_PathGenericInvocationExpression();
        ParseResult<ScopeAccessExpression>            parse_ScopeAccessExpression(ParseResult<> lhs = nullptr);
        ParseResult<DotAccessExpression>              parse_DotAccessExpression(ParseResult<> lhs = nullptr);
        ParseResult<ArrayAccessExpression>            parse_ArrayAccessExpression(ParseResult<> lhs = nullptr);
        ParseResult<PathExpression>                   parse_PathExpression(ParseResult<> simple_path);
        ParseResult<FunctionCallExpression>           parse_FunctionCallExpression(ParseResult<> lhs = nullptr, ParseResult<> gens = nullptr);
        ParseResult<ArrayLiteralExpression>           parse_ArrayLiteralExpression();
        ParseResult<TupleLiteralExpression>           parse_TupleLiteralExpression(ParseResult<> starting_element = nullptr);
        ParseResult<SetLiteralExpression>             parse_SetLiteralExpression(ParseResult<> starting_value);
        ParseResult<MapPairExpression>                parse_MapPairExpression();
        ParseResult<MapLiteralExpression>             parse_MapLiteralExpression(ParseResult<> starting_value);
        ParseResult<ObjectInitializerExpression>      parse_ObjectInitializerExpression(bool skip_start_brace = false);
        ParseResult<LambdaExpression>                 parse_LambdaExpression();
        ParseResult<TernaryExpression>                parse_TernaryExpression(ParseResult<> lhs = nullptr);
        ParseResult<ParenthesizedExpression>          parse_ParenthesizedExpression(ParseResult<> expr = nullptr);
        ParseResult<CastExpression>                   parse_CastExpression();
        ParseResult<InstanceOfExpression>             parse_InstanceOfExpression(ParseResult<> lhs = nullptr);
        ParseResult<PtrType>                          parse_PtrType();
        ParseResult<Type>                             parse_Type();
        ;

        template <typename T>
        ParseResult<T> parse() {
            return std::dynamic_pointer_cast<T>(parse());
        }
        
        ParseResult<> parse();
        ParseResult<> parse_primary();

      private:
        token::TokenList *tokens = nullptr;
        token::TokenList::TokenListIter iter = tokens->begin();
        std::vector<ParseResult<>> parse_stack;
    };
}  // namespace __AST_BEGIN

#endif  // __AST_NODES_H__