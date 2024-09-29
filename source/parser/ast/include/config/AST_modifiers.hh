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
//  @author @ze71111                                                                              //
//                                                                                                //
//===-----------------------------------------------------------------------------------------====//

#ifndef __MODIFIERS_H__
#define __MODIFIERS_H__

#include "clang/AST/ASTTypeTraits.h"
#include "parser/ast/include/config/AST_config.def"

__AST_BEGIN {
    enum class StorageSpecifier : char {
        Ffi,     ///< 'ffi'
        Static,  ///< 'static'
        Async,   ///< 'async'
        Eval,    ///< 'eval'
    };

    enum class FFISpecifier : char {
        Class,     ///< 'class'
        Interface, ///< 'interface'
        Struct,    ///< 'struct'
        Enum,      ///< 'enum'
        Union,     ///< 'union'
        Type,      ///< 'type'
    };

    enum class TypeQualifier : char {
        Const,     ///< 'const'
        Module,    ///< 'module'
        Yield,     ///< 'yield'
        Async,     ///< 'async'
        Ffi,       ///< 'ffi'
        Static,    ///< 'static'
        Macro,     ///< 'macro'
    };

    enum class AccessSpecifier : char {
        Public,     ///< 'pub' - default = exposed by linkage and visibility
        Private,    ///< 'priv'          = not exposed by linkage and visibility
        Protected,  ///< 'prot'          = not exposed by linkage but by visibility
        Internal    ///< 'intl'          = exposed by linkage but not visibility
    };

    enum class FunctionSpecifier : char {
        Inline,    ///< 'inline'
        Async,     ///< 'async'
        Static,    ///< 'static'
        Const,     ///< 'const' - in functions this is 'const' but for classes its 'final'
        Eval,      ///< 'eval' - eval in the case of functions default to 'constinit' for
                   ///           'constexpr' or 'consteval' use 'const eval'
        Other,     ///< 'other' - for any other function specifier

        /// ONLY the following are allowed in UDTs (User Defined Types):
        /// 'const'
    };

    enum class FunctionQualifier : char {  // the part after the function signature
        Default, ///< 'default'
        Panic,   ///< 'panic'
        Delete,  ///< 'delete'
        Const,   ///< 'const'
    };
}

#endif  // __MODIFIERS_H__