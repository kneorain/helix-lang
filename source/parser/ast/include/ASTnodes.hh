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
//  this file exports all the AST nodes used by the parser                                        //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_NODES_HH__
#define __AST_NODES_HH__

#include "parser/ast/include/AST_interface.hh"
#include "parser/ast/include/nodes/AST_annotations.hh"
#include "parser/ast/include/nodes/AST_declarations.hh"
#include "parser/ast/include/nodes/AST_expressions.hh"
#include "parser/ast/include/nodes/AST_generics.hh"
#include "parser/ast/include/nodes/AST_statements.hh"

#define EXPR_VA_CLASS parser::ast::Expression
#define STMT_VA_CLASS parser::ast::Statement
#define DECL_VA_CLASS parser::ast::Declaration
#define ANNO_VA_CLASS parser::ast::Annotation
#define TYPE_VA_CLASS parser::ast::Type

#define MAKE_NODE_ENUM(T, D, B) T,
#define MAKE_NODE_CLASS(T, D, B)                                                       \
    class T : public D {                                                               \
      protected:                                                                       \
        token::TokenList *tokens;                                                      \
                                                                                       \
      public:                                                                          \
        explicit T(token::TokenList &tokens)                                           \
            : tokens(&tokens) {}                                                       \
        ~T()                    = default;                                             \
        T(const T &)            = delete;                                              \
        T &operator=(const T &) = delete;                                              \
        T(T &&)                 = default;                                             \
        T &operator=(T &&)      = delete;                                              \
                                                                                       \
        parser::ast::ParseResult parse() override;                                     \
        parser::ast::ParseResult test() override;                                      \
        void                     accept(parser::ast::Visitor &visitor) const override; \
                                                                                       \
        B                                                                              \
    };

#define GENERATE_NODES_ENUM_AND_CLASSES()                                                       \
                                                                                                \
    enum class nodes {                                                                          \
        EXPRESSION(MAKE_NODE_ENUM, EXPR_VA_CLASS) ANNOTATIONS(MAKE_NODE_ENUM, ANNO_VA_CLASS)    \
            DECLARATIONS(MAKE_NODE_ENUM, DECL_VA_CLASS) GENERICS(MAKE_NODE_ENUM, TYPE_VA_CLASS) \
                STATEMENTS(MAKE_NODE_ENUM, STMT_VA_CLASS)                                       \
    };                                                                                          \
                                                                                                \
    namespace node {                                                                            \
        EXPRESSION(MAKE_NODE_CLASS, EXPR_VA_CLASS)                                              \
        ANNOTATIONS(MAKE_NODE_CLASS, ANNO_VA_CLASS)                                             \
        DECLARATIONS(MAKE_NODE_CLASS, DECL_VA_CLASS)                                            \
        GENERICS(MAKE_NODE_CLASS, TYPE_VA_CLASS)                                                \
        STATEMENTS(MAKE_NODE_CLASS, STMT_VA_CLASS)                                              \
    }

namespace parser::ast {
    GENERATE_NODES_ENUM_AND_CLASSES();
}

#undef EXPR_VA_CLASS
#undef STMT_VA_CLASS
#undef DECL_VA_CLASS
#undef ANNO_VA_CLASS
#undef TYPE_VA_CLASS

#undef MAKE_NODE_ENUM
#undef MAKE_NODE_CLASS
#undef GENERATE_NODES_ENUM_AND_CLASSES

#undef GENERICS
#undef STATEMENTS
#undef EXPRESSION
#undef ANNOTATIONS
#undef DECLARATIONS

#endif  // __AST_NODES_HH__
