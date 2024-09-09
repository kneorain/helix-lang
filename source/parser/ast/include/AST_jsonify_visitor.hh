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
//  This file defines the JsonifyVisitor class, which is used to convert the AST to JSON.         //
//  The JSON representation of the AST is used for debugging and testing purposes.                //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_JSONIFY_VISITOR_H__
#define __AST_JSONIFY_VISITOR_H__

#include "neo-json/include/json.hh"
#include "parser/ast/include/AST_visitor.hh"

namespace parser::ast::visitors {
    class JsonifyVisitor : public Visitor {
    public:
        JsonifyVisitor() = default;
        virtual ~JsonifyVisitor() = default;
        JsonifyVisitor(const JsonifyVisitor&) = default;
        JsonifyVisitor& operator=(const JsonifyVisitor&) = default;
        JsonifyVisitor(JsonifyVisitor&&) = default;
        JsonifyVisitor& operator=(JsonifyVisitor&&) = default;

        neo::json json {"ast"};

        GENERATE_VISITOR_FUNCTIONS;
    };
}

#endif // __AST_JSONIFY_VISITOR_H__