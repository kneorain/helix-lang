
#include <memory>

#include "generator/include/CX-IR/CXIR.hh"
#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/nodes/AST_expressions.hh"
#include "parser/ast/include/nodes/AST_statements.hh"
#include "parser/ast/include/private/AST_generate.hh"
#include "token/include/private/Token_generate.hh"

#define CXIR_NOT_IMPLEMENTED throw std::runtime_error(GET_DEBUG_INFO + "Not implemented yet")
#define ADD_TOKEN(token) tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::token))
#define ADD_TOKEN_AS_VALUE(token, value) \
    tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::token, value))
#define ADD_TOKEN_AS_TOKEN(token, token_value) \
    tokens.push_back(std::make_unique<CX_Token>(token_value, cxir_tokens::token))
#define ADD_NODE_PARAM(param) node.param->accept(*this)

#define PAREN_DELIMIT(...) \
    ADD_TOKEN(CXX_LPAREN); \
    __VA_ARGS__            \
    ADD_TOKEN(CXX_RPAREN)

#define BRACE_DELIMIT(...) \
    ADD_TOKEN(CXX_LBRACE); \
    __VA_ARGS__            \
    ADD_TOKEN(CXX_RBRACE)

#define BRACKET_DELIMIT(...) \
    ADD_TOKEN(CXX_LBRACKET); \
    __VA_ARGS__              \
    ADD_TOKEN(CXX_RBRACKET)

#define ANGLE_DELIMIT(...) \
    ADD_TOKEN(CXX_LESS);   \
    __VA_ARGS__            \
    ADD_TOKEN(CXX_GREATER)

CX_VISIT_IMPL(LiteralExpr) {
    tokens.push_back(std::make_unique<CX_Token>(node.value, cxir_tokens::CXX_CORE_LITERAL));
}

CX_VISIT_IMPL(BinaryExpr) {
    // -> '(' '(' lhs ')' op '(' rhs ')' ')'
    PAREN_DELIMIT(ADD_NODE_PARAM(lhs););
    ADD_TOKEN_AS_TOKEN(CXX_CORE_OPERATOR, node.op);
    PAREN_DELIMIT(ADD_NODE_PARAM(rhs););
}

CX_VISIT_IMPL(UnaryExpr) {
    // -> '(' op '(' opd ')' ')' | '(' opd ')'

    PAREN_DELIMIT(if (node.op.token_kind() != token::PUNCTUATION_QUESTION_MARK)
                      ADD_TOKEN_AS_TOKEN(CXX_CORE_OPERATOR, node.op);

                  PAREN_DELIMIT(ADD_NODE_PARAM(opd);););
}

CX_VISIT_IMPL(IdentExpr) { ADD_TOKEN_AS_TOKEN(CXX_CORE_IDENTIFIER, node.name); }

CX_VISIT_IMPL(NamedArgumentExpr) {
    // -> name '=' value
    ADD_NODE_PARAM(name);
    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
    ADD_NODE_PARAM(value);
}

CX_VISIT_IMPL(ArgumentExpr) { ADD_NODE_PARAM(value); }

// the call is the same but different tokens. could be templated, calling for
// generics could be parsed the same and then templated to not be the same,
// this is a note for future implementations, same with
// this could be a do while
// no trailing comma
#define COMMA_SEP(args)                                                          \
    for (size_t i = 0, size_min_1 = node.args.size() - 1; i < size_min_1; ++i) { \
        ADD_NODE_PARAM(args[i]);                                                 \
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ",");                              \
    }

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
    // -> path '::' path
    ADD_NODE_PARAM(lhs);
    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "::");
    ADD_NODE_PARAM(rhs);
}

CX_VISIT_IMPL(DotPathExpr) {
    // -> path '.' path
    ADD_NODE_PARAM(lhs);
    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ".");
    ADD_NODE_PARAM(rhs);
}

