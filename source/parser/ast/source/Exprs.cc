//===---------------------------------------------------- C++ ----------------------------------------------------====//
//                                                                                                                    //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).                           //
//  You are allowed to use, modify, redistribute, and create derivative works, even for                               //
//  commercial purposes, provided that you give appropriate credit, and indicate if changes                           //
//   were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/                      //
//                                                                                                                    //
//  SPDX-License-Identifier: CC-BY-4.0                                                                                //
//  Copyright (c) 2024 (CC BY 4.0)                                                                                    //
//                                                                                                                    //
//====------------------------------------------------------------------------------------------------------------====//
//                                                                                                                    //
//  @file Expr.cc                                                                                                     //
//  @brief All of expression parsing is contained in this file.                                                       //
//                                                                                                                    //
//  This file contains the entire logic for parsing expressions using a recursive descent parser.                     //
//  The parser adheres to an LL(1) grammar, which means it processes the input left-to-right and                      //
//  constructs the leftmost derivation using one token of lookahead.                                                  //
//                                                                                                                    //
//  Below is a simplified grammar that outlines the expressions handled by this parser:                               //
//                                                                                                                    //
//  LiteralExpression                   := LITERAL                                                                    //
//  BinaryExpression /* FIXME */        := E op E                                                                     //
//  UnaryExpression                     := op E                                                                       //
//  IdentifierExpression                := T                                                                          //
//  KeywordArgument                     := IdentifierExpression '=' E                                                 //
//  PositionalArgumentExpression        := E                                                                          //
//  ArgumentExpression                  := KeywordArgument | PositionalArgumentExpression                             //
//  ArgumentListExpression              := '(' ArgumentExpression (',' ArgumentExpression)* ')'                       //
//  GenericPositionalArgumentExpression := E                                                                          //
//  GenericKeywordArgumentExpression    := IdentifierExpression '=' E                                                 //
//  GenericArgumentExpression           := GenericPositionalArgumentExpression                                        //
//  GenericInvocationExpression         := '<' GenericArgumentExpression ((',' GenericArgumentExpression)*)? '>'      //
//  PathGenericInvocationExpression     := E GenericInvocationExpression                                              //
//  ScopeAccessExpression               := E '::' E                                                                   //
//  DotAccessExpression                 := E '.' E                                                                    //
//  ArrayAccessExpression               := E '[' E ']'                                                                //
//  PathExpression                      := ScopeAccessExpression | DotAccessExpression                                //
//  FunctionCallExpression              := PathExpression GenericInvocationExpression? ArgumentListExpression         //
//  ArrayLiteralExpression              := '[' E (',' E)* ']'                                                         //
//  TupleLiteralExpression              := '(' E (',' E)* ')'                                                         //
//  SetLiteralExpression                := '{' E (',' E)* '}'                                                         //
//  MapPairExpression                   := E ':' E                                                                    //
//  ObjectInitializerExpression         := '{' (KeywordArgument (',' KeywordArgument)*)? '}'                          //
//  LambdaExpression                    := TODO                                                                       //
//  TernaryExpression                   := (E '?' E ':' E) | (E 'if' E 'else' E)                                      //
//  ParenthesizedExpression             := '(' E ')'                                                                  //
//  CastExpression                      := E 'as' E                                                                   //
//  InstanceOfExpression                := E ('has' | 'derives') E                                                    //
//  PtrType                             := ((E '*') | (('*' E)) | ((E '&') | ('&' E)))                                //
//  Type                                := IdentifierExpression | PtrType                                             //
//                                                                                                                    //
//===-------------------------------------------------------------------------------------------------------------====//

#include <exception>
#include <expected>

#include "parser/ast/include/core/AST_core.def"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/core/AST_types.hh"
#include "parser/ast/include/core/Token_case_types.def"

__AST_BEGIN {
    ParseResult<LiteralExpression> Expression::parse_LiteralExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }

        token::Token tok = tokens->front();
        tokens->pop_front();

        LiteralExpression::LiteralType type{};

        switch (tok.token_kind()) {
            case token::tokens::LITERAL_INTEGER:
                type = LiteralExpression::LiteralType::Integer;
                break;
            case token::tokens::LITERAL_FLOATING_POINT:
                type = LiteralExpression::LiteralType::Float;
                break;
            case token::tokens::LITERAL_STRING:
                type = LiteralExpression::LiteralType::String;
                break;
            case token::tokens::LITERAL_CHAR:
                type = LiteralExpression::LiteralType::Char;
                break;
            case token::tokens::LITERAL_TRUE:
            case token::tokens::LITERAL_FALSE:
                type = LiteralExpression::LiteralType::Boolean;
                break;
            case token::tokens::LITERAL_NULL:
                type = LiteralExpression::LiteralType::Null;
                break;
            default:
                return std::unexpected(ParseError(tok, "expected a literal."));
        }

        return make_node<LiteralExpression>(tok, type);
    }

    ParseResult<BinaryExpression> Expression::parse_BinaryExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<UnaryExpression> Expression::parse_UnaryExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<IdentifierExpression> Expression::parse_IdentifierExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<KeywordArgument> Expression::parse_KeywordArgument() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<PositionalArgumentExpression> Expression::parse_PositionalArgumentExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ArgumentExpression> Expression::parse_ArgumentExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ArgumentListExpression> Expression::parse_ArgumentListExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<GenericPositionalArgumentExpression>
    Expression::parse_GenericPositionalArgumentExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<GenericKeywordArgumentExpression>
    Expression::parse_GenericKeywordArgumentExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<GenericArgumentExpression> Expression::parse_GenericArgumentExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<GenericInvocationExpression> Expression::parse_GenericInvocationExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<PathGenericInvocationExpression>
    Expression::parse_PathGenericInvocationExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ScopeAccessExpression> Expression::parse_ScopeAccessExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<DotAccessExpression> Expression::parse_DotAccessExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ArrayAccessExpression> Expression::parse_ArrayAccessExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<PathExpression> Expression::parse_PathExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<FunctionCallExpression> Expression::parse_FunctionCallExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ArrayLiteralExpression> Expression::parse_ArrayLiteralExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<TupleLiteralExpression> Expression::parse_TupleLiteralExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<SetLiteralExpression> Expression::parse_SetLiteralExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<MapPairExpression> Expression::parse_MapPairExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<MapLiteralExpression> Expression::parse_MapLiteralExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ObjectInitializerExpression> Expression::parse_ObjectInitializerExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<LambdaExpression> Expression::parse_LambdaExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<TernaryExpression> Expression::parse_TernaryExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<ParenthesizedExpression> Expression::parse_ParenthesizedExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<CastExpression> Expression::parse_CastExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<InstanceOfExpression> Expression::parse_InstanceOfExpression() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<PtrType> Expression::parse_PtrType() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    ParseResult<Type> Expression::parse_Type() {
        if (tokens->empty()) {
            return std::unexpected(ParseError("expected a literal expression, but found nothing"));
        }
        
        return std::unexpected(ParseError("not implemented"));
    }

    NodeT<> Expression::parse() {
        if (tokens->empty()) {
            return nullptr;
        }

        token::Token tok = tokens->front();
        tokens->pop_front();

        switch (tok.token_kind()) {
            case IS_LITERAL:
                return parse_LiteralExpression().value();

            default:
                return nullptr;
        }
    }

}  // namespace ast