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
#include "parser/ast/include/AST_core.def"
__AST_BEGIN {
    enum class StorageSpecifier : char {
        Static, ///< 'static'
        FFI,    ///< 'ffi'
        /* TODO */ ThreadLocal, ///< 'thread_local'
        /* TODO */ Mutable,     ///< 'mutable'
    };

    enum class TypeQualifier : char {
        Const,              ///< 'const'
        Volatile,           ///< 'volatile'
        /* TODO */ Atomic,  ///< 'atomic'
        /* TODO */ Mutable, ///< 'mutable'
    };

        enum class AccessSpecifier : char {
        Public,             ///< 'pub' - default = exposed by linkage and visibility
        Private,            ///< 'priv'          = not exposed by linkage and visibility
        Protected,          ///< 'prot'          = not exposed by linkage but by visibility
        /* TODO */ Internal ///< 'internal'      = exposed by linkage but not visibility
    };

    enum class FunctionSpecifier : char {
        Inline,            ///< 'inline'
        Abstract,          ///< 'abstract'
        Const,             ///< 'const' - in functions this is 'const' but for classes its 'final'
        Override,          ///< '#[override]' - compiler directive
        Eval               ///< 'eval' - eval in the case of functions default to 'constinit' for
                           ///           'constexpr' or 'consteval' use 'const eval'

        /// ONLY the following are allowed in UDTs (User Defined Types):
        /// 'const'
    };

    enum class FunctionQualifier : char {
        NoExcept,          ///< 'noexcept'
        Abstract,           ///< 'abstract'
        Default,           ///< 'default'
        Delete,            ///< 'delete'
        /* TODO */ Const,  ///< 'const'
        /* TODO */ Override ///< 'override'

        /// ONLY allowed in the scope of a UDT:
        /// 'const'
        /// 'abstract'
        /// 'override'
    };
}


#endif // __MODIFIERS_H__