CX_VISIT_IMPL(ArrayAccessExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(PathExpr) {  // TODO
    ADD_NODE_PARAM(path);
}

CX_VISIT_IMPL(FunctionCallExpr) {
    // path
    // generic
    // args

    ADD_NODE_PARAM(path);
    ADD_NODE_PARAM(generic);
    ADD_NODE_PARAM(args);
}

CX_VISIT_IMPL(ArrayLiteralExpr) { BRACE_DELIMIT(COMMA_SEP(values);); }

CX_VISIT_IMPL(TupleLiteralExpr) { BRACE_DELIMIT(COMMA_SEP(values);); }
/// TODO: is this even imlpementad in the current stage?
CX_VISIT_IMPL(SetLiteralExpr) { BRACE_DELIMIT(COMMA_SEP(values);); }

CX_VISIT_IMPL(MapPairExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(MapLiteralExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ObjInitExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(LambdaExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(TernaryExpr) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ParenthesizedExpr) { PAREN_DELIMIT(ADD_NODE_PARAM(value);); }

CX_VISIT_IMPL(CastExpr) {

    // TODO: WHAT KIND OF CAST???

    PAREN_DELIMIT(PAREN_DELIMIT(ADD_NODE_PARAM(type);); ADD_NODE_PARAM(value););
}
// := E ('has' | 'derives') E
CX_VISIT_IMPL(InstOfExpr) {
    switch (node.op) {
        case parser::ast::node::InstOfExpr::InstanceType::Derives:

            ADD_NODE_PARAM(type);

            ADD_NODE_PARAM(value);

        case parser::ast::node::InstOfExpr::InstanceType::In:
            // In flip flops the type and value
            ADD_NODE_PARAM(value);

            ADD_NODE_PARAM(type);
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
    ADD_NODE_PARAM(generics);
}

CX_VISIT_IMPL(NamedVarSpecifier) {
    // (type | auto) name

    if (node.has_type) {
        ADD_NODE_PARAM(type);
    } else {
        ADD_TOKEN(CXX_AUTO);
    }

    ADD_NODE_PARAM(path);
}

CX_VISIT_IMPL(NamedVarSpecifierList) { CXIR_NOT_IMPLEMENTED; }

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
    PAREN_DELIMIT(ADD_NODE_PARAM(init); ADD_TOKEN(CXX_SEMICOLON); ADD_NODE_PARAM(condition);
                  ADD_TOKEN(CXX_SEMICOLON);
                  ADD_NODE_PARAM(update);

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

    PAREN_DELIMIT(ADD_NODE_PARAM(condition););
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(ElseState) {

    ADD_TOKEN(CXX_ELSE);

    if (node.type != parser::ast::node::ElseState::ElseType::Else) {
        ADD_TOKEN(CXX_IF);

        PAREN_DELIMIT(if (node.type != parser::ast::node::ElseState::ElseType::ElseUnless)
                          ADD_TOKEN(CXX_NOT);

                      PAREN_DELIMIT(ADD_NODE_PARAM(condition);););
    }
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(IfState) {
    ADD_TOKEN(CXX_IF);
    PAREN_DELIMIT(
        // this is bad
        if (node.type == parser::ast::node::IfState::IfType::Unless) { ADD_TOKEN(CXX_NOT); }

        PAREN_DELIMIT(ADD_NODE_PARAM(condition);););
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(SwitchCaseState) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(SwitchState) { CXIR_NOT_IMPLEMENTED; }

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
    for (auto &stmt : node.body) {
        stmt->accept(*this);
        ADD_TOKEN(CXX_SEMICOLON);
    }
}

CX_VISIT_IMPL(SuiteState) {
    // -> '{' body '}'
    ADD_TOKEN(CXX_LBRACE);

    ADD_NODE_PARAM(body);

    ADD_TOKEN(CXX_RBRACE);
}

CX_VISIT_IMPL(ContinueState) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(CatchState) {
    ADD_TOKEN(CXX_CATCH);
    PAREN_DELIMIT(ADD_NODE_PARAM(catch_state););
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(FinallyState){
    // TODO: this needs to be placed before return, so, the code gen needs to be statefull here...
    // for now it will just put the
    // https://stackoverflow.com/questions/33050620/golang-style-defer-in-c
    // for try catch this would have to be placed before the try block
    // shared_ptr<void>_(nullptr, [] { cout << ", World!"; });
    // ADD_TOKEN_AS_TOKEN(CXX_CORE_IDENTIFIER, "shared_ptr");
    // ANGLE_DELIMIT(ADD_TOKEN(CXX_VOID););
    CXIR_NOT_IMPLEMENTED;}

CX_VISIT_IMPL(TryState) {

    // Is this nullable?
    if (node.finally_state != nullptr)
        ADD_NODE_PARAM(finally_state);

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
    node.value->accept(*this);
    tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::CXX_SEMICOLON));
}

CX_VISIT_IMPL(RequiresParamDecl) {
    if (node.is_const) {
        if (!node.var->has_type) {
            // PANIC?
            PARSE_ERROR(node.var->path->name, "Const requires a type");
            return;
        }
    }

    if (node.var->has_type) {
        node.var->type->accept(*this);
    } else {
        ADD_TOKEN(CXX_TYPENAME);  // template <typename
    }

    ADD_NODE_PARAM(var);

    if (node.value != nullptr) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
        ADD_NODE_PARAM(value);
    }
}

CX_VISIT_IMPL(RequiresParamList) {  // -> (param (',' param)*)?

    COMMA_SEP(params);
}

CX_VISIT_IMPL(EnumMemberDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(UDTDeriveDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(TypeBoundList) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(TypeBoundDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(RequiresDecl) {
    // -> 'template' '<' params '>'
    ADD_TOKEN(CXX_TEMPLATE);
    ADD_TOKEN(CXX_LESS);

    ADD_NODE_PARAM(params);

    ADD_TOKEN(CXX_GREATER);
}

CX_VISIT_IMPL(ModuleDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(StructDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ConstDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(ClassDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(InterDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(EnumDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(TypeDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(FuncDecl) {
    if (node.generics != nullptr) {
        ADD_NODE_PARAM(generics);
    }

    if (node.returns != nullptr) {
        ADD_NODE_PARAM(returns);
    } else {
        ADD_TOKEN(CXX_VOID);
    }

    ADD_NODE_PARAM(name);

    PAREN_DELIMIT(COMMA_SEP(params););
    ADD_NODE_PARAM(body);
}

CX_VISIT_IMPL(VarDecl) {
    if (node.var->type != nullptr) {
        node.var->type->accept(*this);
    } else {
        ADD_TOKEN(CXX_AUTO);
    }

    node.var->path->accept(*this);

    if (node.value != nullptr) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
        ADD_NODE_PARAM(value);
    }

    ADD_TOKEN(CXX_SEMICOLON);
}

CX_VISIT_IMPL(FFIDecl) { CXIR_NOT_IMPLEMENTED; }

CX_VISIT_IMPL(LetDecl) {
    for (auto &var : node.vars) {
        var->accept(*this);
    }
}

CX_VISIT_IMPL(OpDecl) { CXIR_NOT_IMPLEMENTED; }