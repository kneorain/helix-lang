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
/// [x] * AsyncExpr                 * AS -> ('spawn' | 'thread') E                               ///
/// [x] * AwaitExpr                 * AS -> 'await' E                                            ///
/// [ ] * ContextManagerExpr        * CM -> E 'as' ID Suite                                      ///
/// [ ] * LambdaExpr                * LE -> 'fn' TODO                                            ///
///                                                                                              ///
///                                /* generics */                                                ///
/// [ ] * GenericInvokeExpr         * GI -> '<' TY? ( ',' TY )* '>'                             ///
/// [ ] * GenericInvokePathExpr     * PGE -> PE GI                                               ///
///                                                                                              ///
///                                                                                              ///
/// [x] * Type    * TY -> ID | PT                                                                ///
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

#include <expected>
#include <memory>
#include <unordered_set>
#include <vector>

#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/private/AST_generate.hh"
#include "parser/ast/include/types/AST_modifiers.hh"
#include "token/include/config/Token_cases.def"
#include "parser/ast/include/private/AST_nodes.hh"
#include "parser/ast/include/nodes/AST_expressions.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"

// ---------------------------------------------------------------------------------------------- //

bool is_excepted(const __TOKEN_N::Token &tok, const std::unordered_set<__TOKEN_TYPES_N> &tokens);
int  get_precedence(const __TOKEN_N::Token &tok);

