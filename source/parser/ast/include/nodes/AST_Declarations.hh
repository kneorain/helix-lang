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

#ifndef __AST_DECLARATIONS_H__
#define __AST_DECLARATIONS_H__

#include <utility>
#include <vector>

#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/config/AST_modifiers.hh"
#include "parser/ast/include/core/AST_nodes.hh"
#include "parser/ast/include/nodes/AST_Expressions.hh"
#include "parser/ast/include/types/AST_types.hh"

__AST_NODE_BEGIN {
    class RequiresParamDecl final : public Node {
        BASE_CORE_METHODS(RequiresParamDecl);
        
        // RequiresParamDecl := 'const'? (S.NamedVarSpecifier) ('=' E)?
        explicit RequiresParamDecl(bool /* unused */) {}

        NodeT<NamedVarSpecifier> var;
        NodeT<> value;
        bool is_const = false;
    };

    class RequiresParamList final : public Node {
        BASE_CORE_METHODS(RequiresParamList);
        
        // RequiresParamList := (RequiresParamDecl (',' RequiresParamDecl)*)?
        explicit RequiresParamList(NodeT<RequiresParamDecl> first) { (this->params).emplace_back(std::move(first)); }
    
        NodeV<RequiresParamDecl> params;
    };

    class EnumMemberDecl final : public Node {
        BASE_CORE_METHODS(EnumMemberDecl);
        
        // EnumMemberDecl := E.IdentExpr ('=' E)?
        explicit EnumMemberDecl(NodeT<IdentExpr> name) : name(std::move(name)) {}

        NodeT<IdentExpr> name;
        NodeT<> value;
    };
    
    class UDTDeriveDecl final : public Node {
        BASE_CORE_METHODS(UDTDeriveDecl);
        
        // UDTDeriveDecl := 'derives' (VisDecl? E.Type (',' VisDecl? E.Type)*)?
        explicit UDTDeriveDecl(std::pair<NodeT<Type>, AccessSpecifier> first) { (this->derives).emplace_back(std::move(first)); }
        
        std::vector<std::pair<NodeT<Type>, AccessSpecifier>> derives;
    };

    class TypeBoundList final : public Node {
        BASE_CORE_METHODS(TypeBoundList);
        
        // TypeBoundList := (TypeBoundDecl (',' TypeBoundDecl)*)?
        explicit TypeBoundList(NodeT<InstOfExpr> bound) { (this->bounds).emplace_back(std::move(bound)); }

        NodeV<InstOfExpr> bounds;
    };

    class TypeBoundDecl final : public Node {
        BASE_CORE_METHODS(TypeBoundDecl);
        
        // TypeBoundDecl := InstOfExpr


        NodeT<InstOfExpr> bound;
    };

    class RequiresDecl final : public Node {
        BASE_CORE_METHODS(RequiresDecl);
        
        // RequiresDecl := 'requires' '<' RequiresParamList '>' ('if' TypeBoundList)?
        explicit RequiresDecl(NodeT<RequiresParamList> params) : params(std::move(params)) {}

        NodeT<RequiresParamList> params;
        NodeT<TypeBoundList>     bounds;
    };

    class StructDecl final : public Node {
        BASE_CORE_METHODS(StructDecl);
        
        // StructDecl := 'const'? VisDecl? 'struct' E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite
        explicit StructDecl(bool /* unused */) {}

        NodeT<IdentExpr>     name;
        NodeT<UDTDeriveDecl> derives;
        NodeT<RequiresDecl>  generics;
        NodeT<SuiteState>    body;

        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::AccessSpec, Modifiers::ExpectedModifier::ClassSpec);
    };

    class ConstDecl final : public Node {
        BASE_CORE_METHODS(ConstDecl);
        
        // ConstDecl :=  VisDecl? 'const' SharedModifiers VarDecl* ';'

        NodeV<VarDecl> vars;
        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::FuncSpec);
    };

    class ClassDecl final : public Node {
        BASE_CORE_METHODS(ClassDecl);
        
        // ClassDecl := 'const'? VisDecl? 'class'     E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::FuncSpec);
        NodeT<IdentExpr>     name;
        NodeT<UDTDeriveDecl> derives;
        NodeT<RequiresDecl>  generics;
        NodeT<SuiteState>    body;
    };

    class InterDecl final : public Node {
        BASE_CORE_METHODS(InterDecl);
        
        // InterDecl := 'const'? VisDecl? 'interface' E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::FuncSpec);
        NodeT<IdentExpr>     name;
        NodeT<UDTDeriveDecl> derives;
        NodeT<RequiresDecl>  generics;
        NodeT<SuiteState>    body;
    };

    class EnumDecl final : public Node {
        BASE_CORE_METHODS(EnumDecl);
        
        // EnumDecl :=  VisDecl? 'enum' ('derives' E.Type)? E.ObjInitExpr

        AccessSpecifier    vis;
        NodeT<IdentExpr>   name;
        NodeT<Type>        derives;
        NodeT<ObjInitExpr> body;
    };

    class TypeDecl final : public Node {
        BASE_CORE_METHODS(TypeDecl);
        
        // TypeDecl :=  VisDecl? 'type'  E.IdentExpr RequiresDecl? '=' E ';'

        AccessSpecifier     vis;
        NodeT<IdentExpr>    name;
        NodeT<RequiresDecl> generics;
        NodeT<>             value;
    };

    class FuncDecl final : public Node {
        BASE_CORE_METHODS(FuncDecl);
        
        // FuncDecl :=  SharedModifiers? 'fn' E.PathExpr '(' VarDecl[true]* ')' RequiresDecl? ('->' E.TypeExpr)? (S.Suite | ';' | '=' ('default' | 'delete'))

        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::FuncSpec);
        Modifiers qualifiers = Modifiers(Modifiers::ExpectedModifier::FuncQual);

        NodeT<PathExpr>     name;
        NodeV<VarDecl>      params;
        NodeT<RequiresDecl> generics;
        NodeT<Type>         returns;
        NodeT<SuiteState>   body;
    };

    class VarDecl final : public Node {
        BASE_CORE_METHODS(VarDecl);
        
        // VarDecl := S.NamedVarSpecifier ('=' E)? ~ also pass in a bool to force type need

        NodeT<NamedVarSpecifier> var;
        NodeT<> value;
    };

    class FFIDecl final : public Node {
        BASE_CORE_METHODS(FFIDecl);
        
        // FFIDecl :=  VisDecl? 'ffi' L.StringLiteral D

        AccessSpecifier    vis;
        NodeT<LiteralExpr> name;
        NodeT<>            value;
    };

    class LetDecl final : public Node {
        BASE_CORE_METHODS(LetDecl);
        
        // LetDecl :=  VisDecl? 'let'   SharedModifiers VarDecl* ';'

        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::FuncSpec);
        NodeV<VarDecl> vars;
    };

    class OpDecl final : public Node {
        BASE_CORE_METHODS(OpDecl);
        
        // OpDecl :=  SharedModifiers? 'op' T FuncDecl[no_SharedModifiers=true]

        Modifiers modifiers = Modifiers(Modifiers::ExpectedModifier::FuncSpec);
        token::Token    op;
        NodeT<FuncDecl> func;
    };

}  // namespace __AST_NODE_BEGIN

#endif  // __AST_DECLARATIONS_H__