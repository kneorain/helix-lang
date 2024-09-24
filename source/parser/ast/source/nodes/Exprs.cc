//===------------------------------------------ C++ ------------------------------------------====//
//                                                                                                //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0). You   //
//  are allowed to use, modify, redistribute, and create derivative works, even for commercial    //
//  purposes, provided that you give appropriate credit, and indicate if changes                  //
//  were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/   //
//                                                                                                //
//  SPDX-License-Identifier: CC-BY-4.0 // Copyright (c) 2024 (CC BY 4.0)                          //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//
///                                                                                              ///
///  @file Expr.cc                                                                               ///
///  @brief This file contains the entire logic to parse expressions using a recursive descent   ///
///         parser. the parser adheres to an ll(1) grammar, which means it processes the input   ///
///         left-to-right and constructs the leftmost derivation using one token of lookahead.   ///
///                                                                                              ///
///  The parser is implemented using the `parse` method, which is a recursive descent parser     ///
///     that uses the token list to parse the expression grammar.                                ///
///                                                                                              ///
///  @code                                                                                       ///
///  Expression expr(tokens);                                                                    ///
///  ParseResult<> node = expr.parse();                                                          ///
///                                                                                              ///
///  if (node.has_value()) {                                                                     ///
///      NodeT<> ast = node.value();                                                             ///
///  } else {                                                                                    ///
///      std::cerr << node.error().what() << std::endl;                                          ///
///  }                                                                                           ///
///  @endcode                                                                                    ///
///                                                                                              ///
///  By default, the parser will parse the entire expression, but you can also parse a specific  ///
///     expression by calling the specific parse method. or get a specific node by calling parse ///
///     and then passing a template argument to the method.                                      ///
///                                                                                              ///
///  @code                                                                                       ///
///  Expression expr(tokens);                                                                    ///
///  ParseResult<BinaryExpression> node = expr.parse<BinaryExpression>();                        ///
///  @endcode                                                                                    ///
///                                                                                              ///
/// The parser is implemented using the following grammar:                                       ///
///                                                                                              ///
/// STS *         /* node types */                                                               ///
/// [x] * Literal  * L                                                                           ///
/// [x] * Operator * O                                                                           ///
/// [x] * Token    * T                                                                           ///
///                                                                                              ///
///                             /* helper nodes (not supposed to be explicitly used) */          ///
/// [x] * ArgumentListExpression * AL -> ( AE? ( ',' AE )* )                                     ///
/// [x] * NamedArgument        * KA -> '.' ID '=' E                                              ///
/// [x] * ArgumentExpression     * AE -> E | ID '=' E                                            ///
/// [x] * MapPairExpression      * MP -> E ':' E                                                 ///
///                                                                                              ///
///                       /* primary nodes */                                                    ///
/// [x] * UnaryExpression  * UE  -> O    PE                                                      ///
/// [x] * BinaryExpression * BE  -> UE   BE'                                                     ///
///                          BE' -> O UE BE' | ϵ                                                 ///
///                                                                                              ///
///                           /* core single associative */                                      ///
/// [x] * IdentifierExpression * ID -> T                                                         ///
/// [x] * LiteralExpression    * LE -> L                                                         ///
///                                                                                              ///
///                             /* multi-associative */                                          ///
/// [x] * ScopeAccessExpression  * SA -> ID '::' ID                                              ///
/// [x] * DotAccessExpression    * DE -> PE '.'  ID                                              ///
/// [x] * PathExpression         * PA -> SA | DE                                                 ///
///                                                                                              ///
/// [x] * TernaryExpression      * TE -> PE '?' E ':' E | PE 'if' E 'else' E                     ///
/// [x] * InstanceOfExpression   * IE -> PE ( 'has' | 'derives' ) ID                             ///
/// [x] * CastExpression         * CE -> PE 'as' E                                               ///
///                                                                                              ///
/// [x] * ArrayAccessExpression  * AA -> PE '[' E ']'                                            ///
/// [x] * FunctionCallExpression * FC -> PA GI? AL                                               ///
///                                                                                              ///
///                                  /* right associative recursive */                           ///
/// [x] * ObjectInitializerExpression * OI -> '{' ( KA ( ',' KA )* )? '}'                        ///
/// [x] * SetLiteralExpression        * SE -> '{' E ( ',' E )* '}'                               ///
/// [x] * TupleLiteralExpression      * TL -> '(' E ( ',' E )* ')'                               ///
/// [x] * ArrayLiteralExpression      * AE -> '[' E ( ',' E )* ']'                               ///
/// [x] * ParenthesizedExpression     * PAE -> '(' E? ')'                                        ///
///                                                                                              ///
///                                      /* generics */                                          ///
/// [ ] * GenericInvocationExpression     * GI -> '<' GAE? ( ',' GAE )* '>'                      ///
/// [ ] * GenericArgumentExpression       * GAE -> E | ID '=' E                                  ///
/// [ ] * PathGenericInvocationExpression * PGE -> PE GI                                         ///
///                                                                                              ///
///              /* FIXME: remove and merge 'PtrType' with unary op and remove 'Type' */         ///
/// [ ] * Type    * TY -> ID | PT                                                                ///
/// [ ] * PtrType * PT -> PrimaryExpression '*' | '*' PrimaryExpression                          ///
///                     | PrimaryExpression '&' | '&' PrimaryExpression                          ///
///                                                                                              ///
///    /* complete parser */                                                                     ///
/// [x] * PE -> LE | ID | AE | SE | TL | OI | PA | PAE                                           ///
/// [x] * E  -> PE | UE | BE | TE | CE | IE | AA | FC                                            ///
///                                                                                              ///
/// TODO: big problem: the parser needs to be able to parse generics in the context of exprs,    ///
///          since doing something like `foo<int>` is a valid expression. This is not currently  ///
///          supported. a better example would be:                                               ///
///                                                                                              ///
///       @code                                                                                  ///
///       const eval let PI: T = T(3.1415926535) requires <T>;                                   ///
///       let x: int = PI<int>;                                                                  ///
///       @endcode                                                                               ///
///                                                                                              ///
///       this is a valid expression, but how do we parse it?                                    ///
///          how can we parse the `PI<int>` and not confuse it with a BinaryExpression like      ///
///          `PI < int`? and the > becoming a syntax error?                                      ///
///                                                                                              ///
//===-----------------------------------------------------------------------------------------====//

