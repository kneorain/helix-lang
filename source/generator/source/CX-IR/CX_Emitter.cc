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

#include <cstdio>
#include <ctime>
#include <memory>
#include <stdexcept>

#include "generator/include/CX-IR/CXIR.hh"
#include "neo-panic/include/error.hh"
#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/AST.hh"
#include "parser/ast/include/nodes/AST_declarations.hh"
#include "parser/ast/include/nodes/AST_expressions.hh"
#include "parser/ast/include/private/AST_generate.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "token/include/private/Token_base.hh"
#include "token/include/private/Token_generate.hh"

#define CXIR_NOT_IMPLEMENTED throw std::runtime_error(GET_DEBUG_INFO + "Not implemented yet")
#define ADD_TOKEN(token) tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::token))
#define ADD_TOKEN_AS_VALUE(token, value) \
    tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::token, value))
#define ADD_TOKEN_AS_TOKEN(token, token_value) \
    tokens.push_back(std::make_unique<CX_Token>(token_value, cxir_tokens::token))

#define ADD_NODE_PARAM(param) ADD_PARAM(node.param)
#define ADD_PARAM(param) param->accept(*this)

// This macro will not add a separator after the last element.
#define SEP(args, sep)                                  \
    if (!node.args.empty()) {                           \
        ADD_NODE_PARAM(args[0]);                        \
        for (size_t i = 1; i < node.args.size(); ++i) { \
            sep;                                        \
            ADD_NODE_PARAM(args[i]);                    \
        }                                               \
    }

// This macro always adds the separator, even after the last element.
#define SEP_TRAILING(args, sep)                         \
    if (!node.args.empty())                             \
        for (size_t i = 0; i < node.args.size(); ++i) { \
            ADD_NODE_PARAM(args[i]);                    \
            sep                                         \
        }

#define UNLESS_NULL(x) (node.x) if (node.x != nullptr)

#define ADD_ALL_PARAMS(params)         \
    for (const auto &param : params) { \
        ADD_PARAM(param);              \
    }

#define ADD_ALL_NODE_PARAMS(params) ADD_ALL_PARAMS(node.params)

#define COMMA_SEP(args) SEP(args, ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ",");)
#define SCOPE_SEP(args) SEP(args, ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "::");)

#define DELIMIT(L, R, ...) \
    ADD_TOKEN(L);          \
    __VA_ARGS__            \
    ADD_TOKEN(R)

#define PAREN_DELIMIT(...) DELIMIT(CXX_LPAREN, CXX_RPAREN, __VA_ARGS__)
#define BRACE_DELIMIT(...) DELIMIT(CXX_LBRACE, CXX_RBRACE, __VA_ARGS__)
#define BRACKET_DELIMIT(...) DELIMIT(CXX_LBRACKET, CXX_RBRACKET, __VA_ARGS__)
#define ANGLE_DELIMIT(...) DELIMIT(CXX_LESS, CXX_GREATER, __VA_ARGS__)

CX_VISIT_IMPL(LiteralExpr) {
    tokens.push_back(std::make_unique<CX_Token>(node.value, cxir_tokens::CXX_CORE_LITERAL));
}

CX_VISIT_IMPL(LetDecl) {

    // for (int i =0; i<node.modifiers.get<parser::ast::TypeSpecifier>().size(); ++i) {

    //     // node.modifiers.

    // }

    ADD_ALL_NODE_PARAMS(vars);
}

CX_VISIT_IMPL(BinaryExpr) {
    // -> '(' lhs op  rhs ')'
    // FIXME: are the parens necessary?
    // ADD_TOKEN(CXX_LPAREN);
    ADD_NODE_PARAM(lhs);
    ADD_TOKEN_AS_TOKEN(CXX_CORE_OPERATOR, node.op);
    ADD_NODE_PARAM(rhs);
    // ADD_TOKEN(CXX_RPAREN);
}

CX_VISIT_IMPL(UnaryExpr) {
    // -> '(' op '(' opd ')' ')' | '(' opd ')'

    PAREN_DELIMIT(if (node.op.token_kind() != token::PUNCTUATION_QUESTION_MARK)
                      ADD_TOKEN_AS_TOKEN(CXX_CORE_OPERATOR, node.op);

                  PAREN_DELIMIT(ADD_NODE_PARAM(opd);););
}

