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

struct UntypedParameter;
struct TypedParameter;
struct AnySeparatedID;
struct QualifiedNamespaceID;
struct Suite;
struct Identifier;
struct DefaultArgument;
struct BaseObjectDecl;
struct RequiresDeclaration;
struct AccessModifiers;
struct DerivesDecl;
struct EnumBody;
struct UnionBody;

// Main Program Structure
struct Program final : ASTBase<Program> {
    AST_NODE_METHODS(Program);
    NodeList<NodePtr<>> statements;
};

// Modules and Imports
struct Module final : ASTBase<Module> {
    AST_NODE_METHODS(Module);
    NodePtr<QualifiedNamespaceID> namespaceID;
    NodePtr<Suite> suite;
};

struct ImportStatement final : ASTBase<ImportStatement> {
    AST_NODE_METHODS(ImportStatement);
    NodePtr<QualifiedNamespaceID> namespaceID;
    NodeList<QualifiedNamespaceID> importList;
    NodePtr<QualifiedNamespaceID> alias;
};

struct FFIImportStatement final : ASTBase<FFIImportStatement> {
    AST_NODE_METHODS(FFIImportStatement);
    Token ffiString;
    NodePtr<ImportStatement> importStatement;
};

// Class and Struct
struct BaseObjectDecl : ASTBase<BaseObjectDecl> {
    AST_NODE_METHODS(BaseObjectDecl);
    NodePtr<AccessModifiers> accessModifiers;
    Token qualifier;  // inline, async, static, eval, const, ffi
};

struct EnumBody final : ASTBase<EnumBody> {
    AST_NODE_METHODS(EnumBody);
    NodeList<NodePtr<>> parameters;  // TypedParameter or UntypedParameter with optional Expression
};

struct UnionBody final : ASTBase<UnionBody> {
    AST_NODE_METHODS(UnionBody);
    NodeList<NodePtr<>> parameters;  // TypedParameter or UntypedParameter
};

// Inheritance and Polymorphism
struct DerivesDecl final : ASTBase<DerivesDecl> {
    AST_NODE_METHODS(DerivesDecl);
    NodeList<QualifiedNamespaceID> baseClasses;
};

struct TypeBound final : ASTBase<TypeBound> {
    AST_NODE_METHODS(TypeBound);
    NodePtr<UntypedParameter> parameter;
    NodeList<QualifiedNamespaceID> bounds;
};

struct GenericType final : ASTBase<GenericType> {
    AST_NODE_METHODS(GenericType);
    bool isEval = false;
    NodePtr<> parameter;  // TypedParameter or UntypedParameter
    NodePtr<Expression<void>> expression;
};

struct RequiresDeclaration final : ASTBase<RequiresDeclaration> {
    AST_NODE_METHODS(RequiresDeclaration);
    NodeList<GenericType> genericTypes;
    NodeList<TypeBound> typeBounds;
};

// Error Handling
struct CatchDefinition final : ASTBase<CatchDefinition> {
    AST_NODE_METHODS(CatchDefinition);
    NodePtr<AnySeparatedID> identifier;
    NodePtr<QualifiedNamespaceID> alias;
    NodePtr<Suite> suite;
};

struct FinallyDefinition final : ASTBase<FinallyDefinition> {
    AST_NODE_METHODS(FinallyDefinition);
    NodePtr<Suite> suite;
};

struct PanicDefinition final : ASTBase<PanicDefinition> {
    AST_NODE_METHODS(PanicDefinition);
    NodePtr<Expression<void>> expression;
};

struct TryDefinition final : ASTBase<TryDefinition> {
    AST_NODE_METHODS(TryDefinition);
    NodePtr<Suite> suite;
    NodePtr<CatchDefinition> catchBlock;
    NodePtr<FinallyDefinition> finallyBlock;
};

struct TestDefinition final : ASTBase<TestDefinition> {
    AST_NODE_METHODS(TestDefinition);
    Token testName;
    NodePtr<Suite> suite;
};

// Access Specifiers
struct AccessModifiers final : ASTBase<AccessModifiers> {
    AST_NODE_METHODS(AccessModifiers);
    Token modifier;  // priv, pub, prot, intl
};

// Concurrency
struct AwaitCall final : ASTBase<AwaitCall> {
    AST_NODE_METHODS(AwaitCall);
    NodePtr<Expression<void>> expression;
};

struct SpawnCall final : ASTBase<SpawnCall> {
    AST_NODE_METHODS(SpawnCall);
    NodePtr<Expression<void>> expression;
};

struct ThreadCall final : ASTBase<ThreadCall> {
    AST_NODE_METHODS(ThreadCall);
    NodePtr<Expression<void>> expression;
};

