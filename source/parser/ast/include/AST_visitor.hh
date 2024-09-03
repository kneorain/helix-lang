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
//  This header defines the Visitor pattern for the Abstract Syntax Tree (AST) in Helix.          //
//                                                                                                //
//  The Visitor pattern is a way to separate the operations (like traversing or modifying nodes)  //
//  from the AST node classes themselves. It allows you to add new operations without having to   //
//  modify the AST node classes—keeping the code cleaner and more maintainable.                   //
//                                                                                                //
//  Here's a quick example of how you might use it:                                               //
//                                                                                                //
//  ```cpp                                                                                        //
//  class MyVisitor : public parser::ast::Visitor {                                               //
//    public:                                                                                     //
//      void Visit(const node::BinaryOp &node) override {                                         //
//          // Handle node::BinaryOp                                                              //
//      }                                                                                         //
//                                                                                                //
//      void Visit(const node::IfStatement &node) override {                                      //
//          // Handle node::IfStatement                                                           //
//      }                                                                                         //
//                                                                                                //
//      // Add more Visit functions as needed                                                     //
//  };                                                                                            //
//                                                                                                //
//  // Now, you can traverse the AST with your visitor:                                           //
//  MyVisitor Visitor;                                                                            //
//  ASTRootNode->Accept(Visitor);                                                                 //
//  ```                                                                                           //
//                                                                                                //
//  In this example, `MyVisitor` implements the `Visitor` interface. Each `Visit` method is       //
//  specialized for a different type of AST node, making it easy to handle each node type         //
//  separately.                                                                                   //
//                                                                                                //
//  The `GENERATE_VISITOR_FUNCTIONS` macro helps reduce boilerplate by automatically declaring    //
//  the visitor functions for all the AST node types. This way, you can focus on what each        //
//  visitor needs to do without worrying about the repetitive setup.                              //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//

#ifndef __AST_VISITOR_H__
#define __AST_VISITOR_H__

#include "parser/ast/include/nodes/AST_generate.hh"  // NOLINT(unused-includes)

namespace parser::ast {

class Visitor {
  public:
    // GENERATE_VISITOR_FUNCTIONS;
    virtual void visit(const node ::Comment &)              = 0;
    virtual void visit(const node ::CompilerDirective &)    = 0;
    virtual void visit(const node ::Suite &)                = 0;
    virtual void visit(const node ::VariableDecl &)         = 0;
    virtual void visit(const node ::Assignment &)           = 0;
    virtual void visit(const node ::ForLoop &)              = 0;
    virtual void visit(const node ::RangeLoop &)            = 0;
    virtual void visit(const node ::WhileLoop &)            = 0;
    virtual void visit(const node ::IfStatement &)          = 0;
    virtual void visit(const node ::ElseIfStatement &)      = 0;
    virtual void visit(const node ::ElseStatement &)        = 0;
    virtual void visit(const node ::ConditionalStatement &) = 0;
    virtual void visit(const node ::ReturnStatement &)      = 0;
    virtual void visit(const node ::ContinueStatement &)    = 0;
    virtual void visit(const node ::BreakStatement &)       = 0;
    virtual void visit(const node ::YieldStatement &)       = 0;
    virtual void visit(const node ::BinaryOp &)             = 0;
    virtual void visit(const node ::UnaryOp &)              = 0;
    virtual void visit(const node ::Literal &)              = 0;
    virtual void visit(const node ::Identifier &)           = 0;
    virtual void visit(const node ::DotAccess &)            = 0;
    virtual void visit(const node ::ScopeAccess &)          = 0;
    virtual void visit(const node ::PathAccess &)           = 0;
    virtual void visit(const node ::FunctionCall &)         = 0;
    virtual void visit(const node ::ArrayAccess &)          = 0;
    virtual void visit(const node ::Parenthesized &)        = 0;
    virtual void visit(const node ::Conditional &)          = 0;
    virtual void visit(const node ::Cast &)                 = 0;
    ;
};

}  // namespace parser::ast

#endif  // __AST_VISITOR_H__