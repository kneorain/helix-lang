
#include <memory>
#include "generator/include/CX-IR/CXIR.hh"
#include "parser/ast/include/config/AST_config.def"
#include "token/include/private/Token_generate.hh"

#define CXIR_NOT_IMPLEMENTED throw std::runtime_error(GET_DEBUG_INFO + "Not implemented yet")
#define ADD_TOKEN(token) tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::token))
#define ADD_TOKEN_AS_VALUE(token, value) tokens.push_back(std::make_unique<CX_Token>(cxir_tokens::token, value))
#define ADD_TOKEN_AS_TOKEN(token, token_value) tokens.push_back(std::make_unique<CX_Token>(token_value, cxir_tokens::token))
#define ADD_NODE_PARAM(param) node.param->accept(*this)

CX_VISIT_IMPL(LiteralExpr) {
    tokens.push_back(std::make_unique<CX_Token>(node.value, cxir_tokens::CXX_CORE_LITERAL));
}

CX_VISIT_IMPL(BinaryExpr) {
    // -> '(' '(' lhs ')' op '(' rhs ')' ')'
    ADD_TOKEN(CXX_LPAREN); ADD_TOKEN(CXX_LPAREN);

    ADD_NODE_PARAM(lhs); ADD_TOKEN(CXX_RPAREN);
    ADD_TOKEN_AS_TOKEN(CXX_CORE_OPERATOR, node.op);
    ADD_TOKEN(CXX_LPAREN); ADD_NODE_PARAM(rhs);

    ADD_TOKEN(CXX_RPAREN); ADD_TOKEN(CXX_RPAREN);
}

CX_VISIT_IMPL(UnaryExpr) {
    // -> '(' op '(' opd ')' ')' | '(' opd ')'
    ADD_TOKEN(CXX_LPAREN);
    
    if (!(node.op.token_kind() == token::PUNCTUATION_QUESTION_MARK)) {
        ADD_TOKEN_AS_TOKEN(CXX_CORE_OPERATOR, node.op);
        ADD_TOKEN(CXX_LPAREN);
    } else {
        ADD_TOKEN(CXX_LPAREN);
    }

    ADD_NODE_PARAM(opd);
    ADD_TOKEN(CXX_RPAREN);
    ADD_TOKEN(CXX_RPAREN);
}

CX_VISIT_IMPL(IdentExpr) {
    ADD_TOKEN_AS_TOKEN(CXX_CORE_IDENTIFIER, node.name);
}

CX_VISIT_IMPL(NamedArgumentExpr) {
    // -> name '=' value
    ADD_NODE_PARAM(name);
    ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
    ADD_NODE_PARAM(value);
}

CX_VISIT_IMPL(ArgumentExpr) {
    ADD_NODE_PARAM(value);
}

CX_VISIT_IMPL(ArgumentListExpr) {
    // -> '(' arg (',' arg)* ')'
    ADD_TOKEN(CXX_LPAREN);
    
    // no trailing comma
    for (size_t i = 0; i < node.args.size(); i++) {
        ADD_NODE_PARAM(args[i]);
        if (i != node.args.size() - 1) {
            ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ",");
        }
    }

    ADD_TOKEN(CXX_RPAREN);
}

CX_VISIT_IMPL(GenericInvokeExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(GenericInvokePathExpr) {
    CXIR_NOT_IMPLEMENTED;
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

CX_VISIT_IMPL(ArrayAccessExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(PathExpr) { // TODO
    ADD_NODE_PARAM(path);
}

CX_VISIT_IMPL(FunctionCallExpr) {
    // path
// args
// generic

    ADD_NODE_PARAM(path);
    ADD_NODE_PARAM(args);
}

CX_VISIT_IMPL(ArrayLiteralExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(TupleLiteralExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(SetLiteralExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(MapPairExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(MapLiteralExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ObjInitExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(LambdaExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(TernaryExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ParenthesizedExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(CastExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(InstOfExpr) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(AsyncThreading) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(Type) {  // TODO
    ADD_NODE_PARAM(value);
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

CX_VISIT_IMPL(NamedVarSpecifierList) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ForPyStatementCore) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ForCStatementCore) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ForState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(WhileState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ElseState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(IfState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(SwitchCaseState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(SwitchState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(YieldState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(DeleteState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(AliasState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(SingleImportState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(MultiImportState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ImportState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ReturnState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(BreakState) {
    CXIR_NOT_IMPLEMENTED;
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

CX_VISIT_IMPL(ContinueState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(CatchState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(FinallyState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(TryState) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(PanicState) {
    CXIR_NOT_IMPLEMENTED;
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
        ADD_TOKEN(CXX_TYPENAME); // template <typename
    }

    ADD_NODE_PARAM(var);

    if (node.value != nullptr) {
        ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, "=");
        ADD_NODE_PARAM(value);
    }
}

CX_VISIT_IMPL(RequiresParamList) {
    // -> (param (',' param)*)?

    for (size_t i = 0; i < node.params.size(); i++) {
        ADD_NODE_PARAM(params[i]);
        if (i != node.params.size() - 1) {
            ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ",");
        }
    }
}

CX_VISIT_IMPL(EnumMemberDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(UDTDeriveDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(TypeBoundList) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(TypeBoundDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(RequiresDecl) {
    // -> 'template' '<' params '>'
    ADD_TOKEN(CXX_TEMPLATE);
    ADD_TOKEN(CXX_LESS);

    ADD_NODE_PARAM(params);

    ADD_TOKEN(CXX_GREATER);
}

CX_VISIT_IMPL(ModuleDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(StructDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ConstDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(ClassDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(InterDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(EnumDecl) {
    CXIR_NOT_IMPLEMENTED; 
}

CX_VISIT_IMPL(TypeDecl) {
    CXIR_NOT_IMPLEMENTED;
}

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
    ADD_TOKEN(CXX_LPAREN);

    for (size_t i = 0; i < node.params.size(); i++) {
        ADD_NODE_PARAM(params[i]);
        
        if (i != node.params.size() - 1) {
            ADD_TOKEN_AS_VALUE(CXX_CORE_OPERATOR, ",");
        }
    }

    ADD_TOKEN(CXX_RPAREN);
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

CX_VISIT_IMPL(FFIDecl) {
    CXIR_NOT_IMPLEMENTED;
}

CX_VISIT_IMPL(LetDecl) {
    for (auto &var : node.vars) {
        var->accept(*this);
    }
}

CX_VISIT_IMPL(OpDecl) {
    CXIR_NOT_IMPLEMENTED;
}