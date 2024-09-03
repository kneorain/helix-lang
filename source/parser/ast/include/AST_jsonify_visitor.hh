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
//                                                                                                //
//  This file defines the JsonifyVisitor class, which is used to convert the AST to JSON.         //
//  The JSON representation of the AST is used for debugging and testing purposes.                //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_JSONIFY_VISITOR_H__
#define __AST_JSONIFY_VISITOR_H__

#include "core/utils/josnify.hh"
#include "parser/ast/include/AST_visitor.hh"

namespace parser::ast::visitors {
    class JsonifyVisitor : public Visitor {
    public:
        JsonifyVisitor() = default;
        virtual ~JsonifyVisitor() = default;
        JsonifyVisitor(const JsonifyVisitor&) = default;
        JsonifyVisitor& operator=(const JsonifyVisitor&) = default;
        JsonifyVisitor(JsonifyVisitor&&) = default;
        JsonifyVisitor& operator=(JsonifyVisitor&&) = default;

        jsonify::Jsonify json = {"ast", 0};

        void visit(const node ::Comment &)              override;
        void visit(const node ::CompilerDirective &)    override;
        void visit(const node ::Suite &)                override;
        void visit(const node ::VariableDecl &)         override;
        void visit(const node ::Assignment &)           override;
        void visit(const node ::ForLoop &)              override;
        void visit(const node ::RangeLoop &)            override;
        void visit(const node ::WhileLoop &)            override;
        void visit(const node ::IfStatement &)          override;
        void visit(const node ::ElseIfStatement &)      override;
        void visit(const node ::ElseStatement &)        override;
        void visit(const node ::ConditionalStatement &) override;
        void visit(const node ::ReturnStatement &)      override;
        void visit(const node ::ContinueStatement &)    override;
        void visit(const node ::BreakStatement &)       override;
        void visit(const node ::YieldStatement &)       override;
        void visit(const node ::BinaryOp &)             override;
        void visit(const node ::UnaryOp &)              override;
        void visit(const node ::Literal &)              override;
        void visit(const node ::Identifier &)           override;
        void visit(const node ::DotAccess &)            override;
        void visit(const node ::ScopeAccess &)          override;
        void visit(const node ::PathAccess &)           override;
        void visit(const node ::FunctionCall &)         override;
        void visit(const node ::ArrayAccess &)          override;
        void visit(const node ::Parenthesized &)        override;
        void visit(const node ::Conditional &)          override;
        void visit(const node ::Cast &)                 override;
    };
}

#endif // __AST_JSONIFY_VISITOR_H__