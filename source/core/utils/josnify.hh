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
#ifndef __JOSNIFY_H__
#define __JOSNIFY_H__

#include <string>
#include <type_traits>

#include "core/types/hx_ints"

#define stringify(object) std::string(#object)

#define TO_JSON_SIGNATURE std::string to_json(u32 depth = 0, bool indent_start = false) const

#define TO_JSON_SIGNATURE_EXTEND(extend) std::string extend::to_json(u32 depth, bool indent_start) const

namespace jsonify {
constexpr inline std::string indent(const u32 &depth) {
    return std::string(static_cast<u32>(depth * 4), ' ');
}

constexpr inline std::string escape(const std::string& val) {
    std::string result;
    result.reserve(val.size());

    for (char car : val) {
        switch (car) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\n': result += "\\n"; break;
            case '\t': result += "\\t"; break;
            case '\r': result += "\\r"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            default: result += car; break;
        }
    }
    return result;
}

template <typename T>
concept HasToJson = requires(T type) {
    { type.to_json() } -> std::same_as<std::string>;
};

template <typename T>
constexpr inline std::string to_json(T key, const u32 &depth, const std::string &alias = "") {
    if constexpr (HasToJson<T>) {
        return indent(depth) + (alias.empty() ? stringify(key) : '"' + alias + '"') + ": " +
               key.to_json(depth + 1);
    } else if constexpr (std::is_same_v<T, char>) {
        return indent(depth) + (alias.empty() ? stringify(key) : '"' + alias + '"') + ": \"" +
               std::string(1, key) + "\"";
    } else if constexpr (std::is_arithmetic_v<T>) {
        return indent(depth) + (alias.empty() ? stringify(key) : '"' + alias + '"') + ": " +
               std::to_string(key);
    } else {
        return indent(depth) + (alias.empty() ? stringify(key) : '"' + alias + '"') + ": \"" +
               std::string(key) + "\"";
    }
}
}  // end namespace jsonify

#endif  // __JOSNIFY_H__