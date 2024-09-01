// -*- C++ -*-
//===------------------------------------------------------------------------------------------===//
//
// Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
// You are allowed to use, modify, redistribute, and create derivative works, even for commercial
// purposes, provided that you give appropriate credit, and indicate if changes were made.
// For more information, please visit: https://creativecommons.org/licenses/by/4.0/
//
// SPDX-License-Identifier: CC-BY-4.0
// Copyright (c) 2024 (CC BY 4.0)
//
//===------------------------------------------------------------------------------------------===//

#ifndef __AST_NODES_HH__
#define __AST_NODES_HH__

#include "parser/ast/include/ast.hh"

namespace parser::ast::node {
using namespace token;

class UntypedParameter;
class TypedParameter;
class AnySeparatedID;
class QualifiedNamespaceID;
class Suite;
class Identifier;
class DefaultArgument;
class BaseObjectDecl;
class RequiresDeclaration;
class AccessModifiers;
class DerivesDecl;
class EnumBody;
class UnionBody;

// Main Program Structure
class Program final : public ASTBase {
    AST_NODE_METHODS(Program);
    NodeList<NodePtr<>> statements;
};

// Modules and Imports
class Module final : public ASTBase {
    AST_NODE_METHODS(Module);
    NodePtr<QualifiedNamespaceID> namespaceID;
    NodePtr<Suite> suite;
};

class ImportStatement final : public ASTBase {
    AST_NODE_METHODS(ImportStatement);
    NodePtr<QualifiedNamespaceID> namespaceID;
    NodeList<QualifiedNamespaceID> importList;
    NodePtr<QualifiedNamespaceID> alias;
};

class FFIImportStatement final : public ASTBase {
    AST_NODE_METHODS(FFIImportStatement);
    Token ffiString;
    NodePtr<ImportStatement> importStatement;
};

// Class and Struct
class BaseObjectDecl : public ASTBase {
    AST_NODE_METHODS(BaseObjectDecl);
    NodePtr<AccessModifiers> accessModifiers;
    Token qualifier;  // inline, async, static, eval, const, ffi
};

class EnumBody final : public ASTBase {
    AST_NODE_METHODS(EnumBody);
    NodeList<NodePtr<>> parameters;  // TypedParameter or UntypedParameter with optional Expression
};

class UnionBody final : public ASTBase {
    AST_NODE_METHODS(UnionBody);
    NodeList<NodePtr<>> parameters;  // TypedParameter or UntypedParameter
};

// Inheritance and Polymorphism
class DerivesDecl final : public ASTBase {
    AST_NODE_METHODS(DerivesDecl);
    NodeList<QualifiedNamespaceID> baseClasses;
};

class TypeBound final : public ASTBase {
    AST_NODE_METHODS(TypeBound);
    NodePtr<UntypedParameter> parameter;
    NodeList<QualifiedNamespaceID> bounds;
};

class GenericType final : public ASTBase {
    AST_NODE_METHODS(GenericType);
    bool isEval = false;
    NodePtr<> parameter;  // TypedParameter or UntypedParameter
    NodePtr<Expression> expression;
};

class RequiresDeclaration final : public ASTBase {
    AST_NODE_METHODS(RequiresDeclaration);
    NodeList<GenericType> genericTypes;
    NodeList<TypeBound> typeBounds;
};

// Error Handling
class CatchDefinition final : public ASTBase {
    AST_NODE_METHODS(CatchDefinition);
    NodePtr<AnySeparatedID> identifier;
    NodePtr<QualifiedNamespaceID> alias;
    NodePtr<Suite> suite;
};

class FinallyDefinition final : public ASTBase {
    AST_NODE_METHODS(FinallyDefinition);
    NodePtr<Suite> suite;
};

class PanicDefinition final : public ASTBase {
    AST_NODE_METHODS(PanicDefinition);
    NodePtr<Expression> expression;
};

class TryDefinition final : public ASTBase {
    AST_NODE_METHODS(TryDefinition);
    NodePtr<Suite> suite;
    NodePtr<CatchDefinition> catchBlock;
    NodePtr<FinallyDefinition> finallyBlock;
};

class TestDefinition final : public ASTBase {
    AST_NODE_METHODS(TestDefinition);
    Token testName;
    NodePtr<Suite> suite;
};

// Access Specifiers
class AccessModifiers final : public ASTBase {
    AST_NODE_METHODS(AccessModifiers);
    Token modifier;  // priv, pub, prot, intl
};

// Concurrency
class AwaitCall final : public ASTBase {
    AST_NODE_METHODS(AwaitCall);
    NodePtr<Expression> expression;
};

class SpawnCall final : public ASTBase {
    AST_NODE_METHODS(SpawnCall);
    NodePtr<Expression> expression;
};

class ThreadCall final : public ASTBase {
    AST_NODE_METHODS(ThreadCall);
    NodePtr<Expression> expression;
};

// Other
class DeleteCall final : public ASTBase {
    AST_NODE_METHODS(DeleteCall);
    NodePtr<Expression> expression;
};

// Type Definitions
class GenericAccess final : public ASTBase {
    AST_NODE_METHODS(GenericAccess);
    NodeList<NodePtr<>> identifiers;  // QualifiedNamespaceIDOrLiteral
};

// Operators
class Operator final : public ASTBase {
    AST_NODE_METHODS(Operator);
    Token op;
};

class Expressions final : public ASTBase {
    AST_NODE_METHODS(Expressions);
    NodeList<Expression> expressions;
};

class Statements final : public ASTBase {
    AST_NODE_METHODS(Statements);
    NodeList<Statement> statements;
};

// Code Structure
class CodeBlock final : public ASTBase {
    AST_NODE_METHODS(CodeBlock);
    NodeList<NodePtr<>> statementsOrExpressions;
};

class CodeLine final : public ASTBase {
    AST_NODE_METHODS(CodeLine);
    NodePtr<> statementOrExpression;
};

class UntypedParameter final : public ASTBase {
    AST_NODE_METHODS(UntypedParameter);
    NodePtr<Identifier> identifier;
};

class TypedParameter final : public ASTBase {
    AST_NODE_METHODS(TypedParameter);
    NodePtr<Identifier> identifier;
    NodePtr<Type> type;
};

class Suite final : public ASTBase {
    AST_NODE_METHODS(Suite);
    NodePtr<> content;  // Either CodeLine or CodeBlock
};

// Default Argument
class DefaultArgument final : public ASTBase {
    AST_NODE_METHODS(DefaultArgument);
    NodePtr<TypedParameter> parameter;
    NodePtr<Expression> expression;
};

// Helper Functions
class UntypedParameterList final : public ASTBase {
    AST_NODE_METHODS(UntypedParameterList);
    NodeList<UntypedParameter> parameters;
};

class TypedParameterList final : public ASTBase {
    AST_NODE_METHODS(TypedParameterList);
    NodeList<TypedParameter> parameters;
};

class DefaultArgumentList final : public ASTBase {
    AST_NODE_METHODS(DefaultArgumentList);
    NodeList<DefaultArgument> arguments;
};

class GenericTypeList final : public ASTBase {
    AST_NODE_METHODS(GenericTypeList);
    NodeList<GenericType> types;
};

class TypeBoundList final : public ASTBase {
    AST_NODE_METHODS(TypeBoundList);
    NodeList<TypeBound> bounds;
};

class QualifiedNamespaceIDOrLiteralList final : public ASTBase {
    AST_NODE_METHODS(QualifiedNamespaceIDOrLiteralList);
    NodeList<NodePtr<>> identifiersOrLiterals;  // QualifiedNamespaceID or Literal
};

class TypeList final : public ASTBase {
    AST_NODE_METHODS(TypeList);
    NodeList<Type> types;
};

class ExpressionList final : public ASTBase {
    AST_NODE_METHODS(ExpressionList);
    NodeList<Expression> expressions;
};

}  // namespace parser::ast::node

#endif  // __AST_NODES_HH__