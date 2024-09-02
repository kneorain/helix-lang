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
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_EXPRESSIONS_H__
#define __AST_EXPRESSIONS_H__

#include "parser/ast/include/AST_types.hh"

// Expression ::= Literal | AnySeparatedID | BinaryOperation | UnaryOperation | FunctionCall | ParenthesizedExpression | ArrayAccess | ObjectAccess | ConditionalExpression

#define EXPRESSION(GENERATE, DERIVE)  \
    GENERATE(BinaryOp, DERIVE,        \
        NodeT<Expression> left;       \
        token::Token op;              \
        NodeT<Expression> right;      \
    )                                 \
                                      \
    GENERATE(UnaryOp, DERIVE,         \
        token::Token op;              \
        NodeT<Expression> right;      \
    )                                 \
                                      \
    GENERATE(Literal, DERIVE,         \
        token::Token value;           \
    )                                 \
                                      \
    GENERATE(Identifier, DERIVE,      \
        token::Token name;            \
    )                                 \
                                      \
    GENERATE(DotAccess, DERIVE,       \
        NodeV<Expression> paths;      \
    )                                 \
                                      \
    GENERATE(ScopeAccess, DERIVE,     \
        NodeV<Expression> paths;      \
    )                                 \
                                      \
    GENERATE(Assignment, DERIVE,      \
        NodeT<Identifier> name;       \
        NodeT<Expression> value;      \
    )                                 \
                                      \
    GENERATE(FunctionCall, DERIVE,    \
        NodeT<Expression> callee;     \
        NodeV<Expression> args;       \
        NodeV<Assignment> defaults;   \
    )                                 \
                                      \
    GENERATE(ArrayAccess, DERIVE,     \
        NodeT<Expression> array;      \
        NodeT<Expression> index;      \
    )                                 \
                                      \
    GENERATE(Parenthesized, DERIVE,   \
        NodeT<Expression> expr;       \
    )                                 \
                                      \
    GENERATE(Conditional, DERIVE,     \
        NodeT<Expression> condition;  \
        NodeT<Expression> if_true;    \
        NodeT<Expression> if_false;   \
    )

#endif // __AST_EXPRESSIONS_H__