#include <expected>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/config/AST_generate.hh"
#include "parser/ast/include/config/case_types.def"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/nodes/AST_Expressions.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"

// ---------------------------------------------------------------------------------------------- //

bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens);
int  get_precedence(const token::Token &tok);

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Expression, parse_primary) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;

    token::Token  tok = CURRENT_TOK;
    ParseResult<> node;

    if (is_excepted(tok, IS_LITERAL)) {
        node = parse_LiteralExpression();
    } else if (is_excepted(tok, IS_IDENTIFIER)) {
        node = parse_IdentifierExpression();

        while (true) {  // this loop is used to build a simple compound expression from the primary
                        // expression parsed above, but now we need way to limit the number of times
                        // for the same reason as the other loop /* TODO */

            if (CURRENT_TOK ==
                token::tokens::PUNCTUATION_OPEN_ANGLE) {  /// why are generics so hard
                                                          /// to parse, fuck them fr
                NOT_IMPLEMENTED;
            } else if (CURRENT_TOK ==
                       token::tokens::PUNCTUATION_OPEN_PAREN) {  /// see? how simple these are to do
                                                                 /// compared to generics
                node = parse_FunctionCallExpression(node);
            } else if (CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_BRACKET) {
                node = parse_ArrayAccessExpression(node);
            } else if (CURRENT_TOK == token::tokens::PUNCTUATION_DOT) {
                node = parse_DotAccessExpression(node);
            } else if (CURRENT_TOK == token::tokens::OPERATOR_SCOPE) {
                node = parse_ScopeAccessExpression(node);
            } else {
                break;  /// exit the loop
            }
        }
    } else if (is_excepted(tok, IS_UNARY_OPERATOR)) {
        node = parse_UnaryExpression();
    } else if (is_excepted(tok, IS_PUNCTUATION)) {
        if (tok.token_kind() ==
            token::tokens::PUNCTUATION_OPEN_PAREN) {  /// at this point we either have a tuple or a
                                                      /// parenthesized expression, so we need to do
                                                      /// further analysis to determine which one it
                                                      /// is
            iter.advance();                           /// skip '('
            ParseResult<> expr = parse();
            RETURN_IF_ERROR(expr);

            if (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {  /// if the next token is a
                                                                    /// comma, then its a tuple
                node = parse_TupleLiteralExpression(expr);
            } else {
                node = parse_ParenthesizedExpression(expr);
            }
        } else if (tok.token_kind() == token::tokens::PUNCTUATION_OPEN_BRACKET) {
            node = parse_ArrayLiteralExpression();
        } else if (tok.token_kind() ==
                   token::tokens::
                       PUNCTUATION_OPEN_BRACE) {  /// heres its either a set, a map or an object
                                                  /// initializer, to determine which one it is, its
                                                  /// quite simple we need to check if the next
                                                  /// token is a '.' which if it is, then its an
                                                  /// object initializer otherwise we parse E(1) and
                                                  /// check if the next token is a ':', if it is,
                                                  /// then its a map otherwise its a set
            iter.advance();                       // skip '{'
            if (CURRENT_TOK == token::tokens::PUNCTUATION_DOT) {
                node = parse_ObjectInitializerExpression(true);
            } else {
                ParseResult<> first = parse();
                RETURN_IF_ERROR(first);

                if (CURRENT_TOK == token::tokens::PUNCTUATION_COLON) {
                    node = parse_MapLiteralExpression(first);
                } else {
                    node = parse_SetLiteralExpression(first);
                }
            }
        } else {
            return std::unexpected(PARSE_ERROR_MSG("Expected an expression, but found nothing"));
        }
    } else {
        return std::unexpected(PARSE_ERROR_MSG("Expected an expression, but found nothing"));
    }

    return node;
}

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Expression, parse) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;                   /// simple macro to check if the iterator is empty, expands to:
                   /// if (iter.remaining_n() == 0) { return std::unexpected(...); }

    ParseResult<> expr = parse_primary();  /// E(1) - this is always the first expression in the
                                           /// expression, we then build coumpound expressions from
                                           /// this

    RETURN_IF_ERROR(expr);  /// simple macro to return if the expression is an error expands to:
                            /// if (!expr.has_value()) { return std::unexpected(expr.error()); }

    while (true) {  /// this loop is used to build compound expressions from the primary expression
                    /// parsed above, but now we need way to limit the number of times we can loop
                    /// since if we have a really really long expression, we could end up in an
                    /// memory exhaustion situation or a stack overflow situation. /* TODO */

        token::Token tok = CURRENT_TOK;  /// simple macro to get the current token expands to:
                                         /// iter.current().get()

        if (tok == token::tokens::PUNCTUATION_OPEN_ANGLE) {  /// what to do if its ident '<' parms
                                                             /// '>' '(' args ')' its now either a
                                                             /// function call w a generic or its a
                                                             /// binary expression may god help me
            NOT_IMPLEMENTED;
        } else if (tok == token::tokens::PUNCTUATION_OPEN_PAREN) {
            expr = parse_FunctionCallExpression(expr);
            RETURN_IF_ERROR(expr);
        } else if (tok == token::tokens::PUNCTUATION_OPEN_BRACKET) {
            expr = parse_ArrayAccessExpression(expr);
            RETURN_IF_ERROR(expr);
        } else if (tok == token::tokens::PUNCTUATION_DOT) {
            expr = parse_DotAccessExpression(expr);
            RETURN_IF_ERROR(expr);
        } else if (tok == token::tokens::OPERATOR_SCOPE) {
            expr = parse_ScopeAccessExpression(expr);
            RETURN_IF_ERROR(expr);
        } else if (tok == token::tokens::PUNCTUATION_OPEN_BRACE) {
            expr = parse_ObjectInitializerExpression();
            RETURN_IF_ERROR(expr);
        } else if (tok == token::tokens::PUNCTUATION_OPEN_PAREN) {
            iter.advance();                              // skip '('
            expr = parse_ParenthesizedExpression(expr);  /// im not sure why this works, but based
                                                         /// on small tests, it seems to work fine
                                                         /// i'll find out soon enough if it doesn't
            RETURN_IF_ERROR(expr);
        } else if (is_excepted(tok, IS_BINARY_OPERATOR)) {
            expr = parse_BinaryExpression(expr, get_precedence(tok));
            RETURN_IF_ERROR(expr);
        } else if (is_excepted(tok, {token::tokens::KEYWORD_HAS, token::tokens::KEYWORD_DERIVES})) {
            expr = parse_InstanceOfExpression(expr);
            RETURN_IF_ERROR(expr);
        } else if (is_excepted(
                       tok,
                       {token::tokens::PUNCTUATION_QUESTION_MARK, token::tokens::KEYWORD_IF})) {
            expr = parse_TernaryExpression(expr);
            RETURN_IF_ERROR(expr);
        } else {
            break;
        }

        tok = CURRENT_TOK;
    }

    return expr;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(LiteralExpression) {
    if (iter.remaining_n() == 0) {
        return std::unexpected(PARSE_ERROR_MSG("expected a literal expression, but found nothing"));
    }

    token::Token tok = iter.current().get();  // get tokens[0]
    iter.advance();                           // pop tokens[0]

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
            return std::unexpected(
                PARSE_ERROR(tok, "expected a literal. but found: " + tok.token_kind_repr()));
    }

    return make_node<LiteralExpression>(tok, type);
}

