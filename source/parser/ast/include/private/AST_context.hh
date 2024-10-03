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
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __AST_CONTEXT_H__
#define __AST_CONTEXT_H__

#include <unordered_map>
#include "parser/ast/include/config/AST_config.def"
#include "parser/ast/include/private/AST_generate.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "parser/ast/include/types/AST_visitor.hh"
#include "token/include/Token.hh"

__AST_BEGIN {
    struct Symbol {
        __AST_NODE::nodes type;    ///< type of the symbol
        __AST_N::NodeT<>  node;    ///< node that represents the symbol
        __AST_N::NodeT<>  parent;  ///< parent node of the symbol
        __TOKEN_N::Token  marker;  ///< token that marks the symbol
    };

    class Context {
        // needs the following things:
        //    - the constructor takes in an AST node
        //      recursively traverses the AST node using 'accept' and gathers a list of symbols
        //      uses said symbols to build a symbol table
        //    - a 'find' method that takes in a string and returns a symbol
        //    - a 'find' method that takes in a token  and returns all the matching symbols
        //    - a 'get' method that returns the symbol table
        //    - a 'get' method that takes in a parent node and returns all the symbols that are children of the parent node
        //    - a 'is' method that takes in a symbol and a type and returns true if the symbol is of the given type
        //    - a 'merge' method that takes in a Context and merges the symbol tables of the two contexts
        //    - a 'append' method that takes in a symbol and adds it to the symbol table
        //    - a 'remove' method that takes in a symbol and removes it from the symbol table
        //    - a 'clear' method that clears the symbol table
        //    - a 'size' method that returns the number of symbols in the symbol table
        // felids:
        //    - 'symbols' is a hash map of <std::string, Symbol> where the std::string is name
        //                which is a mangled name of the symbol (guaranteed to be unique)

        private:
            std::unordered_map<std::string, Symbol> symbols;
    };
}

#endif  // __AST_CONTEXT_H__