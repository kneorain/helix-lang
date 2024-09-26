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
/// STS *         /* node types */                                                               ///
/// [x] * Literal  * L                                                                           ///
/// [x] * Operator * O                                                                           ///
/// [x] * Token    * T                                                                           ///
///                                                                                              ///
///                          * helper nodes (not supposed to be explicitly used) */              ///
/// [x] * ArgumentListExpr   *
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

// ---------------------------------------------------------------------------------------------- //

bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens);

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Expression, parse_primary) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_BASE_IMPL(Expression, parse) {  // NOLINT(readability-function-cognitive-complexity)
    IS_NOT_EMPTY;                   /// simple macro to check if the iterator is empty, expands to:
                                    /// if(iter.remaining_n() == 0) { return std::unexpected(...); }
    NOT_IMPLEMENTED;
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Statement, NamedVarSpecifier) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, NamedVarSpecifier) {
    json.section("NamedVarSpecifier");
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

AST_NODE_IMPL(Statement, BlockState) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, BlockState) { json.section("BlockState"); }

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

bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens) {
    return tokens.find(tok.token_kind()) != tokens.end();
}