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
#include "parser/ast/include/config/AST_generate.def"
#include "parser/ast/include/config/AST_generate.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "parser/ast/include/types/AST_visitor.hh"
#include "token/include/token_list.hh"

#define null nullptr
#define GENERATE_IF_STATEMENTS(name)                      \
    if constexpr (std::is_same_v<T, name>) {              \
        return parse_##name(std::forward<Args>(args)...); \
    }

__AST_NODE_BEGIN {
    class Node {  // base node
      public:
        Node()                                                                          = default;
        virtual ~Node()                                                                 = default;
        virtual void                      accept(__AST_VISITOR::Visitor &visitor) const = 0;
        [[nodiscard]] virtual nodes       getNodeType() const                           = 0;
        [[nodiscard]] virtual std::string getNodeName() const                           = 0;

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
        AST_CLASS_BASE(Expression, EXPRS);

        p_r<> parse_primary();
        template <typename T, typename... Args>
        p_r<T> parse(Args &&...args) { /* NOLINT */
            if constexpr (std ::is_same_v<T, LiteralExpr>) {
                return parse_LiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, BinaryExpr>) {
                return parse_BinaryExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, UnaryExpr>) {
                return parse_UnaryExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, IdentExpr>) {
                return parse_IdentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, NamedArgumentExpr>) {
                return parse_NamedArgumentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArgumentExpr>) {
                return parse_ArgumentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArgumentListExpr>) {
                return parse_ArgumentListExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, GenericArgumentExpr>) {
                return parse_GenericArgumentExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, GenericInvokeExpr>) {
                return parse_GenericInvokeExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, GenericInvokePathExpr>) {
                return parse_GenericInvokePathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ScopePathExpr>) {
                return parse_ScopePathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, DotPathExpr>) {
                return parse_DotPathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArrayAccessExpr>) {
                return parse_ArrayAccessExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, PathExpr>) {
                return parse_PathExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, FunctionCallExpr>) {
                return parse_FunctionCallExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ArrayLiteralExpr>) {
                return parse_ArrayLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TupleLiteralExpr>) {
                return parse_TupleLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, SetLiteralExpr>) {
                return parse_SetLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, MapPairExpr>) {
                return parse_MapPairExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, MapLiteralExpr>) {
                return parse_MapLiteralExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ObjInitExpr>) {
                return parse_ObjInitExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, LambdaExpr>) {
                return parse_LambdaExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TernaryExpr>) {
                return parse_TernaryExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ParenthesizedExpr>) {
                return parse_ParenthesizedExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, CastExpr>) {
                return parse_CastExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, InstOfExpr>) {
                return parse_InstOfExpr(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, Type>) {
                return parse_Type(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, AsyncThreading>) {
                return parse_AsyncThreading(std ::forward<Args>(args)...);
            }
        };

      private:
        p_r<NamedArgumentExpr>     parse_NamedArgumentExpr(bool is_anonymous = false);
        p_r<PathExpr>              parse_PathExpr(p_r<> simple_path = null);
        p_r<UnaryExpr>             parse_UnaryExpr(p_r<> lhs = null);
        p_r<BinaryExpr>            parse_BinaryExpr(p_r<> lhs, int min_precedence);
        p_r<LiteralExpr>           parse_LiteralExpr(p_r<> str_concat = null);
        p_r<ArgumentExpr>          parse_ArgumentExpr();
        p_r<DotPathExpr>           parse_DotPathExpr(p_r<> lhs = null);
        p_r<IdentExpr>             parse_IdentExpr();
        p_r<ScopePathExpr>         parse_ScopePathExpr(p_r<> lhs = null);
        p_r<ArrayAccessExpr>       parse_ArrayAccessExpr(p_r<> lhs = null);
        p_r<ArgumentListExpr>      parse_ArgumentListExpr();
        p_r<GenericArgumentExpr>   parse_GenericArgumentExpr();
        p_r<GenericInvokeExpr>     parse_GenericInvokeExpr();
        p_r<GenericInvokePathExpr> parse_GenericInvokePathExpr();
        p_r<ArrayLiteralExpr>      parse_ArrayLiteralExpr();
        p_r<TupleLiteralExpr>      parse_TupleLiteralExpr(p_r<> starting_element = null);
        p_r<SetLiteralExpr>        parse_SetLiteralExpr(p_r<> starting_value);
        p_r<MapPairExpr>           parse_MapPairExpr();
        p_r<MapLiteralExpr>        parse_MapLiteralExpr(p_r<> starting_value);
        p_r<ObjInitExpr> parse_ObjInitExpr(bool skip_start_brace = false, p_r<> obj_path = null);
        p_r<LambdaExpr>  parse_LambdaExpr();
        p_r<TernaryExpr> parse_TernaryExpr(p_r<> lhs = null);
        p_r<ParenthesizedExpr> parse_ParenthesizedExpr(p_r<> expr = null);
        p_r<CastExpr>          parse_CastExpr(p_r<> lhs);
        p_r<InstOfExpr>        parse_InstOfExpr(p_r<> lhs = null);
        p_r<Type>              parse_Type();
        p_r<AsyncThreading>    parse_AsyncThreading();
        p_r<FunctionCallExpr>  parse_FunctionCallExpr(p_r<> lhs = null, p_r<> gens = null);
    };

    /*
     *  Statement class
     *
     *  This class is responsible for parsing the statement grammar.
     *  It is a recursive descent parser that uses the token list
     *  to parse the statement grammar.
     *
     *  (its very bad quality but will be improved when written in helix)
     *
     *  usage:
     *     Statement state(tokens);
     *     NodeT<> node = state.parse();
     *
     *     // or
     *
     *     NodeT<...> node = state.parse<...>();
     */
    class Statement {  // THIS IS NOT A NODE
        AST_CLASS_BASE(Statement, STATES);

        template <typename T, typename... Args>
        p_r<T> parse(Args &&...args) { /* NOLINT */
            if constexpr (std ::is_same_v<T, NamedVarSpecifier>) {
                return parse_NamedVarSpecifier(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, NamedVarSpecifierList>) {
                return parse_NamedVarSpecifierList(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ForPyStatementCore>) {
                return parse_ForPyStatementCore(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ForCStatementCore>) {
                return parse_ForCStatementCore(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ForState>) {
                return parse_ForState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, WhileState>) {
                return parse_WhileState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ElseState>) {
                return parse_ElseState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, IfState>) {
                return parse_IfState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, SwitchCaseState>) {
                return parse_SwitchCaseState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, SwitchState>) {
                return parse_SwitchState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, YieldState>) {
                return parse_YieldState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, DeleteState>) {
                return parse_DeleteState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, AliasState>) {
                return parse_AliasState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, SingleImportState>) {
                return parse_SingleImportState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, MultiImportState>) {
                return parse_MultiImportState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ImportState>) {
                return parse_ImportState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ReturnState>) {
                return parse_ReturnState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, BreakState>) {
                return parse_BreakState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, BlockState>) {
                return parse_BlockState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, SuiteState>) {
                return parse_SuiteState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ContinueState>) {
                return parse_ContinueState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, CatchState>) {
                return parse_CatchState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, FinallyState>) {
                return parse_FinallyState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TryState>) {
                return parse_TryState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, PanicState>) {
                return parse_PanicState(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ExprState>) {
                return parse_ExprState(std ::forward<Args>(args)...);
            };
        };

      private:
        std::vector<token::Token> modifiers;

        p_r<NamedVarSpecifier>     parse_NamedVarSpecifier(bool force_type = false);
        p_r<NamedVarSpecifierList> parse_NamedVarSpecifierList(bool force_types = false);
        p_r<ForPyStatementCore>    parse_ForPyStatementCore(bool skip_start = false);
        p_r<ForCStatementCore>     parse_ForCStatementCore(bool skip_start = false);
        p_r<ForState>              parse_ForState();
        p_r<WhileState>            parse_WhileState();
        p_r<IfState>               parse_IfState();
        p_r<ElseState>             parse_ElseState(Expression &expr_parser);
        p_r<SwitchState>           parse_SwitchState();
        p_r<SwitchCaseState>       parse_SwitchCaseState();
        p_r<ImportState>           parse_ImportState();
        p_r<SingleImportState>     parse_SingleImportState();
        p_r<MultiImportState>      parse_MultiImportState();
        p_r<AliasState>            parse_AliasState();
        p_r<YieldState>            parse_YieldState();
        p_r<DeleteState>           parse_DeleteState();
        p_r<ReturnState>           parse_ReturnState();
        p_r<BreakState>            parse_BreakState();
        p_r<ContinueState>         parse_ContinueState();
        p_r<ExprState>             parse_ExprState();
        p_r<BlockState>            parse_BlockState();
        p_r<TryState>              parse_TryState();
        p_r<CatchState>            parse_CatchState();
        p_r<FinallyState>          parse_FinallyState();
        p_r<PanicState>            parse_PanicState();
        p_r<SuiteState>            parse_SuiteState();
    };

    /*
     *  Declaration class
     *
     *  This class is responsible for parsing the declaration grammar.
     *  It is a recursive descent parser that uses the token list
     *  to parse the declaration grammar.
     *
     *  (its very bad quality but will be improved when written in helix)
     *
     *  usage:
     *     Declaration decl(tokens);
     *     NodeT<> node = decl.parse();
     *
     *     // or
     *
     *     NodeT<...> node = decl.parse<...>();
     */
    class Declaration {
        AST_CLASS_BASE(Declaration, STATES);

        template <typename T, typename... Args>
        p_r<T> parse(Args &&...args) { /* NOLINT */
            if constexpr (std ::is_same_v<T, RequiresParamDecl>) {
                return parse_RequiresParamDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, RequiresParamList>) {
                return parse_RequiresParamList(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, EnumMemberDecl>) {
                return parse_EnumMemberDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, UDTDeriveDecl>) {
                return parse_UDTDeriveDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TypeBoundList>) {
                return parse_TypeBoundList(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TypeBoundDecl>) {
                return parse_TypeBoundDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, RequiresDecl>) {
                return parse_RequiresDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, StructDecl>) {
                return parse_StructDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ConstDecl>) {
                return parse_ConstDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, ClassDecl>) {
                return parse_ClassDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, InterDecl>) {
                return parse_InterDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, EnumDecl>) {
                return parse_EnumDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, TypeDecl>) {
                return parse_TypeDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, FuncDecl>) {
                return parse_FuncDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, VarDecl>) {
                return parse_VarDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, FFIDecl>) {
                return parse_FFIDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, LetDecl>) {
                return parse_LetDecl(std ::forward<Args>(args)...);
            } else if constexpr (std ::is_same_v<T, OpDecl>) {
                return parse_OpDecl(std ::forward<Args>(args)...);
            };
        }

      private:
        std::vector<token::Token> modifiers;

        p_r<RequiresParamDecl> parse_RequiresParamDecl();
        p_r<RequiresParamList> parse_RequiresParamList();
        p_r<EnumMemberDecl>    parse_EnumMemberDecl();
        p_r<UDTDeriveDecl>     parse_UDTDeriveDecl();
        p_r<TypeBoundList>     parse_TypeBoundList();
        p_r<TypeBoundDecl>     parse_TypeBoundDecl();
        p_r<RequiresDecl>      parse_RequiresDecl();
        p_r<StructDecl>        parse_StructDecl();
        p_r<ConstDecl>         parse_ConstDecl();
        p_r<ClassDecl>         parse_ClassDecl();
        p_r<InterDecl>         parse_InterDecl();
        p_r<EnumDecl>          parse_EnumDecl();
        p_r<TypeDecl>          parse_TypeDecl();
        p_r<FuncDecl>          parse_FuncDecl();
        p_r<VarDecl>           parse_VarDecl();
        p_r<FFIDecl>           parse_FFIDecl();
        p_r<LetDecl>           parse_LetDecl();
        p_r<OpDecl>            parse_OpDecl();
    };
}  // namespace __AST_BEGIN

#undef null

#endif  // __AST_NODES_H__