bool is_function_specifier(const __TOKEN_N::Token &tok);
bool is_function_qualifier(const __TOKEN_N::Token &tok);
bool is_storage_specifier(const __TOKEN_N::Token &tok);
bool is_access_specifier(const __TOKEN_N::Token &tok);
bool is_type_qualifier(const __TOKEN_N::Token &tok);
bool is_ffi_specifier(const __TOKEN_N::Token &tok);

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Expression, parse_primary) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;

    __TOKEN_N::Token  tok = CURRENT_TOK;
    ParseResult<> node;

    if (is_excepted(tok, IS_LITERAL)) {
        node = parse<LiteralExpr>();
    } else if (is_excepted(tok, IS_IDENTIFIER)) {
        node = parse<IdentExpr>();
    } else if (is_excepted(tok, IS_UNARY_OPERATOR)) {
        node = parse<UnaryExpr>();
    } else if (is_excepted(tok, IS_PUNCTUATION)) {
        if (tok.token_kind() ==
            __TOKEN_N::PUNCTUATION_OPEN_PAREN) {  /// at this point we either have a tuple or a
                                              /// parenthesized expression, so we need to do
                                              /// further analysis to determine which one it
                                              /// is
            iter.advance();                   /// skip '('
            ParseResult<> expr = parse();
            RETURN_IF_ERROR(expr);

            if (CURRENT_TOK == __TOKEN_N::PUNCTUATION_COMMA) {  /// if the next token is a
                                                            /// comma, then its a tuple
                node = parse<TupleLiteralExpr>(expr);
            } else {
                node = parse<ParenthesizedExpr>(expr);
            }
        } else if (tok.token_kind() == __TOKEN_N::PUNCTUATION_OPEN_BRACKET) {
            node = parse<ArrayLiteralExpr>();
        } else if (tok.token_kind() == __TOKEN_N::PUNCTUATION_OPEN_BRACE) {
            /// heres its either a set, a map or an object
            /// initializer, to determine which one it is, its
            /// quite simple we need to check if the next
            /// token is a '.' which if it is, then its an
            /// object initializer otherwise we parse E(1) and
            /// check if the next token is a ':', if it is,
            /// then its a map otherwise its a set

            iter.advance();  // skip '{'

            if (CURRENT_TOK == __TOKEN_N::PUNCTUATION_DOT) {
                node = parse<ObjInitExpr>(true);
            } else {
                ParseResult<> first = parse();
                RETURN_IF_ERROR(first);

                if (CURRENT_TOK == __TOKEN_N::PUNCTUATION_COLON) {
                    node = parse<MapLiteralExpr>(first);
                } else {
                    node = parse<SetLiteralExpr>(first);
                }
            }
        } else {
            if (tok.token_kind() != __TOKEN_N::PUNCTUATION_SEMICOLON) {
                return std::unexpected(
                    PARSE_ERROR_MSG("Expected an expression, but found nothing"));
            }
        }
    } else if (is_excepted(tok,
                           {__TOKEN_N::KEYWORD_THREAD, __TOKEN_N::KEYWORD_SPAWN, __TOKEN_N::KEYWORD_AWAIT})) {
        node = parse<AsyncThreading>();
    } else {
        return std::unexpected(
            PARSE_ERROR_MSG("Expected an expression, but found an unexpected token '" +
                            CURRENT_TOK.token_kind_repr() + "'"));
    }

    return node;
}

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Expression, parse) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;                   /// simple macro to check if the iterator is empty, expands to:
                                    /// if(iter.remaining_n() == 0) { return std::unexpected(...); }

    __TOKEN_N::Token tok;
    size_t       iter_n = 0;
    size_t n_max = iter.remaining_n() << 1;  /// this is a way to approx the tokens to parse, and is
                                             /// used to prevent the parser from going into an
                                             /// infinite loop  if the expression is malformed, this
                                             /// is a simple way to prevent stack overflows and
                                             /// memory exhaustion
    bool          continue_loop = true;
    ParseResult<> expr = parse_primary();  /// E(1) - this is always the first expression in the
                                           /// expression, we then build compound expressions from
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
            // case __TOKEN_N::PUNCTUATION_OPEN_ANGLE:  /// what to do if its ident '<' parms
            //                                      /// '>' '(' args ')' its now either a
            //                                      /// function call w a generic or its a
            //                                      /// binary expression may god help me
            //     NOT_IMPLEMENTED;
            // SOLUTION: 2 pass compiler
            case __TOKEN_N::PUNCTUATION_OPEN_PAREN:
                expr = parse<FunctionCallExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::PUNCTUATION_OPEN_BRACKET:
                expr = parse<ArrayAccessExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::PUNCTUATION_DOT:
                expr = parse<DotPathExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::OPERATOR_SCOPE:
                expr = parse<ScopePathExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::PUNCTUATION_OPEN_BRACE:
                if (iter.peek().has_value() &&
                    iter.peek().value().get().token_kind() != __TOKEN_TYPES_N::IDENTIFIER) {
                    continue_loop = false;
                    break;
                }

                if (iter.peek(2).has_value() &&
                    iter.peek(2).value().get().token_kind() != __TOKEN_TYPES_N::OPERATOR_ASSIGN) {
                    continue_loop = false;
                    break;
                }

                expr = parse<ObjInitExpr>(false, expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::KEYWORD_HAS:
            case __TOKEN_N::KEYWORD_DERIVES:
                expr = parse<InstOfExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::PUNCTUATION_QUESTION_MARK:
            case __TOKEN_N::KEYWORD_IF:
                expr = parse<TernaryExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::KEYWORD_AS:
                expr = parse<CastExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            case __TOKEN_N::LITERAL_CHAR:
            case __TOKEN_N::LITERAL_STRING:
                expr = parse<LiteralExpr>(expr);
                RETURN_IF_ERROR(expr);
                break;

            default:
                if (is_excepted(tok, IS_BINARY_OPERATOR)) {
                    expr = parse<BinaryExpr>(expr, get_precedence(tok));
                    RETURN_IF_ERROR(expr);
                } else if (is_excepted(tok, IS_UNARY_OPERATOR)) {
                    expr = parse<UnaryExpr>(expr);
                    RETURN_IF_ERROR(expr);
                } else if (tok == __TOKEN_N::PUNCTUATION_OPEN_PAREN) {
                    iter.advance();                         // skip '('
                    expr = parse<ParenthesizedExpr>(expr);  /// im not sure why this works, but
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

AST_NODE_IMPL(Expression, LiteralExpr, ParseResult<> str_concat) {
    IS_NOT_EMPTY;

    __TOKEN_N::Token tok = CURRENT_TOK;  // get tokens[0]
    iter.advance();                  // pop tokens[0]

    LiteralExpr::LiteralType type{};

    IS_NOT_NULL_RESULT(str_concat) {
        if (str_concat.value()->getNodeType() != nodes::LiteralExpr ||
            std::static_pointer_cast<LiteralExpr>(str_concat.value())->type !=
                LiteralExpr::LiteralType::String) {
            return std::unexpected(PARSE_ERROR(tok, "expected a string literal"));
        }

        NodeT<LiteralExpr> str = std::static_pointer_cast<LiteralExpr>(str_concat.value());

        if (tok.token_kind() != __TOKEN_N::LITERAL_STRING) {
            return std::unexpected(PARSE_ERROR(tok, "expected a string literal"));
        }

        str->value.set_value(str->value.value() + tok.value());
        return str;
    }

    switch (tok.token_kind()) {
        case __TOKEN_N::LITERAL_INTEGER:
            type = LiteralExpr::LiteralType::Integer;
            break;
        case __TOKEN_N::LITERAL_FLOATING_POINT:
            type = LiteralExpr::LiteralType::Float;
            break;
        case __TOKEN_N::LITERAL_STRING:
            type = LiteralExpr::LiteralType::String;
            break;
        case __TOKEN_N::LITERAL_CHAR:
            type = LiteralExpr::LiteralType::Char;
            break;
        case __TOKEN_N::LITERAL_TRUE:
        case __TOKEN_N::LITERAL_FALSE:
            type = LiteralExpr::LiteralType::Boolean;
            break;
        case __TOKEN_N::LITERAL_NULL:
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

    __TOKEN_N::Token tok = CURRENT_TOK;

    while (is_excepted(tok, IS_BINARY_OPERATOR) && get_precedence(tok) >= min_precedence) {
        int          precedence = get_precedence(tok);
        __TOKEN_N::Token op         = tok;

        iter.advance();

        ParseResult<> rhs = parse_primary();
        RETURN_IF_ERROR(rhs);

        tok = CURRENT_TOK;
        while (is_excepted(tok, IS_BINARY_OPERATOR) && get_precedence(tok) > precedence) {
            rhs = parse<BinaryExpr>(rhs, get_precedence(tok));
            RETURN_IF_ERROR(rhs);
            tok = CURRENT_TOK;
        }

        lhs = make_node<BinaryExpr>(lhs.value(), rhs.value(), op);
    }

    return std::static_pointer_cast<BinaryExpr>(lhs.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, BinaryExpr) {
    json.section("BinaryExpr")
        .add("lhs", get_node_json(node.lhs))
        .add("op", node.op)
        .add("rhs", get_node_json(node.rhs));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, UnaryExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := op E | E op

    IS_IN_EXCEPTED_TOKENS(IS_UNARY_OPERATOR);
    __TOKEN_N::Token op = CURRENT_TOK;
    iter.advance();

    IS_NULL_RESULT(lhs) {
        ParseResult<> rhs = parse();
        RETURN_IF_ERROR(rhs);

        return make_node<UnaryExpr>(rhs.value(), op, UnaryExpr::PosType::PreFix);
    }

    return make_node<UnaryExpr>(lhs.value(), op, UnaryExpr::PosType::PostFix);
}

AST_NODE_IMPL_VISITOR(Jsonify, UnaryExpr) {
    json.section("UnaryExpr")
        .add("operand", get_node_json(node.opd))
        .add("op", node.op)
        .add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, IdentExpr) {
    IS_NOT_EMPTY;

    // verify the current token is an identifier
    __TOKEN_N::Token tok                   = CURRENT_TOK;
    bool         is_reserved_primitive = false;

    IS_IN_EXCEPTED_TOKENS(IS_IDENTIFIER);

    if (tok.token_kind() != __TOKEN_N::IDENTIFIER) {
        is_reserved_primitive = true;
    }

    iter.advance();  // pop the token
    return make_node<IdentExpr>(tok, is_reserved_primitive);
}

AST_NODE_IMPL_VISITOR(Jsonify, IdentExpr) { json.section("IdentExpr", node.name); }

// ---------------------------------------------------------------------------------------------- //

/* FIXME: use this method, if unused remove */
// should not be called by `parse` directly as it is a helper function
AST_NODE_IMPL(Expression, NamedArgumentExpr, bool is_anonymous) {
    IS_NOT_EMPTY;

    // := '.'? IdentExpr '=' E
    if (is_anonymous) {
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_DOT);
        iter.advance();  // skip '.'
    } else {
        IS_NOT_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_DOT);
    }

    ParseResult<IdentExpr> name = parse<IdentExpr>();
    RETURN_IF_ERROR(name);

    IS_EXCEPTED_TOKEN(__TOKEN_N::OPERATOR_ASSIGN);
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
            bin_expr->op.token_kind() == __TOKEN_N::OPERATOR_ASSIGN) {

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

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_PAREN);
    iter.advance();  // skip '('

    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_PAREN) {
        iter.advance();  // skip ')'
        return make_node<ArgumentListExpr>(nullptr);
    }

    ParseResult<ArgumentExpr> first = parse<ArgumentExpr>();
    RETURN_IF_ERROR(first);

    NodeT<ArgumentListExpr> args = make_node<ArgumentListExpr>(first.value());

    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            ParseResult<ArgumentExpr> arg = parse<ArgumentExpr>();
            RETURN_IF_ERROR(arg);

            args->args.push_back(arg.value());
        }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_PAREN);
    iter.advance();  // skip ')'

    return args;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArgumentListExpr) {
    std::vector<neo::json> args;

    for (const auto &arg : node.args) {
        args.push_back(get_node_json(arg));
    }

    json.section("ArgumentListExpr", args);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, GenericInvokeExpr) {
    IS_NOT_EMPTY;
    // := '<' GenericArgumentExpr (',' GenericArgumentExpr)* '>'

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_ANGLE);
    iter.advance();  // skip '<'

    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_ANGLE) {
        iter.advance();  // skip '>'
        return make_node<GenericInvokeExpr>(nullptr);
    }

    ParseResult<Type> first = parse<Type>();
    RETURN_IF_ERROR(first);

    NodeT<GenericInvokeExpr> generics = make_node<GenericInvokeExpr>(first.value());

    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            ParseResult<Type> arg = parse<Type>();
            RETURN_IF_ERROR(arg);

            generics->args.push_back(arg.value());
        }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_ANGLE);
    iter.advance();  // skip '>'

    return generics;
}

