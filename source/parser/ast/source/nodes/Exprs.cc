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
///  ParseResult<BinaryExpr> node = expr.parse<BinaryExpr>();                                    ///
///  @endcode                                                                                    ///
///                                                                                              ///
/// The parser is implemented using the following grammar:                                       ///
///                                                                                              ///
/// STS *         /* node types */                                                               ///
/// [x] * Literal  * L                                                                           ///
/// [x] * Operator * O                                                                           ///
/// [x] * Token    * T                                                                           ///
///                                                                                              ///
///                          * helper nodes (not supposed to be explicitly used) */              ///
/// [x] * ArgumentListExpr   * AL -> ( AE? ( ',' AE )* )                                         ///
/// [x] * NamedArgumentExpr  * KA -> '.' ID '=' E                                                ///
/// [x] * ArgumentExpr       * AE -> E | ID '=' E                                                ///
/// [x] * MapPairExpr        * MP -> E ':' E                                                     ///
///                                                                                              ///
///                   /* primary nodes */                                                        ///
/// [x] * UnaryExpr    * UE  -> O    PE                                                          ///
/// [x] * BinaryExpr   * BE  -> UE   BE'                                                         ///
///                      BE' -> O UE BE' | ϵ                                                     ///
///                                                                                              ///
///                     /* core single associative */                                            ///
/// [x] * IdentExpr      * ID -> T                                                               ///
/// [x] * LiteralExpr    * LE -> L                                                               ///
///                                                                                              ///
///                       /* multi-associative */                                                ///
/// [x] * ScopePathExpr    * SA -> ID '::' ID                                                    ///
/// [x] * DotPathExpr      * DE -> PE '.'  ID                                                    ///
/// [x] * PathExpr         * PA -> SA | DE                                                       ///
///                                                                                              ///
/// [x] * TernaryExpr      * TE -> PE '?' E ':' E | PE 'if' E 'else' E                           ///
/// [x] * InstOfExpr       * IE -> PE ( 'has' | 'derives' ) ID                                   ///
/// [x] * CastExpr         * CE -> PE 'as' E                                                     ///
///                                                                                              ///
/// [x] * ArrayAccessExpr  * AA -> PE '[' E ']'                                                  ///
/// [x] * FunctionCallExpr * FC -> PA GI? AL                                                     ///
///                                                                                              ///
///                            /* right associative recursive */                                 ///
/// [x] * ObjInitExpr           * OI -> '{' ( KA ( ',' KA )* )? '}'                              ///
/// [x] * SetLiteralExpr        * SE -> '{' E ( ',' E )* '}'                                     ///
/// [x] * TupleLiteralExpr      * TL -> '(' E ( ',' E )* ')'                                     ///
/// [x] * ArrayLiteralExpr      * AE -> '[' E ( ',' E )* ']'                                     ///
/// [x] * ParenthesizedExpr     * PAE -> '(' E? ')'                                              ///
///                                                                                              ///
///                                /* generics */                                                ///
/// [ ] * GenericInvokeExpr         * GI -> '<' GAE? ( ',' GAE )* '>'                            ///
/// [ ] * GenericArgumentExpr       * GAE -> E | ID '=' E                                        ///
/// [ ] * GenericInvokePathExpr     * PGE -> PE GI                                               ///
///                                                                                              ///
/// [ ] * AsyncExpr                 * AS -> ('spawn' | 'thread') E                               ///
/// [ ] * AwaitExpr                 * AS -> 'await' E                                            ///
///                                                                                              ///
/// [ ] * Type    * TY -> ID | PT                                                                ///
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
///          how can we parse the `PI<int>` and not confuse it with a BinaryExpr like            ///
///          `PI < int`? and the > becoming a syntax error?                                      ///
///                                                                                              ///
/// TODO: add support for async keywords, 'await', 'spawn', 'thread'                             ///
/// TODO: add support for 'match' expressions                                                    ///
///                                                                                              ///
//===-----------------------------------------------------------------------------------------====//

