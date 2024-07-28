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

#ifndef __AST_EXPR_NODES_HH__
#define __AST_EXPR_NODES_HH__

#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/nodes.hh"

namespace parser::ast::node {
using namespace token;

// Functions and Methods
struct FunctionDecl final : Declaration<FunctionDecl> {
    AST_NODE_METHODS(FunctionDecl);
    NodePtr<QualifiedNamespaceID> name;
    NodeList<TypedParameter> parameters;
    NodeList<DefaultArgument> defaultArguments;
    NodePtr<Type<void>> returnType;
};

struct FunctionDefinition final : Declaration<FunctionDefinition> {
    AST_NODE_METHODS(FunctionDefinition);
    bool isUnsafe = false;
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<FunctionDecl> functionDecl;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct OperatorDefinition final : Declaration<OperatorDefinition> {
    AST_NODE_METHODS(OperatorDefinition);
    Token op;
    NodePtr<FunctionDecl> functionDecl;
    NodePtr<Suite> suite;
};

// Class and Struct
struct ClassDefinition final : Declaration<ClassDefinition> {
    AST_NODE_METHODS(ClassDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl> derives;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct EnumDefinition final : Declaration<EnumDefinition> {
    AST_NODE_METHODS(EnumDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<EnumBody> body;
};

struct StructDefinition final : Declaration<StructDefinition> {
    AST_NODE_METHODS(StructDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct UnionDefinition final : Declaration<UnionDefinition> {
    AST_NODE_METHODS(UnionDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<UnionBody> body;
};

struct TypeDefinition final : Declaration<TypeDefinition> {
    AST_NODE_METHODS(TypeDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Type<void>> type;
};

// Inheritance and Polymorphism
struct AbstractDefinition final : Declaration<AbstractDefinition> {
    AST_NODE_METHODS(AbstractDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl> derives;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct InterfaceDefinition final : Declaration<InterfaceDefinition> {
    AST_NODE_METHODS(InterfaceDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl> derives;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

// Variable Declarations
struct VariableDeclaration final : Declaration<VariableDeclaration> {
    AST_NODE_METHODS(VariableDeclaration);
    NodePtr<AccessModifiers> accessModifiers;
    bool isUnsafe = false;
    Token qualifier;      // const, atomic, shared, eval
    NodePtr<> parameter;  // TypedParameter or UntypedParameter
    NodePtr<Expression<void>> initializer;
};

}  // namespace parser::ast::node

#endif  // __AST_EXPR_NODES_HH__