AST_NODE_IMPL_VISITOR(Jsonify, GenericInvokeExpr) {
    std::vector<neo::json> args;

    for (const auto &arg : node.args) {
        args.push_back(get_node_json(arg));
    }

    json.section("GenericInvokeExpr", args);
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

    IS_NULL_RESULT(lhs) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::OPERATOR_SCOPE);
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

    IS_NULL_RESULT(lhs) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_DOT);
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

    IS_NULL_RESULT(lhs) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_BRACKET);
    iter.advance();  // skip '['

    ParseResult<> index = parse();
    RETURN_IF_ERROR(index);

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_BRACKET);
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

    // := IdentExpr | ScopePathExpr | DotPathExpr

    IS_NULL_RESULT(simple_path) {
        simple_path = parse_primary();
        RETURN_IF_ERROR(simple_path);
    }

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
            return std::unexpected(
                PARSE_ERROR_MSG("expected a simple path expression, but found nothing"));
    }

    return path;
}

AST_NODE_IMPL_VISITOR(Jsonify, PathExpr) {
    json.section("PathExpr").add("path", get_node_json(node.path)).add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, FunctionCallExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    /*
        FunctionCallExpr = {
            NodeT<PathExpr>
            NodeT<ArgumentListExpr>
            NodeT<GenericInvokeExpr>
        }
    */

    ParseResult<PathExpr> path;

    IS_NULL_RESULT(lhs) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    path = parse<PathExpr>(lhs.value());
    RETURN_IF_ERROR(path);

    // TODO: add support for generics

    ParseResult<ArgumentListExpr> args = parse<ArgumentListExpr>();
    RETURN_IF_ERROR(args);

    return make_node<FunctionCallExpr>(path.value(), args.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, FunctionCallExpr) {
    json.section("FunctionCallExpr")
        .add("path", get_node_json(node.path))
        .add("args", get_node_json(node.args))
        .add("generics", get_node_json(node.generic));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ArrayLiteralExpr) {
    IS_NOT_EMPTY;
    // := '[' E (',' E)* ']'

    // [1, 2, 3, ]

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_BRACKET);
    iter.advance();  // skip '['

    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACKET) {
        iter.advance();  // skip ']'
        return std::unexpected(PARSE_ERROR_MSG("array literals must have at least one element"));
    }

    ParseResult<> first = parse();

    RETURN_IF_ERROR(first);

    NodeT<ArrayLiteralExpr> array = make_node<ArrayLiteralExpr>(first.value());

    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACKET) {
                break;
            }

            ParseResult<> next = parse();
            RETURN_IF_ERROR(next);

            array->values.push_back(next.value());
        }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_BRACKET);
    iter.advance();  // skip ']'

    return array;
}

