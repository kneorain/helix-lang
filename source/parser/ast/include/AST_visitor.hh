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

#include "parser/ast/include/nodes/AST_generate.hh"
#include "parser/ast/include/AST_core.def"

__AST_BEGIN {

class Visitor {
  public:
    GENERATE_BASE_VISITOR_FUNCTIONS;
};

}  // namespace __AST_BEGIN

#endif  // __AST_VISITOR_H__