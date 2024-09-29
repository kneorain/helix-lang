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

#ifndef __AST_STATEMENTS_H__
#define __AST_STATEMENTS_H__

#include <utility>

#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/types/AST_types.hh"

// va
// var_decl := 'let' Ident (':' E)? ('=' expr)? ';'

__AST_NODE_BEGIN {
    class NamedVarSpecifier final : public Node {
        BASE_CORE_METHODS(NamedVarSpecifier);

        // := Ident (':' E)?

        explicit NamedVarSpecifier(NodeT<PathExpr> path,  NodeT<> type = nullptr)
            : path(std::move(path))
            , type(std::move(type)) {
            if (type != nullptr) {
                has_type = true;
            }
        }

        NodeT<PathExpr> path;
        NodeT<>         type;

        bool has_type;
    };

    class ForPyStatementCore final : public Node {
        BASE_CORE_METHODS(ForPyStatementCore);

        // := NamedVarSpecifier 'in 'expr' Suite

        ForPyStatementCore(NodeT<NamedVarSpecifier> vars, NodeT<> range, NodeT<> body)
            : vars(std::move(vars))
            , range(std::move(range))
            , body(std::move(body)) {}

        NodeT<NamedVarSpecifier> vars;
        NodeT<>                  range;
        NodeT<>                  body;
    };

    class ForCStatementCore final : public Node {
        BASE_CORE_METHODS(ForCStatementCore);

        // := (expr)? ';' (expr)? ';' (expr)? Suite

        ForCStatementCore(NodeT<> init, NodeT<> condition, NodeT<> update, NodeT<SuiteState> body)
            : init(std::move(init))
            , condition(std::move(condition))
            , update(std::move(update))
            , body(std::move(body)) {}

        NodeT<>           init;
        NodeT<>           condition;
        NodeT<>           update;
        NodeT<SuiteState> body;
    };

    class ForState final : public Node {
        BASE_CORE_METHODS(ForState);

        // := 'for' (ForPyStatementCore | ForCStatementCore)

        enum class ForType {
            Python,
            C,
        };

        explicit ForState(NodeT<> core)
            : core(std::move(core)) {
            if (core->getNodeName() == "ForPyStatementCore") {
                type = ForType::Python;
            } else if (core->getNodeName() == "ForCStatementCore") {
                type = ForType::C;
            } else {
                // error
                throw std::runtime_error(GET_DEBUG_INFO + "Invalid for loop type");
            }
        }

        NodeT<> core;
        ForType type;
    };

    class WhileState final : public Node {
        BASE_CORE_METHODS(WhileState);

        // := 'while' expr Suite

        explicit WhileState(NodeT<> condition, NodeT<SuiteState> body)
            : condition(std::move(condition))
            , body(std::move(body)) {}

        NodeT<>           condition;
        NodeT<SuiteState> body;
    };

    class IfState final : public Node {
        BASE_CORE_METHODS(IfState);

        // := 'if' expr Suite (ElseState)?

        IfState(NodeT<> condition, NodeT<SuiteState> body, NodeT<> else_body = nullptr)
            : condition(std::move(condition))
            , body(std::move(body))
            , else_body(std::move(else_body)) {}

        NodeT<>           condition;
        NodeT<SuiteState> body;
        NodeT<>           else_body;
    };

    class ElseState final : public Node {
        BASE_CORE_METHODS(ElseState);

        // := 'else' Suite

        explicit ElseState(NodeT<SuiteState> body)
            : body(std::move(body)) {}

        NodeT<SuiteState> body;
    };

    class SwitchState final : public Node {
        BASE_CORE_METHODS(SwitchState);

        // := 'switch' expr '{' SwitchCaseState* '}'

        SwitchState(NodeT<> condition, NodeV<SwitchCaseState> cases)
            : condition(std::move(condition))
            , cases(std::move(cases)) {}

        NodeT<>                condition;
        NodeV<SwitchCaseState> cases;
    };

    class SwitchCaseState final : public Node {
        BASE_CORE_METHODS(SwitchCaseState);

        // := 'case' expr Suite | 'default' Suite

        enum class CaseType {
            Case,
            Default,
        };

        SwitchCaseState(NodeT<> condition, NodeT<SuiteState> body, CaseType type)
            : condition(std::move(condition))
            , body(std::move(body))
            , type(type) {}

        NodeT<>           condition;
        NodeT<SuiteState> body;
        CaseType          type;
    };

    class ImportState final : public Node {
        BASE_CORE_METHODS(ImportState);
    };

    class SingleImportState final : public Node {
        BASE_CORE_METHODS(SingleImportState);
    };

    class MultiImportState final : public Node {
        BASE_CORE_METHODS(MultiImportState);
    };

    class AliasState final : public Node {
        BASE_CORE_METHODS(AliasState);
    };

    class YieldState final : public Node {
        BASE_CORE_METHODS(YieldState);

        // := 'yield' expr ';'

        explicit YieldState(NodeT<> value)
            : value(std::move(value)) {}

        NodeT<> value;
    };

    class DeleteState final : public Node {
        BASE_CORE_METHODS(DeleteState);

        // := 'yield' expr ';'

        explicit DeleteState(NodeT<> value)
            : value(std::move(value)) {}

        NodeT<> value;
    };

    class ReturnState final : public Node {
        BASE_CORE_METHODS(ReturnState);

        // := 'return' expr ';'

        explicit ReturnState(NodeT<> value)
            : value(std::move(value)) {}

        NodeT<> value;
    };

    class BreakState final : public Node {
        BASE_CORE_METHODS(BreakState);

        // := 'break' ';'
        
        explicit BreakState(token::Token marker)
            : marker(std::move(marker)) {}

        token::Token marker;
    };

    class ContinueState final : public Node {
        BASE_CORE_METHODS(ContinueState);

        // := 'continue' ';'

        explicit ContinueState(token::Token marker)
            : marker(std::move(marker)) {}

        token::Token marker;
    };

    class ExprState final : public Node {
        BASE_CORE_METHODS(ExprState);

        // := expr ';'

        explicit ExprState(NodeT<> value)
            : value(std::move(value)) {}

        NodeT<> value;
    };

    class BlockState final : public Node {
        BASE_CORE_METHODS(BlockState);

        // := '{' Statement* '}'

        explicit BlockState(NodeV<> body)
            : body(std::move(body)) {}

        NodeV<> body;
    };

    class SuiteState final : public Node {
        BASE_CORE_METHODS(SuiteState);

        // := BlockState | (':' Statement)
        // the suite parser will either make a block node if theres a { or a single statement with
        // the :

        explicit SuiteState(NodeT<BlockState> body)
            : body(std::move(body)) {}

        NodeT<BlockState> body;
    };

    class CatchState final : public Node {
        BASE_CORE_METHODS(CatchState);

        // := 'catch' (NamedVarSpecifier ((',' NamedVarSpecifier)*)?)? SuiteState (CatchState | FinallyState)?

        CatchState(NodeT<NamedVarSpecifier> catch_state, NodeT<SuiteState> body)
            : catch_state(std::move(catch_state))
            , body(std::move(body)) {}

        NodeT<NamedVarSpecifier> catch_state;
        NodeT<SuiteState>        body;
    };

    class FinallyState final : public Node {
        BASE_CORE_METHODS(FinallyState);

        // := 'finally' SuiteState

        explicit FinallyState(NodeT<SuiteState> body)
            : body(std::move(body)) {}

        NodeT<SuiteState> body;
    };

    class TryState final : public Node {
        BASE_CORE_METHODS(TryState);

        // := 'try' SuiteState (CatchState*) (FinallyState)?

        explicit TryState(NodeT<SuiteState> body) : body(std::move(body)) {}

        TryState(NodeT<SuiteState> body, NodeV<CatchState> catch_states, NodeT<FinallyState> finally_state = nullptr)
            : body(std::move(body))
            , catch_states(std::move(catch_states))
            , finally_state(std::move(finally_state)) {}

        NodeT<SuiteState>    body;
        NodeV<CatchState>    catch_states;
        NodeT<FinallyState>  finally_state;
    };

    class PanicState final : public Node {
        BASE_CORE_METHODS(PanicState);

        // := 'panic' E ';'

        explicit PanicState(NodeT<> expr)
            : expr(std::move(expr)) {}

        NodeT<> expr;
    };

}  // namespace __AST_NODE_BEGIN

#endif  // __AST_STATEMENTS_H__