#include <cstddef>
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
        node = parse_LiteralExpr();
    } else if (is_excepted(tok, IS_IDENTIFIER)) {
        node = parse_IdentExpr();
    } else if (is_excepted(tok, IS_UNARY_OPERATOR)) {
        node = parse_UnaryExpr();
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
                node = parse_TupleLiteralExpr(expr);
            } else {
                node = parse_ParenthesizedExpr(expr);
            }
        } else if (tok.token_kind() == token::tokens::PUNCTUATION_OPEN_BRACKET) {
            node = parse_ArrayLiteralExpr();
        } else if (tok.token_kind() == token::tokens::PUNCTUATION_OPEN_BRACE) {
            /// heres its either a set, a map or an object
            /// initializer, to determine which one it is, its
            /// quite simple we need to check if the next
            /// token is a '.' which if it is, then its an
            /// object initializer otherwise we parse E(1) and
            /// check if the next token is a ':', if it is,
            /// then its a map otherwise its a set

            iter.advance();  // skip '{'

            if (CURRENT_TOK == token::tokens::PUNCTUATION_DOT) {
                node = parse_ObjInitExpr(true);
            } else {
                ParseResult<> first = parse();
                RETURN_IF_ERROR(first);

                if (CURRENT_TOK == token::tokens::PUNCTUATION_COLON) {
                    node = parse_MapLiteralExpr(first);
                } else {
                    node = parse_SetLiteralExpr(first);
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
                                    /// if(iter.remaining_n() == 0) { return std::unexpected(...); }

    token::Token tok;
    size_t       iter_n = 0;
    size_t n_max = iter.remaining_n() << 1;  /// this is a way to approx the tokens to parse, and is
                                             /// used to prevent the parser from going into an
                                             /// infinite loop  if the expression is malformed, this
                                             /// is a simple way to prevent stack overflows and
                                             /// memory exhaustion
    bool          continue_loop = true;
    ParseResult<> expr = parse_primary();  /// E(1) - this is always the first expression in the
                                           /// expression, we then build coumpound expressions from
                                           /// this

    RETURN_IF_ERROR(expr);  /// simple macro to return if the expression is an error expands to:
                            /// if (!expr.has_value()) { return std::unexpected(expr.error()); }

    /// parsed above, but now we need way to limit the number of times we can loop since if we have
    /// a really really long expression, we could end up in an memory exhaustion situation or a
    /// stack overflow situation. /* TODO */
    for (; iter_n < n_max && continue_loop; iter_n++) {  /// this is a simple loop that will
                                                         /// continue to loop until we have parsed
                                                         /// all the tokens in the expression, the
                                                         /// expression

        tok = CURRENT_TOK;  /// simple macro to get the current token expands to:
                            /// CURRENT_TOK

        switch (tok.token_kind()) {
            case token::tokens::PUNCTUATION_OPEN_ANGLE:  /// what to do if its ident '<' parms
                                                         /// '>' '(' args ')' its now either a
                                                         /// function call w a generic or its a
                                                         /// binary expression may god help me
                NOT_IMPLEMENTED;
            case token::tokens::PUNCTUATION_OPEN_PAREN:
                expr = parse_FunctionCallExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::PUNCTUATION_OPEN_BRACKET:
                expr = parse_ArrayAccessExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::PUNCTUATION_DOT:
                expr = parse_DotPathExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::OPERATOR_SCOPE:
                expr = parse_ScopePathExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::PUNCTUATION_OPEN_BRACE:
                expr = parse_ObjInitExpr();
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::KEYWORD_HAS:
                [[fallthrough]];
            case token::tokens::KEYWORD_DERIVES:
                expr = parse_InstOfExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::PUNCTUATION_QUESTION_MARK:
                [[fallthrough]];
            case token::tokens::KEYWORD_IF:
                expr = parse_TernaryExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::tokens::KEYWORD_AS:
                expr = parse_CastExpr(expr);
                RETURN_IF_ERROR(expr);
                break;

            case token::KEYWORD_SPAWN:
            case token::KEYWORD_AWAIT:
            case token::KEYWORD_THREAD:


            default:
                if (is_excepted(tok, IS_BINARY_OPERATOR)) {
                    expr = parse_BinaryExpr(expr, get_precedence(tok));
                    RETURN_IF_ERROR(expr);
                } else if (tok == token::tokens::PUNCTUATION_OPEN_PAREN) {
                    iter.advance();                        // skip '('
                    expr = parse_ParenthesizedExpr(expr);  /// im not sure why this works, but
                                                           /// based on small tests, it seems
                                                           /// to work fine i'll find out soon
                                                           /// enough if it doesn't
                    RETURN_IF_ERROR(expr);
                } else {
                    continue_loop = false;
                }
        }
    }

    if (iter_n >= n_max) {
        return std::unexpected(PARSE_ERROR_MSG("expression is too long"));
    }

    return expr;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, LiteralExpr) {
    if (iter.remaining_n() == 0) {
        return std::unexpected(PARSE_ERROR_MSG("expected a literal expression, but found nothing"));
    }

    token::Token tok = CURRENT_TOK;  // get tokens[0]
    iter.advance();                  // pop tokens[0]

    LiteralExpr::LiteralType type{};

    switch (tok.token_kind()) {
        case token::tokens::LITERAL_INTEGER:
            type = LiteralExpr::LiteralType::Integer;
            break;
        case token::tokens::LITERAL_FLOATING_POINT:
            type = LiteralExpr::LiteralType::Float;
            break;
        case token::tokens::LITERAL_STRING:
            type = LiteralExpr::LiteralType::String;
            break;
        case token::tokens::LITERAL_CHAR:
            type = LiteralExpr::LiteralType::Char;
            break;
        case token::tokens::LITERAL_TRUE:
        case token::tokens::LITERAL_FALSE:
            type = LiteralExpr::LiteralType::Boolean;
            break;
        case token::tokens::LITERAL_NULL:
            type = LiteralExpr::LiteralType::Null;
            break;
        default:
            return std::unexpected(
                PARSE_ERROR(tok, "expected a literal. but found: " + tok.token_kind_repr()));
    }

    return make_node<LiteralExpr>(tok, type);
}

AST_NODE_IMPL_VISITOR(Jsonify, LiteralExpr) {
    json.section("LiteralExpr").add("value", node.value).add("type", (int)node.getNodeType());
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, BinaryExpr, ParseResult<> lhs, int min_precedence) {
    IS_NOT_EMPTY;

    // := E op E
    // TODO if E(2) does not exist, check if its a & | * token, since if it is,
    // then return a unary expression since its a pointer or reference type

    token::Token tok = CURRENT_TOK;

    while (is_excepted(tok, IS_BINARY_OPERATOR) && get_precedence(tok) >= min_precedence) {
        int          precedence = get_precedence(tok);
        token::Token op         = tok;

        iter.advance();

        ParseResult<> rhs = parse_primary();
        RETURN_IF_ERROR(rhs);

        tok = CURRENT_TOK;
        while (is_excepted(tok, IS_BINARY_OPERATOR) && get_precedence(tok) > precedence) {
            rhs = parse_BinaryExpr(rhs, get_precedence(tok));
            RETURN_IF_ERROR(rhs);
            tok = CURRENT_TOK;
        }

        lhs = make_node<BinaryExpr>(lhs.value(), rhs.value(), op);
    }

    return std::dynamic_pointer_cast<BinaryExpr>(lhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, BinaryExpr) {
    json.section("BinaryExpr")
        .add("lhs", get_node_json(node.lhs))
        .add("op", node.op)
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, UnaryExpr) {
    IS_NOT_EMPTY;

    // := op E
    if (!is_excepted(CURRENT_TOK, IS_UNARY_OPERATOR)) {
        return std::unexpected(PARSE_ERROR(
            CURRENT_TOK, "expected a unary operator, but found: " + CURRENT_TOK.token_kind_repr()));
    }

    token::Token op = CURRENT_TOK;
    iter.advance();  // pop the token

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<UnaryExpr>(rhs.value(), op);
}

AST_NODE_IMPL_VISITOR(Jsonify, UnaryExpr) {
    json.section("UnaryExpr").add("rhs", get_node_json(node.rhs)).add("op", node.op);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, IdentExpr) {
    IS_NOT_EMPTY;

    // verify the current token is an identifier
    token::Token tok                   = CURRENT_TOK;
    bool         is_reserved_primitive = false;

    switch (tok.token_kind()) {
        case token::PRIMITIVE_VOID:
            [[fallthrough]];
        case token::PRIMITIVE_BOOL:
            [[fallthrough]];
        case token::PRIMITIVE_BYTE:
            [[fallthrough]];
        case token::PRIMITIVE_CHAR:
            [[fallthrough]];
        case token::PRIMITIVE_POINTER:
            [[fallthrough]];
        case token::PRIMITIVE_I8:
            [[fallthrough]];
        case token::PRIMITIVE_U8:
            [[fallthrough]];
        case token::PRIMITIVE_I16:
            [[fallthrough]];
        case token::PRIMITIVE_U16:
            [[fallthrough]];
        case token::PRIMITIVE_I32:
            [[fallthrough]];
        case token::PRIMITIVE_U32:
            [[fallthrough]];
        case token::PRIMITIVE_F32:
            [[fallthrough]];
        case token::PRIMITIVE_I64:
            [[fallthrough]];
        case token::PRIMITIVE_U64:
            [[fallthrough]];
        case token::PRIMITIVE_F64:
            [[fallthrough]];
        case token::PRIMITIVE_FLOAT:
            [[fallthrough]];
        case token::PRIMITIVE_I128:
            [[fallthrough]];
        case token::PRIMITIVE_U128:
            [[fallthrough]];
        case token::PRIMITIVE_INT:
            [[fallthrough]];
        case token::PRIMITIVE_DECIMAL:
            [[fallthrough]];
        case token::PRIMITIVE_STRING:
            [[fallthrough]];
        case token::PRIMITIVE_LIST:
            [[fallthrough]];
        case token::PRIMITIVE_TUPLE:
            [[fallthrough]];
        case token::PRIMITIVE_SET:
            [[fallthrough]];
        case token::PRIMITIVE_MAP:
            [[fallthrough]];
        case token::PRIMITIVE_ANY:
            is_reserved_primitive = true;
            break;
        case token::IDENTIFIER:
            break;
        default:
            return std::unexpected(
                PARSE_ERROR(tok, +"expected an identifier, but found: " + tok.token_kind_repr()));
    }

    iter.advance();  // pop the token

    return make_node<IdentExpr>(tok, is_reserved_primitive);
}

AST_NODE_IMPL_VISITOR(Jsonify, IdentExpr) { json.section("IdentExpr").add("name", node.name); }

// ---------------------------------------------------------------------------------------------- //

/* FIXME: use this method, if unused remove */
// should not be called by `parse` directly as it is a helper function
AST_NODE_IMPL(Expression, NamedArgumentExpr) {
    IS_NOT_EMPTY;

    // := '.' IdentExpr '=' E

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_DOT)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '.', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '.'

    ParseResult<IdentExpr> name = parse_IdentExpr();
    RETURN_IF_ERROR(name);

    if ((CURRENT_TOK != token::tokens::OPERATOR_ASSIGN)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '=', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '='

    ParseResult<> value = parse();
    RETURN_IF_ERROR(value);

    return make_node<NamedArgumentExpr>(name.value(), value.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, NamedArgumentExpr) {
    json.section("NamedArgumentExpr")
        .add("name", get_node_json(node.name))
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

// should not be called by `parse` directly as it is a helper function
AST_NODE_IMPL(Expression, ArgumentExpr) {
    IS_NOT_EMPTY;

    NodeT<ArgumentExpr> result;

    ParseResult<> lhs = parse();  // E(1)
    RETURN_IF_ERROR(lhs);

    NodeT<> lhs_node = lhs.value();

    if (lhs_node->getNodeType() == nodes::BinaryExpr) {
        NodeT<BinaryExpr> bin_expr = std::static_pointer_cast<BinaryExpr>(lhs_node);

        if (bin_expr->lhs->getNodeType() == nodes::IdentExpr &&
            bin_expr->op.token_kind() == token::tokens::OPERATOR_ASSIGN) {

            NodeT<NamedArgumentExpr> kwarg = make_node<NamedArgumentExpr>(
                std::static_pointer_cast<IdentExpr>(bin_expr->lhs), bin_expr->rhs);

            result       = make_node<ArgumentExpr>(kwarg);
            result->type = ArgumentExpr::ArgumentType::Keyword;

            return result;
        }
    }

    result       = make_node<ArgumentExpr>(lhs_node);
    result->type = ArgumentExpr::ArgumentType::Positional;

    return result;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArgumentExpr) {
    json.section("ArgumentExpr")
        .add("type", (int)node.type)
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ArgumentListExpr) {
    IS_NOT_EMPTY;

    // := '(' ArgumentExpr (',' ArgumentExpr)* ')'
    // in typical recursive descent fashion, we parse the first argument expression

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '(', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '('

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN) {
        iter.advance();  // skip ')'
        return make_node<ArgumentListExpr>(nullptr);
    }

    ParseResult<ArgumentExpr> first = parse_ArgumentExpr();

    RETURN_IF_ERROR(first);

    NodeT<ArgumentListExpr> args = make_node<ArgumentListExpr>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','
        ParseResult<ArgumentExpr> arg = parse_ArgumentExpr();
        RETURN_IF_ERROR(arg);
        args->args.push_back(arg.value());
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected ')', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip ')'

    return args;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArgumentListExpr) {
    std::vector<neo::json> args;

    for (const auto &arg : node.args) {
        args.push_back(get_node_json(arg));
    }

    json.section("ArgumentListExpr").add("args", args);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, GenericArgumentExpr) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, GenericInvokeExpr) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, GenericInvokePathExpr) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ScopePathExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E '::' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if ((CURRENT_TOK != token::tokens::OPERATOR_SCOPE)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '::', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '::'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<ScopePathExpr>(lhs.value(), rhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ScopePathExpr) {
    json.section("ScopePathExpr")
        .add("lhs", get_node_json(node.lhs))
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, DotPathExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E '.' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_DOT)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '.', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '.'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<DotPathExpr>(lhs.value(), rhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, DotPathExpr) {
    json.section("DotPathExpr")
        .add("lhs", get_node_json(node.lhs))
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ArrayAccessExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E '[' E ']'

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '[', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '['

    ParseResult<> index = parse();
    RETURN_IF_ERROR(index);

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected ']', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip ']'

    return make_node<ArrayAccessExpr>(lhs.value(), index.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ArrayAccessExpr) {
    json.section("ArrayAccessExpr")
        .add("array", get_node_json(node.lhs))
        .add("index", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, PathExpr, ParseResult<> simple_path) {
    IS_NOT_EMPTY;

    if (simple_path != nullptr && simple_path.has_value()) {
        NodeT<PathExpr> path = make_node<PathExpr>(simple_path.value());

        switch (simple_path.value()->getNodeType()) {
            case parser::ast::node::nodes::IdentExpr:
                path->type = PathExpr::PathType::Identifier;
                break;

            case parser::ast::node::nodes::ScopePathExpr:
                path->type = PathExpr::PathType::Scope;
                break;

            case parser::ast::node::nodes::DotPathExpr:
                path->type = PathExpr::PathType::Dot;
                break;

            default:
                return std::unexpected(PARSE_ERROR_MSG("expected a path expression, but found '" +
                                                       simple_path.value()->getNodeName() + "'"));
        }

        return path;
    }

    return std::unexpected(PARSE_ERROR_MSG("expected a simple path expression, but found nothing"));
}

AST_NODE_IMPL_VISITOR(Jsonify, PathExpr) {
    json.section("PathExpr").add("path", get_node_json(node.path)).add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, FunctionCallExpr, ParseResult<> lhs, ParseResult<> gens) {
    IS_NOT_EMPTY;

    /*
        FunctionCallExpr = {
            NodeT<PathExpr>
            NodeT<ArgumentListExpr>
            NodeT<GenericInvokeExpr>
        }
    */

    // if lhs is not empty, then we have a path expression
    ParseResult<PathExpr> path;
    // ParseResult<GenericInvokeExpr> generics;

    if (lhs != nullptr && lhs.has_value()) {
        path = parse_PathExpr(lhs.value());
    } else {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
        path = parse_PathExpr(lhs.value());
    }

    RETURN_IF_ERROR(path);

    // TODO: add support for generics

    IS_NOT_EMPTY;

    ParseResult<ArgumentListExpr> args = parse_ArgumentListExpr();

    RETURN_IF_ERROR(args);

    return make_node<FunctionCallExpr>(path.value(), args.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, FunctionCallExpr) {
    json.section("FunctionCallExpr")
        .add("path", get_node_json(node.path))
        .add("args", get_node_json(node.args));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ArrayLiteralExpr) {
    IS_NOT_EMPTY;
    // := '[' E (',' E)* ']'

    // [1, 2, 3, ]

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '[', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '['

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACKET) {
        iter.advance();  // skip ']'
        return std::unexpected(PARSE_ERROR_MSG("array literals must have at least one element"));
    }

    ParseResult<> first = parse();

    RETURN_IF_ERROR(first);

    NodeT<ArrayLiteralExpr> array = make_node<ArrayLiteralExpr>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACKET) {
            break;
        }

        ParseResult<> next = parse();
        RETURN_IF_ERROR(next);
        array->values.push_back(next.value());
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_BRACKET)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected ']', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip ']'

    return array;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArrayLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("ArrayLiteralExpr").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, TupleLiteralExpr, ParseResult<> starting_element) {
    IS_NOT_EMPTY;

    // := '(' E (',' E)* ')'

    ParseResult<> first;

    if (starting_element != nullptr && starting_element.has_value()) {
        first = starting_element;  // we have a starting element
        // the current token is ',' the '(' has already been parsed
    } else {
        if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_PAREN)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected '(', but found: " + CURRENT_TOK.token_kind_repr()));
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

    NodeT<TupleLiteralExpr> tuple = make_node<TupleLiteralExpr>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_PAREN) {
            break;
        }

        ParseResult<> next = parse();
        RETURN_IF_ERROR(next);
        tuple->values.push_back(next.value());
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected ')', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip ')'

    return tuple;
}

AST_NODE_IMPL_VISITOR(Jsonify, TupleLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("TupleLiteralExpr").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, SetLiteralExpr, ParseResult<> starting_value) {
    IS_NOT_EMPTY;

    // := '{' E (',' E)* '}'
    // {1}
    // {1, 2, 3, }

    NodeT<SetLiteralExpr> set;

    if (starting_value != nullptr && starting_value.has_value()) {
        // we have parsed the '{' and the first E, so we need to check if the current token is ','
        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            set = make_node<SetLiteralExpr>(starting_value.value());

            iter.advance();  // skip '}'
            return set;
        }

        if ((CURRENT_TOK != token::tokens::PUNCTUATION_COMMA)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected ',', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        set = make_node<SetLiteralExpr>(starting_value.value());
    } else {
        if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_BRACE)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected '{', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip '{'

        ParseResult<> first = parse();

        RETURN_IF_ERROR(first);

        set = make_node<SetLiteralExpr>(first.value());
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

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_BRACE)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '}', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '}'

    return set;
}

AST_NODE_IMPL_VISITOR(Jsonify, SetLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("SetLiteralExpr").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, MapPairExpr) {
    IS_NOT_EMPTY;

    // := E ':' E

    ParseResult<> key = parse();

    RETURN_IF_ERROR(key);

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_COLON)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected ':', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip ':'

    ParseResult<> value = parse();

    RETURN_IF_ERROR(value);

    return make_node<MapPairExpr>(key.value(), value.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, MapPairExpr) {
    json.section("MapPairExpr")
        .add("key", get_node_json(node.key))
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, MapLiteralExpr, ParseResult<> starting_key) {
    IS_NOT_EMPTY;

    // := '{' E (':' E)* '}'

    NodeT<MapPairExpr> pair;

    if (starting_key != nullptr && starting_key.has_value()) {
        // we have parsed the '{' and the first E, so we need to check if the current token is ':'
        if ((CURRENT_TOK != token::tokens::PUNCTUATION_COLON)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected ':', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip ':'

        ParseResult<> value = parse();
        RETURN_IF_ERROR(value);

        pair = make_node<MapPairExpr>(starting_key.value(), value.value());
    } else {
        if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_BRACE)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected '{', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip '{'

        ParseResult<MapPairExpr> tmp_pair = parse_MapPairExpr();
        RETURN_IF_ERROR(tmp_pair);

        pair = tmp_pair.value();
    }

    // := (',' E)* '}' is the remaining part of the map literal expression (there could be a
    // trailing comma)

    NodeT<MapLiteralExpr> map = make_node<MapLiteralExpr>(pair);

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            break;
        }

        ParseResult<MapPairExpr> next_pair = parse_MapPairExpr();
        RETURN_IF_ERROR(next_pair);

        map->values.push_back(next_pair.value());
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_BRACE)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '}', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '}'

    return map;
}

