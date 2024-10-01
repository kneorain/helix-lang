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

#include <variant>

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
        Class,      ///< 'class'
        Interface,  ///< 'interface'
        Struct,     ///< 'struct'
        Enum,       ///< 'enum'
        Union,      ///< 'union'
        Type,       ///< 'type'
    };

    enum class TypeQualifier : char {
        Const,   ///< 'const'
        Module,  ///< 'module'
        Yield,   ///< 'yield'
        Async,   ///< 'async'
        Ffi,     ///< 'ffi'
        Static,  ///< 'static'
        Macro,   ///< 'macro'
    };

    enum class AccessSpecifier : char {
        Public,     ///< 'pub' - default = exposed by linkage and visibility
        Private,    ///< 'priv'          = not exposed by linkage and visibility
        Protected,  ///< 'prot'          = not exposed by linkage but by visibility
        Internal    ///< 'intl'          = exposed by linkage but not visibility
    };

    enum class FunctionSpecifier : char {
        Inline,  ///< 'inline'
        Async,   ///< 'async'
        Static,  ///< 'static'
        Const,   ///< 'const' - in functions this is 'const' but for classes its 'final'
        Eval,    ///< 'eval' - eval in the case of functions default to 'constinit' for
                 ///           'constexpr' or 'consteval' use 'const eval'
        Other,   ///< 'other' - for any other function specifier

        /// ONLY the following are allowed in UDTs (User Defined Types):
        /// 'const'
    };

    enum class FunctionQualifier : char {  // the part after the function signature
        Default,                           ///< 'default'
        Panic,                             ///< 'panic'
        Delete,                            ///< 'delete'
        Const,                             ///< 'const'
    };