CX_VISIT_IMPL(IdentExpr) {
    // if self then set to (*this)
    if (node.name.value() == "self") {
        ADD_TOKEN(CXX_LPAREN);
        ADD_TOKEN(CXX_ASTERISK);
        ADD_TOKEN(CXX_THIS);
        ADD_TOKEN(CXX_RPAREN);
        return;
    }

    ADD_TOKEN_AS_TOKEN(CXX_CORE_IDENTIFIER, node.name);
}

CX_VISIT_IMPL(NamedArgumentExpr) {
    // -> name '=' value
    ADD_NODE_PARAM(name);
    if (node.value) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
        ADD_NODE_PARAM(value);
    }
}

CX_VISIT_IMPL(ArgumentExpr) { ADD_NODE_PARAM(value); }

CX_VISIT_IMPL(ArgumentListExpr) {

    // -> '(' arg (',' arg)* ')'
    PAREN_DELIMIT(COMMA_SEP(args););
}

CX_VISIT_IMPL(GenericInvokeExpr) { ANGLE_DELIMIT(COMMA_SEP(args);); }

CX_VISIT_IMPL(GenericInvokePathExpr) {
    // := E GenericInvokeExpr
    ADD_NODE_PARAM(generic);  // TODO: WT is this
}

CX_VISIT_IMPL(ScopePathExpr) {
    // -> path ('::' path)*

    for (const parser::ast::NodeT<parser::ast::node::IdentExpr> &ident : node.path) {
        ident->accept(*this);
        ADD_TOKEN(CXX_SCOPE_RESOLUTION);
    }

    ADD_NODE_PARAM(access);
}

CX_VISIT_IMPL(DotPathExpr) {
    // -> path '.' path
    ADD_NODE_PARAM(lhs);
    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ".");
    ADD_NODE_PARAM(rhs);
}

CX_VISIT_IMPL(ArrayAccessExpr) {
    // -> array '[' index ']'
    ADD_NODE_PARAM(lhs);
    BRACKET_DELIMIT(          //
        ADD_NODE_PARAM(rhs);  //
    );
}

CX_VISIT_IMPL(PathExpr) {  // TODO
    ADD_NODE_PARAM(path);
}

CX_VISIT_IMPL(FunctionCallExpr) {
    // path
    // generic
    // args

    ADD_NODE_PARAM(path);

    if (node.generic) {
        ADD_NODE_PARAM(generic);
    };
    ADD_NODE_PARAM(args);
}

CX_VISIT_IMPL(ArrayLiteralExpr) { BRACE_DELIMIT(COMMA_SEP(values);); }

CX_VISIT_IMPL(TupleLiteralExpr) { BRACE_DELIMIT(COMMA_SEP(values);); }
/// TODO: is this even imlpementad in the current stage?
CX_VISIT_IMPL(SetLiteralExpr) { BRACE_DELIMIT(COMMA_SEP(values);); }

CX_VISIT_IMPL(MapPairExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(MapLiteralExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ObjInitExpr) {

    if (node.path) {
        ADD_NODE_PARAM(path);
    }
    BRACE_DELIMIT(  //
        if (!node.kwargs.empty()) {
            ADD_NODE_PARAM(kwargs[0]->value);

            for (size_t i = 1; i < node.kwargs.size(); ++i) {
                ADD_TOKEN(CXX_COMMA);
                ADD_NODE_PARAM(kwargs[i]->value);
            }
        }  //
    );
}

CX_VISIT_IMPL(LambdaExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(TernaryExpr) {

    PAREN_DELIMIT(                  //
        ADD_NODE_PARAM(condition);  //
    );
    ADD_TOKEN(CXX_QUESTION);
    ADD_NODE_PARAM(if_true);
    ADD_TOKEN(CXX_COLON);
    ADD_NODE_PARAM(if_false);
}

CX_VISIT_IMPL(ParenthesizedExpr) { PAREN_DELIMIT(ADD_NODE_PARAM(value);); }

CX_VISIT_IMPL(CastExpr) {

    // TODO: WHAT KIND OF CAST???
    // static for now...
    ADD_TOKEN(CXX_STATIC_CAST);

    ANGLE_DELIMIT(             //
        ADD_NODE_PARAM(type);  //
    );

    PAREN_DELIMIT(              //
        ADD_NODE_PARAM(value);  //
    );
}

// := E ('in' | 'derives') E
CX_VISIT_IMPL(InstOfExpr) {
    switch (node.op) {
        case parser::ast::node::InstOfExpr::InstanceType::Derives:
            // TODO: make it so it does not require that it is a class
            /// std::is_base_of<A, B>::value
            ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "std");
            ADD_TOKEN(CXX_SCOPE_RESOLUTION);
            ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "is_base_of");
            ANGLE_DELIMIT(              //
                ADD_NODE_PARAM(type);   //
                ADD_TOKEN(CXX_COMMA);   //
                ADD_NODE_PARAM(value);  //
            );
            ADD_TOKEN(CXX_SCOPE_RESOLUTION);
            ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "value");

            break;
        case parser::ast::node::InstOfExpr::InstanceType::In:
            // In flip flops the type and value
            ADD_NODE_PARAM(value);

            ANGLE_DELIMIT(ADD_NODE_PARAM(type););  // TODO: This is temp
    }
}