AST_NODE_IMPL_VISITOR(Jsonify, MapLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("MapLiteralExpr").add("values", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ObjInitExpr, bool skip_start_brace) {
    IS_NOT_EMPTY;

    // := '{' (NamedArgumentExpr (',' NamedArgumentExpr)*)? '}'

    if (!skip_start_brace) {
        if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_BRACE)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected '{', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip '{'
    }

    if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
        return std::unexpected(PARSE_ERROR(
            CURRENT_TOK, "expected a keyword argument, but got an empty object initializer"));
    }

    ParseResult<NamedArgumentExpr> first = parse_NamedArgumentExpr();
    RETURN_IF_ERROR(first);

    NodeT<ObjInitExpr> obj = make_node<ObjInitExpr>(first.value());

    while (CURRENT_TOK == token::tokens::PUNCTUATION_COMMA) {
        iter.advance();  // skip ','

        if (CURRENT_TOK == token::tokens::PUNCTUATION_CLOSE_BRACE) {
            break;
        }

        ParseResult<NamedArgumentExpr> next = parse_NamedArgumentExpr();
        RETURN_IF_ERROR(next);
        obj->kwargs.push_back(next.value());
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_BRACE)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '}', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '}'

    return obj;
}

AST_NODE_IMPL_VISITOR(Jsonify, ObjInitExpr) {
    std::vector<neo::json> kwargs;

    for (const auto &kwarg : node.kwargs) {
        kwargs.push_back(get_node_json(kwarg));
    }

    json.section("ObjInitExpr").add("keyword_args", kwargs);
}