AST_NODE_IMPL_VISITOR(Jsonify, ArrayLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("ArrayLiteralExpr", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, TupleLiteralExpr, ParseResult<> starting_element) {
    IS_NOT_EMPTY;
    // := '(' E (',' E)* ')'

    ParseResult<> first;

    IS_NULL_RESULT(starting_element) {  // we dont have a starting element in this case
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_PAREN);
        iter.advance();  // skip '('

        if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_PAREN) {
            iter.advance();  // skip ')'
            return std::unexpected(
                PARSE_ERROR_MSG("tuple literals must have at least one element"));
        }

        first = parse();
        RETURN_IF_ERROR(first);
    }
    else {
        first = starting_element;
    }

    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_PAREN) {
        iter.advance();  // skip ')'
        return std::unexpected(PARSE_ERROR_MSG("tuple literals must have at least one element"));
    }

    NodeT<TupleLiteralExpr> tuple = make_node<TupleLiteralExpr>(first.value());
    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_PAREN) {
                break;
            }

            ParseResult<> next = parse();
            RETURN_IF_ERROR(next);

            tuple->values.push_back(next.value());
        }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_PAREN);
    iter.advance();  // skip ')'

    return tuple;
}

AST_NODE_IMPL_VISITOR(Jsonify, TupleLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("TupleLiteralExpr", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, SetLiteralExpr, ParseResult<> first) {
    IS_NOT_EMPTY;
    // := '{' E (',' E)* '}'
    // {1}
    // {1, 2, 3, }

    NodeT<SetLiteralExpr> set;

    IS_NULL_RESULT(first) {
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_BRACE);
        iter.advance();  // skip '{'

        first = parse();
        RETURN_IF_ERROR(first);
    }

    set = make_node<SetLiteralExpr>(first.value());

    // we have parsed the '{' and the first E, so we need to check if the current token is ','
    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACE) {
        iter.advance();  // skip '}'
        return set;
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_COMMA);  // we expect a comma here

    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACE) {
                break;
            }

            ParseResult<> next = parse();
            RETURN_IF_ERROR(next);

            set->values.push_back(next.value());
        }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_BRACE);
    iter.advance();  // skip '}'

    return set;
}

