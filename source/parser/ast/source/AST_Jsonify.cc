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

#include <string>

#include "parser/ast/include/AST_jsonify_visitor.hh"

namespace parser::ast::visitors {
void JsonifyVisitor::visit(const node::Literal &node) {
    json.create_sub("literal").add("value", node.value).add("type", (int)node.getNodeType());
};

void JsonifyVisitor::visit(const node ::Comment &node) {}

void JsonifyVisitor::visit(const node ::CompilerDirective &node) {}

void JsonifyVisitor::visit(const node ::Suite &node) {}

void JsonifyVisitor::visit(const node ::VariableDecl &node) {}

void JsonifyVisitor::visit(const node ::Assignment &node) {}

void JsonifyVisitor::visit(const node ::ForLoop &node) {}

void JsonifyVisitor::visit(const node ::RangeLoop &node) {}

void JsonifyVisitor::visit(const node ::WhileLoop &node) {}

void JsonifyVisitor::visit(const node ::IfStatement &node) {}

void JsonifyVisitor::visit(const node ::ElseIfStatement &node) {}

void JsonifyVisitor::visit(const node ::ElseStatement &node) {}

void JsonifyVisitor::visit(const node ::ConditionalStatement &node) {}

void JsonifyVisitor::visit(const node ::ReturnStatement &node) {}

void JsonifyVisitor::visit(const node ::ContinueStatement &node) {}

void JsonifyVisitor::visit(const node ::BreakStatement &node) {}

void JsonifyVisitor::visit(const node ::YieldStatement &node) {}

void JsonifyVisitor::visit(const node ::BinaryOp &node) {
    auto sub = json.create_sub("binary_op");
    node.left->accept(*this);
    node.right->accept(*this);

    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::UnaryOp &node) {
    auto sub = json.create_sub("unary_op")
                     .add("operator", node.op)
                     .add("type", (int)node.getNodeType());
    node.right->accept(*this);
}

void JsonifyVisitor::visit(const node ::Identifier &node) {
    json.create_sub("identifier").add("value", node.value).add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::DotAccess &node) {
    auto sub = json.create_sub("dot_access");
    for (auto &child : node.paths) {
        child->accept(*this);
    }

    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::ScopeAccess &node) {
    auto sub = json.create_sub("scope_access");
    for (auto &child : node.paths) {
        child->accept(*this);
    }

    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::PathAccess &node) {
    auto sub = json.create_sub("path_access");
    for (auto &child : node.paths) {
        child->accept(*this);
    }

    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::FunctionCall &node) {
    auto sub = json.create_sub("function_call");
    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::ArrayAccess &node) {
    auto sub = json.create_sub("array_access");
    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::Parenthesized &node) {
    auto sub = json.create_sub("parenthesized");
    sub.add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::Conditional &node) {}

void JsonifyVisitor::visit(const node ::Cast &node) {
    auto sub = json.create_sub("cast");
    node.type->accept(*this);
    node.expr->accept(*this);

    sub.add("type", (int)node.getNodeType());
}

}  // namespace parser::ast::visitors