// Other
struct DeleteCall final : ASTBase<DeleteCall> {
    AST_NODE_METHODS(DeleteCall);
    NodePtr<Expression<void>> expression;
};

// Type Definitions
struct GenericAccess final : ASTBase<GenericAccess> {
    AST_NODE_METHODS(GenericAccess);
    NodeList<NodePtr<>> identifiers;  // QualifiedNamespaceIDOrLiteral
};

// Operators
struct Operator final : ASTBase<Operator> {
    AST_NODE_METHODS(Operator);
    Token op;
};

struct Expressions final : ASTBase<Expressions> {
    AST_NODE_METHODS(Expressions);
    NodeList<Expression<void>> expressions;
};

struct Statements final : ASTBase<Statements> {
    AST_NODE_METHODS(Statements);
    NodeList<Statement<void>> statements;
};

// Code Structure
struct CodeBlock final : ASTBase<CodeBlock> {
    AST_NODE_METHODS(CodeBlock);
    NodeList<NodePtr<>> statementsOrExpressions;
};

struct CodeLine final : ASTBase<CodeLine> {
    AST_NODE_METHODS(CodeLine);
    NodePtr<> statementOrExpression;
};

// Base Elements
struct Number final : ASTBase<Number> {
    AST_NODE_METHODS(Number);
    Token value;
};

struct String final : ASTBase<String> {
    AST_NODE_METHODS(String);
    Token value;
};

struct Identifier final : ASTBase<Identifier> {
    AST_NODE_METHODS(Identifier);
    Token value;
};

struct Digit final : ASTBase<Digit> {
    AST_NODE_METHODS(Digit);
    Token value;
};

struct UntypedParameter final : ASTBase<UntypedParameter> {
    AST_NODE_METHODS(UntypedParameter);
    NodePtr<Identifier> identifier;
};

struct TypedParameter final : ASTBase<TypedParameter> {
    AST_NODE_METHODS(TypedParameter);
    NodePtr<Identifier> identifier;
    NodePtr<Type<void>> type;
};

struct AnySeparatedID final : ASTBase<AnySeparatedID> {
    AST_NODE_METHODS(AnySeparatedID);
    NodeList<NodePtr<>> identifiers;  // Can be a mix of DotSeparatedID or QualifiedNamespaceID
};

struct QualifiedNamespaceID final : ASTBase<QualifiedNamespaceID> {
    AST_NODE_METHODS(QualifiedNamespaceID);
    NodeList<Identifier> identifiers;
};

struct Suite final : ASTBase<Suite> {
    AST_NODE_METHODS(Suite);
    NodePtr<> content;  // Either CodeLine or CodeBlock
};

// Default Argument
struct DefaultArgument final : ASTBase<DefaultArgument> {
    AST_NODE_METHODS(DefaultArgument);
    NodePtr<TypedParameter> parameter;
    NodePtr<Expression<void>> expression;
};

// Helper Functions
struct UntypedParameterList final : ASTBase<UntypedParameterList> {
    AST_NODE_METHODS(UntypedParameterList);
    NodeList<UntypedParameter> parameters;
};

struct TypedParameterList final : ASTBase<TypedParameterList> {
    AST_NODE_METHODS(TypedParameterList);
    NodeList<TypedParameter> parameters;
};

struct DefaultArgumentList final : ASTBase<DefaultArgumentList> {
    AST_NODE_METHODS(DefaultArgumentList);
    NodeList<DefaultArgument> arguments;
};

struct GenericTypeList final : ASTBase<GenericTypeList> {
    AST_NODE_METHODS(GenericTypeList);
    NodeList<GenericType> types;
};

struct TypeBoundList final : ASTBase<TypeBoundList> {
    AST_NODE_METHODS(TypeBoundList);
    NodeList<TypeBound> bounds;
};

struct QualifiedNamespaceIDOrLiteralList final : ASTBase<QualifiedNamespaceIDOrLiteralList> {
    AST_NODE_METHODS(QualifiedNamespaceIDOrLiteralList);
    NodeList<NodePtr<>> identifiersOrLiterals;  // QualifiedNamespaceID or Literal
};

struct TypeList final : ASTBase<TypeList> {
    AST_NODE_METHODS(TypeList);
    NodeList<Type<void>> types;
};

struct ExpressionList final : ASTBase<ExpressionList> {
    AST_NODE_METHODS(ExpressionList);
    NodeList<Expression<void>> expressions;
};

Statement<void> parse_state(TokenListRef tokens);
Expression<void> parse_expr(TokenListRef tokens);
Declaration<void> parse_decl(TokenListRef tokens);

}  // namespace parser::ast::node

#endif  // __AST_NODES_HH__