AST_NODE_IMPL_VISITOR(Jsonify, SetLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("SetLiteralExpr", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, MapPairExpr) {
    IS_NOT_EMPTY;
    // := E ':' E

    ParseResult<> key = parse();
    RETURN_IF_ERROR(key);

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_COLON);
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

AST_NODE_IMPL(Expression, MapLiteralExpr, ParseResult<> key) {
    IS_NOT_EMPTY;

    // := '{' E (':' E)* '}'

    NodeT<MapPairExpr> pair;

    IS_NULL_RESULT(key) {
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_BRACE);
        iter.advance();  // skip '{'

        ParseResult<MapPairExpr> pair = parse<MapPairExpr>();
        RETURN_IF_ERROR(pair);

        pair = pair.value();
    }
    else {
        // we have parsed the '{' and the first E, so we need to check if the current token is ':'
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_COLON);
        iter.advance();  // skip ':'

        ParseResult<> value = parse();
        RETURN_IF_ERROR(value);

        pair = make_node<MapPairExpr>(key.value(), value.value());
    }

    // := (',' E)* '}' is the remaining part of the map literal expression (there could be a
    // trailing comma)

    NodeT<MapLiteralExpr> map = make_node<MapLiteralExpr>(pair);

    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACE) {
                break;
            }

            ParseResult<MapPairExpr> next_pair = parse<MapPairExpr>();
            RETURN_IF_ERROR(next_pair);

            map->values.push_back(next_pair.value());
        }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_BRACE);
    iter.advance();  // skip '}'

    return map;
}

AST_NODE_IMPL_VISITOR(Jsonify, MapLiteralExpr) {
    std::vector<neo::json> values;

    for (const auto &value : node.values) {
        values.push_back(get_node_json(value));
    }

    json.section("MapLiteralExpr", values);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, ObjInitExpr, bool skip_start_brace, ParseResult<> obj_path) {
    IS_NOT_EMPTY;

    // := PATH? '{' (NamedArgumentExpr (',' NamedArgumentExpr)*)? '}'

    bool is_anonymous = true;

    IS_NOT_NULL_RESULT(obj_path) { is_anonymous = false; }

    if (!skip_start_brace) {
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_BRACE);
        iter.advance();  // skip '{'
    }

    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACE) {
        return std::unexpected(PARSE_ERROR(
            CURRENT_TOK, "expected a keyword argument, but got an empty object initializer"));
    }

    ParseResult<NamedArgumentExpr> first = parse<NamedArgumentExpr>(is_anonymous);
    RETURN_IF_ERROR(first);

    NodeT<ObjInitExpr> obj = make_node<ObjInitExpr>(first.value());

    while
        CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
            iter.advance();  // skip ','

            if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_BRACE) {
                break;
            }

            ParseResult<NamedArgumentExpr> next = parse<NamedArgumentExpr>(is_anonymous);
            RETURN_IF_ERROR(next);

            obj->kwargs.push_back(next.value());
        }

    if (is_anonymous) {
        obj->path = obj_path.value();
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_BRACE);
    iter.advance();  // skip '}'

    return obj;
}

AST_NODE_IMPL_VISITOR(Jsonify, ObjInitExpr) {
    std::vector<neo::json> kwargs;

    for (const auto &kwarg : node.kwargs) {
        kwargs.push_back(get_node_json(kwarg));
    }

    json.section("ObjInitExpr").add("keyword_args", kwargs).add("path", get_node_json(node.path));
}

// ---------------------------------------------------------------------------------------------- //

