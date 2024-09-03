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
//  This file defines the interface to the AST classes.                                           //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_INTERFACE_H__
#define __AST_INTERFACE_H__

#include "parser/ast/include/AST_types.hh"
#include "token/include/token_list.hh"

#define DEFINE_SUB_NODE(name)                                                    \
    class name : public Node {                                                   \
      public:                                                                    \
        name();                                                                  \
        explicit name(token::TokenList &tokens);                                 \
                                                                                 \
        name(const name &)            = default;                                 \
        name &operator=(const name &) = default;                                 \
        name(name &&)                 = default;                                 \
        name &operator=(name &&)      = default;                                 \
        ~name() override              = default;                                 \
                                                                                 \
        virtual ParseResult         parse() override                        = 0; \
        virtual bool                test() override                         = 0; \
        virtual void                accept(Visitor &visitor) const override = 0; \
        [[nodiscard]] virtual nodes getNodeType() const override            = 0; \
                                                                                 \
      protected:                                                                 \
        token::TokenList *tokens = nullptr;                                      \
    };                                                                           \
                                                                                 \
    NodeT<name> get_##name(token::TokenList &tokens);

namespace parser::ast {
class Visitor;
enum class nodes;

class Node {
  public:
    Node() = default;
    explicit Node(token::TokenList &tokens) {}
    virtual ~Node()                                            = default;
    virtual ParseResult         parse()                        = 0;
    virtual bool                test()                         = 0;
    virtual void                accept(Visitor &visitor) const = 0;
    [[nodiscard]] virtual nodes getNodeType() const            = 0;

    Node(const Node &)            = default;
    Node &operator=(const Node &) = default;
    Node(Node &&)                 = default;
    Node &operator=(Node &&)      = default;
};

DEFINE_SUB_NODE(Type);
DEFINE_SUB_NODE(Expression);
DEFINE_SUB_NODE(Statement);
DEFINE_SUB_NODE(Annotation);
DEFINE_SUB_NODE(Declaration);
}  // namespace parser::ast

#undef DEFINE_SUB_NODE

#endif  // __AST_INTERFACE_H__