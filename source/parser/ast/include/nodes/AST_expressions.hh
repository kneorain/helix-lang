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

#define EXPRESSION(GENERATE, DERIVE)  \
    GENERATE(BinaryExpr, DERIVE,      \
        Token op;                     \
        NodeT<Expression> *left;      \
        NodeT<Expression> *right;     \
    )                                 \
                                      \
    GENERATE(UnaryExpr, DERIVE,       \
        Token op;                     \
        NodeT<Expression> *right;     \
    )

#endif // __AST_EXPRESSIONS_H__