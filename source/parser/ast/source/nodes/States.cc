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
///  @file States.cc                                                                             ///
///  @brief This file contains the entire logic to parse statements using a recursive descent    ///
///         parser. the parser adheres to an ll(1) grammar, which means it processes the input   ///
///         left-to-right and constructs the leftmost derivation using one token of lookahead.   ///
///                                                                                              ///
///  The parser is implemented using the `parse` method, which is a recursive descent parser     ///
///     that uses the token list to parse the Statement grammar.                                 ///
///                                                                                              ///
///  @code                                                                                       ///
///  Statement state(tokens);                                                                    ///
///  ParseResult<> node = state.parse();                                                         ///
///                                                                                              ///
///  if (node.has_value()) {                                                                     ///
///      NodeT<> ast = node.value();                                                             ///
///  } else {                                                                                    ///
///      std::cerr << node.error().what() << std::endl;                                          ///
///  }                                                                                           ///
///  @endcode                                                                                    ///
///                                                                                              ///
///  By default, the parser will parse the entire statement, but you can also parse a specific   ///
///     statement by calling the specific parse method. or get a specific node by calling parse  ///
///     and then passing a template argument to the method.                                      ///
///                                                                                              ///
///  @code                                                                                       ///
///  Statement state(tokens);                                                                    ///
///  ParseResult<ReturnState> node = state.parse<ReturnState>();                                 ///
///  @endcode                                                                                    ///
///                                                                                              ///
/// The parser is implemented using the following grammar:                                       ///
///                                                                                              ///
/// STS *           /* node types */                                                             ///
/// [x] * Literal    * L                                                                         ///
/// [x] * Operator   * O                                                                         ///
/// [x] * Token      * T                                                                         ///
/// [x] * Statement  * E                                                                         ///
///                                                                                              ///
/// STS *               /* statement types */                                                    ///
/// [x] * BreakState     * 'break' ';'                                                           ///
/// [x] * ContinueState  * 'continue' ';'                                                        ///
/// [x] * ExprState      * E ';'                                                                 ///
/// [x] * BlockState     * '{' Statement* '}'                                                    ///
/// [x] * SuiteState     * BlockState | (':' Statement)                                          ///
/// [x] * ReturnState    * 'return' E? ';'                                                       ///
///                                                                                              ///
/// [x] * YieldState         * 'yield' E ';'                                                     ///
/// [x] * DeleteState        * 'delete' E ';'                                                    ///
/// [ ] * SwitchState        * 'switch' E '{' SwitchCaseState* '}'                       ///
/// [ ] * IfState            * ('if' | 'unless') E SuiteState (ElseState)?               ///
/// [ ] * ElseState          * 'else' SuiteState                                                 ///
/// [ ] * WhileState         * 'while' E SuiteState                                      ///
/// [ ] * ForState           * 'for' ForPyStatementCore | ForCStatementCore SuiteState   ///
/// [ ] * ForPyStatementCore * NamedVarSpecifier 'in' E SuiteState                               ///
/// [ ] * ForCStatementCore  * (E)? ';' (E)? ';' (E)? SuiteState                                 ///
/// [ ] * NamedVarSpecifier  * Ident (':' E)?                                                    ///
/// [ ] * SwitchCaseState    * 'case' E SuiteState | 'default' SuiteState                        ///
/// [ ] * TryState           * 'try' SuiteState (CatchState) (FinallyState)?                     ///
/// [ ] * CatchState         * 'catch' (NamedVarSpecifier (',' NamedVarSpecifier)*)? SuiteState
/// (CatchState | FinallyState)? /// [ ] * FinallyState       * 'finally' SuiteState /// [x] *
/// PanicState         * 'panic' ';'                                                       ///
///                                                                                              ///
/// [ ] * ImportState        * 'import' (SingleImportState | MultiImportState)                   ///
/// [ ] * AliasState         * Ident 'as' Ident ';'                                              ///
/// [ ] * SingleImportState  * Ident (',' Ident)*                                                ///
/// [ ] * MultiImportState   * Ident 'as' Ident (',' Ident 'as' Ident)*                          ///
///                                                                                              ///
//===-----------------------------------------------------------------------------------------====//

#include <__expected/unexpected.h>

#include <cstddef>
#include <expected>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/config/AST_generate.hh"
#include "parser/ast/include/config/case_types.def"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/nodes/AST_Expressions.hh"
#include "parser/ast/include/nodes/AST_Statements.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