AST_NODE_IMPL_VISITOR(Jsonify, LiteralExpression) {
    json.section("LiteralExpression").add("value", node.value).add("type", (int)node.getNodeType());
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(BinaryExpression, ParseResult<> lhs, int min_precedence) {
    IS_NOT_EMPTY;

    // := E op E

    token::Token tok = CURRENT_TOK;

    while (is_excepted(tok, IS_BINARY_OPERATOR) && get_precedence(tok) >= min_precedence) {
        int          precedence = get_precedence(tok);
        token::Token op         = tok;

        iter.advance();

        ParseResult<> rhs = parse_primary();
        RETURN_IF_ERROR(rhs);

        tok = CURRENT_TOK;
        while (is_excepted(tok, IS_BINARY_OPERATOR) && get_precedence(tok) > precedence) {
            rhs = parse_BinaryExpression(rhs, get_precedence(tok));
            RETURN_IF_ERROR(rhs);
            tok = CURRENT_TOK;
        }

        lhs = make_node<BinaryExpression>(lhs.value(), rhs.value(), op);
    }

    return std::dynamic_pointer_cast<BinaryExpression>(lhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, BinaryExpression) {
    json.section("BinaryExpression")
        .add("lhs", get_node_json(node.lhs))
        .add("op", node.op)
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(UnaryExpression) {
    IS_NOT_EMPTY;

    // := op E
    if (!is_excepted(CURRENT_TOK, IS_UNARY_OPERATOR)) {
        return std::unexpected(PARSE_ERROR(iter.current().get(),
                                           "expected a unary operator, but found: " +
                                               iter.current().get().token_kind_repr()));
    }

    token::Token op = iter.current().get();
    iter.advance();  // pop the token

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<UnaryExpression>(rhs.value(), op);
}

AST_NODE_IMPL_VISITOR(Jsonify, UnaryExpression) {
    json.section("UnaryExpression").add("rhs", get_node_json(node.rhs)).add("op", node.op);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(IdentifierExpression) {
    IS_NOT_EMPTY;

    // verify the current token is an identifier
    token::Token tok = iter.current().get();

    if (tok.token_kind() != token::tokens::IDENTIFIER) {
        return std::unexpected(
            PARSE_ERROR(tok, +"expected an identifier, but found: " + tok.token_kind_repr()));
    }

    iter.advance();  // pop the token

    return make_node<IdentifierExpression>(tok);
}

AST_NODE_IMPL_VISITOR(Jsonify, IdentifierExpression) {
    json.section("IdentifierExpression").add("name", node.name);
}

// ---------------------------------------------------------------------------------------------- //

/* FIXME: use this method, if unused remove */
// should not be called by `parse` directly as it is a helper function
AST_NODE_IMPL(NamedArgument) {
    IS_NOT_EMPTY;

    // := '.' IdentifierExpression '=' E

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_DOT)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '.', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '.'

    ParseResult<IdentifierExpression> name = parse_IdentifierExpression();
    RETURN_IF_ERROR(name);

    if (!(CURRENT_TOK == token::tokens::OPERATOR_ASSIGN)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '=', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '='

    ParseResult<> value = parse();
    RETURN_IF_ERROR(value);

    return make_node<NamedArgument>(name.value(), value.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, NamedArgument) {
    json.section("NamedArgument")
        .add("name", get_node_json(node.name))
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

// should not be called by `parse` directly as it is a helper function
AST_NODE_IMPL(ArgumentExpression) {
    IS_NOT_EMPTY;

    NodeT<ArgumentExpression> result;

    ParseResult<> lhs = parse();  // E(1)
    RETURN_IF_ERROR(lhs);

    NodeT<> lhs_node = lhs.value();

    if (lhs_node->getNodeType() == nodes::BinaryExpression) {
        NodeT<BinaryExpression> bin_expr = std::static_pointer_cast<BinaryExpression>(lhs_node);

        if (bin_expr->lhs->getNodeType() == nodes::IdentifierExpression &&
            bin_expr->op.token_kind() == token::tokens::OPERATOR_ASSIGN) {

            NodeT<NamedArgument> kwarg = make_node<NamedArgument>(
                std::static_pointer_cast<IdentifierExpression>(bin_expr->lhs), bin_expr->rhs);

            result       = make_node<ArgumentExpression>(kwarg);
            result->type = ArgumentExpression::ArgumentType::Keyword;

            return result;
        }
    }

    result       = make_node<ArgumentExpression>(lhs_node);
    result->type = ArgumentExpression::ArgumentType::Positional;

    return result;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArgumentExpression) {
    json.section("ArgumentExpression")
        .add("type", (int)node.type)
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(ArgumentListExpression) {
    IS_NOT_EMPTY;

    // := '(' ArgumentExpression (',' ArgumentExpression)* ')'
    // in typical recursive descent fashion, we parse the first argument expression

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '(', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '('

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN) {
        iter.advance();  // skip ')'
        return make_node<ArgumentListExpression>(nullptr);
    }

    ParseResult<ArgumentExpression> first = parse_ArgumentExpression();

    RETURN_IF_ERROR(first);

    NodeT<ArgumentListExpression> args = make_node<ArgumentListExpression>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','
        ParseResult<ArgumentExpression> arg = parse_ArgumentExpression();
        RETURN_IF_ERROR(arg);
        args->args.push_back(arg.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected ')', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip ')'

    return args;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArgumentListExpression) {
    std::vector<neo::json> args;

    for (const auto &arg : node.args) {
        args.push_back(get_node_json(arg));
    }

    json.section("ArgumentListExpression").add("args", args);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(GenericArgumentExpression) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(GenericInvocationExpression) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(PathGenericInvocationExpression) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(ScopeAccessExpression, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E '::' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if (!(CURRENT_TOK == token::tokens::OPERATOR_SCOPE)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '::', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '::'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<ScopeAccessExpression>(lhs.value(), rhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ScopeAccessExpression) {
    json.section("ScopeAccessExpression")
        .add("lhs", get_node_json(node.lhs))
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(DotAccessExpression, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E '.' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_DOT)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '.', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '.'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<DotAccessExpression>(lhs.value(), rhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, DotAccessExpression) {
    json.section("DotAccessExpression")
        .add("lhs", get_node_json(node.lhs))
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(ArrayAccessExpression, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E '[' E ']'

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '[', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '['

    ParseResult<> index = parse();
    RETURN_IF_ERROR(index);

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected ']', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip ']'

    return make_node<ArrayAccessExpression>(lhs.value(), index.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ArrayAccessExpression) {
    json.section("ArrayAccessExpression")
        .add("array", get_node_json(node.lhs))
        .add("index", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(PathExpression, ParseResult<> simple_path) {
    IS_NOT_EMPTY;

    if (simple_path != nullptr && simple_path.has_value()) {
        NodeT<PathExpression> path = make_node<PathExpression>(simple_path.value());

        switch (simple_path.value()->getNodeType()) {
            case parser::ast::node::nodes::IdentifierExpression:
                path->type = PathExpression::PathType::Identifier;
                break;

            case parser::ast::node::nodes::ScopeAccessExpression:
                path->type = PathExpression::PathType::Scope;
                break;

            case parser::ast::node::nodes::DotAccessExpression:
                path->type = PathExpression::PathType::Dot;
                break;

            default:
                return std::unexpected(PARSE_ERROR_MSG("expected a path expression, but found '" +
                                                       simple_path.value()->getNodeName() + "'"));
        }

        return path;
    }

    return std::unexpected(PARSE_ERROR_MSG("expected a simple path expression, but found nothing"));
}

AST_NODE_IMPL_VISITOR(Jsonify, PathExpression) {
    json.section("PathExpression")
        .add("path", get_node_json(node.path))
        .add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(FunctionCallExpression, ParseResult<> lhs, ParseResult<> gens) {
    IS_NOT_EMPTY;

    /*
        FunctionCallExpression = {
            NodeT<PathExpression>
            NodeT<ArgumentListExpression>
            NodeT<GenericInvocationExpression>
        }
    */

    // if lhs is not empty, then we have a path expression
    ParseResult<PathExpression> path;
    // ParseResult<GenericInvocationExpression> generics;

    if (lhs != nullptr && lhs.has_value()) {
        path = parse_PathExpression(lhs.value());
    } else {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
        path = parse_PathExpression(lhs.value());
    }

    RETURN_IF_ERROR(path);

    // TODO: add support for generics

    IS_NOT_EMPTY;

    ParseResult<ArgumentListExpression> args = parse_ArgumentListExpression();

    RETURN_IF_ERROR(args);

    return make_node<FunctionCallExpression>(path.value(), args.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, FunctionCallExpression) {
    json.section("FunctionCallExpression")
        .add("path", get_node_json(node.path))
        .add("args", get_node_json(node.args));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(ArrayLiteralExpression) {
    IS_NOT_EMPTY;
    // := '[' E (',' E)* ']'

    // [1, 2, 3, ]

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '[', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '['

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACKET) {
        iter.advance();  // skip ']'
        return std::unexpected(PARSE_ERROR_MSG("array literals must have at least one element"));
    }

    ParseResult<> first = parse();

    RETURN_IF_ERROR(first);

    NodeT<ArrayLiteralExpression> array = make_node<ArrayLiteralExpression>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACKET) {
            break;
        }

        ParseResult<> next = parse();
        RETURN_IF_ERROR(next);
        array->values.push_back(next.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected ']', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip ']'

    return array;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArrayLiteralExpression) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("ArrayLiteralExpression").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(TupleLiteralExpression, ParseResult<> starting_element) {
    IS_NOT_EMPTY;

    // := '(' E (',' E)* ')'

    ParseResult<> first;

    if (starting_element != nullptr && starting_element.has_value()) {
        first = starting_element;  // we have a starting element
        // the current token is ',' the '(' has already been parsed
    } else {
        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_PAREN)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected '(', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip '('

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN) {
            iter.advance();  // skip ')'
            return std::unexpected(
                PARSE_ERROR_MSG("tuple literals must have at least one element"));
        }

        first = parse();

        RETURN_IF_ERROR(first);
    }

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN) {
        iter.advance();  // skip ')'
        return std::unexpected(PARSE_ERROR_MSG("tuple literals must have at least one element"));
    }

    NodeT<TupleLiteralExpression> tuple = make_node<TupleLiteralExpression>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN) {
            break;
        }

        ParseResult<> next = parse();
        RETURN_IF_ERROR(next);
        tuple->values.push_back(next.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected ')', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip ')'

    return tuple;
}

AST_NODE_IMPL_VISITOR(Jsonify, TupleLiteralExpression) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("TupleLiteralExpression").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(SetLiteralExpression, ParseResult<> starting_value) {
    IS_NOT_EMPTY;

    // := '{' E (',' E)* '}'
    // {1}
    // {1, 2, 3, }

    NodeT<SetLiteralExpression> set;

    if (starting_value != nullptr && starting_value.has_value()) {
        // we have parsed the '{' and the first E, so we need to check if the current token is ','
        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            set = make_node<SetLiteralExpression>(starting_value.value());

            iter.advance();  // skip '}'
            return set;
        }

        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_COMMA)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected ',', but found: " + iter.current().get().token_kind_repr()));
        }

        set = make_node<SetLiteralExpression>(starting_value.value());
    } else {
        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_BRACE)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected '{', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip '{'

        ParseResult<> first = parse();

        RETURN_IF_ERROR(first);

        set = make_node<SetLiteralExpression>(first.value());
    }

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            break;
        }

        ParseResult<> next = parse();
        RETURN_IF_ERROR(next);
        set->values.push_back(next.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '}', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '}'

    return set;
}

AST_NODE_IMPL_VISITOR(Jsonify, SetLiteralExpression) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("SetLiteralExpression").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(MapPairExpression) {
    IS_NOT_EMPTY;

    // := E ':' E

    ParseResult<> key = parse();

    RETURN_IF_ERROR(key);

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_COLON)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected ':', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip ':'

    ParseResult<> value = parse();

    RETURN_IF_ERROR(value);

    return make_node<MapPairExpression>(key.value(), value.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, MapPairExpression) {
    json.section("MapPairExpression")
        .add("key", get_node_json(node.key))
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(MapLiteralExpression, ParseResult<> starting_key) {
    IS_NOT_EMPTY;

    // := '{' E (':' E)* '}'

    NodeT<MapPairExpression> pair;

    if (starting_key != nullptr && starting_key.has_value()) {
        // we have parsed the '{' and the first E, so we need to check if the current token is ':'
        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_COLON)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected ':', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip ':'

        ParseResult<> value = parse();
        RETURN_IF_ERROR(value);

        pair = make_node<MapPairExpression>(starting_key.value(), value.value());
    } else {
        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_BRACE)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected '{', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip '{'

        ParseResult<MapPairExpression> tmp_pair = parse_MapPairExpression();
        RETURN_IF_ERROR(tmp_pair);

        pair = tmp_pair.value();
    }

    // := (',' E)* '}' is the remaining part of the map literal expression (there could be a
    // trailing comma)

    NodeT<MapLiteralExpression> map = make_node<MapLiteralExpression>(pair);

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            break;
        }

        ParseResult<MapPairExpression> next_pair = parse_MapPairExpression();
        RETURN_IF_ERROR(next_pair);

        map->values.push_back(next_pair.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '}', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '}'

    return map;
}

AST_NODE_IMPL_VISITOR(Jsonify, MapLiteralExpression) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("MapLiteralExpression").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(ObjectInitializerExpression, bool skip_start_brace) {
    IS_NOT_EMPTY;

    // := '{' (NamedArgument (',' NamedArgument)*)? '}'

    if (!skip_start_brace) {
        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_BRACE)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected '{', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip '{'
    }

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected a keyword argument, but got an empty object initializer"));
    }

    ParseResult<NamedArgument> first = parse_NamedArgument();
    RETURN_IF_ERROR(first);

    NodeT<ObjectInitializerExpression> obj = make_node<ObjectInitializerExpression>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            break;
        }

        ParseResult<NamedArgument> next = parse_NamedArgument();
        RETURN_IF_ERROR(next);
        obj->kwargs.push_back(next.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '}', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '}'

    return obj;
}

AST_NODE_IMPL_VISITOR(Jsonify, ObjectInitializerExpression) {
    std::vector<neo::json> kwargs;

    for (const auto &kwarg : node.kwargs) {
        kwargs.push_back(get_node_json(kwarg));
    }

    json.section("ObjectInitializerExpression").add("keyword_args", kwargs);
}

// ---------------------------------------------------------------------------------------------- //

/* TODO: after Suite can be parsed */
AST_NODE_IMPL(LambdaExpression) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, LambdaExpression) { json.section("LambdaExpression"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(TernaryExpression, ParseResult<> E1) {
    IS_NOT_EMPTY;

    // := (E '?' E ':' E) | (E 'if' E 'else' E)
    // true ? 1 : 0 | 1 if true else 0

    if (E1 == nullptr || !E1.has_value()) {
        E1 = parse();
        RETURN_IF_ERROR(E1);
    }

    if (CURRENT_TOK == token::tokens::PUNCTUATION_QUESTION_MARK) {
        iter.advance();  // skip '?'

        ParseResult<> E2 = parse();
        RETURN_IF_ERROR(E2);

        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_COLON)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected ':', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip ':'

        ParseResult<> E3 = parse();
        RETURN_IF_ERROR(E3);

        return make_node<TernaryExpression>(E1.value(), E2.value(), E3.value());
    }

    if (CURRENT_TOK == token::tokens::KEYWORD_IF) {
        iter.advance();  // skip 'if'

        ParseResult<> E2 = parse();
        RETURN_IF_ERROR(E2);

        if (!(CURRENT_TOK == token::tokens::KEYWORD_ELSE)) {
            return std::unexpected(PARSE_ERROR(iter.current().get(),
                                               "expected 'else', but found: " +
                                                   iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip 'else'

        ParseResult<> E3 = parse();
        RETURN_IF_ERROR(E3);

        return make_node<TernaryExpression>(E2.value(), E1.value(), E3.value());
    }

    return std::unexpected(
        PARSE_ERROR(iter.current().get(),
                    "expected '?' or 'if', but found: " + iter.current().get().token_kind_repr()));
}

AST_NODE_IMPL_VISITOR(Jsonify, TernaryExpression) {
    json.section("TernaryExpression")
        .add("condition", get_node_json(node.condition))
        .add("if_true", get_node_json(node.if_true))
        .add("if_false", get_node_json(node.if_false));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(ParenthesizedExpression, ParseResult<> expr) {
    IS_NOT_EMPTY;

    // := '(' E ')'

    if (expr != nullptr && expr.has_value()) {
        // check if the current token is a ')'
        if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN)) {
            return std::unexpected(
                PARSE_ERROR(iter.current().get(),
                            "expected ')', but found: " + iter.current().get().token_kind_repr()));
        }

        iter.advance();  // skip ')'

        return make_node<ParenthesizedExpression>(expr.value());
    }

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_OPEN_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected '(', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip '('

    ParseResult<> inner = parse();

    RETURN_IF_ERROR(inner);

    if (!(CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected ')', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip ')'

    return make_node<ParenthesizedExpression>(inner.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ParenthesizedExpression) {
    json.section("ParenthesizedExpression").add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(CastExpression) {
    IS_NOT_EMPTY;

    // := E 'as' E

    ParseResult<> lhs = parse();
    RETURN_IF_ERROR(lhs);

    if (!(CURRENT_TOK == token::tokens::KEYWORD_AS)) {
        return std::unexpected(
            PARSE_ERROR(iter.current().get(),
                        "expected 'as', but found: " + iter.current().get().token_kind_repr()));
    }

    iter.advance();  // skip 'as'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<CastExpression>(lhs.value(), rhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, CastExpression) {
    json.section("CastExpression")
        .add("value", get_node_json(node.value))
        .add("type", get_node_json(node.type));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(InstanceOfExpression, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E 'has' E | E 'derives' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if (!(CURRENT_TOK == token::tokens::KEYWORD_HAS ||
          CURRENT_TOK == token::tokens::KEYWORD_DERIVES)) {
        return std::unexpected(PARSE_ERROR(CURRENT_TOK,
                                           "expected 'has' or 'derives', but found: " +
                                               iter.current().get().token_kind_repr()));
    }

    InstanceOfExpression::InstanceType op = (CURRENT_TOK == token::tokens::KEYWORD_HAS)
                                                ? InstanceOfExpression::InstanceType::Has
                                                : InstanceOfExpression::InstanceType::Derives;

    iter.advance();  // skip 'has' or 'derives'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<InstanceOfExpression>(lhs.value(), rhs.value(), op);
}

AST_NODE_IMPL_VISITOR(Jsonify, InstanceOfExpression) {
    json.section("InstanceOfExpression")
        .add("value", get_node_json(node.value))
        .add("type", get_node_json(node.type))
        .add("op", (int)node.op);
}

// ---------------------------------------------------------------------------------------------- //

/* DEPRECATED: a pointer or ref type is deduced from context and at this stage is considered a
 * UnaryExpression */
AST_NODE_IMPL(PtrType) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

/* DEPRECATED: a Type is deduced from context and at this stage is considered a Expression */
AST_NODE_IMPL(Type) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //


bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens) {
    return tokens.find(tok.token_kind()) != tokens.end();
}

int get_precedence(const token::Token &tok) {
    switch (tok.token_kind()) {
        case token::OPERATOR_MUL:
        case token::OPERATOR_DIV:
        case token::OPERATOR_MOD:
        case token::OPERATOR_POW:
            return 5;

        case token::OPERATOR_ADD:
        case token::OPERATOR_SUB:
            return 4;

        case token::OPERATOR_BITWISE_AND:
        case token::OPERATOR_BITWISE_OR:
        case token::OPERATOR_BITWISE_XOR:
        case token::OPERATOR_BITWISE_L_SHIFT:
        case token::OPERATOR_BITWISE_R_SHIFT:
            return 3;

        case token::OPERATOR_EQUAL:
        case token::OPERATOR_NOT_EQUAL:
        case token::OPERATOR_GREATER_THAN_EQUALS:
        case token::OPERATOR_LESS_THAN_EQUALS:
        case token::PUNCTUATION_OPEN_ANGLE:
        case token::PUNCTUATION_CLOSE_ANGLE:
            return 2;

        case token::OPERATOR_ASSIGN:
        case token::OPERATOR_ADD_ASSIGN:
        case token::OPERATOR_SUB_ASSIGN:
        case token::OPERATOR_MUL_ASSIGN:
        case token::OPERATOR_DIV_ASSIGN:
        case token::OPERATOR_MOD_ASSIGN:
        case token::OPERATOR_LOGICAL_AND:
        case token::OPERATOR_LOGICAL_OR:
        case token::OPERATOR_RANGE:
        case token::OPERATOR_RANGE_INCLUSIVE:
            return 1;

        default:
            return 0;  // Return 0 for non-binary operators
    }
}
