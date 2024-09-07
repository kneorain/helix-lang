// -*- C++ -*-
//===------------------------------------------------------------------------------------------===//
//
// Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
// You are allowed to use, modify, redistribute, and create derivative works, even for commercial
// purposes, provided that you give appropriate credit, and indicate if changes were made.
// For more information, please visit: https://creativecommons.org/licenses/by/4.0/
//
// SPDX-License-Identifier: CC-BY-4.0
// Copyright (c) 2024 (CC BY 4.0)
//
//===------------------------------------------------------------------------------------------===//

#ifndef __JOSNIFY_HH__
#define __JOSNIFY_HH__

#include <exception>
#include <list>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "core/types/hx_ints"
#include "core/utils/hx_print"

#define stringify(object) std::string(#object)

#define TO_JSON_SIGNATURE std::string to_json(u32 depth = 0) const

#define TO_JSON_SIGNATURE_EXTEND(extend) std::string to_json(u32 depth) const

#define TO_JSON_RETURN(var) return var.to_json();

namespace jsonify {
constexpr inline std::string indent(const u32 &depth) {
    return std::string(static_cast<u32>(depth * 4), ' ');
}

constexpr inline std::string add_indent(const std::string &base_str, const u32 &depth) {
    // split by \n
    // append the indent to the start of each line
    // merge them back
    std::string result;

    std::string              current;
    std::vector<std::string> lines;

    for (auto &chr : base_str) {
        if (chr == '\n') {
            lines.push_back(current);
            current.clear();
            continue;
        }

        current += chr;
    }

    // add the final line
    lines.push_back(current);
    current.clear();

    for (auto &line : lines) {
        result += indent(depth) + line + "\n";
    }

    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}

constexpr inline std::string make_key(const std::string &key, const u32 &depth) {
    return indent(depth) + '"' + key + '"' + ": ";
}

constexpr inline std::string make_block(const std::string &data, const u32 &depth) {
    return "{\n" + data + "\n" + indent(depth) + '}';
}

constexpr inline std::string
make_block(const std::string &key, const std::string &data, const u32 &depth) {
    return make_key(key, depth) + "{\n" + data + "\n" + indent(depth) + '}';
}

constexpr inline std::string escape(const std::string &val) {
    std::string result;
    result.reserve(val.size());

    for (char car : val) {
        switch (car) {
            case '"':
                result += "\\\"";
                break;
            case '\\':
                result += "\\\\";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\t':
                result += "\\t";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\b':
                result += "\\b";
                break;
            case '\f':
                result += "\\f";
                break;
            default:
                result += car;
                break;
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
               escape(std::string(1, key)) + "\"";
    } else if constexpr (std::is_arithmetic_v<T>) {
        return indent(depth) + (alias.empty() ? stringify(key) : '"' + alias + '"') + ": " +
               std::to_string(key);
    } else {
        return indent(depth) + (alias.empty() ? stringify(key) : '"' + alias + '"') + ": \"" +
               escape(std::string(key)) + "\"";
    }
}

/* use case
Jsonify json("token");
json.add("value", value);

Jsonify loc_json("loc");
loc_json.add("file", file);
loc_json.add("col", col);
loc_json.add("lines", lines);

json.add(loc_json);

json.to_json(0); // prints:

"token": {
    "value": "lmao",
    "loc": {
        "file": "test/some.hlx"
        "col":  1
        "lines": [
            // each .to_json call separated by commas
        ]
    }
}


*/
class Jsonify {
    u32                                                                        depth = 0;
    std::string                                                                this_key;
    std::map<std::string, std::variant<std::string, std::vector<std::string>>> json;

    std::vector<std::shared_ptr<Jsonify>> sub_json;

    template <typename T>
    [[nodiscard]] bool is_jsonify(const T &value) const {
        return std::holds_alternative<Jsonify>(value);
    }

    template <typename T>
    [[nodiscard]] bool is_string(const T &value) const {
        return std::holds_alternative<std::string>(value);
    }

    template <typename T>
    [[nodiscard]] bool is_string_vec(const T &value) const {
        return std::holds_alternative<std::vector<std::string>>(value);
    }

    template <typename T>
    [[nodiscard]] Jsonify &get_jsonify(T value) const {
        return std::get<Jsonify>(value);
    }

    template <typename T>
    [[nodiscard]] std::string get_string(T value) const {
        return std::get<std::string>(value);
    }

    template <typename T>
    std::vector<std::string> get_string_vec(T value) const {
        return std::get<std::vector<std::string>>(value);
    }

    template <typename T>
    constexpr std::string convert_to_valid_format(const std::string &key, const T &val) {
        if constexpr (HasToJson<T>) {
            return val.to_json(depth + 1) + "\1\2\1\u002bjson-dnc\1\2\1\u002b";
        } else if constexpr (std::is_same_v<T, char>) {
            return '"' + escape(std::string(1, val)) + '"';
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(val);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return '"' + escape(val) + '"';
        } else if constexpr (std::ranges::input_range<T>) {
            add_iterable(key, val);
            return "\1\2\1\u002biterable\1\2\1\u002b";
        } else {
            static_assert(std::is_same_v<T, std::false_type>, "Unsupported type");
        }

        return "";
    }

    template <std::ranges::input_range Range>
    void add_iterable(const std::string &key, const Range &values) {
        std::vector<std::string> json_array;

        for (const auto &val : values) {
            json_array.push_back(convert_to_valid_format(key, val));
        }

        json[key] = json_array;
    }

    static constexpr std::string make_key(const std::string &key, const u32 &dep) {
        return indent(dep) + "\"" + escape(key) + "\": ";
    }

    explicit Jsonify(const u32 &dep)
        : depth(dep) {}

  public:
    Jsonify()  = default;
    ~Jsonify() = default;

    Jsonify(std::string base_key, const u32 &dep)
        : depth(dep)
        , this_key(std::move(base_key)) {}
    Jsonify(const Jsonify &other)
        : depth(other.depth)
        , this_key(other.this_key)
        , json(other.json) {}
    Jsonify &operator=(const Jsonify &other) {
        if (this != &other) {  // Check for self-assignment
            json = other.json;
        }
        return *this;
    }

    template <typename T>
    Jsonify &add(const std::string &key, const T &value) {
        std::string temp = convert_to_valid_format(key, value);

        if (temp.ends_with("\1\2\1\u002bjson-dnc\1\2\1\u002b")) {
            temp.erase(temp.begin(), temp.begin() + temp.find_first_of('{'));
            temp.erase(temp.end() - std::string("\1\2\1\u002bjson-dnc\1\2\1\u002b").size(),
                       temp.end());

            json[key] = temp;
        } else if (temp != "\1\2\1\u002biterable\1\2\1\u002b") {
            json[key] = temp;
        }

        return *this;
    }

    template <typename T>
    Jsonify &add(const T &value) {
        std::string temp = convert_to_valid_format("", value);

        if (temp.ends_with("\1\2\1\u002bjson-dnc\1\2\1\u002b")) {
            auto key = temp.substr(temp.find_first_of('"') + 1, temp.find_first_of('{') - 8);

            temp.erase(temp.begin(), temp.begin() + temp.find_first_of('{'));
            temp.erase(temp.end() - std::string("\1\2\1\u002bjson-dnc\1\2\1\u002b").size(),
                       temp.end());

            json[key] = temp;
        }
        return *this;
    }

    Jsonify &create_sub(const std::string &sub_section_key) {
        sub_json.push_back(
            std::make_shared<Jsonify>(std::string(sub_section_key), this->depth + 1));
        Jsonify &jsonify_ref = *sub_json.back().get();

        return jsonify_ref;
    }

    [[nodiscard]] std::string to_json() {
        std::string result;

        if (!this_key.empty()) {
            result += make_key(this_key, depth) + "{\n";
        }

        for (const auto &[key, value] : json) {
            if (is_string(value)) {
                auto temp_str = get_string(value);
                if (temp_str.ends_with("\1\2\1\u002bjson-dnc\1\2\1\u002b")) {
                    temp_str.erase(temp_str.end() -
                                       std::string("\1\2\1\u002bjson-dnc\1\2\1\u002b").size(),
                                   temp_str.end());

                    // remove the key, since this is in a list
                    // temp_str.erase(temp_str.begin() + temp_str.find_first_of('"'),
                    // temp_str.begin() + temp_str.find_first_of('{'));

                    result += add_indent(temp_str, 1);
                }
            }

            result += make_key(key, depth + 1);

            if (is_string(value)) {
                result += get_string(value);

            } else if (is_string_vec(value)) {
                result += "[\n";

                for (auto str : get_string_vec(value)) {
                    if (str.ends_with("\1\2\1\u002bjson-dnc\1\2\1\u002b")) {
                        // remove the identifier chars
                        str.erase(str.end() -
                                      std::string("\1\2\1\u002bjson-dnc\1\2\1\u002b").size(),
                                  str.end());

                        // remove the key, since this is in a list
                        str.erase(str.begin() + str.find_first_of('"'),
                                  str.begin() + str.find_first_of('{'));

                        result += add_indent(str, 1);
                    } else {
                        result += indent(depth + 2) + convert_to_valid_format("", str);
                    }
                    result += ",\n";
                }

                result.pop_back();  // remove \n
                result.pop_back();  // remove last comma
                result += "\n" + indent(depth + 1) + "]";
            }

            result += ",\n";
        }

        if (!sub_json.empty()) {
            for (const auto &value : sub_json) {
                // result += make_key(key, depth + 1);
                result += value->to_json();

                result += ",\n";
            }
        }

        result.pop_back();  // remove \n
        result.pop_back();  // remove last comma

        if (!this_key.empty()) {
            result += "\n" + indent(depth) + "}";
        }

        return result;
    }
};

}  // end namespace jsonify

#endif  // __JOSNIFY_HH__