/* TODO: after Suite can be parsed */
AST_NODE_IMPL(Expression, LambdaExpr) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, LambdaExpr) {
    std::vector<neo::json> args;

    for (const auto &arg : node.args) {
        args.push_back(get_node_json(arg));
    }

    json.section("LambdaExpr")
        .add("args", args)
        .add("body", get_node_json(node.body))
        .add("return_type", get_node_json(node.ret));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, TernaryExpr, ParseResult<> E1) {
    IS_NOT_EMPTY;

    // := (E '?' E ':' E) | (E 'if' E 'else' E)
    // true ? 1 : 0 | 1 if true else 0

    IS_NULL_RESULT(E1) {
        E1 = parse();
        RETURN_IF_ERROR(E1);
    }

    if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_QUESTION_MARK) {
        iter.advance();  // skip '?'

        ParseResult<> E2 = parse();
        RETURN_IF_ERROR(E2);

        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_COLON);
        iter.advance();  // skip ':'

        ParseResult<> E3 = parse();
        RETURN_IF_ERROR(E3);

        return make_node<TernaryExpr>(E1.value(), E2.value(), E3.value());
    }

    if CURRENT_TOKEN_IS (__TOKEN_N::KEYWORD_IF) {
        iter.advance();  // skip 'if'

        ParseResult<> E2 = parse();
        RETURN_IF_ERROR(E2);

        IS_EXCEPTED_TOKEN(__TOKEN_N::KEYWORD_ELSE);
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

    IS_NOT_NULL_RESULT(expr) {
        // check if the current token is a ')'
        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_PAREN);
        iter.advance();  // skip ')'

        return make_node<ParenthesizedExpr>(expr.value());
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_PAREN);
    iter.advance();  // skip '('

    ParseResult<> inner = parse();
    RETURN_IF_ERROR(inner);

    IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_PAREN);
    iter.advance();  // skip ')'

    return make_node<ParenthesizedExpr>(inner.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ParenthesizedExpr) {
    json.section("ParenthesizedExpr", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, CastExpr, ParseResult<> lhs) {
    IS_NOT_EMPTY;

    // := E 'as' E

    IS_NULL_RESULT(lhs) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

    IS_EXCEPTED_TOKEN(__TOKEN_N::KEYWORD_AS);
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

    InstOfExpr::InstanceType op = InstOfExpr::InstanceType::Derives;

    IS_NULL_RESULT(lhs) {
        lhs = parse();
        RETURN_IF_ERROR(lhs);
    }

#define INST_OF_OPS {__TOKEN_N::KEYWORD_HAS, __TOKEN_N::KEYWORD_DERIVES}
    IS_IN_EXCEPTED_TOKENS(INST_OF_OPS);
#undef INST_OF_OPS

    if CURRENT_TOKEN_IS (__TOKEN_N::KEYWORD_HAS)
        op = InstOfExpr::InstanceType::Has;
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
AST_NODE_IMPL(Expression, Type) {  // TODO - REMAKE using the new Modifiers and stricter rules, such
                                   // as no types can contain a binary expression
    // if E(2) does not exist, check if its a & | * token, since if it is,
    // then return a unary expression since its a pointer or reference type

    // types are quite complex in helix since this is the gammer:
    // Type := ('fn' '(' (Type ((',' Type)*)?)? ')' ('->' Type)?)
    //      | (TypePrefixes ((',' TypePrefixes)*)?)? PathExpr GenericInvocationExpr?

    // enums: StorageSpecifier, FFISpecifier, TypeQualifier, AccessSpecifier, FunctionSpecifier,
    // FunctionQualifier
    IS_NOT_EMPTY;

    Modifiers   fn_specifiers(Modifiers::ExpectedModifier::FuncSpec);
    NodeT<Type> node = make_node<Type>(true);

    if (CURRENT_TOKEN_IS(__TOKEN_N::KEYWORD_FUNCTION)) {
        iter.advance();  // skip 'fn'
        NodeT<LambdaExpr> lambda = make_node<LambdaExpr>(iter.peek_back()->get());

        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_OPEN_PAREN);
        iter.advance();  // skip '('

        if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_PAREN) {
            iter.advance();  // skip ')'
            return make_node<Type>(lambda);
        }

        ParseResult<> first = parse<Type>();
        RETURN_IF_ERROR(first);

        lambda->args.push_back(first.value());

        while
            CURRENT_TOKEN_IS(__TOKEN_N::PUNCTUATION_COMMA) {
                iter.advance();  // skip ','

                if CURRENT_TOKEN_IS (__TOKEN_N::PUNCTUATION_CLOSE_PAREN) {
                    break;
                }

                ParseResult<> next = parse<Type>();
                RETURN_IF_ERROR(next);

                lambda->args.push_back(next.value());
            }

        IS_EXCEPTED_TOKEN(__TOKEN_N::PUNCTUATION_CLOSE_PAREN);
        iter.advance();  // skip ')'

        if CURRENT_TOKEN_IS (__TOKEN_N::OPERATOR_ARROW) {
            iter.advance();  // skip '->'

            ParseResult<> ret = parse<Type>();
            RETURN_IF_ERROR(ret);

            lambda->ret = ret.value();
        }

        return make_node<Type>(lambda);
    }

    while (node->specifiers.find_add(CURRENT_TOK)) {
        iter.advance();  // TODO: Handle 'ffi' ('class' | 'interface' | 'struct' | 'enum' | 'union'
                         // | 'type')
    }

    ParseResult<> EXPR = parse_primary();
    RETURN_IF_ERROR(EXPR);

    bool continue_loop = true;

    while (continue_loop) {
        const __TOKEN_N::Token &tok = CURRENT_TOK;

        switch (tok.token_kind()) {
            // case __TOKEN_N::PUNCTUATION_OPEN_ANGLE:  /// what to do if its ident '<' parms
            //                                      /// '>' '(' args ')' its now either a
            //                                      /// function call w a generic or its a
            //                                      /// binary expression may god help me
            //     NOT_IMPLEMENTED;
            // SOLUTION: 2 pass compiler
            case __TOKEN_N::PUNCTUATION_OPEN_PAREN:
                EXPR = parse<FunctionCallExpr>(EXPR);
                RETURN_IF_ERROR(EXPR);
                break;

            case __TOKEN_N::PUNCTUATION_OPEN_BRACKET:
                EXPR = parse<ArrayAccessExpr>(EXPR);
                RETURN_IF_ERROR(EXPR);
                break;

            case __TOKEN_N::OPERATOR_SCOPE:
                EXPR = parse<ScopePathExpr>(EXPR);
                RETURN_IF_ERROR(EXPR);
                break;

            case __TOKEN_N::KEYWORD_HAS:
            case __TOKEN_N::KEYWORD_DERIVES:
                return std::unexpected(
                    PARSE_ERROR(tok, "expected a type, but found a 'has' or 'derives' keyword"));

            case __TOKEN_N::PUNCTUATION_QUESTION_MARK:
            case __TOKEN_N::KEYWORD_IF:
                EXPR = parse<TernaryExpr>(EXPR);
                RETURN_IF_ERROR(EXPR);
                break;

            case __TOKEN_N::KEYWORD_AS:
                return std::unexpected(
                    PARSE_ERROR(tok, "expected a type, but found a 'as' keyword"));
            case __TOKEN_N::PUNCTUATION_OPEN_ANGLE:  // generic lol
            {
                ParseResult<GenericInvokeExpr> generic = parse<GenericInvokeExpr>();
                RETURN_IF_ERROR(generic);

                node->generics = generic.value();
                continue_loop  = false;
                break;
            }

            default:
                if (is_excepted(tok, IS_UNARY_OPERATOR)) {
                    EXPR = parse<UnaryExpr>(EXPR);
                    RETURN_IF_ERROR(EXPR);
                } else if (tok == __TOKEN_N::PUNCTUATION_OPEN_PAREN) {
                    iter.advance();                         // skip '('
                    EXPR = parse<ParenthesizedExpr>(EXPR);  /// im not sure why this works, but
                                                            /// based on small tests, it seems
                                                            /// to work fine i'll find out soon
                                                            /// enough if it doesn't
                    RETURN_IF_ERROR(EXPR);
                } else {
                    continue_loop = false;
                }
        }
    }

    node->value = EXPR.value();
    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, Type) {
    json.section("Type")
        .add("value", get_node_json(node.value))
        .add("generics", get_node_json(node.generics))
        .add("specifiers", node.specifiers.to_json());
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Expression, AsyncThreading) {
    IS_NOT_EMPTY;
    // := ('await' | 'spawn' | 'thread') E

    __TOKEN_N::Token tok = CURRENT_TOK;

#define ASYNC_THREADING_OPS {__TOKEN_N::KEYWORD_AWAIT, __TOKEN_N::KEYWORD_SPAWN, __TOKEN_N::KEYWORD_THREAD}

    IS_IN_EXCEPTED_TOKENS(ASYNC_THREADING_OPS);
    iter.advance();  // skip 'await', 'spawn' or 'thread'

#undef ASYNC_THREADING_OPS

    ParseResult<> expr = parse();
    RETURN_IF_ERROR(expr);

    return make_node<AsyncThreading>(expr.value(), tok);
}

