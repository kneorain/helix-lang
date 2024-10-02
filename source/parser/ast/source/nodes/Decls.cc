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
#include <utility>
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

    NodeT<RequiresParamDecl>       node = make_node<RequiresParamDecl>(true);
    ParseResult<NamedVarSpecifier> var;

    if CURRENT_TOKEN_IS (token::KEYWORD_CONST) {
        iter.advance();  // skip 'const'
        node->is_const = true;
    }

    var = state_parser.parse<NamedVarSpecifier>(node->is_const);  // force type if is_const is true
    RETURN_IF_ERROR(var);

    node->var = var.value();

    if CURRENT_TOKEN_IS (token::OPERATOR_ASSIGN) {
        iter.advance();  // skip '='

        ParseResult<> value = expr_parser.parse();
        RETURN_IF_ERROR(value);

        node->value = value.value();
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, RequiresParamDecl) {
    json.section("RequiresParamDecl")
        .add("is_const", node.is_const ? "true" : "false")
        .add("var", get_node_json(node.var))
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, RequiresParamList) {
    IS_NOT_EMPTY;
    // RequiresParamList := RequiresParamDecl (',' RequiresParamDecl)*)?

#define TOKENS_REQUIRED {token::KEYWORD_CONST, token::IDENTIFIER}
    IS_IN_EXCEPTED_TOKENS(TOKENS_REQUIRED);
#undef TOKENS_REQUIRED

    ParseResult<RequiresParamDecl> first = parse<RequiresParamDecl>();
    RETURN_IF_ERROR(first);

    NodeT<RequiresParamList> node = make_node<RequiresParamList>(first.value());

    while (CURRENT_TOKEN_IS(token::PUNCTUATION_COMMA)) {
        iter.advance();  // skip ','

        ParseResult<RequiresParamDecl> next = parse<RequiresParamDecl>();
        RETURN_IF_ERROR(next);

        node->params.emplace_back(next.value());
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, RequiresParamList) {
    std::vector<neo::json> params;

    for (const auto &param : node.params) {
        params.push_back(get_node_json(param));
    }

    json.section("RequiresParamList").add("params", params);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, EnumMemberDecl) {
    IS_NOT_EMPTY;
    // EnumMemberDecl := E.IdentExpr ('=' E)?
    IS_EXCEPTED_TOKEN(token::IDENTIFIER);

    ParseResult<IdentExpr> name = expr_parser.parse<IdentExpr>();
    RETURN_IF_ERROR(name);

    NodeT<EnumMemberDecl> node = make_node<EnumMemberDecl>(name.value());

    if (CURRENT_TOKEN_IS(token::OPERATOR_ASSIGN)) {
        iter.advance();  // skip '='

        ParseResult<> value = expr_parser.parse();
        RETURN_IF_ERROR(value);

        node->value = value.value();
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, EnumMemberDecl) {
    json.section("EnumMemberDecl")
        .add("name", get_node_json(node.name))
        .add("value", get_node_json(node.value));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, UDTDeriveDecl) {
    IS_NOT_EMPTY;
    // UDTDeriveDecl := 'derives' (VisDecl? E.Type (',' VisDecl? E.Type)*)?

    IS_EXCEPTED_TOKEN(token::KEYWORD_DERIVES);

    iter.advance();  // skip 'derives'

    AccessSpecifier access = AccessSpecifier(
        token::Token(token::KEYWORD_PUBLIC, "HZL_CMPILER_INL.ACCESS_SPECIFIER__.tmp"));
    if (AccessSpecifier::is_access_specifier(CURRENT_TOK)) {
        access = AccessSpecifier(CURRENT_TOK);
    }

    ParseResult<Type> type = expr_parser.parse<Type>();
    RETURN_IF_ERROR(type);

    NodeT<UDTDeriveDecl> node = make_node<UDTDeriveDecl>(std::make_pair(type.value(), access));

    while (CURRENT_TOKEN_IS(token::PUNCTUATION_COMMA)) {
        iter.advance();  // skip ','

        AccessSpecifier access = AccessSpecifier(
            token::Token(token::KEYWORD_PUBLIC, "HZL_CMPILER_INL.ACCESS_SPECIFIER__.tmp"));
        if (AccessSpecifier::is_access_specifier(CURRENT_TOK)) {
            access = AccessSpecifier(CURRENT_TOK);
        }

        ParseResult<Type> next = expr_parser.parse<Type>();
        RETURN_IF_ERROR(next);

        node->derives.emplace_back(next.value(), access);
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, UDTDeriveDecl) {
    std::vector<neo::json> derives;

    for (const auto &derive : node.derives) {
        derives.push_back(get_node_json(derive.first));
        derives.push_back(derive.second.to_json());
    }

    json.section("UDTDeriveDecl").add("derives", derives);
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, TypeBoundList) {
    IS_NOT_EMPTY;
    // TypeBoundList := InstOfExpr (',' InstOfExpr)*)?

    ParseResult<InstOfExpr> bound = expr_parser.parse<InstOfExpr>(expr_parser.parse_primary());
    RETURN_IF_ERROR(bound);

    NodeT<TypeBoundList> node = make_node<TypeBoundList>(bound.value());

    while (CURRENT_TOKEN_IS(token::PUNCTUATION_COMMA)) {
        iter.advance();  // skip ','

        ParseResult<InstOfExpr> next = expr_parser.parse<InstOfExpr>(expr_parser.parse_primary());
        RETURN_IF_ERROR(next);

        node->bounds.emplace_back(next.value());
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, TypeBoundList) {
    std::vector<neo::json> bounds;

    for (const auto &bound : node.bounds) {
        bounds.push_back(get_node_json(bound));
    }

    json.section("TypeBoundList").add("bounds", bounds);
}

// ---------------------------------------------------------------------------------------------- //

/* TODO: DEPRECATE MERGED WITH LIST*/
AST_NODE_IMPL(Declaration, TypeBoundDecl) {
    IS_NOT_EMPTY;
    NOT_IMPLEMENTED;
}

AST_NODE_IMPL_VISITOR(Jsonify, TypeBoundDecl) { json.section("TypeBoundDecl"); }

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, RequiresDecl) {
    IS_NOT_EMPTY;
    // RequiresDecl := requires' '<' RequiresParamList '>' ('if' TypeBoundList)?

    IS_EXCEPTED_TOKEN(token::KEYWORD_REQUIRES);
    iter.advance();  // skip 'requires

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_OPEN_ANGLE);
    iter.advance();  // skip '<'

    ParseResult<RequiresParamList> params = parse<RequiresParamList>();
    RETURN_IF_ERROR(params);

    NodeT<RequiresDecl> node = make_node<RequiresDecl>(params.value());

    IS_EXCEPTED_TOKEN(token::PUNCTUATION_CLOSE_ANGLE);
    iter.advance();  // skip '>'

    if (CURRENT_TOKEN_IS(token::KEYWORD_IF)) {
        iter.advance();  // skip 'if'

        ParseResult<TypeBoundList> bounds = parse<TypeBoundList>();
        RETURN_IF_ERROR(bounds);

        node->bounds = bounds.value();
    }

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, RequiresDecl) {
    json.section("RequiresDecl")
        .add("params", get_node_json(node.params))
        .add("bounds", get_node_json(node.bounds));
}

// ---------------------------------------------------------------------------------------------- //

AST_NODE_IMPL(Declaration, StructDecl) {
    IS_NOT_EMPTY;
    // StructDecl := Modifiers 'struct'    E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

    NodeT<StructDecl> node = make_node<StructDecl>(true);

    while (node->modifiers.find_add(CURRENT_TOK)) {
        iter.advance();  // skip modifier
    }

    IS_EXCEPTED_TOKEN(token::KEYWORD_STRUCT);
    iter.advance();  // skip 'struct'

    ParseResult<IdentExpr> name = expr_parser.parse<IdentExpr>();
    RETURN_IF_ERROR(name);

    node->name = name.value();

    if (CURRENT_TOKEN_IS(token::KEYWORD_DERIVES)) {
        ParseResult<UDTDeriveDecl> derives = parse<UDTDeriveDecl>();
        RETURN_IF_ERROR(derives);

        node->derives = derives.value();
    }

    if (CURRENT_TOKEN_IS(token::KEYWORD_REQUIRES)) {
        ParseResult<RequiresDecl> generics = parse<RequiresDecl>();
        RETURN_IF_ERROR(generics);

        node->generics = generics.value();
    }

    ParseResult<SuiteState> body = state_parser.parse<SuiteState>();
    RETURN_IF_ERROR(body);

    node->body = body.value();

    return node;
}

AST_NODE_IMPL_VISITOR(Jsonify, StructDecl) { json.section("StructDecl")
        .add("name", get_node_json(node.name))
        .add("derives", get_node_json(node.derives))
        .add("generics", get_node_json(node.generics))
        .add("body", get_node_json(node.body))
        .add("modifiers", node.modifiers.to_json());
}

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

AST_BASE_IMPL(Declaration, parse) {
    IS_NOT_EMPTY;

    token::Token tok = CURRENT_TOK;          /// get the current token from the iterator

    switch (tok.token_kind()) {
        case token::KEYWORD_STRUCT:
            return parse<StructDecl>();
        default:
            return state_parser.parse();
    }
}