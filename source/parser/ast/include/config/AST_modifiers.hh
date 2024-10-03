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

#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include "neo-json/include/json.hh"
#include "parser/ast/include/config/AST_config.def"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

// Specifier - the part before the signature
// Qualifier - the part after the signature

bool is_excepted(const token::Token &tok, const std::unordered_set<token::tokens> &tokens);

__AST_BEGIN {
    struct StorageSpecifier {
        enum class Specifier : char {
            Ffi,     ///< 'ffi'
            Static,  ///< 'static'
        };

        static bool is_storage_specifier(const token::Token &tok) {
            return tok == token::KEYWORD_FFI || tok == token::KEYWORD_STATIC;
        }

        explicit StorageSpecifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_FFI:
                    type = Specifier::Ffi;
                    break;
                case token::KEYWORD_STATIC:
                    type = Specifier::Static;
                    break;
                default:
                    throw std::runtime_error("Invalid storage specifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("StorageSpecifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Specifier    type;
    };

    struct FFIQualifier {  // excepted after the ffi keyword
        enum class Qualifier : char {
            Class,      ///< 'class'
            Interface,  ///< 'interface'
            Struct,     ///< 'struct'
            Enum,       ///< 'enum'
            Union,      ///< 'union'
            Type,       ///< 'type'
        };

        static bool is_ffi_specifier(const token::Token &tok) {
            return tok == token::KEYWORD_CLASS || tok == token::KEYWORD_INTERFACE ||
                   tok == token::KEYWORD_STRUCT || tok == token::KEYWORD_ENUM ||
                   tok == token::KEYWORD_UNION || tok == token::KEYWORD_TYPE;
        }

        explicit FFIQualifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_CLASS:
                    type = Qualifier::Class;
                    break;
                case token::KEYWORD_INTERFACE:
                    type = Qualifier::Interface;
                    break;
                case token::KEYWORD_STRUCT:
                    type = Qualifier::Struct;
                    break;
                case token::KEYWORD_ENUM:
                    type = Qualifier::Enum;
                    break;
                case token::KEYWORD_UNION:
                    type = Qualifier::Union;
                    break;
                case token::KEYWORD_TYPE:
                    type = Qualifier::Type;
                    break;
                default:
                    throw std::runtime_error("Invalid ffi specifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("FFIQualifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Qualifier    type;
    };

    struct TypeSpecifier {
        enum class Specifier : char {
            Const,   ///< 'const'
            Yield,   ///< 'yield'
            Async,   ///< 'async'
            Module,  ///< 'module'
            Ffi,     ///< 'ffi'
        };

        static bool is_type_qualifier(const token::Token &tok) {
            return tok == token::KEYWORD_CONST || tok == token::KEYWORD_MODULE ||
                   tok == token::KEYWORD_YIELD || tok == token::KEYWORD_ASYNC ||
                   tok == token::KEYWORD_FFI;
        }

        explicit TypeSpecifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_CONST:
                    type = Specifier::Const;
                    break;
                case token::KEYWORD_MODULE:
                    type = Specifier::Module;
                    break;
                case token::KEYWORD_YIELD:
                    type = Specifier::Yield;
                    break;
                case token::KEYWORD_ASYNC:
                    type = Specifier::Async;
                    break;
                case token::KEYWORD_FFI:
                    type = Specifier::Ffi;
                    break;
                default:
                    throw std::runtime_error("Invalid type specifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("TypeSpecifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Specifier    type;
    };

    struct AccessSpecifier {
        enum class Specifier : char {
            Public,     ///< 'pub' - default = exposed by linkage and visibility
            Private,    ///< 'priv'          = not exposed by linkage and visibility
            Protected,  ///< 'prot'          = not exposed by linkage but by visibility
            Internal    ///< 'intl'          = exposed by linkage but not visibility
        };

        static bool is_access_specifier(const token::Token &tok) {
            return tok == token::KEYWORD_PUBLIC || tok == token::KEYWORD_PRIVATE ||
                   tok == token::KEYWORD_PROTECTED || tok == token::KEYWORD_INTERNAL;
        }

        explicit AccessSpecifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_PUBLIC:
                    type = Specifier::Public;
                    break;
                case token::KEYWORD_PRIVATE:
                    type = Specifier::Private;
                    break;
                case token::KEYWORD_PROTECTED:
                    type = Specifier::Protected;
                    break;
                case token::KEYWORD_INTERNAL:
                    type = Specifier::Internal;
                    break;
                default:
                    throw std::runtime_error("Invalid access specifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("AccessSpecifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Specifier    type;
    };

    struct FunctionSpecifier {  // the part before the function signature
        enum class Specifier : char {
            Inline,  ///< 'inline'
            Async,   ///< 'async'
            Static,  ///< 'static'
            Const,   ///< 'const' - in functions this is 'const' but for classes its 'final'
            Eval,    ///< 'eval' - eval in the case of functions default to 'constinit' for
                     ///           'constexpr' or 'consteval' use 'const eval'
        };

        static bool is_function_specifier(const token::Token &tok) {
            return tok == token::KEYWORD_INLINE || tok == token::KEYWORD_ASYNC ||
                   tok == token::KEYWORD_STATIC || tok == token::KEYWORD_CONST ||
                   tok == token::KEYWORD_EVAL;
        }

        explicit FunctionSpecifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_INLINE:
                    type = Specifier::Inline;
                    break;
                case token::KEYWORD_ASYNC:
                    type = Specifier::Async;
                    break;
                case token::KEYWORD_STATIC:
                    type = Specifier::Static;
                    break;
                case token::KEYWORD_CONST:
                    type = Specifier::Const;
                    break;
                case token::KEYWORD_EVAL:
                    type = Specifier::Eval;
                    break;
                default:
                    throw std::runtime_error("Invalid function specifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("FunctionSpecifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Specifier    type;
    };

    struct FunctionQualifier {
        enum class Qualifier : char {  // the part after the function signature
            Default,                   ///< 'default'
            Panic,                     ///< 'panic'
            Delete,                    ///< 'delete'
            Const,                     ///< 'const'
        };

        static bool is_function_qualifier(const token::Token &tok) {
            return tok == token::KEYWORD_DEFAULT || tok == token::KEYWORD_PANIC ||
                   tok == token::KEYWORD_DELETE || tok == token::KEYWORD_CONST;
        }

        explicit FunctionQualifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_DEFAULT:
                    type = Qualifier::Default;
                    break;
                case token::KEYWORD_PANIC:
                    type = Qualifier::Panic;
                    break;
                case token::KEYWORD_DELETE:
                    type = Qualifier::Delete;
                    break;
                case token::KEYWORD_CONST:
                    type = Qualifier::Const;
                    break;
                default:
                    throw std::runtime_error("Invalid function qualifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("FunctionQualifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Qualifier    type;
    };

    struct ClassSpecifier {
        enum class Specifier : char {
            Static,  ///< 'static'
            Const,   ///< 'const' - in functions this is 'const' but for classes its 'final'
        };

        static bool is_class_specifier(const token::Token &tok) {
            return tok == token::KEYWORD_CONST || tok == token::KEYWORD_STATIC;
        }

        explicit ClassSpecifier(token::Token marker)
            : marker(std::move(marker)) {
            switch (marker.token_kind()) {
                case token::KEYWORD_CONST:
                    type = Specifier::Const;
                    break;
                case token::KEYWORD_STATIC:
                    type = Specifier::Static;
                    break;
                default:
                    throw std::runtime_error("Invalid class specifier");
                    break;
            }
        }

        TO_NEO_JSON_IMPL {
            neo::json json("ClassSpecifier");

            json.add("type", (int)type).add("marker", marker);

            return json;
        }

        token::Token marker;
        Specifier    type;
    };

    struct Modifiers {
      public:
        enum class ExpectedModifier : char {
            StorageSpec,  ///< 'ffi' | 'static'
            FfiSpec,      ///< 'class' | 'interface' | 'struct' | 'enum' | 'union' | 'type'
            TypeSpec,     ///< 'const' | 'module' | 'yield' | 'async' | 'ffi'
            AccessSpec,   ///< 'pub' | 'priv' | 'prot' | 'intl'
            FuncSpec,     ///< 'inline' | 'async' | 'static' | 'const' | 'eval'
            FuncQual,     ///< 'default' | 'panic' | 'delete' | 'const'
            ClassSpec,    ///< 'const' | 'static'
        };

      private:
        std::vector<ExpectedModifier>                                    expected_modifiers;
        std::unordered_set<token::tokens>                                allowed_modifiers;
        std::unordered_map<ExpectedModifier, std::vector<token::tokens>> modifiers_map = {
            {ExpectedModifier::StorageSpec, {token::KEYWORD_FFI, token::KEYWORD_STATIC}},
            {ExpectedModifier::FfiSpec,
             {token::KEYWORD_CLASS,
              token::KEYWORD_INTERFACE,
              token::KEYWORD_STRUCT,
              token::KEYWORD_ENUM,
              token::KEYWORD_UNION,
              token::KEYWORD_TYPE}},
            {ExpectedModifier::TypeSpec,
             {token::KEYWORD_CONST,
              token::KEYWORD_MODULE,
              token::KEYWORD_YIELD,
              token::KEYWORD_ASYNC,
              token::KEYWORD_FFI}},
            {ExpectedModifier::AccessSpec,
             {token::KEYWORD_PUBLIC,
              token::KEYWORD_PRIVATE,
              token::KEYWORD_PROTECTED,
              token::KEYWORD_INTERNAL}},
            {ExpectedModifier::FuncSpec,
             {token::KEYWORD_INLINE,
              token::KEYWORD_ASYNC,
              token::KEYWORD_STATIC,
              token::KEYWORD_CONST,
              token::KEYWORD_EVAL}},
            {ExpectedModifier::FuncQual,
             {token::KEYWORD_DEFAULT,
              token::KEYWORD_PANIC,
              token::KEYWORD_DELETE,
              token::KEYWORD_CONST}},
            {ExpectedModifier::ClassSpec, {token::KEYWORD_CONST, token::KEYWORD_STATIC}}};

        std::vector<std::variant<StorageSpecifier,
                                 FFIQualifier,
                                 TypeSpecifier,
                                 AccessSpecifier,
                                 FunctionSpecifier,
                                 FunctionQualifier,
                                 ClassSpecifier>>
            modifiers;

      public:
        template <typename... Args>
        explicit Modifiers(Args &&...args)
            : expected_modifiers{std::forward<Args>(args)...} {
            for (const auto &modifier : expected_modifiers) {
                const auto &tokens = modifiers_map[modifier];
                allowed_modifiers.insert(tokens.begin(), tokens.end());
            }
        }

        // so if we set the modifiers to another Modifiers object
        // we can copy the expected_modifiers and allowed_modifiers and verify if the other
        // object has the modifiers we are looking for

        static bool is_modifier(const token::Token &tok, ExpectedModifier modifier) {
            switch (modifier) {
                case ExpectedModifier::StorageSpec:
                    return StorageSpecifier::is_storage_specifier(tok);
                case ExpectedModifier::FfiSpec:
                    return FFIQualifier::is_ffi_specifier(tok);
                case ExpectedModifier::TypeSpec:
                    return TypeSpecifier::is_type_qualifier(tok);
                case ExpectedModifier::AccessSpec:
                    return AccessSpecifier::is_access_specifier(tok);
                case ExpectedModifier::FuncSpec:
                    return FunctionSpecifier::is_function_specifier(tok);
                case ExpectedModifier::FuncQual:
                    return FunctionQualifier::is_function_qualifier(tok);
                case ExpectedModifier::ClassSpec:
                    return ClassSpecifier::is_class_specifier(tok);
                default:
                    return false;
            }
        }
        static bool is_modifier(const token::Token &tok) {
            return StorageSpecifier::is_storage_specifier(tok) ||
                   AccessSpecifier::is_access_specifier(tok) ||
                   FunctionSpecifier::is_function_specifier(tok) ||
                   ClassSpecifier::is_class_specifier(tok);
        }

        [[nodiscard]] bool find_add(const token::Token &current_token) {

            if (allowed_modifiers.find(current_token.token_kind()) == allowed_modifiers.end()) {
                return false;  // not a modifier
            }

            for (const auto &modifier_type : expected_modifiers) {
                if (is_modifier(current_token, modifier_type)) {
                    switch (modifier_type) {
                        case ExpectedModifier::StorageSpec:
                            modifiers.emplace_back(StorageSpecifier(current_token));
                            break;
                        case ExpectedModifier::FfiSpec:
                            modifiers.emplace_back(FFIQualifier(current_token));
                            break;
                        case ExpectedModifier::TypeSpec:
                            modifiers.emplace_back(TypeSpecifier(current_token));
                            break;
                        case ExpectedModifier::AccessSpec:
                            modifiers.emplace_back(AccessSpecifier(current_token));
                            break;
                        case ExpectedModifier::FuncSpec:
                            modifiers.emplace_back(FunctionSpecifier(current_token));
                            break;
                        case ExpectedModifier::FuncQual:
                            modifiers.emplace_back(FunctionQualifier(current_token));
                            break;
                        case ExpectedModifier::ClassSpec:
                            modifiers.emplace_back(ClassSpecifier(current_token));
                            break;
                        default:
                            return false;
                    }

                    return true;
                }
            }

            return false;
        }

        template <typename T>
        [[nodiscard]] std::vector<T> get() {
            std::vector<T> result;

            for (const auto &modifier : modifiers) {
                if (std::holds_alternative<T>(modifier)) {
                    result.push_back(std::get<T>(modifier));
                }
            }

            return result;
        }

        [[nodiscard]] bool empty() const { return modifiers.empty(); }

        void clear() { modifiers.clear(); }

        explicit operator bool() const { return !empty(); }

        [[nodiscard]] size_t size() const { return modifiers.size(); }

        template <typename T>
        [[nodiscard]] T first() {
            if (modifiers.empty()) {
                throw std::runtime_error("No modifiers found");
            }

            return std::get<T>(modifiers.front());
        }

        template <typename T>
        [[nodiscard]] T last() {
            if (modifiers.empty()) {
                throw std::runtime_error("No modifiers found");
            }

            return std::get<T>(modifiers.back());
        }

        template <typename T>
        [[nodiscard]] T pop_first() {
            if (modifiers.empty()) {
                throw std::runtime_error("No modifiers found");
            }

            T result = std::get<T>(modifiers.front());
            modifiers.erase(modifiers.begin());
            return result;
        }

        template <typename T>
        [[nodiscard]] T pop_last() {
            if (modifiers.empty()) {
                throw std::runtime_error("No modifiers found");
            }

            T result = std::get<T>(modifiers.back());
            modifiers.pop_back();
            return result;
        }

        template <typename T>
        void remove(long long index) {
            if (index >= static_cast<long long>(modifiers.size())) {
                throw std::runtime_error("Index out of bounds");
            }

            modifiers.erase(modifiers.begin() + index);
        }

        TO_NEO_JSON_IMPL {
            neo::json              json("Modifiers");
            std::vector<neo::json> modifiers_json;

            for (const auto &modifier : modifiers) {
                if (std::holds_alternative<StorageSpecifier>(modifier)) {
                    modifiers_json.push_back(std::get<StorageSpecifier>(modifier).to_json());
                } else if (std::holds_alternative<FFIQualifier>(modifier)) {
                    modifiers_json.push_back(std::get<FFIQualifier>(modifier).to_json());
                } else if (std::holds_alternative<TypeSpecifier>(modifier)) {
                    modifiers_json.push_back(std::get<TypeSpecifier>(modifier).to_json());
                } else if (std::holds_alternative<AccessSpecifier>(modifier)) {
                    modifiers_json.push_back(std::get<AccessSpecifier>(modifier).to_json());
                } else if (std::holds_alternative<FunctionSpecifier>(modifier)) {
                    modifiers_json.push_back(std::get<FunctionSpecifier>(modifier).to_json());
                } else if (std::holds_alternative<FunctionQualifier>(modifier)) {
                    modifiers_json.push_back(std::get<FunctionQualifier>(modifier).to_json());
                } else if (std::holds_alternative<ClassSpecifier>(modifier)) {
                    modifiers_json.push_back(std::get<ClassSpecifier>(modifier).to_json());
                }
            }

            json.add("modifiers", modifiers_json);
            return json;
        }
    };
}

#undef CHECK_N_SET
#endif  // __MODIFIERS_H__