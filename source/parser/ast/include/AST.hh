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
//  this file exports all the AST related files                                                   //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//
//  fyi: i aim to make the AST have the PERFECT readable and maintainable code i can ever write.  //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_HH__
#define __AST_HH__

#include "parser/ast/include/AST_core.def"
#include "parser/ast/include/AST_classifier.hh"
#include "parser/ast/include/AST_context.hh"
#include "parser/ast/include/AST_interface.hh"
#include "parser/ast/include/AST_matcher.hh"
#include "parser/ast/include/AST_types.hh"
#include "parser/ast/include/AST_visitor.hh"
#include "parser/ast/include/nodes/AST_generate.hh"

// TODO: Make this work again

// #undef EXPR_VA_CLASS
// #undef STMT_VA_CLASS
// #undef DECL_VA_CLASS
// #undef ANNO_VA_CLASS
// #undef TYPE_VA_CLASS

// #undef MAKE_NODE_ENUM
// #undef MAKE_NODE_CLASS
// #undef MAKE_FORWARD_DECL
// #undef MAKE_VISITOR_FUNCTION

// #undef GENERATE_NODES_ENUM
// #undef GENERATE_NODES_FORWARD_DECLS
// #undef GENERATE_NODES_CLASSES

// #undef GENERICS
// #undef STATEMENTS
// #undef EXPRESSION
// #undef ANNOTATIONS
// #undef DECLARATIONS

#endif  // __AST_HH__