CX_VISIT_IMPL(AsyncThreading) {

    switch (node.type) {
        case parser::ast::node::AsyncThreading::AsyncThreadingType::Await:
            ADD_TOKEN(CXX_CO_AWAIT);
            ADD_NODE_PARAM(value);
            break;
        case parser::ast::node::AsyncThreading::AsyncThreadingType::Spawn:
        case parser::ast::node::AsyncThreading::AsyncThreadingType::Thread:
        case parser::ast::node::AsyncThreading::AsyncThreadingType::Other:
            CXIR_NOT_IMPLEMENTED;
    }
}

CX_VISIT_IMPL(Type) {  // TODO Modifiers

    ADD_NODE_PARAM(value);
    // TODO: make *null into null_ptr

    if (node.generics)
        ADD_NODE_PARAM(generics);
}

CX_VISIT_IMPL(NamedVarSpecifier) {
    // (type | auto) name

    if (node.type) {
        ADD_NODE_PARAM(type);
    } else {
        ADD_TOKEN(CXX_AUTO);
    }

    ADD_NODE_PARAM(path);
}

CX_VISIT_IMPL(NamedVarSpecifierList) { COMMA_SEP(vars); }

CX_VISIT_IMPL(ForPyStatementCore) {
    // := NamedVarSpecifier 'in 'expr' Suite

    ADD_TOKEN(CXX_LPAREN);

    ADD_NODE_PARAM(vars);

    ADD_TOKEN(CXX_COLON);

    ADD_NODE_PARAM(range);

    ADD_TOKEN(CXX_RPAREN);

    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(ForCStatementCore) {
    PAREN_DELIMIT(                  //
        ADD_NODE_PARAM(init);       //
        ADD_TOKEN(CXX_SEMICOLON);   //
        ADD_NODE_PARAM(condition);  //
        ADD_TOKEN(CXX_SEMICOLON);   //
        ADD_NODE_PARAM(update);     //
    );
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(ForState) {
    // := 'for' (ForPyStatementCore | ForCStatementCore)

    ADD_TOKEN(CXX_FOR);

    ADD_NODE_PARAM(core);
}

CX_VISIT_IMPL(WhileState) {
    // := 'while' expr Suite

    ADD_TOKEN(CXX_WHILE);

    PAREN_DELIMIT(                  //
        ADD_NODE_PARAM(condition);  //
    );
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(ElseState) {

    ADD_TOKEN(CXX_ELSE);

    if (node.type != parser::ast::node::ElseState::ElseType::Else) {
        ADD_TOKEN(CXX_IF);
        PAREN_DELIMIT(  //
            if (node.type != parser::ast::node::ElseState::ElseType::ElseUnless) {
                ADD_TOKEN(CXX_EXCLAMATION);
            }

            PAREN_DELIMIT(                  //
                ADD_NODE_PARAM(condition);  //
            );                              //
        );
    }
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(IfState) {
    ADD_TOKEN(CXX_IF);

    if (node.type == parser::ast::node::IfState::IfType::Unless) {  //
        PAREN_DELIMIT(                                              //
            ADD_TOKEN(CXX_EXCLAMATION);                             //
            PAREN_DELIMIT(                                          //
                ADD_NODE_PARAM(condition);                          //
            );                                                      //
        );                                                          //
    } else {
        PAREN_DELIMIT(                  //
            ADD_NODE_PARAM(condition);  //
        );                              //
    }

    ADD_NODE_PARAM(body);

    ADD_ALL_NODE_PARAMS(else_body);
}

CX_VISIT_IMPL(SwitchCaseState) {
    // What are case markers?? TODO: Implement them
    switch (node.type) {

        case parser::ast::node::SwitchCaseState::CaseType::Case:
            ADD_TOKEN(CXX_CASE);
            ADD_NODE_PARAM(condition);
            ADD_TOKEN(CXX_COLON);
            ADD_NODE_PARAM(body);
            break;

        case parser::ast::node::SwitchCaseState::CaseType::Fallthrough:
            ADD_TOKEN(CXX_CASE);
            ADD_NODE_PARAM(condition);
            ADD_TOKEN(CXX_COLON);

            BRACKET_DELIMIT(                                                 //
                BRACKET_DELIMIT(                                             //
                    ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "fallthrough");  //
                );                                                           //
            );                                                               //

            break;

        case parser::ast::node::SwitchCaseState::CaseType::Default:
            ADD_TOKEN(CXX_DEFAULT);
            ADD_TOKEN(CXX_COLON);
            ADD_NODE_PARAM(body);
    }
}

CX_VISIT_IMPL(SwitchState) {
    ADD_TOKEN(CXX_SWITCH);

    PAREN_DELIMIT(                  //
        ADD_NODE_PARAM(condition);  //
    );

    BRACE_DELIMIT(                   //
        ADD_ALL_NODE_PARAMS(cases);  //
    );
}

CX_VISIT_IMPL(YieldState) {
    ADD_TOKEN(CXX_CO_YIELD);
    ADD_NODE_PARAM(value);
    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(DeleteState) {
    ADD_TOKEN(CXX_DELETE);
    ADD_NODE_PARAM(value);
    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(AliasState) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(SingleImportState) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(MultiImportState) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ImportState) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ReturnState) {
    ADD_TOKEN(CXX_RETURN);  // TODO co_return for generator contexts?
    ADD_NODE_PARAM(value);
    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(BreakState) {
    ADD_TOKEN(CXX_BREAK);
    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(BlockState) {
    // -> (statement ';')*
    SEP_TRAILING(body, ADD_TOKEN(CXX_SEMICOLON););
}

CX_VISIT_IMPL(SuiteState) {
    // -> '{' body '}'
    BRACE_DELIMIT(  //

        if (node.body) { ADD_NODE_PARAM(body); }  //
    );
}
CX_VISIT_IMPL(ContinueState) { ADD_TOKEN(CXX_CONTINUE); }

CX_VISIT_IMPL(CatchState) {
    ADD_TOKEN(CXX_CATCH);
    PAREN_DELIMIT(                    //
        ADD_NODE_PARAM(catch_state);  //
    );                                //
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(FinallyState) {
    // TODO: this needs to be placed before return, so, the code gen needs to be statefull here...
    // for now it will just put the
    // https://stackoverflow.com/questions/33050620/golang-style-defer-in-c
    // for try catch this would have to be placed before the try block
    // shared_ptr<void>_(nullptr, [] { cout << ", World!"; });
    // ADD_TOKEN_AS_TOKEN(CXX_CORE_IDENTIFIER, "shared_ptr");
    // ANGLE_DELIMIT(ADD_TOKEN(CXX_VOID););
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(TryState) {

    // Is this nullable?
    if (node.finally_state) {           //
        ADD_NODE_PARAM(finally_state);  //
    }

    ADD_TOKEN(CXX_TRY);
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(PanicState) {
    ADD_TOKEN(CXX_THROW);
    ADD_NODE_PARAM(expr);
    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(ExprState) {
    // -> expr ';'
    ADD_NODE_PARAM(value);
    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(RequiresParamDecl) {
    if (node.is_const) {
        if (node.var) {
            PARSE_ERROR(node.var->path->name, "Const requires a type");  //
            return;                                                      //
        };
    }

    if (node.var->type) {           //
        ADD_NODE_PARAM(var->type);  // TODO: verify
    } else {
        ADD_TOKEN(CXX_TYPENAME);  // template <typename
    }

    ADD_NODE_PARAM(var->path);

    if (node.value) {                                //
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");  //
        ADD_NODE_PARAM(value);                       //
    };
}

CX_VISIT_IMPL(RequiresParamList) {  // -> (param (',' param)*)?
    COMMA_SEP(params);
}

CX_VISIT_IMPL(EnumMemberDecl) {
    ADD_NODE_PARAM(name);
    if (node.value) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
        ADD_NODE_PARAM(value);
    };
}

CX_VISIT_IMPL(UDTDeriveDecl) {

    switch (node.derives[0].second.type) {
        case parser::ast::AccessSpecifier::Specifier::Internal:
            CXIR_NOT_IMPLEMENTED;  // TODO: ERROR?
            break;
        case parser::ast::AccessSpecifier::Specifier::Public:
            ADD_TOKEN(CXX_PUBLIC);
            break;
        case parser::ast::AccessSpecifier::Specifier::Protected:
            ADD_TOKEN(CXX_PROTECTED);
            break;
        case parser::ast::AccessSpecifier::Specifier::Private:
            ADD_TOKEN(CXX_PRIVATE);
            break;
    }

    ADD_NODE_PARAM(derives[0].first);
    for (size_t i = 1; i < node.derives.size(); ++i) {
        ADD_TOKEN(CXX_COMMA);
        switch (node.derives[i].second.type) {
            case parser::ast::AccessSpecifier::Specifier::Internal:
                CXIR_NOT_IMPLEMENTED;  // TODO: ERROR?
                break;
            case parser::ast::AccessSpecifier::Specifier::Public:
                ADD_TOKEN(CXX_PUBLIC);
                break;
            case parser::ast::AccessSpecifier::Specifier::Protected:
                ADD_TOKEN(CXX_PROTECTED);
                break;
            case parser::ast::AccessSpecifier::Specifier::Private:
                ADD_TOKEN(CXX_PRIVATE);
                break;
        }

        ADD_NODE_PARAM(derives[i].first);
    }
}

CX_VISIT_IMPL(TypeBoundList){

    SEP(bounds, ADD_TOKEN(CXX_LOGICAL_AND))

}

CX_VISIT_IMPL(TypeBoundDecl) {
    ADD_NODE_PARAM(bound);
}

CX_VISIT_IMPL(RequiresDecl) {
    // -> 'template' '<' params '>'
    ADD_TOKEN(CXX_TEMPLATE);

    ANGLE_DELIMIT(               //
        ADD_NODE_PARAM(params);  //
    );
    if (node.bounds) {
        ADD_TOKEN(CXX_REQUIRES);
        ADD_NODE_PARAM(bounds);
    }
}

CX_VISIT_IMPL(ModuleDecl) {

    if (node.inline_module) {
        ADD_TOKEN(CXX_INLINE);
    }

    ADD_TOKEN(CXX_NAMESPACE);

    ADD_NODE_PARAM(name);

    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(StructDecl) {  // TODO: only enums, types, and unions
    // TODO: Modifiers
    if (node.generics) {           //
        ADD_NODE_PARAM(generics);  //
    };

    // ADD_TOKEN(CXX_TYPEDEF);

    ADD_TOKEN(CXX_STRUCT);

    ADD_NODE_PARAM(name);

    if (node.derives) {
        ADD_TOKEN(CXX_COLON);
        ADD_NODE_PARAM(derives);  // should be its own generator
    }

    ADD_NODE_PARAM(body);
    ADD_TOKEN(CXX_SEMICOLON);

    // structs can derive?
    // enums should be able to as well... idea?
}

CX_VISIT_IMPL(ConstDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ClassDecl) {
    auto check_self_and_static =
        [&](const parser::ast::NodeT<parser::ast::node::FuncDecl> &func_decl)
        -> std::pair<bool, bool> {
        std::pair<bool, bool>                          found_self_static = {false, false};
        parser::ast::NodeT<parser::ast::node::VarDecl> self_arg          = nullptr;

        if (func_decl->params.size() > 0 && func_decl->params[0] != nullptr) {
            self_arg = func_decl->params[0];

            if (self_arg->var->path->name.value() == "self") {
                if (self_arg->var->type != nullptr || self_arg->value != nullptr) {
                    throw error::Panic(
                        error::CodeError{.pof = &self_arg->var->path->name, .err_code = 0.3006});
                }

                found_self_static.first = true;  // found 'self'
            }
        }

        if (func_decl->modifiers.contains(token::tokens::KEYWORD_STATIC)) {
            found_self_static.second = true;  // found 'static'
        }

        return found_self_static;
    };

    auto process_func_decl = [&](const parser::ast::NodeT<parser::ast::node::FuncDecl> &func_decl,
                                 token::Token                                          &pof) {
        auto [has_self, has_static] = check_self_and_static(func_decl);

        if (!has_static) {
            if (!has_self) {
                error::Panic(error::CodeError{.pof      = &pof,
                                              .err_code = 0.3004});  // Warn: static should be added
                func_decl->modifiers.add(parser::ast::FunctionSpecifier(
                    token::Token(token::tokens::KEYWORD_STATIC, "helix_internal.file")));
            }
        } else if (has_self) {
            throw error::Panic(error::CodeError{
                .pof = &pof, .err_code = 0.3005});  // Error: both 'self' and 'static' found
        }

        if (has_self) {
            func_decl->params.erase(func_decl->params.begin());  // Remove 'self'
        }
    };

    if (node.generics != nullptr) {
        ADD_NODE_PARAM(generics);
    }

    ADD_TOKEN(CXX_CLASS);
    ADD_NODE_PARAM(name);

    if (node.derives) {
        ADD_TOKEN(CXX_COLON);
        ADD_NODE_PARAM(derives);
    }

    if (node.body != nullptr) {
        BRACE_DELIMIT(  //
            for (auto &child
                 : node.body->body->body) {
                if (child->getNodeType() == parser::ast::node::nodes::FuncDecl) {
                    auto func_decl = std::static_pointer_cast<parser::ast::node::FuncDecl>(child);
                    token::Token func_name = func_decl->name->get_back_name();

                    process_func_decl(func_decl, func_name);

                    if (func_decl->modifiers.contains(token::tokens::KEYWORD_PUBLIC)) {
                        ADD_TOKEN(CXX_PUBLIC);
                        ADD_TOKEN(CXX_COLON);
                    } else if (func_decl->modifiers.contains(token::tokens::KEYWORD_PROTECTED)) {
                        ADD_TOKEN(CXX_PROTECTED);
                        ADD_TOKEN(CXX_COLON);
                    } else if (func_decl->modifiers.contains(token::tokens::KEYWORD_PRIVATE)) {
                        ADD_TOKEN(CXX_PRIVATE);
                        ADD_TOKEN(CXX_COLON);
                    } else {  // public by default
                        ADD_TOKEN(CXX_PUBLIC);
                        ADD_TOKEN(CXX_COLON);
                    }

                    visit(*func_decl, func_name.value() == node.name->name.value());
                } else if (child->getNodeType() == parser::ast::node::nodes::OpDecl) {
                    auto op_decl = std::static_pointer_cast<parser::ast::node::OpDecl>(child);
                    token::Token op_name = op_decl->func->name->get_back_name();

                    process_func_decl(op_decl->func, op_name);

                    if (op_decl->modifiers.contains(token::tokens::KEYWORD_PUBLIC)) {
                        ADD_TOKEN(CXX_PUBLIC);
                        ADD_TOKEN(CXX_COLON);
                    } else if (op_decl->modifiers.contains(token::tokens::KEYWORD_PROTECTED)) {
                        ADD_TOKEN(CXX_PROTECTED);
                        ADD_TOKEN(CXX_COLON);
                    } else if (op_decl->modifiers.contains(token::tokens::KEYWORD_PRIVATE)) {
                        ADD_TOKEN(CXX_PRIVATE);
                        ADD_TOKEN(CXX_COLON);
                    } else {  // public by default
                        ADD_TOKEN(CXX_PUBLIC);
                        ADD_TOKEN(CXX_COLON);
                    }

                    visit(*op_decl);
                } else {
                    ADD_PARAM(child);
                    ADD_TOKEN(CXX_SEMICOLON);
                }
            }  //
        );
    }

    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(InterDecl) {
    // can have let const eval, type and functions, default impl functions...
    // TODO: Modifiers
    // InterDecl := 'const'? VisDecl? 'interface' E.IdentExpr UDTDeriveDecl? RequiresDecl?
    // S.Suite
    // ADD_NODE_PARAM(generics); // WE need a custom generics impl here as Self is the first generic

    ADD_NODE_PARAM(generics);  // not null, as I (@jrcarl624) went into the ast and made this change
                               // for interfaces
    ADD_TOKEN(CXX_CONCEPT);

    ADD_NODE_PARAM(name);

    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
    if (node.derives != nullptr)
        if (!node.derives->derives.empty()) {

#define INSERT_AT_FRONT_GEN(i)                                              \
    if (node.derives->derives[i].first->generics != nullptr) {              \
        node.derives->derives[i].first->generics->args.insert(              \
            node.derives->derives[i].first->generics->args.begin(),         \
            node.generics->params->params.front());                         \
    } else {                                                                \
        parser::ast::NodeT<parser::ast::node::GenericInvokeExpr> gie_node = \
            parser::ast::make_node<parser::ast::node::GenericInvokeExpr>(   \
                node.generics->params->params.front());                     \
        node.derives->derives[i].first->generics.swap(gie_node);            \
    }

            // if null, swap ^^

            INSERT_AT_FRONT_GEN(0);
            ADD_PARAM(node.derives->derives[0].first->value);
            ANGLE_DELIMIT(  //
                for (auto &node
                     : node.derives->derives[0].first->generics->args) {
                    if (node->getNodeName() != "RequiresParamDecl")
                        continue;

                    parser::ast::NodeT<parser::ast::node::RequiresParamDecl> gen =
                        std::static_pointer_cast<parser::ast::node::RequiresParamDecl>(node);

                    ADD_PARAM(gen->var->path);  //
                    ADD_TOKEN(CXX_COMMA);
                }  //

                if (!node.derives->derives[0].first->generics->args.empty()) {
                    tokens.pop_back();
                }
            );

            for (size_t i = 1; i < node.derives->derives.size(); ++i) {

                // TODO: accses Spes

                INSERT_AT_FRONT_GEN(i);
                ADD_PARAM(node.derives->derives[i].first->value);

                ADD_TOKEN(CXX_LOGICAL_AND);
            }

            if (node.body) {
                ADD_TOKEN(CXX_LOGICAL_AND);
            }
        }

    // ADD_NODE_PARAM(body);

    // bool not_added_req = true;  // there is prob a better way to do this...
    // when we have context we will know if there is a function on the interface...

    if (node.body->body) {

        for (size_t i = 0; i < node.body->body->body.size(); ++i) {

            if (node.body->body->body[i]->getNodeType() != parser::ast::node::nodes::FuncDecl)
                continue;  // TODO: Error? no error?

            parser::ast::NodeT<parser::ast::node::FuncDecl> fn =
                std::static_pointer_cast<parser::ast::node::FuncDecl>(node.body->body->body[i]);

            if (fn->body) {
                // TODO: ERROR
            };

            ADD_TOKEN(CXX_REQUIRES);
            PAREN_DELIMIT(                                        //
                ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "Self");  //
                ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "self");  //
                for (auto &param
                     : fn->params) {              //
                    ADD_TOKEN(CXX_COMMA);         //
                    ADD_PARAM(param->var->type);  //
                    ADD_PARAM(param->var->path);  //
                }  //
            );

            // TODO: The only way to derive an interface is to use
            // static_assert(CONCEPT<CLASSNAME>); but this requires that there is context of the
            // interfaces.
            BRACE_DELIMIT(                                            // The outer
                BRACE_DELIMIT(                                        //
                    ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "self");  //
                    ADD_TOKEN(CXX_DOT);                               //
                    ADD_PARAM(fn->name);                              //
                    PAREN_DELIMIT(                                    //
                        for (auto &param                              //
                             : fn->params) {                          //
                            ADD_TOKEN(CXX_COMMA);                     //
                            ADD_PARAM(param->var->path);              // The
                        }  //
                    );                                               //
                );                                                   //
                ADD_TOKEN(CXX_PTR_ACC);                              //
                ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "std");      //
                ADD_TOKEN(CXX_SCOPE_RESOLUTION);                     //
                ADD_TOKEN_AS_VALUE(CXX_CORE_IDENTIFIER, "same_as");  //
                ANGLE_DELIMIT(                                       //
                    if (fn->returns != nullptr) {                    //
                        ADD_PARAM(fn->returns);                      //
                    } else {                                         //
                        ADD_TOKEN(CXX_VOID);                         //
                    }  //
                );
                ADD_TOKEN(CXX_SEMICOLON););
            ADD_TOKEN(CXX_LOGICAL_AND);
        }
        ADD_TOKEN(CXX_TRUE);  // This is just to prevent a syntax error, will be removed in the
        // MAYBE this->tokens.pop_back();
        // future
        ADD_TOKEN(CXX_SEMICOLON);
    }
}

CX_VISIT_IMPL(EnumDecl) {

    ADD_TOKEN(CXX_ENUM);
    ADD_TOKEN(CXX_STRUCT);  // Same as enum class, but it makes more sense here to be a struct
    ADD_NODE_PARAM(name);
    ADD_TOKEN(CXX_COLON);

    // bool has_neg= false;

    // for (auto& mem : node.members) {
    //     if (mem->value) {
    //         mem->value.get().
    //     }
    // }

    if (node.derives) {           //
        ADD_NODE_PARAM(derives);  //
    } else {                      // TODO: after sign is checked use: ADD_TOKEN(CXX_UNSIGNED);
        // if (node.members.size() >=256 )      { ADD_TOKEN(CXX_CHAR);}
        // else if (node.members.size()  ) { ADD_TOKEN(CXX_SHORT);}
        // else if (node.members.size()  ) { ADD_TOKEN(CXX_CHAR);}
        // TODO: SIZING restrictions based on number of elements
    }

    BRACE_DELIMIT(           //
        COMMA_SEP(members);  //
    );

    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(TypeDecl) {
    // TODO: vis, as there is no way to make a type priv if its not on a class
    ADD_NODE_PARAM(generics);
    ADD_TOKEN(CXX_USING);
    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
    ADD_NODE_PARAM(value);
}

CX_VISIT_IMPL_VA(FuncDecl, bool no_return_t) {
    if (node.generics != nullptr) {  //
        ADD_NODE_PARAM(generics);
    };

    if (!no_return_t) {
        if (node.returns != nullptr) {  //
            ADD_NODE_PARAM(returns);
        } else {
            ADD_TOKEN(CXX_VOID);
        }
    }

    // if (node.name == nullptr) {
    //     print("error");
    //     throw std::runtime_error("This is bad");
    // }

    ADD_NODE_PARAM(name);
    PAREN_DELIMIT(          //
        COMMA_SEP(params);  //
    );
    if (node.body) {
        ADD_NODE_PARAM(body);  // TODO: should only error in interfaces
    };
}

CX_VISIT_IMPL(VarDecl) {
    // if (node.var->type, ADD_PARAM(node.var->type);) else { ADD_TOKEN(CXX_AUTO); }

    ADD_NODE_PARAM(var);

    if (node.value) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
        ADD_NODE_PARAM(value);
    }
}

CX_VISIT_IMPL(FFIDecl) {
    if (node.name->value.value() != "\"c++\"") {
        throw std::runtime_error("Only C++ is supported at the moment");
    }

    ADD_TOKEN(CXX_PP_INCLUDE);

    if (node.value->getNodeType() == parser::ast::node::nodes::SingleImportState) {
        ADD_TOKEN_AS_VALUE(
            CXX_CORE_LITERAL,
            std::static_pointer_cast<parser::ast::node::LiteralExpr>(
                std::static_pointer_cast<parser::ast::node::SingleImportState>(node.value)->path)
                ->value.value());
    } else {
        throw std::runtime_error("Only string literals are supported at the moment");
    }
}

CX_VISIT_IMPL(OpDecl) {

    // Add the function normally
    ADD_NODE_PARAM(func);

    if (node.func->generics) {  //
        ADD_NODE_PARAM(func->generics);
    };

    ADD_TOKEN(CXX_INLINE);  // inline the operator
    if (node.func->returns) {  //
        ADD_NODE_PARAM(func->returns);
    } else {
        ADD_TOKEN(CXX_VOID);
    }

    // if (node.func->name == nullptr) {
    //     print("error");
    //     throw std::runtime_error("This is bad");
    // }

    ADD_TOKEN(CXX_OPERATOR);

    for (auto &tok : node.op) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, tok.value());
    }

    PAREN_DELIMIT(                //
        COMMA_SEP(func->params);  //
    );

    if (node.func->body) {
        // ADD_NODE_PARAM(func->body);  // TODO: should only error in interfaces
        BRACE_DELIMIT(
            ADD_TOKEN(CXX_RETURN);       //
            ADD_NODE_PARAM(func->name);  //
            PAREN_DELIMIT(               //

                for (auto &param
                     : node.func->params) {
                    ADD_PARAM(param->var->path);
                    ADD_TOKEN(CXX_COMMA);
                }
                
                if (node.func->params.size() > 0) {
                    this->tokens.pop_back();  // TODO: make better: remove last `,` , make better in the
                }
            );
            ADD_TOKEN(CXX_SEMICOLON););
    };
}

CX_VISIT_IMPL(Program) {
    ADD_TOKEN_AS_VALUE(
        CXX_ANNOTATION,
        R"(///*--- Helix ---*
///
///  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
///  You are allowed to use, modify, redistribute, and create derivative works, even for
///  commercial purposes, provided that you give appropriate credit, and indicate if changes
///  were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/
///
///  SPDX-License-Identifier: CC-BY-4.0
///  Copyright (c) 2024 (CC BY 4.0)
///
///  This file was generated by the Helix compiler, do not modify it directly.
///  Generated on: )" +
            std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) +
            R"( [unix-timestamp]
///
///*--- Helix ---*
)");

    for (const auto &child : node.children) {
        child->accept(*this);
    }
}