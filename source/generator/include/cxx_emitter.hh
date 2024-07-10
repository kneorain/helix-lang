/**
 * @author Dhruvan Kartik
 * @copyright Copyright (c) 2024 (CC BY 4.0)
 *
 * @note This code is part of the Helix Language Project and is licensed under the Attribution 4.0
 * International license (CC BY 4.0). You are allowed to use, modify, redistribute, and create
 * derivative works, even for commercial purposes, provided that you give appropriate credit,
 * provide a link to the license, and indicate if changes were made. For more information, please
 * visit: https://creativecommons.org/licenses/by/4.0/ SPDX-License-Identifier: CC-BY-4.0
 *
 * @note This code is provided by the creators of Helix. Visit our website at:
 * https://helix-lang.com/ for more information.
 */
#ifndef __CXX_EMITTER_HH__
#define __CXX_EMITTER_HH__

#include <cstddef>
#include <cstdlib>
#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "core/types/hx_ints"
#include "parser/ast/include/ast.hh"
#include "parser/ast/include/context.hh"


/* usage
#include "generator/include/cxx_emitter.hh"
#include "parser/ast/include/nodes.hh"

using namespace codegen::cxx;

CXXBuilder builder = CXXBuilder(ast::node::Program, Context);

CXXBody built = builder.generate();

CXXNodeList functions  = built.get_functions(include_priv: false));
CXXNodeList classes    = built.get_classes  (include_priv: false));
CXXNodeList structs    = built.get_structs  (include_priv: false));
CXXNodeList enums      = built.get_enums    (include_priv: false));
CXXNodeList unions     = built.get_unions   (include_priv: false));

CXXNodeList types      = built.get_types    (include_priv: false));
CXXNodeList variables  = built.get_variables(include_priv: false));
CXXNodeList constants  = built.get_constants(include_priv: false));

built.to_code(); // the whole ir code

std::string current_namespace;
std::string header;

for (auto &const fn : functions) {
    if (current_namespace != fn->parent().to_code()) {
        if (!current_namespace.empty()) {
            header += "}  \\ end namespace " + current_namespace + "\n";
        }
        header += "namespace " + fn->parent().to_code() + "{\n";
    }

    header += fn->signature().to_code() + ";\n"; // int some_func();
}

for the example ast (10 + (9 + 1)):
{
    "BinaryExpr" : {
        "type": "expr",
        "op": "+",
        "left": {
            "type": "literal",
            "value": "10"
        },
        "right": {
            "BinaryExpr" : {
                "type": "expr",
                "op": "+",
                "left": {
                    "type": "literal",
                    "value": "9"
                },
                "right": {
                    "type": "literal",
                    "value": "1"
                }
            }
        }
    }
}

CXXNodeList = [
    BinaryExprBuilder(
        op: "+",
        left: *BuilderLiteralInt(10),
        right: *BinaryExprBuilder(
            op: "+",
            left: *BuilderLiteralInt(9),
            right: *BuilderLiteralInt(1)
        )
    )
]

CXXNodeList[0].to_string();
*/

namespace codegen::cxx {
using namespace parser;

template <typename T>
struct CXXNode;

template <typename T = void>
using CXXNodePtr = std::shared_ptr<CXXNode<T>>;

template <>
struct CXXNode<void> {
    CXXNode()                           = default;
    CXXNode(CXXNode &&)                 = default;
    CXXNode(const CXXNode &)            = default;
    CXXNode &operator=(CXXNode &&)      = default;
    CXXNode &operator=(const CXXNode &) = delete;
    virtual ~CXXNode()                  = default;

    CXXNodePtr<> get_parent();
    CXXNodePtr<> get_signature();
    CXXNodePtr<> get_body();
    CXXNodePtr<> generate();

    std::string to_code(); // emit entire object  as a string
    std::string to_stub(); // emit only signature as a string
    std::string to_json();
};

template <typename T>
struct CXXNode : public CXXNode<void> {
    CXXNode(ast::NodePtr<> &ast, ast::Context &context);
    CXXNode()                           = default;
    CXXNode(CXXNode &&)                 = default;
    CXXNode(const CXXNode &)            = default;
    CXXNode &operator=(CXXNode &&)      = default;
    CXXNode &operator=(const CXXNode &) = delete;
   ~CXXNode()                           = default;
};

template <typename T = void>
struct CXXNodeList {
    explicit CXXNodeList(const std::string &file_name);
    CXXNodeList()                               = default;
    CXXNodeList(CXXNodeList &&)                 = default;
    CXXNodeList(const CXXNodeList &)            = default;
    CXXNodeList &operator=(CXXNodeList &&)      = default;
    CXXNodeList &operator=(const CXXNodeList &) = delete;
   ~CXXNodeList()                               = default;

    void append(CXXNodePtr<T> node);
    void append_front(CXXNodePtr<T> node);

    CXXNodePtr<T> pop(u32 n);
    void          remove(u32 n);
    void          clear();

    std::string to_code();
    std::string to_stub();
    std::string to_json();
    
    private:
      std::string filename;
      std::vector<CXXNodePtr<T>> nodes;
};

struct CXXBody {
    CXXBody()                           = default;
    CXXBody(CXXBody &&)                 = default;
    CXXBody(const CXXBody &)            = default;
    CXXBody &operator=(CXXBody &&)      = default;
    CXXBody &operator=(const CXXBody &) = delete;
   ~CXXBody()                           = default;
    
    CXXNodeList< /*FunctionNode*/> get_functions(bool include_priv = false);
    CXXNodeList< /*VariableNode*/> get_variables(bool include_priv = false);
    CXXNodeList< /*ConstantNode*/> get_constants(bool include_priv = false);
    CXXNodeList< /*ClassNode*/   > get_classes  (bool include_priv = false);
    CXXNodeList< /*StructNode*/  > get_structs  (bool include_priv = false);
    CXXNodeList< /*UnionNode*/   > get_unions   (bool include_priv = false);
    CXXNodeList< /*EnumNode*/    > get_enums    (bool include_priv = false);
    CXXNodeList< /*TypeNode*/    > get_types    (bool include_priv = false);

    std::string to_code();
    std::string to_stub();
    std::string to_json();
    
    private:
      friend void generate_from_node(ast::NodePtr<> node);
};

struct CXXBuilder {
    CXXBuilder()                              = delete;
    CXXBuilder(CXXBuilder &&)                 = default;
    CXXBuilder(const CXXBuilder &)            = default;
    CXXBuilder &operator=(CXXBuilder &&)      = delete;
    CXXBuilder &operator=(const CXXBuilder &) = delete;
   ~CXXBuilder()                              = default;
        
    CXXBody     generate();
    
    private:
      parser::ast::node::Program& AST;
      ast::Context&   context;
};
}

#endif // __CXX_EMITTER_HH__