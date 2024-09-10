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
#include <vector>

#include "parser/ast/include/AST_jsonify_visitor.hh"

namespace parser::ast::visitors {
neo::json get_node_json(const Node *node) {
    auto visitor = JsonifyVisitor();
    node->accept(visitor);
    return visitor.json;
}

void JsonifyVisitor::visit(const node::Literal &node) {
    json.section("literal")
        .add("value", node.value)
        .add("type", (int)node.getNodeType());
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
    json.section("binary_op")
        .add("type", (int)node.getNodeType())
        .add("left", get_node_json(node.left))
        .add("operator", node.op)
        .add("right", get_node_json(node.right));
}

void JsonifyVisitor::visit(const node ::UnaryOp &node) {
    json.section("unary_op")
        .add("operator", node.op)
        .add("right", get_node_json(node.right))
        .add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::Identifier &node) {
    json.section("identifier")
        .add("value", node.value)
        .add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::DotAccess &node) {
    std::vector<neo::json> paths;

    for (auto &child : node.paths) {
        paths.push_back(get_node_json(child));
    }

    json.section("dot_access")
        .add("paths", paths)
        .add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::ScopeAccess &node) {
    std::vector<neo::json> paths;

    for (auto &child : node.paths) {
        paths.push_back(get_node_json(child));
    }

    json.section("scope_access")
        .add("paths", paths)
        .add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::PathAccess &node) {
    std::vector<neo::json> paths;

    for (auto &child : node.paths) {
        paths.push_back(get_node_json(child));
    }

    json.section("path_access")
        .add("paths", paths)
        .add("type", (int)node.getNodeType());
}
/*GENERATE(FunctionCall, DERIVE,    \
    NodeT<PathAccess> callee;     \
    NodeV<Expression> args;       \
    NodeV<Assignment> defaults;   \
)      */
void JsonifyVisitor::visit(const node ::FunctionCall &node) {
    std::vector<neo::json> args;
    for (auto &arg : node.args) {
        args.push_back(get_node_json(arg));
    }

    json.section("function_call")
        .add("type", (int)node.getNodeType())
        .add("callee", get_node_json(node.callee))
        .add("args", args);

}

void JsonifyVisitor::visit(const node ::ArrayAccess &node) {
    json.section("array_access")
        .add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::Parenthesized &node) {
    json.section("parenthesized")
        .add("type", (int)node.getNodeType());
}

void JsonifyVisitor::visit(const node ::Conditional &node) {}

void JsonifyVisitor::visit(const node ::Cast &node) {
    json.section("cast")
        .add("type", (int)node.getNodeType())
        .add("cast_t", get_node_json(node.type))
        .add("expr", get_node_json(node.expr));
}

}  // namespace parser::ast::visitors