AST_NODE_IMPL_VISITOR(Jsonify, AsyncThreading) {
    json.section("AsyncThreading")
        .add("value", get_node_json(node.value))
        .add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

bool is_excepted(const __TOKEN_N::Token &tok, const std::unordered_set<__TOKEN_TYPES_N> &tokens) {
    return tokens.find(tok.token_kind()) != tokens.end();
}

int get_precedence(const __TOKEN_N::Token &tok) {
    switch (tok.token_kind()) {
        case __TOKEN_N::OPERATOR_MUL:
        case __TOKEN_N::OPERATOR_DIV:
        case __TOKEN_N::OPERATOR_MOD:
        case __TOKEN_N::OPERATOR_POW:
            return 12;

        case __TOKEN_N::OPERATOR_ADD:
        case __TOKEN_N::OPERATOR_SUB:
            return 11;

        case __TOKEN_N::OPERATOR_BITWISE_L_SHIFT:
        case __TOKEN_N::OPERATOR_BITWISE_R_SHIFT:
            return 10;

        case __TOKEN_N::OPERATOR_GREATER_THAN_EQUALS:
        case __TOKEN_N::OPERATOR_LESS_THAN_EQUALS:
        case __TOKEN_N::PUNCTUATION_OPEN_ANGLE:
        case __TOKEN_N::PUNCTUATION_CLOSE_ANGLE:
            return 9;

        case __TOKEN_N::OPERATOR_EQUAL:
        case __TOKEN_N::OPERATOR_NOT_EQUAL:
            return 8;

        case __TOKEN_N::OPERATOR_BITWISE_AND:
            return 7;
        case __TOKEN_N::OPERATOR_BITWISE_XOR:
            return 6;
        case __TOKEN_N::OPERATOR_BITWISE_OR:
            return 5;
        case __TOKEN_N::OPERATOR_LOGICAL_AND:
            return 4;
        case __TOKEN_N::OPERATOR_LOGICAL_OR:
            // MISSING ?:
            return 3;
        case __TOKEN_N::OPERATOR_RANGE_INCLUSIVE:
        case __TOKEN_N::OPERATOR_RANGE:
            return 2;

        case __TOKEN_N::OPERATOR_ADD_ASSIGN:
        case __TOKEN_N::OPERATOR_SUB_ASSIGN:
        case __TOKEN_N::OPERATOR_MUL_ASSIGN:
        case __TOKEN_N::OPERATOR_DIV_ASSIGN:
        case __TOKEN_N::OPERATOR_MOD_ASSIGN:
        case __TOKEN_N::OPERATOR_ASSIGN:
            return 1;

        default:
            return 0;  // Return 0 for non-binary operators
    }
}

bool is_ffi_specifier(const __TOKEN_N::Token &tok) {
    return is_excepted(tok,
                       {__TOKEN_N::KEYWORD_CLASS,
                        __TOKEN_N::KEYWORD_INTERFACE,
                        __TOKEN_N::KEYWORD_STRUCT,
                        __TOKEN_N::KEYWORD_ENUM,
                        __TOKEN_N::KEYWORD_UNION,
                        __TOKEN_N::KEYWORD_TYPE});
};

bool is_type_qualifier(const __TOKEN_N::Token &tok) {
    return is_excepted(tok,
                       {__TOKEN_N::KEYWORD_CONST,
                        __TOKEN_N::KEYWORD_MODULE,
                        __TOKEN_N::KEYWORD_YIELD,
                        __TOKEN_N::KEYWORD_ASYNC,
                        __TOKEN_N::KEYWORD_FFI,
                        __TOKEN_N::KEYWORD_STATIC,
                        __TOKEN_N::KEYWORD_MACRO});
};

bool is_access_specifier(const __TOKEN_N::Token &tok) {
    return is_excepted(tok,
                       {__TOKEN_N::KEYWORD_PUBLIC,
                        __TOKEN_N::KEYWORD_PRIVATE,
                        __TOKEN_N::KEYWORD_PROTECTED,
                        __TOKEN_N::KEYWORD_INTERNAL});
};

bool is_function_specifier(const __TOKEN_N::Token &tok) {
    return is_excepted(tok,
                       {__TOKEN_N::KEYWORD_INLINE,
                        __TOKEN_N::KEYWORD_ASYNC,
                        __TOKEN_N::KEYWORD_STATIC,
                        __TOKEN_N::KEYWORD_CONST,
                        __TOKEN_N::KEYWORD_EVAL});
};

bool is_function_qualifier(const __TOKEN_N::Token &tok) {
    return is_excepted(tok,
                       {__TOKEN_N::KEYWORD_DEFAULT,
                        __TOKEN_N::KEYWORD_PANIC,
                        __TOKEN_N::KEYWORD_DELETE,
                        __TOKEN_N::KEYWORD_CONST});
};

bool is_storage_specifier(const __TOKEN_N::Token &tok) {
    return is_excepted(
        tok,
        {__TOKEN_N::KEYWORD_FFI, __TOKEN_N::KEYWORD_STATIC, __TOKEN_N::KEYWORD_ASYNC, __TOKEN_N::KEYWORD_EVAL});
};