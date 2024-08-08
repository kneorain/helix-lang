/**
 * @author Dhruvan Kartik
 * @date 2024
 * @copyright Copyright (c) 2024 (CC BY 4.0)
 *
 * @brief Defines error handling structures and classes for the Helix Language Project.
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
#include "core/error/error.hh"

#include <array>
#include <format>
#include <iomanip>
#include <optional>
#include <tuple>
#include <vector>

#include "controllers/include/file_system.hh"
#include "core/utils/colors_ansi.hh"
#include "core/utils/hx_print"
#include "parser/ast/include/ast.hh"
#include "token/include/token.hh"

/**
 @namespace error
 * @brief Contains classes and functions related to error handling and reporting.
 */
namespace error {
using line_type = std::pair<bool, std::tuple<string, string, bool>>;
using lines_vec = std::vector<line_type>;

template <typename T>
class Reverse {
  public:
    explicit Reverse(T &container)
        : container_(container) {}

    auto begin() const { return container_.rbegin(); }
    auto end() const { return container_.rend(); }

  private:
    T &container_;
};

static inline void lstrip(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(),
                                        [](unsigned char chr) { return std::isspace(chr) == 0; }));
}

// Trim from the end (in place)
static inline void rstrip(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(),
                           [](unsigned char chr) { return std::isspace(chr) == 0; })
                  .base(),
              str.end());
}

// Trim from both ends (in place)
static inline void strip(std::string &str) {
    lstrip(str);
    rstrip(str);
}

// Check if a string is empty or contains only whitespace
bool is_empty_or_whitespace(const std::string &str) {
    std::string trimmed = str;
    strip(trimmed);
    return trimmed.empty();
}

string bold_red(const string &str) {
    return string(colors::effects::bold) + string(colors::fg16::red) + str + string(colors::reset);
};

string bold_green(const string &str) {
    return string(colors::effects::bold) + string(colors::fg16::green) + str +
           string(colors::reset);
};

string bold_yellow(const string &str) {
    return string(colors::effects::bold) + string(colors::fg16::yellow) + str +
           string(colors::reset);
};

string red(const string &str) { return string(colors::fg16::red) + str + string(colors::reset); };

string green(const string &str) {
    return string(colors::fg16::green) + str + string(colors::reset);
};

string yellow(const string &str) {
    return string(colors::fg16::yellow) + str + string(colors::reset);
};

string format_loc_info(const string &file_name, u64 line, u64 col) {
    return green(file_name) + ":" + yellow(std::to_string(line)) + ":" +
           yellow(std::to_string(col));
};

lines_vec get_surrounding_lines(const string &file_name, u64 line) {
    // if odd number, get even amount of lines behind and after
    // if even number, get -1 lines before and same amount of lines after

    // calculate lines to get before

    u64 lines_before = (LINES_TO_SHOW % 2 == 0) ? (LINES_TO_SHOW / 2) - 1 : (LINES_TO_SHOW / 2);
    lines_vec lines;  // {bool : (string, string, bool)}

    u64 start_line = (line <= lines_before) ? 1 : (line - lines_before);

    for (u64 i = start_line; i < start_line + LINES_TO_SHOW; ++i) {
        auto line_content = file_system::get_line(file_name, i);
        if (line_content.has_value()) {
            lines.emplace_back(
                false, std::make_tuple(std::to_string(i), line_content.value(), i == line));
        } else {
            break;
        }
    }

    // remove blank lines from either side

    for (auto &line : lines) {
        if (std::get<2>(line.second)) {
            break;  // we have marked discard for the part before the error line
        }

        if (is_empty_or_whitespace(std::get<1>(line.second))) {
            line.first = true;  // set discard to true
        } else {
            break;
        }
    }

    for (auto &line : Reverse(lines)) {
        if (std::get<2>(line.second)) {
            break;  // we have marked discard for the part after the error line
        }

        if (is_empty_or_whitespace(std::get<1>(line.second))) {
            line.first = true;  // set discard to true
        } else {
            break;
        }
    }

    // remove all the elements marked for discard from 'lines' of type
    // std::vector<std::pair<bool, std::tuple<string, string, bool>>>
    // aka {discard : (line_no, line, is_err_line)}

    lines.erase(std::remove_if(lines.begin(), lines.end(),
                                [](const auto &line) {
                                    return line.first;  // discard is true
                                }),
                lines.end());

    return lines;
};

// pop the first elemnt from teh vec and insert it into the string and add the len of the fix to the rest of the cols
void insert_and_reorder(string& line, std::vector<std::pair<string, u32>>& quick_fix) {
    std::pair<string, u32> fix;

    if (!quick_fix.empty()) {
        fix = quick_fix[0];
        quick_fix.erase(quick_fix.begin());
    }

    for (auto &fixes : quick_fix) {
        fixes.second += fix.first.size();
    }

    for (int i = 0; i < fix.first.size(); i++) {
        line.insert((line.begin() + fix.second + i), fix.first[i]);
    }
}