// ---------------------------------------------------------------------------------------------- //

/* TODO: after Suite can be parsed */
AST_NODE_IMPL(Expression, LambdaExpr) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, LambdaExpr) { json.section("LambdaExpr"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, TernaryExpr, ParseResult<> E1) {
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

        if ((CURRENT_TOK != token::tokens::PUNCTUATION_COLON)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected ':', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip ':'

        ParseResult<> E3 = parse();
        RETURN_IF_ERROR(E3);

        return make_node<TernaryExpr>(E1.value(), E2.value(), E3.value());
    }

    if (CURRENT_TOK == token::tokens::KEYWORD_IF) {
        iter.advance();  // skip 'if'

        ParseResult<> E2 = parse();
        RETURN_IF_ERROR(E2);

        if ((CURRENT_TOK != token::tokens::KEYWORD_ELSE)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected 'else', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip 'else'

        ParseResult<> E3 = parse();
        RETURN_IF_ERROR(E3);

        return make_node<TernaryExpr>(E2.value(), E1.value(), E3.value());
    }

    return std::unexpected(PARSE_ERROR(
        CURRENT_TOK, "expected '?' or 'if', but found: " + CURRENT_TOK.token_kind_repr()));
}

AST_NODE_IMPL_VISITOR(Jsonify, TernaryExpr) {
    json.section("TernaryExpr")
        .add("condition", get_node_json(node.condition))
        .add("if_true", get_node_json(node.if_true))
        .add("if_false", get_node_json(node.if_false));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ParenthesizedExpr, ParseResult<> expr) {
    IS_NOT_EMPTY;

    // := '(' E ')'

    if (expr != nullptr && expr.has_value()) {
        // check if the current token is a ')'
        if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_PAREN)) {
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "expected ')', but found: " + CURRENT_TOK.token_kind_repr()));
        }

        iter.advance();  // skip ')'

        return make_node<ParenthesizedExpr>(expr.value());
    }

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_OPEN_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected '(', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip '('

    ParseResult<> inner = parse();

    RETURN_IF_ERROR(inner);

    if ((CURRENT_TOK != token::tokens::PUNCTUATION_CLOSE_PAREN)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected ')', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip ')'

    return make_node<ParenthesizedExpr>(inner.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ParenthesizedExpr) {
    json.section("ParenthesizedExpr").add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, CastExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E 'as' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if ((CURRENT_TOK != token::tokens::KEYWORD_AS)) {
        return std::unexpected(
            PARSE_ERROR(CURRENT_TOK, "expected 'as', but found: " + CURRENT_TOK.token_kind_repr()));
    }

    iter.advance();  // skip 'as'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<CastExpr>(lhs.value(), rhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, CastExpr) {
    json.section("CastExpr")
        .add("value", get_node_json(node.value))
        .add("type", get_node_json(node.type));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, InstOfExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E 'has' E | E 'derives' E

    if (lhs == nullptr || !lhs.has_value()) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    if ((CURRENT_TOK != token::tokens::KEYWORD_HAS ||
         CURRENT_TOK == token::tokens::KEYWORD_DERIVES)) {
        return std::unexpected(PARSE_ERROR(CURRENT_TOK,
                                           "expected 'has' or 'derives', but found: " +
                                               CURRENT_TOK.token_kind_repr()));
    }

    InstOfExpr::InstanceType op = (CURRENT_TOK == token::tokens::KEYWORD_HAS)
                                      ? InstOfExpr::InstanceType::Has
                                      : InstOfExpr::InstanceType::Derives;

    iter.advance();  // skip 'has' or 'derives'

    ParseResult<> rhs = parse();
    RETURN_IF_ERROR(rhs);

    return make_node<InstOfExpr>(lhs.value(), rhs.value(), op);
}

AST_NODE_IMPL_VISITOR(Jsonify, InstOfExpr) {
    json.section("InstOfExpr")
        .add("value", get_node_json(node.value))
        .add("type", get_node_json(node.type))
        .add("op", (int)node.op);
}

// ---------------------------------------------------------------------------------------------- //

/* DEPRECATED: a Type is deduced from context and at this stage is considered a Expression */
AST_NODE_IMPL(Expression, Type) {
    // if E(2) does not exist, check if its a & | * token, since if it is,
    // then return a unary expression since its a pointer or reference type
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