// ---------------------------------------------------------------------------------------------- //

bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens);
std::vector<token::Token> get_modifiers(token::TokenList::TokenListIter &iter);
bool                      is_ffi_specifier(const token::Token &tok);
bool                      is_type_qualifier(const token::Token &tok);
bool                      is_access_specifier(const token::Token &tok);
bool                      is_function_specifier(const token::Token &tok);
bool                      is_function_qualifier(const token::Token &tok);
bool                      is_storage_specifier(const token::Token &tok);

// ---------------------------------------------------------------------------------------------- //

// REVALUATE: if a parse_primary is needed for statements or if it should be removed
// AST_BASE_IMPL(Statement, parse_primary) {  // NOLINT(readability-function-cognitive-complexity)
//     IS_NOT_EMPTY;
//     NOT_IMPLEMENTED;
// }

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Statement, parse) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;                  /// simple macro to check if the iterator is empty, expands to:
                                   /// if(iter.remaining_n() == 0) { return std::unexpected(...); }

    token::Token tok = CURRENT_TOK;          /// get the current token from the iterator
    modifiers        = get_modifiers(iter);  /// get the modifiers for the statement

    switch (tok.token_kind()) {
        // TODO: case token::KEYWORD_IMPORT
        case token::KEYWORD_IF:
        case token::KEYWORD_UNLESS:
            return parse_IfState();

        case token::KEYWORD_RETURN:
            return parse_ReturnState();

        case token::KEYWORD_FOR:
            return parse_ForState();

        case token::KEYWORD_WHILE:
            return parse_WhileState();

        case token::KEYWORD_BREAK:
            return parse_BreakState();

        case token::KEYWORD_CONTINUE:
            return parse_ContinueState();

        case token::KEYWORD_SWITCH:
            return parse_SwitchState();

        case token::KEYWORD_TRY:
            return parse_TryState();

        case token::KEYWORD_PANIC:
            return parse_PanicState();

        case token::KEYWORD_FINALLY:
            return parse_FinallyState();

        case token::KEYWORD_YIELD:
            return parse_YieldState();

        case token::KEYWORD_DELETE:
            return parse_DeleteState();

        case token::KEYWORD_ELSE:
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "found dangling 'else' without a matching 'if' or 'unless'"));

        case token::KEYWORD_CASE:
            return std::unexpected(
                PARSE_ERROR(CURRENT_TOK, "found dangling 'case' without a matching 'switch'"));

        case token::KEYWORD_DEFAULT:
            return std::unexpected(
                PARSE_ERROR(CURRENT_TOK, "found dangling 'default' without a matching 'switch'"));

        case token::KEYWORD_CATCH:
            return std::unexpected(
                PARSE_ERROR(CURRENT_TOK, "found dangling 'catch' without a matching 'try'"));

        default:
            return parse_ExprState();
    }
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, NamedVarSpecifier, bool force_type) {
    IS_NOT_EMPTY;

    // := Ident (':' Type)?

    Expression expr_parser(iter);

    ParseResult<IdentExpr> path = expr_parser.parse<IdentExpr>();
    RETURN_IF_ERROR(path);

    if (force_type) {
        IS_EXCEPTED_TOKEN(token::PUNCTUATION_COLON);
    }

    if (CURRENT_TOKEN_IS(token::PUNCTUATION_COLON)) {
        iter.advance();  // skip ':'

        ParseResult<Type> type = expr_parser.parse<Type>();
        RETURN_IF_ERROR(type);

        return make_node<NamedVarSpecifier>(path.value(), type.value());
    }

    return make_node<NamedVarSpecifier>(path.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, NamedVarSpecifier) {
    json.section("NamedVarSpecifier")
        .add("path", get_node_json(node.path))
        .add("type", get_node_json(node.type));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ForPyStatementCore) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ForPyStatementCore) { json.section("ForPyStatementCore"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ForCStatementCore) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ForCStatementCore) { json.section("ForCStatementCore"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ForState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ForState) { json.section("ForState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, WhileState) {
    IS_NOT_EMPTY;
    // := 'while' E SuiteState

    Expression expr_parser(iter);

    IS_EXCEPTED_TOKEN(token::KEYWORD_WHILE);
    iter.advance();  // skip 'while'

    ParseResult<> condition = expr_parser.parse();
    RETURN_IF_ERROR(condition);

    ParseResult<SuiteState> body = parse<SuiteState>();
    RETURN_IF_ERROR(body);

    return make_node<WhileState>(condition.value(), body.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, WhileState) {
    json.section("WhileState")
        .add("condition", get_node_json(node.condition))
        .add("body", get_node_json(node.body));
}

// ---------------------------------------------------------------------------------------------- //

/* TODO: REFACTOR */
AST_NODE_IMPL(Statement, ElseState, Expression &expr_parser) {
    IS_NOT_EMPTY;

    // := ('else' Suite) | ('else' ('if' | 'unless') E Suite)

    NodeT<ElseState> node = make_node<ElseState>(true);

    IS_EXCEPTED_TOKEN(token::KEYWORD_ELSE);
    iter.advance();  // skip 'else'

    if (CURRENT_TOKEN_IS(token::KEYWORD_IF) || CURRENT_TOKEN_IS(token::KEYWORD_UNLESS)) {
        node->type = CURRENT_TOKEN_IS(token::KEYWORD_IF) ? ElseState::ElseType::ElseIf
                                                         : ElseState::ElseType::ElseUnless;
        iter.advance();  // skip 'if' | 'unless'

        ParseResult<> expr = expr_parser.parse();
        RETURN_IF_ERROR(expr);

        node->condition = expr.value();
    }

    ParseResult<SuiteState> body = parse<SuiteState>();
    RETURN_IF_ERROR(body);

    node->body = body.value();

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, ElseState) {
    json.section("ElseState")
        .add("condition", get_node_json(node.condition))
        .add("body", get_node_json(node.body))
        .add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

/* TODO: REFACTOR */
AST_NODE_IMPL(Statement, IfState) {
    IS_NOT_EMPTY;

    // := ('if' | 'unless') E SuiteState (ElseState*)?

    Expression     expr_parser(iter);
    bool           is_unless = false;
    NodeT<IfState> node;

#define IF_UNLESS_TOKENS {token::KEYWORD_IF, token::KEYWORD_UNLESS}
    IS_IN_EXCEPTED_TOKENS(IF_UNLESS_TOKENS);
    if (CURRENT_TOKEN_IS(token::KEYWORD_UNLESS)) {
        is_unless = true;
    }

    iter.advance();  // skip 'if' or 'unless'
#undef IF_UNLESS_TOKENS

    auto condition = expr_parser.parse();
    RETURN_IF_ERROR(condition);

    node = make_node<IfState>(condition.value());

    if (is_unless) {
        node->type = IfState::IfType::Unless;
    }

    ParseResult<SuiteState> body = parse<SuiteState>();
    RETURN_IF_ERROR(body);

    node->body = body.value();

    if CURRENT_TOKEN_IS (token::KEYWORD_ELSE) {
        bool         captured_final_else = false;
        token::Token starting_else;

        ParseResult<ElseState> else_body = parse<ElseState>(expr_parser);
        RETURN_IF_ERROR(else_body);

        node->else_body.emplace_back(else_body.value());

        if (else_body.value()->type == ElseState::ElseType::Else) {
            captured_final_else = true;
        }

        while (CURRENT_TOKEN_IS(token::KEYWORD_ELSE)) {
            starting_else = CURRENT_TOK;

            else_body = parse<ElseState>(expr_parser);
            RETURN_IF_ERROR(else_body);

            node->else_body.emplace_back(else_body.value());

            if (else_body.value()->type == ElseState::ElseType::Else) {
                if (captured_final_else) {
                    return std::unexpected(
                        PARSE_ERROR(starting_else, "redefinition of captured else block"));
                }

                captured_final_else = true;
            }
        }
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, IfState) {
    std::vector<neo::json> else_body;

    for (const auto &else_state : node.else_body) {
        else_body.push_back(get_node_json(else_state));
    }

    json.section("IfState")
        .add("condition", get_node_json(node.condition))
        .add("body", get_node_json(node.body))
        .add("else_body", else_body)
        .add("type", (int)node.type);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, SwitchCaseState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, SwitchCaseState) { json.section("SwitchCaseState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, SwitchState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, SwitchState) { json.section("SwitchState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, YieldState) {
    IS_NOT_EMPTY;

    IS_EXCEPTED_TOKEN(token::KEYWORD_YIELD);
    iter.advance();

    auto expr = Expression(iter).parse();
    RETURN_IF_ERROR(expr);

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();

    return make_node<YieldState>(expr.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, YieldState) {
    json.section("YieldState").add("expr", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, DeleteState) {
    IS_NOT_EMPTY;

    IS_EXCEPTED_TOKEN(token::KEYWORD_DELETE);
    iter.advance();

    auto expr = Expression(iter).parse();
    RETURN_IF_ERROR(expr);

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();

    return make_node<DeleteState>(expr.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, DeleteState) {
    json.section("DeleteState").add("expr", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, AliasState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, AliasState) { json.section("AliasState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, SingleImportState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, SingleImportState) { json.section("SingleImportState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, MultiImportState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, MultiImportState) { json.section("MultiImportState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ImportState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ImportState) { json.section("ImportState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ReturnState) {
    IS_NOT_EMPTY;

    IS_EXCEPTED_TOKEN(token::KEYWORD_RETURN);
    iter.advance();  // skip 'return'

    auto expr = Expression(iter).parse();
    RETURN_IF_ERROR(expr);

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();  // skip ';'

    return make_node<ReturnState>(expr.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ReturnState) {
    json.section("ReturnState").add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, BreakState) {
    IS_NOT_EMPTY;

    IS_EXCEPTED_TOKEN(token::KEYWORD_BREAK);
    auto node = make_node<BreakState>(CURRENT_TOK);

    iter.advance();

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, BreakState) {
    json.section("BreakState").add("marker", node.marker);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ContinueState) {
    IS_NOT_EMPTY;

    IS_EXCEPTED_TOKEN(token::KEYWORD_CONTINUE);
    auto node = make_node<ContinueState>(CURRENT_TOK);

    iter.advance();

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, ContinueState) {
    json.section("ContinueState").add("marker", node.marker);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ExprState) {
    IS_NOT_EMPTY;

    auto expr = Expression(iter).parse();
    RETURN_IF_ERROR(expr);

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();

    return make_node<ExprState>(expr.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, ExprState) {
    json.section("ExprState").add("expr", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, SuiteState) {
    IS_NOT_EMPTY;

    // := BlockState | (':' Statement)

    if CURRENT_TOKEN_IS (token::PUNCTUATION_OPEN_BRACE) {
        ParseResult<BlockState> block = parse<BlockState>();
        RETURN_IF_ERROR(block);

        return make_node<SuiteState>(block.value());
    }

    if CURRENT_TOKEN_IS (token::PUNCTUATION_COLON) {
        iter.advance();  // skip ':'

        ParseResult<> stmt = parse();
        RETURN_IF_ERROR(stmt);

        NodeT<BlockState> block = make_node<BlockState>(NodeV<>{stmt.value()});
        return make_node<SuiteState>(block);
    }

    return std::unexpected(
        PARSE_ERROR(CURRENT_TOK,
                    "expected a suite block or a single statement, '{' or ':', but found: " +
                        CURRENT_TOK.token_kind_repr()));
}

AST_NODE_IMPL_VISITOR(Jsonify, SuiteState) {
    json.section("SuiteState").add("body", get_node_json(node.body));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, BlockState) {
    IS_NOT_EMPTY;
    // := '{' Statement* '}'

    NodeV<>      body;
    token::Token starting_tok;

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_OPEN_BRACE);
    starting_tok = CURRENT_TOK;
    iter.advance();  // skip '{'

    while (CURRENT_TOKEN_IS_NOT(
        token::PUNCTUATION_CLOSE_BRACE)) {  // TODO: implement this kind of bounds checks for all
                                            // the pair token parsers '(', '[', '{'.
        ParseResult<> stmt = parse();
        RETURN_IF_ERROR(stmt);

        body.push_back(stmt.value());
    }

    if (iter.remaining_n() == 0) {
        return std::unexpected(
            PARSE_ERROR(starting_tok, "expected '}' to close the block, but found EOF"));
    }

    iter.advance();  // skip '}'
    return make_node<BlockState>(body);
}

AST_NODE_IMPL_VISITOR(Jsonify, BlockState) {
    std::vector<neo::json> body_json;

    for (const auto &node : node.body) {
        body_json.push_back(get_node_json(node));
    }

    json.section("BlockState").add("body", body_json);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, TryState) {
    IS_NOT_EMPTY;

    // := 'try' SuiteState (CatchState)* (FinallyState)?

    NodeT<TryState> node;

    IS_EXCEPTED_TOKEN(token::KEYWORD_TRY);
    iter.advance();  // skip 'try'

    ParseResult<SuiteState> body = parse<SuiteState>();
    RETURN_IF_ERROR(body);

    node = make_node<TryState>(body.value());

    if CURRENT_TOKEN_IS (token::KEYWORD_FINALLY) {
        ParseResult<FinallyState> finally_state = parse<FinallyState>();
        RETURN_IF_ERROR(finally_state);

        node->no_catch      = true;
        node->finally_state = finally_state.value();

        return node;
    }

    IS_EXCEPTED_TOKEN(token::KEYWORD_CATCH);

    ParseResult<CatchState> catch_state = parse<CatchState>();
    RETURN_IF_ERROR(catch_state);

    node->catch_states.emplace_back(catch_state.value());

    while
        CURRENT_TOKEN_IS(token::KEYWORD_CATCH) {
            ParseResult<CatchState> next_catch = parse<CatchState>();
            RETURN_IF_ERROR(next_catch);

            node->catch_states.emplace_back(next_catch.value());
        }

    if CURRENT_TOKEN_IS (token::KEYWORD_FINALLY) {
        ParseResult<FinallyState> finally_state = parse<FinallyState>();
        RETURN_IF_ERROR(finally_state);

        node->finally_state = finally_state.value();
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, TryState) {
    std::vector<neo::json> catch_states;

    for (const auto &catch_state : node.catch_states) {
        catch_states.push_back(get_node_json(catch_state));
    }

    json.section("TryState")
        .add("body", get_node_json(node.body))
        .add("catches", catch_states)
        .add("finally", get_node_json(node.finally_state))
        .add("no_catch", (int)node.no_catch);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, CatchState) {
    IS_NOT_EMPTY;

    // := 'catch' (NamedVarSpecifier) SuiteState (CatchState)?

    IS_EXCEPTED_TOKEN(token::KEYWORD_CATCH);
    iter.advance();  // skip 'catch'

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_OPEN_PAREN);
    iter.advance();  // skip '('

    ParseResult<NamedVarSpecifier> catch_state = parse<NamedVarSpecifier>(true);
    RETURN_IF_ERROR(catch_state);

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_CLOSE_PAREN);
    iter.advance();  // skip ')'

    ParseResult<SuiteState> body = parse<SuiteState>();
    RETURN_IF_ERROR(body);

    return make_node<CatchState>(catch_state.value(), body.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, CatchState) {
    json.section("CatchState")
        .add("catch", get_node_json(node.catch_state))
        .add("body", get_node_json(node.body));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, PanicState) {
    IS_NOT_EMPTY;

    // := 'panic' E ';'

    IS_EXCEPTED_TOKEN(token::KEYWORD_PANIC);
    iter.advance();  // skip 'panic'

    auto expr = Expression(iter).parse();
    RETURN_IF_ERROR(expr);

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_SEMICOLON);
    iter.advance();  // skip ';'

    return make_node<PanicState>(expr.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, PanicState) {
    json.section("PanicState").add("expr", get_node_json(node.expr));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, FinallyState) {
    IS_NOT_EMPTY;

    // := 'finally' SuiteState

    IS_EXCEPTED_TOKEN(token::KEYWORD_FINALLY);
    iter.advance();  // skip 'finally'

    auto body = parse<SuiteState>();
    RETURN_IF_ERROR(body);

    return make_node<FinallyState>(body.value());
}

AST_NODE_IMPL_VISITOR(Jsonify, FinallyState) {
    json.section("FinallyState").add("body", get_node_json(node.body));
}

// ---------------------------------------------------------------------------------------------- //

std::vector<token::Token> get_modifiers(token::TokenList::TokenListIter &iter) {
    std::vector<token::Token> modifiers;

    while (iter.remaining_n() > 0) {
        switch (iter->token_kind()) {
            case token::KEYWORD_INLINE:
            case token::KEYWORD_STATIC:
            case token::KEYWORD_ASYNC:
            case token::KEYWORD_EVAL:
            case token::KEYWORD_PRIVATE:
            case token::KEYWORD_CONST:
            case token::KEYWORD_UNSAFE:
            case token::KEYWORD_PUBLIC:
            case token::KEYWORD_PROTECTED:
            case token::KEYWORD_INTERNAL:
            case token::LITERAL_COMPLIER_DIRECTIVE:
                modifiers.push_back(CURRENT_TOK);
                iter.advance();
                break;
            default:
                goto exit_loop;
        }
    }

exit_loop:
    return modifiers;
}