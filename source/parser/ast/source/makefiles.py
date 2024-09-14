exprs = [
    "BinaryOp",
    "UnaryOp",
    "Identifier",
    "DotAccess",
    "ScopeAccess",
    "PathAccess",
    "FunctionCall",
    "ArrayAccess",
    "Parenthesized",
    "Conditional",
    "Cast"
]

states = [
    "Assignment",
    "ForLoop",
    "RangeLoop",
    "WhileLoop",
    "IfStatement",
    "ElseIfStatement",
    "ElseStatement",
    "ConditionalStatement",
    "ReturnStatement",
    "ContinueStatement",
    "BreakStatement",
    "YieldStatement"
]

annos = [
    "Comment",
"CompilerDirective"

]



data_to_write = ("""//===------------------------------------------ C++ ------------------------------------------====//
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
#include "parser/ast/include/AST_core.def"

__AST_BEGIN::node {
ParseResult \0REPLACE\0::parse() {
    if (tokens->empty()) [[unlikely]] {
        return 0;
    }

    return 0;
}

bool \0REPLACE\0::test() {
    if (tokens->empty()) [[unlikely]] {
        return false;
    }
    return false;
}

void \0REPLACE\0::accept(Visitor &visitor) const { visitor.visit(*this); }

}  // namespace __AST_BEGIN::node
""")


data_to_write2 = ("""//===------------------------------------------ C++ ------------------------------------------====//
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
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#include "parser/ast/include/AST.hh"

#include "parser/ast/include/case_types.def"
#include "token/include/token_list.hh"

namespace parser::ast {

NodeT<\0REPLACE\0> get_\0REPLACE\0(token::TokenList &tokens) {
    for (auto &token : tokens) {}

    return nullptr;
}

\0REPLACE\0::\0REPLACE\0() = default;
\0REPLACE\0::\0REPLACE\0(token::TokenList &tokens)
    : Node(tokens)
    , tokens(&tokens) {}
}  // namespace __AST_BEGIN
""")


import os


os.makedirs("expressions", exist_ok=True)
os.makedirs("statements", exist_ok=True)
os.makedirs("annotations", exist_ok=True)
os.makedirs("types", exist_ok=True)
os.makedirs("declarations", exist_ok=True)

for file in exprs:
    with open(f"expressions/AST_{file}.cc", "w") as f:
        f.write(data_to_write.replace("\0REPLACE\0", file))
        print(f"Created file: {file}.cc")

for file in states:
    with open(f"statements/AST_{file}.cc", "w") as f:
        f.write(data_to_write.replace("\0REPLACE\0", file))
        print(f"Created file: {file}.cc")

for file in annos:
    with open(f"annotations/AST_{file}.cc", "w") as f:
        f.write(data_to_write.replace("\0REPLACE\0", file))
        print(f"Created file: {file}.cc")


# make 5 files: Expression.cc, Statement.cc, Annotation.cc, Type.cc, and Declaration.cc in thier respective directories
# each file should have the same content as the data_to_write2 variable, with the \0REPLACE\0 replaced with the name of the file
# for example, the Expression.cc file should have the content of data_to_write2 with \0REPLACE\0 replaced with Expression

with open("statements/Statement.cc", "w") as f:
    f.write(data_to_write2.replace("\0REPLACE\0", "Statement"))
    print("Created file: Statement.cc")

with open("annotations/Annotation.cc", "w") as f:
    f.write(data_to_write2.replace("\0REPLACE\0", "Annotation"))
    print("Created file: Annotation.cc")

with open("types/Type.cc", "w") as f:
    f.write(data_to_write2.replace("\0REPLACE\0", "Type"))
    print("Created file: Type.cc")

with open("declarations/Declaration.cc", "w") as f:
    f.write(data_to_write2.replace("\0REPLACE\0", "Declaration"))
    print("Created file: Declaration.cc")

print("Done!")
