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
//  Generates the AST nodes for the Helix Parser.                                                 //
//  This file is used to generate the AST nodes for the Helix Parser.                             //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_GENERATE_H__
#define __AST_GENERATE_H__

#include "parser/ast/include/AST_nodes.def"
#include "parser/ast/include/AST_core.def"

__AST_BEGIN {
GENERATE_NODES_ENUM;

namespace node {
    GENERATE_NODES_FORWARD_DECLS;
    GENERATE_NODES_CLASSES;  // NOLINT(cppcoreguidelines-pro-type-member-init)
}  // namespace node
}  // namespace __AST_BEGIN

#endif  // __AST_GENERATE_H__