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

#include <vector>
#include "parser/ast/include/ast.hh"
#include "parser/ast/include/nodes/nodes.hh"
#include "token/include/token_list.hh"

namespace parser::ast::node {
using namespace token;
// Control Flow
class MatchExpression final : public Expression {
    AST_NODE_METHODS(MatchExpression);
    NodeList<std::pair<NodePtr<Expression>, NodePtr<>>>
        cases;  // (Expression | '_') -> (CodeBlock | (':' Expression))
};

// Functions and Methods
class ReturnExpression final : public Expression {
    AST_NODE_METHODS(ReturnExpression);
    NodePtr<Expression> expression;
};

class YieldExpression final : public Expression {
    AST_NODE_METHODS(YieldExpression);
    NodePtr<Expression> expression;
};

// Operators
class BinaryOperation final : public Expression {
    AST_NODE_METHODS(BinaryOperation);
    NodePtr<Expression> left;
    NodePtr<Operator> op;
    NodePtr<Expression> right;
};

class UnaryOperation final : public Expression {
    AST_NODE_METHODS(UnaryOperation);
    NodePtr<Operator> op;
    NodePtr<Expression> expression;
};

// Expressions
class FunctionCall final : public Expression {
    AST_NODE_METHODS(FunctionCall);
    NodePtr<AnySeparatedID> function;
    NodePtr<GenericAccess> genericAccess;
    NodeList<Expression> arguments;
};

class ParenthesizedExpression final : public Expression {
    AST_NODE_METHODS(ParenthesizedExpression);
    NodePtr<Expression> expression;
};

class ArrayAccess final : public Expression {
    AST_NODE_METHODS(ArrayAccess);
    NodePtr<AnySeparatedID> array;
    NodePtr<Expression> index;
};

class ObjectAccess final : public Expression {
    AST_NODE_METHODS(ObjectAccess);
    NodePtr<AnySeparatedID> object;
    NodePtr<Identifier> member;
};

class ConditionalExpression final : public Expression {
    AST_NODE_METHODS(ConditionalExpression);
    NodePtr<Expression> condition;
    NodePtr<Expression> trueExpression;
    NodePtr<Expression> falseExpression;
};

// Base Elements
class Literal final : public Expression {
    public:
    enum class LiteralType : u8 { INVALID, BOOL, CHAR, FLOAT, STRING, INTEGER, SCIENTIFIC, NONE };

    AST_NODE_METHODS(Literal);
    LiteralType type = LiteralType::INVALID;
    Token value;

    TO_JSON_SIGNATURE {
        jsonify::Jsonify node_json(node_repr(), depth);

        switch (type) {
            case LiteralType::INVALID:
                node_json.add("type", std::string("INVALID"));
                break;
            case LiteralType::BOOL:
                node_json.add("type", std::string("BOOL"));
                break;
            case LiteralType::CHAR:
                node_json.add("type", std::string("CHAR"));
                break;
            case LiteralType::FLOAT:
                node_json.add("type", std::string("FLOAT"));
                break;
            case LiteralType::STRING:
                node_json.add("type", std::string("STRING"));
                break;
            case LiteralType::INTEGER:
                node_json.add("type", std::string("INTEGER"));
                break;
            case LiteralType::SCIENTIFIC:
                node_json.add("type", std::string("SCIENTIFIC"));
                break;
            case LiteralType::NONE:
                node_json.add("type", std::string("NONE"));
                break;
        }

        node_json.add("value", value);

        TO_JSON_RETURN(node_json);
    }
};

class Identifier final : public Expression {
    AST_NODE_METHODS(Identifier);
    Token value;

    TO_JSON_SIGNATURE {
        jsonify::Jsonify node_json(node_repr(), depth);

        node_json.add("value", value);
        
        TO_JSON_RETURN(node_json);
    }
};

class AnySeparatedID final : public Expression {
    AST_NODE_METHODS(AnySeparatedID);
    NodeList<Expression> identifiers;  // Can be a mix of DotSeparatedID or QualifiedNamespaceID

    TO_JSON_SIGNATURE {
        jsonify::Jsonify node_json(node_repr(), depth);

        
        node_json.add("path", "none");
        
        TO_JSON_RETURN(node_json);
    }
};

class QualifiedNamespaceID final : public Expression { // PATH so id::id::id...
    AST_NODE_METHODS(QualifiedNamespaceID);
    NodeList<Identifier> identifiers; // id::id::id...

    TO_JSON_SIGNATURE {
        jsonify::Jsonify node_json(node_repr(), depth);

        std::vector<Identifier> temp_de_ref;

        for (auto &_ : identifiers) {
            temp_de_ref.push_back(*_);
        }
        
        node_json.add("path", temp_de_ref);
        
        TO_JSON_RETURN(node_json);
    }
};

class DotSeparatedID final : public Expression { // PATH so id::id::id...
    AST_NODE_METHODS(DotSeparatedID);
    NodeList<Identifier> identifiers; // id.id.id...

    TO_JSON_SIGNATURE {
        jsonify::Jsonify node_json(node_repr(), depth);

        std::vector<Identifier> temp_de_ref;

        for (auto &_ : identifiers) {
            temp_de_ref.push_back(*_);
        }
        
        node_json.add("path", temp_de_ref);
        
        TO_JSON_RETURN(node_json);
    }
};
}  // namespace parser::ast::node

#endif  // __AST_EXPR_NODES_HH__