// colors and adds quick fixes to line itself and returns the marking lines
string color_and_mark(line_type& line_typ, u64 col, u64 len, std::vector<std::pair<string, u32>> quick_fix = {}) {
    string line_no = std::get<0>(line_typ.second);
    string line    = std::get<1>(line_typ.second);
    bool   is_pof  = std::get<2>(line_typ.second);
    
    string marking;
    marking.reserve(line.size());

    std::sort(quick_fix.begin(), quick_fix.end(), [](const auto& first, const auto& second) {
        return first.second < second.second;
    }); // sort the quick_fix based on the loc

    rstrip(line); // remove any trailing whitespace on the left side only

    if (quick_fix.empty()) {
        goto mark_line;
    }

    // else if there are quick_fixes

    for (auto &fixes : quick_fix) {
        fixes.first = green(fixes.first);
    }

    // line = ffi "c++" import "hi_there"
    // quick_fix = [(";", -1)]
    

mark_line:

    
    return "";
}

Error::Error(const CodeError &err) {
    HAS_ERRORED = true;

    final_err.color_mode = "16bit";
    final_err.error_type = "code";

    switch (ERROR_MAP.at(err.err_code)->level) {
        case NOTE:
            final_err.level = "note";
            break;
        case WARN:
            final_err.level = "warn";
            break;
        case ERR:
            final_err.level = "error";
            break;
        case FATAL:
            final_err.level = "fatal";
            break;
    }

    final_err.file = err.pof->file_name();

    final_err.msg = ERROR_MAP.at(err.err_code)->err;
    if (err.err_fmt_args.has_value() && !err.err_fmt_args->empty()) {
        final_err.msg = fmt_string(ERROR_MAP.at(err.err_code)->err, err.err_fmt_args.value());
    }

    final_err.fix = ERROR_MAP.at(err.err_code)->fix;
    if (err.fix_fmt_args.has_value() && !err.fix_fmt_args->empty()) {
        final_err.fix = fmt_string(ERROR_MAP.at(err.err_code)->fix, err.fix_fmt_args.value());
    }

    final_err.line = err.pof->line_number();
    final_err.col = err.pof->column_number();
    final_err.offset = err.pof->length();

    if (err.opt_fixes.has_value()) {
        for (const auto &fix_pos_pair : err.opt_fixes.value()) {
            final_err.quick_fix.emplace_back((fix_pos_pair.first.value() == fix_pos_pair.first.token_kind_repr() ? fix_pos_pair.first.token_kind_repr() : fix_pos_pair.first.value()),
                                             calculate_addition_pos(fix_pos_pair.second));
        }
    }

    ERRORS.push_back(final_err);

    if (SHOW_ERROR) {
        show_error();
    }
}

Error::Error(const CompilerError &err) {
    HAS_ERRORED = true;

    final_err.color_mode = "16bit";
    final_err.error_type = "compiler";

    switch (ERROR_MAP.at(err.err_code)->level) {
        case NOTE:
            final_err.level = "note";
            break;
        case WARN:
            final_err.level = "warn";
            break;
        case ERR:
            final_err.level = "error";
            break;
        case FATAL:
            final_err.level = "fatal";
            break;
    }

    final_err.msg = ERROR_MAP.at(err.err_code)->err;
    if (err.err_fmt_args.has_value() && !err.err_fmt_args->empty()) {
        final_err.msg = fmt_string(ERROR_MAP.at(err.err_code)->err, err.err_fmt_args.value());
    }

    final_err.fix = ERROR_MAP.at(err.err_code)->fix;
    if (err.fix_fmt_args.has_value() && !err.fix_fmt_args->empty()) {
        final_err.fix = fmt_string(ERROR_MAP.at(err.err_code)->fix, err.fix_fmt_args.value());
    }

    final_err.line = 0;
    final_err.col = 0;
    final_err.offset = 0;

    ERRORS.push_back(final_err);
}

void Error::process_full_line() {
    auto full_line = file_system::get_line(final_err.file, final_err.line);

    if (!full_line.has_value()) {
        // TODO: throw error
        std::exit(288);
    }

    while (true) {
        if (full_line->empty()) {
            break;
        }

        if (full_line->ends_with(' ')) {
            full_line->erase(full_line->end());
        } else {
            break;
        }
    }

    final_err.full_line = full_line.value();
}

u32 Error::calculate_addition_pos(i64 pos) const {
    if (pos < 0) {
        pos = static_cast<i64>(final_err.full_line.size() - 1 /* remove term */) + pos;
    }

    return static_cast<u32>(pos);
}

void Error::show_error() {
    /*
    fatal: missing semicolon
         ├─>  at tests/main.hlx:1:18
       1 │ ffi "c++" import "hi_there";
         :                  ^^^^^^^^^^+
       2 │
       3 │
       4 │
       5 │ const cols: int = 14;
      fix: insert a semi-colon

    fatal: missing semicolon
         ├─>  at tests/main.hlx:1:18
       1 │ ffi "c++" import "hi_there"
         :                  ++++++++++
       2 │
       3 │
       4 │
       5 │ const cols: int = 14;
      fix: insert a semi-colon
    */
    
    lines_vec lines = get_surrounding_lines(final_err.file, final_err.line);
    string markings;

    for (auto line : lines) {
        if (std::get<2>(line.second)) {
            markings = color_and_mark(line, final_err.col, final_err.offset, final_err.quick_fix);
        }
    }

    print(final_err.to_json());


}
}  // namespace error

#undef LINES_TO_SHOW