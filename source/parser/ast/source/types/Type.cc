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

#include "parser/ast/include/AST.hh"

#include "parser/ast/include/case_types.def"
#include "token/include/token_list.hh"

namespace parser::ast {

NodeT<Type> get_Type(token::TokenList &tokens) {
    for (auto &token : tokens) {}

    return nullptr;
}

Type::Type() = default;
Type::Type(token::TokenList &tokens)
    : Node(tokens)
    , tokens(&tokens) {}
}  // namespace parser::ast
