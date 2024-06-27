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
#include <include/error/error.hh>

#include <array>
#include <iomanip>
#include <iostream>
#include <optional>

#include <include/colors_ansi.hh>
#include <tools/controllers/include/file_system.hh>

/**
 @namespace error
 * @brief Contains classes and functions related to error handling and reporting.
 */
namespace error {
/**
 * @brief Constructs an Error object with the given error information.
 * @param error The error information.
 */
Error::Error(const Line &error) {
    if (error.file_name.starts_with("<") && error.file_name.ends_with(">")) {
        print_start(error.message, error.level);
        print_info(error.message, error.file_name, error.line_number, error.column, error.offset);
        return;
    }
    
    std::array<std::optional<std::string>, LINES_TO_SHOW> lines;
    file_system::get_line(error.file_name, error.line_number);

    u32 half_lines_to_show = u32(LINES_TO_SHOW / 2);
    u32 start_index =
        (error.line_number < half_lines_to_show) ? 1 : (error.line_number - half_lines_to_show);

    u8 index = 0;
    for (u32 i = start_index; (i - start_index) < LINES_TO_SHOW; i++) {
        lines[index] = file_system::get_line(error.file_name, i);
        ++index;
    }

    if (lines[LINES_TO_SHOW].has_value() && lines[LINES_TO_SHOW].value().empty()) {
        lines[LINES_TO_SHOW] = std::nullopt;
    }

    // std::cout << "file_name: " << error.file_name << "\n"
    //           << "line_number: " << error.line_number << "\n"
    //           << "column: " << error.column << "\n"
    //           << "offset: " << error.offset << "\n"
    //           << "message: " << error.message << "\n"
    //           << "level: " << error.level << "\n"
    //           << "fix: " << error.fix << "\n";

    print_start(error.message, error.level);
    print_info(error.message, error.file_name, error.line_number, error.column, error.offset);
    print_lines(lines, start_index, error.line_number, error.column, error.offset);

    if (!error.fix.empty()) {
        print_fix(error.fix, error.column, error.offset);
    } else {
        print_no_fix();
    }
}

/**
 * @brief Constructs an Error object with the given message and level.
 * @param message The error message.
 * @param level The level of the error.
 */
Error::Error(const std::string &message, const Level &level) { print_start(message, level); }

/**
 * @brief Constructs an Error object with the given compiler information.
 * @param compiler The compiler information.
 */
Error::Error(const Compiler &compiler) {
    print_start(compiler.message, compiler.level, compiler.file_name);
    if (!compiler.fix.empty()) {
        print_fix(compiler.fix, 0, 0);
    } else {
        print_no_fix();
    }
}

/**
 * @brief Prints the start of the error message, including the level and file name if provided.
 * @param message The error message.
 * @param level The level of the error.
 * @param file_name The name of the file where the error occurred.
 */
void Error::print_start(const std::string_view message, const Level &level,
                        const std::string_view file_name) {
    switch (level) {
        case NOTE:
            std::cout << std::string(colors::fg8::cyan) << std::string(colors::effects::bold) << "note";
            break;
        case WARN:
            std::cout << std::string(colors::fg8::yellow) << std::string(colors::effects::bold) << "warning";
            break;
        case ERR:
            std::cout << std::string(colors::fg8::red) << std::string(colors::effects::bold) << "error";
            break;
        case FATAL:
            std::cout << std::string(colors::fg8::red) << std::string(colors::effects::blink) << std::string(colors::bold) << "fatal";
            break;
    }

    if (!file_name.empty()) {
        std::cout << std::string(colors::reset) << " at " << std::string(colors::fg8::green)
                  << file_name << std::string(colors::reset);
    }
    std::cout << std::string(colors::reset) << ": " << message << '\n';
}

/**
 * @brief Prints additional information about the error, such as file name, line number, and column.
 * @param message The error message.
 * @param file_name The name of the file where the error occurred.
 * @param line The line number where the error occurred.
 * @param col The column number where the error occurred.
 * @param offset The offset where the error occurred.
 */
void Error::print_info(const std::string_view message, const std::string_view file_name,
                       const u32 &line, const u32 &col, const u32 &offset) {
    std::cout << "     "
              << "├─> " << std::string(colors::reset) << " at " << std::string(colors::fg8::green)
              << file_name << std::string(colors::reset) << ":" << std::string(colors::fg8::yellow)
              << line << std::string(colors::reset) << ":" << std::string(colors::fg8::yellow)
              << col + 1 << std::string(colors::reset) << '\n';
}

/**
 * @brief Prints the lines of code surrounding the error location.
 * @param lines The lines of code.
 * @param line The line number where the error occurred.
 * @param col The column number where the error occurred.
 * @param offset The offset where the error occurred.
 */
void Error::print_lines(const std::array<std::optional<std::string>, LINES_TO_SHOW> &lines,
                        const u32 &start_index, const u32 &error_line, const u32 &col,
                        const u32 &offset) {
    u32 index = start_index;

    for (auto line : lines) {
        if (index != error_line) {
            if (line.has_value()) {
                std::cout << std::setw(4) << index << " "
                          << "│ " << std::string(colors::reset) << line.value() << "\n";
            }
        } else {
            if (line.has_value()) {
                print_line(line.value(), error_line, col, offset);
            }
        }

        ++index;
    }

    std::cout << "\n";
}

void Error::print_line(const std::string &line, const u32 &line_number, const u32 &col,
                       const u32 &offset) {
    std::cout << std::setw(4) << line_number << " "
              << "│ " << std::string(colors::reset) << line.substr(0, col)
              << std::string(colors::fg8::red) << line.substr(col, offset)
              << std::string(colors::reset) << line.substr(offset + col) << "\n";
    std::cout << "     "
              << ": " << std::string(colors::reset) << std::string(col, ' ')
              << std::string(colors::fg8::red) << std::string(offset, '^')
              << std::string(colors::reset) << '\n';
}

/**
 * @brief Prints the fix message for the error, if available.
 * @param fix_message The fix message.
 * @param col The column number where the error occurred.
 * @param offset The offset where the error occurred.
 */
void Error::print_fix(const std::string_view fix_message, const u32 &col, const u32 &offset) {
    std::cout << "  " << std::string(colors::fg8::green) << "fix" << std::string(colors::reset)
              << ": " << fix_message << '\n';
}

/**
 * @brief Prints a message indicating that no fix is available for the error.
 */
void Error::print_no_fix() { std::cout << '\n'; }
}  // namespace error

#undef LINES_TO_SHOW