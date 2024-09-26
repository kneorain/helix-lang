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
/// [ ] * BreakState     * 'break' ';'                                                           ///
/// [ ] * ContinueState  * 'continue' ';'                                                        ///
/// [ ] * ExprState      * E ';'                                                                 ///
/// [ ] * BlockState     * '{' Statement* '}'                                                    ///
/// [ ] * SuiteState     * BlockState | (':' Statement)                                          ///
/// [ ] * ReturnState    * 'return' E? ';'                                                       ///
///                                                                                              ///
/// [ ] * YieldState         * 'yield' E ';'                                                     ///
/// [ ] * DeleteState        * 'delete' E ';'                                                    ///
/// [ ] * SwitchState        * 'switch' '(' E ')' '{' SwitchCaseState* '}'                       ///
/// [ ] * IfState            * ('if' | 'unless') '(' E ')' SuiteState (ElseState)?               ///
/// [ ] * ElseState          * 'else' SuiteState                                                 ///
/// [ ] * WhileState         * 'while' '(' E ')' SuiteState                                      ///
/// [ ] * ForState           * 'for' '(' ForPyStatementCore | ForCStatementCore ')' SuiteState   ///
/// [ ] * ForPyStatementCore * NamedVarSpecifier 'in' E SuiteState                               ///
/// [ ] * ForCStatementCore  * (E)? ';' (E)? ';' (E)? SuiteState                                 ///
/// [ ] * NamedVarSpecifier  * Ident (':' E)?                                                    ///
/// [ ] * SwitchCaseState    * 'case' E SuiteState | 'default' SuiteState                        ///
///                                                                                              ///
/// [ ] * ImportState        * 'import' (SingleImportState | MultiImportState)                   ///
/// [ ] * AliasState         * Ident 'as' Ident ';'                                              ///
/// [ ] * SingleImportState  * Ident (',' Ident)*                                                ///
/// [ ] * MultiImportState   * Ident 'as' Ident (',' Ident 'as' Ident)*                          ///
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
#include "parser/ast/include/nodes/AST_Statements.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

// ---------------------------------------------------------------------------------------------- //

bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens);
std::vector<token::Token> get_modifiers(token::TokenList::TokenListIter &iter);

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

    token::Token tok = CURRENT_TOK;  /// get the current token from the iterator

    modifiers = get_modifiers(iter);  /// get the modifiers for the statement

    switch (tok.token_kind()) {
            // TODO: case token::KEYWORD_IMPORT

        case token::KEYWORD_IF:
        case token::KEYWORD_UNLESS:
            return parse_IfState();

        case token::KEYWORD_ELSE:
            return std::unexpected(PARSE_ERROR(
                CURRENT_TOK, "found dangling 'else' without a matching 'if' or 'unless'"));

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

        case token::KEYWORD_CASE:
            return std::unexpected(
                PARSE_ERROR(CURRENT_TOK, "found dangling 'case' without a matching 'switch'"));

        case token::KEYWORD_DEFAULT:
            return std::unexpected(
                PARSE_ERROR(CURRENT_TOK, "found dangling 'default' without a matching 'switch'"));

        case token::KEYWORD_TRY:
            return parse_TryState();

        case token::KEYWORD_PANIC:
            return parse_PanicState();

        case token::KEYWORD_FINALLY:
            return parse_FinallyState();
            
        case token::KEYWORD_CATCH:
            return std::unexpected(
                PARSE_ERROR(CURRENT_TOK, "found dangling 'catch' without a matching 'try'"));

        case token::KEYWORD_YIELD:
            return parse_YieldState();

        case token::KEYWORD_DELETE:
            return parse_DeleteState();

        case token::PUNCTUATION_OPEN_BRACE:
            return parse_BlockState();

        default:
            return parse_ExprState();
    }
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, NamedVarSpecifier) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, NamedVarSpecifier) { json.section("NamedVarSpecifier"); }

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
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, WhileState) { json.section("WhileState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ElseState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ElseState) { json.section("ElseState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, IfState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, IfState) { json.section("IfState"); }

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
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, YieldState) { json.section("YieldState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, DeleteState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, DeleteState) { json.section("DeleteState"); }

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
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ReturnState) { json.section("ReturnState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, BreakState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, BreakState) { json.section("BreakState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ContinueState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ContinueState) { json.section("ContinueState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, ExprState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ExprState) { json.section("ExprState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, SuiteState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, SuiteState) { json.section("SuiteState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, BlockState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, BlockState) { json.section("BlockState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, TryState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, TryState) { json.section("TryState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, CatchState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, CatchState) { json.section("CatchState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, PanicState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, PanicState) { json.section("PanicState"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, FinallyState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, FinallyState) { json.section("FinallyState"); }

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