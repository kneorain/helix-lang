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

#ifndef __AST_BASE_H__
#define __AST_BASE_H__

#include <string>
#include <neo-pprint/include/hxpprint.hh>

#include "neo-pprint/include/ansi_colors.hh"
#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/private/base/AST_base_declaration.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "parser/ast/include/types/AST_visitor.hh"

__AST_NODE_BEGIN {
    class Node {  // base node
      public:
        Node()                                                                          = default;
        virtual ~Node()                                                                 = default;
        virtual void                      accept(__AST_VISITOR::Visitor &visitor) const = 0;
        [[nodiscard]] virtual nodes       getNodeType() const                           = 0;
        [[nodiscard]] virtual std::string getNodeName() const                           = 0;

        Node(const Node &)            = default;
        Node &operator=(const Node &) = default;
        Node(Node &&)                 = default;
        Node &operator=(Node &&)      = default;
    };

    class Program : public Node {
      public:
        Program()                           = delete;
        ~Program() override                 = default;
        Program(const Program &)            = default;  // no move or copy semantics
        Program &operator=(const Program &) = delete;
        Program(Program &&)                 = delete;
        Program &operator=(Program &&)      = delete;

        Program(__TOKEN_N::TokenList &source_tokens)
            : source_tokens(source_tokens) {}

        void accept(parser ::ast ::visitor ::Visitor &visitor) const override {
            visitor.visit(*this);
        }

        [[nodiscard]] nodes        getNodeType() const override { return nodes::Program; }
        [[nodiscard]] std ::string getNodeName() const override { return "Program"; };

        Program &parse() {
            auto iter = source_tokens.begin();

            ParseResult<> expr;

            while (iter.remaining_n() != 0) {
                auto decl = node::Declaration(iter);
                expr      = decl.parse();

                if (!expr.has_value()) {
                    expr.error().panic();
                    #ifdef DEBUG
                    print(std::string(colors::fg16::red),
                          "error: ",
                          std::string(colors::reset),
                          expr.error().what());
                    #endif
                    return *this;
                }

                children.emplace_back(expr.value());
            }

            return *this;
        }

        NodeV<> children;
        NodeV<> annotations;

      private:
        __TOKEN_N::TokenList &source_tokens;
    };
}  //  namespace __AST_NODE_BEGIN

#endif  // __AST_BASE_H__