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
///  @file Decls.cc                                                                              ///
///  @brief This file contains the entire logic to parse declarations using a recursive descent  ///
///         parser. the parser adheres to an ll(1) grammar, which means it processes the input   ///
///         left-to-right and constructs the leftmost derivation using one token of lookahead.   ///
///                                                                                              ///
///  The parser is implemented using the `parse` method, which is a recursive descent parser     ///
///     that uses the token list to parse the Declaration grammar.                               ///
///                                                                                              ///
///  @code                                                                                       ///
///  Declaration decl(tokens);                                                                   ///
///  ParseResult<> node = decl.parse();                                                          ///
///                                                                                              ///
///  if (node.has_value()) {                                                                     ///
///      NodeT<> ast = node.value();                                                             ///
///  } else {                                                                                    ///
///      std::cerr << node.error().what() << std::endl;                                          ///
///  }                                                                                           ///
///  @endcode                                                                                    ///
///                                                                                              ///
///  By default, the parser will parse the entire declaration, but you can also parse a specific ///
///     declaration by calling the specific parse method. or get a specific node by calling      ///
///     parse and then passing a template argument to the method.                                ///
///                                                                                              ///
///  @code                                                                                       ///
///  Declaration state(tokens);                                                                  ///
///  ParseResult<ReturnState> node = state.parse<ReturnState>();                                 ///
///  @endcode                                                                                    ///
///                                                                                              ///
/// The parser is implemented using the following grammar:                                       ///
///                                                                                              ///
/// STS *           /* node types */                                                             ///
/// [x] * Literal     * L                                                                        ///
/// [x] * Operator    * O                                                                        ///
/// [x] * Token       * T                                                                        ///
/// [x] * Expression  * E                                                                        ///
/// [x] * Statement   * S                                                                        ///
/// [x] * Declaration * D                                                                        ///
///                                                                                              ///
/// STS *                  /* generics and type bounds */                                        ///
/// [ ] * RequiresParamDecl * 'const'? (S.NamedVarSpecifier) ('=' E)?                            ///
/// [ ] * RequiresParamList * (RequiresParamDecl (',' RequiresParamDecl)*)?                      ///
/// [ ] * TypeBoundDecl     * 'if' InstOfExpr                                                    ///
/// [ ] * TypeBoundList     * (TypeBoundDecl (',' TypeBoundDecl)*)?                              ///
/// [ ] * RequiresDecl      * 'requires' '<' RequiresParamList '>' TypeBoundList?                ///
/// [ ] * EnumMemberDecl    * E.IdentExpr ('=' E)?                                               ///
/// [ ] * UDTDeriveDecl     * 'derives' (E.Type (',' E.Type)*)?                                  ///
///                                                                                              ///
///                        /* declaration helpers */                                             ///
/// [ ] * StorageSpecifier  * 'ffi' | 'static' | 'async' | 'eval'                                ///
/// [ ] * FFISpecifier      * 'class' | 'interface' | 'struct' | 'enum' | 'union' | 'type'       ///
/// [ ] * TypeQualifier     * 'const' | 'module' | 'yield' | 'async' | 'ffi' | 'static'          ///
/// [ ] * AccessSpecifier   * 'pub' | 'priv' | 'prot' | 'intl'                                   ///
/// [ ] * FunctionSpecifier * 'inline'  | 'async' | 'static' | 'const' | 'eval' | 'other'        ///
/// [ ] * FunctionQualifier * 'default' | 'panic' | 'delete' | 'const'                           ///
///                                                                                              ///
/// [ ] * VisDecl         * AccessSpecifier                                                       //
/// [ ] * VarDecl         * S.NamedVarSpecifier ('=' E)? ~ also pass in a bool to force type need //
/// [ ] * SharedModifiers * (FunctionSpecifier)*)?                                               ///
///                                                                                              ///
///                /* declaration nodes */                                                       ///
/// [ ] * FFIDecl   *  VisDecl? 'ffi' L.StringLiteral D                                          ///
/// [ ] * LetDecl   *  VisDecl? 'let'   SharedModifiers VarDecl* ';'                             ///
/// [ ] * ConstDecl *  VisDecl? 'const' SharedModifiers VarDecl* ';'                             ///
/// [ ] * TypeDecl  *  VisDecl? 'type'  E.IdentExpr RequiresDecl? '=' E ';'                      ///
/// [ ] * EnumDecl  *  VisDecl? 'enum' ('derives' E.Type)? E.ObjInitExpr                         ///
/// [ ] * OpDecl    *  SharedModifiers? 'op' T FuncDecl[no_SharedModifiers=true]                 ///
/// [ ] * FuncDecl  *  SharedModifiers? 'fn' E.PathExpr '(' VarDecl[true]* ')' RequiresDecl? S.Suite
/// [ ] * StructDecl* 'const'? VisDecl? 'struct'    E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite
/// [ ] * ClassDecl * 'const'? VisDecl? 'class'     E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite
/// [ ] * InterDecl * 'const'? VisDecl? 'interface' E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite
///                                                                                              ///
/// [ ] * ExtDecl   * 'extend' E.PathExpr UDTDeriveDecl? S.Suite       /* TODO: dont forget */   ///
///                                                                                              ///
/// [ ] * UnionDecl     * VisDecl? 'union'  E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite     ///
/// TODO: should unions be Statements in the form of anonymous unions or concrete type decls???  ///
//===-----------------------------------------------------------------------------------------====//

