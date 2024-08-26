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
#ifndef __ERROR_HH__
#define __ERROR_HH__

#include <cstdio>
#include <exception>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "core/types/hx_ints"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

#define LINES_TO_SHOW 5

namespace error {
struct _internal_error {
  private:
    using fix_pair_vec = std::vector<std::pair<string, u32>>;

  public:
    string       color_mode;
    string       error_type;
    string       level;
    string       file;
    string       msg;
    string       fix;
    string       display;
    string       full_line;
    u64          line{};
    u64          col{};
    u64          offset{};
    fix_pair_vec quick_fix;

    _internal_error() = default;

    [[nodiscard]] string to_json() const {
        string json;

        json += "{";
        json += R"("color_mode": ")" + color_mode + "\", ";
        json += R"("error_type": ")" + error_type + "\", ";
        json += R"("level": ")" + level + "\", ";
        json += R"("file": ")" + file + "\", ";
        json += R"("msg": ")" + msg + "\", ";
        json += R"("fix": ")" + fix + "\", ";
        json += R"("display": ")" + display + "\", ";
        json += R"("line": )" + std::to_string(line) + ", ";
        json += R"("col": )" + std::to_string(col) + ", ";
        json += R"("offset": )" + std::to_string(offset) + ", ";
        json += R"("quick_fix": [)";

        for (size_t i = 0; i < quick_fix.size(); ++i) {
            json += R"({"fix": ")" + quick_fix[i].first + R"(", "loc": )" +
                    std::to_string(quick_fix[i].second) + "}";
            if (i < quick_fix.size() - 1) {
                json += ", ";
            }
        }
        
        json += "]";
        return json += "}";
    }
};


using string_vec   = std::vector<string>;
using fix_pair     = std::pair<token::Token, i64>;
using fix_pair_vec = std::vector<fix_pair>;
using errors_rep   = std::vector<_internal_error>;


inline bool       HAS_ERRORED = false;
inline bool       SHOW_ERROR  = true;
inline errors_rep ERRORS;


enum Level {
    NOTE,   ///< Just a Info.
    WARN,   ///< Warn, the compiler can move on to code gen. and produce a binary
    ERR,    ///< Error, but compiler can continue parsing
    FATAL,  ///< Fatal error all other proceeding errors omitted
};


struct Errors {
    string err;
    string fix;
    Level  level = ERR;
};


struct CodeError {
    token::Token *pof;  //< point of failure
    float         err_code;
    bool          mark_pof = true;
    string_vec    fix_fmt_args;
    string_vec    err_fmt_args;
    fix_pair_vec  opt_fixes;  //< fixes that show in the code to fix

    ~CodeError() = default;
};


struct CompilerError {
    float      err_code;
    string_vec fix_fmt_args;
    string_vec err_fmt_args;
};


class Panic {
  public:
    _internal_error final_err;

    explicit Panic(const CodeError &);
    explicit Panic(const CompilerError &);

  private:
    void process_compiler_error(CompilerError);
    void process_code_error(CodeError);
    void process_full_line();
    void show_error();

    u32 calculate_addition_pos(i64) const;

    size_t level_len;
    bool   mark_pof;
};


static inline CodeError create_old_CodeError(token::Token *pof,
                                             float         err_code,
                                             string_vec    fix_fmt_args = {},
                                             string_vec    err_fmt_args = {},
                                             fix_pair_vec  opt_fixes    = {}) {
    return CodeError{.pof          = pof,
                     .err_code     = err_code,
                     .fix_fmt_args = std::move(fix_fmt_args),
                     .err_fmt_args = std::move(err_fmt_args),
                     .opt_fixes    = std::move(opt_fixes)};
};


static inline string fmt_string(const string &format, const string_vec &fmt_args) {
    string      result;
    std::size_t N = fmt_args.size();
    result.reserve(format.size());

    std::size_t argIndex = 0;
    std::size_t len      = format.size();

    for (std::size_t i = 0; i < len; ++i) {
        if (format[i] == '{' && i + 1 < len && format[i + 1] == '}') {
            if (argIndex >= N) {
                throw std::invalid_argument("Insufficient arguments provided for format string");
            }
            result += fmt_args[argIndex++];
            ++i;  // Skip over the closing '}'
        } else {
            result += format[i];
        }
    }

    if (argIndex != N) {
        throw std::invalid_argument("Too many arguments provided for format string: \"" + format +
                                    "\"");
    }

    return result;
}
}  // namespace error

#endif  // __ERROR_HH__
