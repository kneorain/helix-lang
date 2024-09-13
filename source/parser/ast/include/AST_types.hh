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
//  This file contains the AST types used by the parser and lexer.                                //
//                                                                                                //
//  The AST types are defined as follows:                                                         //
//      - ParseResult is a pair of an integer and a T                                             //
//      - NodeT is a raw pointer to a T (where T is a AST node)                                //
//      - NodeV is a vector of NodeT                                                              //
//      - NodeVP is a unique pointer to a NodeV                                                   //
//      - NodeR is a reference to a T                                                             //
//      - NodeCR is a const reference to a T                                                      //
//      - NodeVR is a reference to a NodeV                                                        //
//      - NodeVCR is a const reference to a NodeV                                                 //
//      - NodeVPR is a reference to a NodeVP                                                      //
//      - make_node is a helper function to create a new node with perfect forwarding             //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_TYPES_H__
#define __AST_TYPES_H__

#include <memory>
#include <vector>

#include "neo-types/include/hxint.hh"
#include "parser/ast/include/AST_core.def"

__AST_BEGIN {
/// ParseResult is just an integer of the tokens consumed
using ParseResult = i32;

class Node;

/// NodeT is a unique pointer to a T (where T is a AST node)
template <typename T = Node>
using NodeT = T*;

/// NodeV is a vector of NodeT
template <typename T = Node>
using NodeV = std::vector<NodeT<T>>;

/// NodeVP is a unique pointer to a NodeV
template <typename T>
using NodeVP = std::unique_ptr<NodeV<T>>;

/// NodeR is a reference to a T
template <typename T>
using NodeR = T &;

/// NodeCR is a const reference to a T
template <typename T>
using NodeCR = const T &;

/// NodeVR is a reference to a NodeV
template <typename T>
using NodeVR = NodeV<T> &;

/// NodeVCR is a const reference to a NodeV
template <typename T>
using NodeVCR = const NodeV<T> &;

/// NodeVPR is a reference to a NodeVP
template <typename T>
using NodeVPR = NodeVP<T> &;

/// make_node is a helper function to create a new node with perfect forwarding
/// @tparam T is the type of the node
/// @param args are the arguments to pass to the constructor of T
/// @return a unique pointer to the new node
template <typename T, typename... Args>
inline constexpr NodeT<T> make_node(Args &&...args) {
    // return a heap-alloc unique pointer to the new node with
    // perfect forwarding of the arguments allowing the caller
    // to identify any errors in the arguments at compile time
    return NodeT<T>(std::forward<Args>(args)...);
}
}  // namespace __AST_BEGIN

#endif  // __AST_TYPES_H__