#define CHECK_N_SET(x) \
    if (x) {           \
        return true;   \
    }                  \
    x = true;          \
    return false

    struct Modifiers {
      private:
        bool type_qual    = false;
        bool func_qual    = false;
        bool func_spec    = false;
        bool storage_spec = false;
        bool ffi_spec     = false;
        bool visibility   = false;

      public:
        enum class ExpectedModifier : char {
            None,
            TypeQual,
            FuncQual,
            FuncSpec,
            StorageSpec,
            FfiSpec
        };

        struct TypeQual {
            bool is_const  = false;
            bool is_module = false;
            bool is_yield  = false;
            bool is_async  = false;
            bool is_ffi    = false;
            bool is_static = false;
            bool is_macro  = false;
        };

        struct FuncQual {
            bool is_default = false;
            bool is_panic   = false;
            bool is_delete  = false;
            bool is_const   = false;
        };

        struct FuncSpec {
            bool is_inline = false;
            bool is_async  = false;
            bool is_static = false;
            bool is_const  = false;
            bool is_eval   = false;
            bool is_other  = false;
        };

        struct StorageSpec {
            bool is_ffi    = false;
            bool is_static = false;
            bool is_async  = false;
            bool is_eval   = false;
        };

        struct FfiSpec {
            bool is_class     = false;
            bool is_interface = false;
            bool is_struct    = false;
            bool is_enum      = false;
            bool is_union     = false;
            bool is_type      = false;
        };

        AccessSpecifier  Visibility = AccessSpecifier::Public;
        ExpectedModifier expect     = ExpectedModifier::None;
        TypeQual         type_qualifiers;
        FuncQual         function_qualifiers;
        FuncSpec         function_specifiers;
        StorageSpec      storage_specifiers;
        FfiSpec          ffi_specifiers;

        // usage
        /// initialize with like: Modifiers modifiers(Modifiers::ExpectedModifier::TypeQual, ...);
        /// add with modifiers.add(FunctionSpecifier::Async);
        /// get with modifier.get(); -> returns a array with pointers to
        /// Modifiers::ExpectedModifier::TypeQual, ...
        // all functionality provided at compile time rather then runtime

        template <typename... Args>
        consteval explicit Modifiers(ExpectedModifier first, Args... args) {
            static_assert(sizeof...(args) < 6, "Too many modifiers");
            std::array<ExpectedModifier, sizeof...(args) + 1> modifiers = {first, args...};

            for (ExpectedModifier mod : modifiers) {
                switch (mod) {
                    case ExpectedModifier::TypeQual:
                        type_qual = true;
                        break;
                    case ExpectedModifier::FuncQual:
                        func_qual = true;
                        break;
                    case ExpectedModifier::FuncSpec:
                        func_spec = true;
                        break;
                    case ExpectedModifier::StorageSpec:
                        storage_spec = true;
                        break;
                    case ExpectedModifier::FfiSpec:
                        ffi_spec = true;
                        break;
                    default:
                        static_assert(false, "invalid modifier provided");
                }
            }
        }

      private:
        consteval bool add_storage_specifier(StorageSpecifier modifier) {
            switch (modifier) {
                case StorageSpecifier::Ffi:
                    CHECK_N_SET(storage_specifiers.is_ffi);
                case StorageSpecifier::Static:
                    CHECK_N_SET(storage_specifiers.is_static);
                case StorageSpecifier::Async:
                    CHECK_N_SET(storage_specifiers.is_async);
                case StorageSpecifier::Eval:
                    CHECK_N_SET(storage_specifiers.is_eval);
                default:
                    throw "invalid function specifier provided.";
            }
            return false;
        }

        consteval bool add_access_specifier(AccessSpecifier modifier) {
            switch (modifier) {
                case AccessSpecifier::Public:
                    Visibility = AccessSpecifier::Public;
                    return true;
                case AccessSpecifier::Private:
                    Visibility = AccessSpecifier::Private;
                    return true;
                case AccessSpecifier::Protected:
                    Visibility = AccessSpecifier::Protected;
                    return true;
                case AccessSpecifier::Internal:
                    Visibility = AccessSpecifier::Internal;
                    return true;
                default:
                    throw "invalid access specifier provided.";
            }
            return false;
        }

        consteval bool add_function_specifier(FunctionSpecifier modifier) {
            switch (modifier) {
                case FunctionSpecifier::Inline:
                    CHECK_N_SET(function_specifiers.is_inline);
                case FunctionSpecifier::Async:
                    CHECK_N_SET(function_specifiers.is_async);
                case FunctionSpecifier::Static:
                    CHECK_N_SET(function_specifiers.is_static);
                case FunctionSpecifier::Const:
                    CHECK_N_SET(function_specifiers.is_const);
                case FunctionSpecifier::Eval:
                    CHECK_N_SET(function_specifiers.is_eval);
                default:
                    throw "invalid function specifier provided.";
            }
            return false;
        }

        consteval bool add_function_qualifier(FunctionQualifier modifier) {
            switch (modifier) {
                case FunctionQualifier::Default:
                    CHECK_N_SET(function_qualifiers.is_default);
                case FunctionQualifier::Panic:
                    CHECK_N_SET(function_qualifiers.is_panic);
                case FunctionQualifier::Delete:
                    CHECK_N_SET(function_qualifiers.is_delete);
                case FunctionQualifier::Const:
                    CHECK_N_SET(function_qualifiers.is_const);
                default:
                    throw "invalid function qualifier provided.";
            }
            return false;
        }

        consteval bool add_type_qualifier(TypeQualifier modifier) {
            switch (modifier) {
                case TypeQualifier::Const:
                    CHECK_N_SET(type_qualifiers.is_const);
                case TypeQualifier::Module:
                    CHECK_N_SET(type_qualifiers.is_module);
                case TypeQualifier::Yield:
                    CHECK_N_SET(type_qualifiers.is_yield);
                case TypeQualifier::Async:
                    CHECK_N_SET(type_qualifiers.is_async);
                case TypeQualifier::Ffi:
                    CHECK_N_SET(type_qualifiers.is_ffi);
                case TypeQualifier::Static:
                    CHECK_N_SET(type_qualifiers.is_static);
                case TypeQualifier::Macro:
                    CHECK_N_SET(type_qualifiers.is_macro);
                default:
                    throw "invalid type qualifier provided.";
            }
            return false;
        }

        consteval bool add_ffi_specifier(FFISpecifier modifier) {
            switch (modifier) {
                case FFISpecifier::Class:
                    CHECK_N_SET(ffi_specifiers.is_class);
                case FFISpecifier::Interface:
                    CHECK_N_SET(ffi_specifiers.is_interface);
                case FFISpecifier::Struct:
                    CHECK_N_SET(ffi_specifiers.is_struct);
                case FFISpecifier::Enum:
                    CHECK_N_SET(ffi_specifiers.is_enum);
                case FFISpecifier::Union:
                    CHECK_N_SET(ffi_specifiers.is_union);
                case FFISpecifier::Type:
                    CHECK_N_SET(ffi_specifiers.is_type);
                default:
                    throw "invalid ffi specifier provided.";
            }
            return false;
        }

      public:
        template <typename ModT>
        consteval bool add(ModT modifier) {
            static_assert(
                std::is_same_v<ModT, StorageSpecifier> || std::is_same_v<ModT, AccessSpecifier> ||
                    std::is_same_v<ModT, FFISpecifier> || std::is_same_v<ModT, FunctionSpecifier> ||
                    std::is_same_v<ModT, TypeQualifier> || std::is_same_v<ModT, FunctionQualifier>,
                "invalid modifier type provided to add.");

            if constexpr (std::is_same_v<ModT, StorageSpecifier>) {
                return add_storage_specifier(static_cast<StorageSpecifier>(modifier));
            } else if constexpr (std::is_same_v<ModT, AccessSpecifier>) {
                return add_access_specifier(static_cast<AccessSpecifier>(modifier));
            } else if constexpr (std::is_same_v<ModT, FFISpecifier>) {
                return add_ffi_specifier(static_cast<FFISpecifier>(modifier));
            } else if constexpr (std::is_same_v<ModT, FunctionSpecifier>) {
                return add_function_specifier(static_cast<FunctionSpecifier>(modifier));
            } else if constexpr (std::is_same_v<ModT, TypeQualifier>) {
                return add_type_qualifier(static_cast<TypeQualifier>(modifier));
            } else if constexpr (std::is_same_v<ModT, FunctionQualifier>) {
                return add_function_qualifier(static_cast<FunctionQualifier>(modifier));
            } else {
                static_assert(false, "invalid function specifier provided.");
            }
        }
    };
}

#undef CHECK_N_SET
#endif  // __MODIFIERS_H__