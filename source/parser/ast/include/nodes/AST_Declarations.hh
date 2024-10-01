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
#include "parser/ast/include/types/AST_types.hh"

__AST_NODE_BEGIN {
    class RequiresParamDecl final : public Node {
        BASE_CORE_METHODS(RequiresParamDecl);
        
        // RequiresParamDecl := 'const'? (S.NamedVarSpecifier) ('=' E)?

        NodeT<NamedVarSpecifier> var;
        NodeT<> value;
        bool is_const;
    };

    class RequiresParamList final : public Node {
        BASE_CORE_METHODS(RequiresParamList);
        
        // RequiresParamList := (RequiresParamDecl (',' RequiresParamDecl)*)?

        NodeV<RequiresParamDecl> params;
    };

    class EnumMemberDecl final : public Node {
        BASE_CORE_METHODS(EnumMemberDecl);
        
        // EnumMemberDecl := E.IdentExpr ('=' E)?

        NodeT<IdentExpr> name;
        NodeT<> value;
    };
    
    class UDTDeriveDecl final : public Node {
        BASE_CORE_METHODS(UDTDeriveDecl);
        
        // UDTDeriveDecl := 'derives' (VisDecl? E.Type (',' VisDecl? E.Type)*)?

        std::vector<std::pair<NodeT<Type>, AccessSpecifier>> derives;
    };

    class TypeBoundList final : public Node {
        BASE_CORE_METHODS(TypeBoundList);
        
        // TypeBoundList := (TypeBoundDecl (',' TypeBoundDecl)*)?

        NodeV<TypeBoundDecl> bounds;
    };

    class TypeBoundDecl final : public Node {
        BASE_CORE_METHODS(TypeBoundDecl);
        
        // TypeBoundDecl := 'if' InstOfExpr

        NodeT<InstOfExpr> bound;
    };

    class RequiresDecl final : public Node {
        BASE_CORE_METHODS(RequiresDecl);
        
        // RequiresDecl := 'requires' '<' RequiresParamList '>' TypeBoundList?

        NodeT<RequiresParamList> params;
        NodeT<TypeBoundList>     bounds;
    };

    class StructDecl final : public Node {
        BASE_CORE_METHODS(StructDecl);
        
        // StructDecl := 'const'? VisDecl? 'struct'    E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite

        NodeT<IdentExpr>     name;
        NodeT<UDTDeriveDecl> derives;
        NodeT<RequiresDecl>  generics;
        NodeT<SuiteState>    body;

        AccessSpecifier vis;
        bool            is_const;
    };

    class ConstDecl final : public Node {
        BASE_CORE_METHODS(ConstDecl);
        
        // ConstDecl :=  VisDecl? 'const' SharedModifiers VarDecl* ';'

        AccessSpecifier vis;
        NodeV<VarDecl> vars;
        std::vector<FunctionSpecifier> modifiers;
    };

    class ClassDecl final : public Node {
        BASE_CORE_METHODS(ClassDecl);
        
        // ClassDecl := 'const'? VisDecl? 'class'     E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite


    };

    class InterDecl final : public Node {
        BASE_CORE_METHODS(InterDecl);
        
        // InterDecl := 'const'? VisDecl? 'interface' E.IdentExpr UDTDeriveDecl? RequiresDecl? S.Suite


    };

    class EnumDecl final : public Node {
        BASE_CORE_METHODS(EnumDecl);
        
        // EnumDecl :=  VisDecl? 'enum' ('derives' E.Type)? E.ObjInitExpr


    };

    class TypeDecl final : public Node {
        BASE_CORE_METHODS(TypeDecl);
        
        // TypeDecl :=  VisDecl? 'type'  E.IdentExpr RequiresDecl? '=' E ';'


    };

    class FuncDecl final : public Node {
        BASE_CORE_METHODS(FuncDecl);
        
        // FuncDecl :=  SharedModifiers? 'fn' E.PathExpr '(' VarDecl[true]* ')' RequiresDecl? S.Suite


    };

    class VarDecl final : public Node {
        BASE_CORE_METHODS(VarDecl);
        
        // VarDecl := S.NamedVarSpecifier ('=' E)? ~ also pass in a bool to force type need


    };

    class FFIDecl final : public Node {
        BASE_CORE_METHODS(FFIDecl);
        
        // FFIDecl :=  VisDecl? 'ffi' L.StringLiteral D


    };

    class LetDecl final : public Node {
        BASE_CORE_METHODS(LetDecl);
        
        // LetDecl :=  VisDecl? 'let'   SharedModifiers VarDecl* ';'


    };

    class OpDecl final : public Node {
        BASE_CORE_METHODS(OpDecl);
        
        // OpDecl :=  SharedModifiers? 'op' T FuncDecl[no_SharedModifiers=true]


    };

}  // namespace __AST_NODE_BEGIN

#endif  // __AST_DECLARATIONS_H__