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

#ifndef __AST_DECL_NODES_HH__
#define __AST_DECL_NODES_HH__

#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/nodes.hh"

namespace parser::ast::node {
using namespace token;

// Functions and Methods
class FunctionDecl final : public Declaration {
    AST_NODE_METHODS(FunctionDecl);
    NodePtr<QualifiedNamespaceID> name;
    NodeList<TypedParameter>      params;
    NodeList<DefaultArgument>     kw_params;
    NodePtr<Type>           return_ty;
    NodePtr<RequiresDeclaration>  generics;
    NodePtr<Suite>                body;
};

// untouched beyond this point.

class FunctionDefinition final : public Declaration {
    AST_NODE_METHODS(FunctionDefinition);
    bool                    isUnsafe = false;
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<FunctionDecl>   functionDecl;

    NodePtr<Suite> suite;
};

class OperatorDefinition final : public Declaration {
    AST_NODE_METHODS(OperatorDefinition);
    Token                 op;
    NodePtr<FunctionDecl> functionDecl;
    NodePtr<Suite>        suite;
};

// Class and class
class ClassDefinition final : public Declaration {
    AST_NODE_METHODS(ClassDefinition);
    NodePtr<BaseObjectDecl>       baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl>          derives;
    NodePtr<RequiresDeclaration>  _requires;
    NodePtr<Suite>                suite;
};

class EnumDefinition final : public Declaration {
    AST_NODE_METHODS(EnumDefinition);
    NodePtr<BaseObjectDecl>       baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<EnumBody>             body;
};

class classDefinition final : public Declaration {
    AST_NODE_METHODS(classDefinition);
    NodePtr<BaseObjectDecl>      baseObject;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite>               suite;
};

class UnionDefinition final : public Declaration {
    AST_NODE_METHODS(UnionDefinition);
    NodePtr<BaseObjectDecl>      baseObject;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<UnionBody>           body;
};

class TypeDefinition final : public Declaration {
    AST_NODE_METHODS(TypeDefinition);
    NodePtr<BaseObjectDecl>       baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<RequiresDeclaration>  _requires;
    NodePtr<Type>           type;
};

// Inheritance and Polymorphism
class AbstractDefinition final : public Declaration {
    AST_NODE_METHODS(AbstractDefinition);
    NodePtr<BaseObjectDecl>       baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl>          derives;
    NodePtr<RequiresDeclaration>  _requires;
    NodePtr<Suite>                suite;
};

class InterfaceDefinition final : public Declaration {
    AST_NODE_METHODS(InterfaceDefinition);
    NodePtr<BaseObjectDecl>       baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl>          derives;
    NodePtr<RequiresDeclaration>  _requires;
    NodePtr<Suite>                suite;
};

// Variable Declarations
class VariableDeclaration final : public Declaration {
    AST_NODE_METHODS(VariableDeclaration);
    NodePtr<AccessModifiers>  accessModifiers;
    bool                      isUnsafe = false;
    Token                     qualifier;  // const, atomic, shared, eval
    NodePtr<>                 parameter;  // TypedParameter or UntypedParameter
    NodePtr<Expression> initializer;
};

}  // namespace parser::ast::node

#endif  // __AST_DECL_NODES_HH__