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

#include "parser/ast/include/AST.hh"

namespace parser::ast::node {
ParseResult CompilerDirective::parse() {
    if (tokens->empty()) [[unlikely]] {
        return 0;
    }

    return 0;
}

bool CompilerDirective::test() {
    if (tokens->empty()) [[unlikely]] {
        return false;
    }
    return false;
}

void CompilerDirective::accept(Visitor &visitor) const { visitor.visit(*this); }

}  // namespace __AST_BEGIN::node