#include <expected>
#include <memory>
#include <unordered_set>
#include <vector>

#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/config/AST_generate.hh"
#include "parser/ast/include/config/case_types.def"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/nodes/AST_Expressions.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "token/include/generate.hh"

AST_NODE_IMPL(Declaration, RequiresParamDecl) {
    IS_NOT_EMPTY;
    // RequiresParamDecl := const'? (S.NamedVarSpecifier) ('=' E)?

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, RequiresParamDecl) { json.section("RequiresParamDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, RequiresParamList) {
    IS_NOT_EMPTY;
    // RequiresParamList := RequiresParamDecl (',' RequiresParamDecl)*)?

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, RequiresParamList) { json.section("RequiresParamList"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, EnumMemberDecl) {
    IS_NOT_EMPTY;
    // EnumMemberDecl := E.IdentExpr ('=' E)?

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, EnumMemberDecl) { json.section("EnumMemberDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, UDTDeriveDecl) {
    IS_NOT_EMPTY;
    // UDTDeriveDecl := derives' (E.Type (',' E.Type)*)?

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, UDTDeriveDecl) { json.section("UDTDeriveDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, TypeBoundList) {
    IS_NOT_EMPTY;
    // TypeBoundList := TypeBoundDecl (',' TypeBoundDecl)*)?

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, TypeBoundList) { json.section("TypeBoundList"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, TypeBoundDecl) {
    IS_NOT_EMPTY;
    // TypeBoundDecl := if' InstOfExpr

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, TypeBoundDecl) { json.section("TypeBoundDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, RequiresDecl) {
    IS_NOT_EMPTY;
    // RequiresDecl := requires' '<' RequiresParamList '>' TypeBoundList?

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, RequiresDecl) { json.section("RequiresDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, StructDecl) {
    IS_NOT_EMPTY;
    // StructDecl := const'? VisDecl? 'struct'    E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, StructDecl) { json.section("StructDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, ConstDecl) {
    IS_NOT_EMPTY;
    // ConstDecl := VisDecl? 'const' SharedModifiers VarDecl* ';'

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ConstDecl) { json.section("ConstDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, ClassDecl) {
    IS_NOT_EMPTY;
    // ClassDecl := const'? VisDecl? 'class'     E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, ClassDecl) { json.section("ClassDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, InterDecl) {
    IS_NOT_EMPTY;
    // InterDecl := const'? VisDecl? 'interface' E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, InterDecl) { json.section("InterDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, EnumDecl) {
    IS_NOT_EMPTY;
    // EnumDecl := VisDecl? 'enum' ('derives' E.Type)? E.ObjInitExpr

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, EnumDecl) { json.section("EnumDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, TypeDecl) {
    IS_NOT_EMPTY;
    // TypeDecl := VisDecl? 'type'  E.IdentExpr RequiresDecl? '=' E ';'

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, TypeDecl) { json.section("TypeDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, FuncDecl) {
    IS_NOT_EMPTY;
    // FuncDecl := SharedModifiers? 'fn' E.PathExpr '(' VarDecl[true]* ')' RequiresDecl? S.Suite

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, FuncDecl) { json.section("FuncDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, VarDecl) {
    IS_NOT_EMPTY;
    // VarDecl := S.NamedVarSpecifier ('=' E)? ~ also pass in a bool to force type need

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, VarDecl) { json.section("VarDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, FFIDecl) {
    IS_NOT_EMPTY;
    // FFIDecl := VisDecl? 'ffi' L.StringLiteral D

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, FFIDecl) { json.section("FFIDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, LetDecl) {
    IS_NOT_EMPTY;
    // LetDecl := VisDecl? 'let' SharedModifiers VarDecl* ';'

    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, LetDecl) { json.section("LetDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, OpDecl) {
    IS_NOT_EMPTY;
    // OpDecl := SharedModifiers? 'op' T FuncDecl[no_SharedModifiers=true]

    NOT_IMPLEMENTED;

}

AST_NODE_IMPL_VISITOR(Jsonify, OpDecl) { json.section("OpDecl"); }

// ---------------------------------------------------------------------------------------------- //