#include "error.hh"

#include <iomanip>
#include <iostream>

#include "../colors_ansi.hh"

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
    print_start(error.message, error.level);
    print_info(error.message, error.file_name, error.line_number, error.column, error.offset);
    print_lines({}, error.line_number, error.column, error.offset);
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
        std::cout << std::string(colors::fg16::cyan) << "note";
        break;
    case WARN:
        std::cout << std::string(colors::fg16::yellow) << "warning";
        break;
    case ERR:
        std::cout << std::string(colors::fg16::red) << "error";
        break;
    case FATAL:
        std::cout << std::string(colors::fg16::red) << std::string(colors::bold) << "fatal";
        break;
    }

    if (!file_name.empty()) {
        std::cout << std::string(colors::reset) << "at " << std::string(colors::fg16::green)
                  << file_name << std::string(colors::reset);
    }
    std::cout << ": " << std::string(colors::reset) << message << '\n';
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
              << "├─> " << std::string(colors::reset) << "at " << std::string(colors::fg16::green)
              << file_name << std::string(colors::reset) << ":" << std::string(colors::fg16::yellow)
              << line + 1 << std::string(colors::reset) << ":" << std::string(colors::fg16::yellow)
              << col + 1 << std::string(colors::reset) << '\n';
}

/**
 * @brief Prints the lines of code surrounding the error location.
 * @param lines The lines of code.
 * @param line The line number where the error occurred.
 * @param col The column number where the error occurred.
 * @param offset The offset where the error occurred.
 */
void Error::print_lines(const std::vector<std::string> &lines, const u32 &line, const u32 &col,
                        const u32 &offset) {
    for (u32 i = 0; i < lines.size(); i++) {
        if (i == line) {
            std::cout << std::setw(4) << (i + 1) << " "
                      << ": " << std::string(colors::reset) << lines[i] << '\n';
            std::cout << "     "
                      << "│ " << std::string(colors::reset) << std::string(col, ' ')
                      << std::string(colors::fg16::yellow) << std::string(offset, '^')
                      << std::string(colors::reset) << '\n';
        } else {
            std::cout << std::setw(4) << (i + 1) << " "
                      << "│ " << std::string(colors::reset) << lines[i] << '\n';
        }
    }
}

/**
 * @brief Prints the fix message for the error, if available.
 * @param fix_message The fix message.
 * @param col The column number where the error occurred.
 * @param offset The offset where the error occurred.
 */
void Error::print_fix(const std::string_view fix_message, const u32 &col, const u32 &offset) {
    std::cout << "  " << std::string(colors::fg16::green) << "fix" << std::string(colors::reset)
              << ": " << fix_message << '\n';
}

/**
 * @brief Prints a message indicating that no fix is available for the error.
 */
void Error::print_no_fix() {
    std::cout << "  " << std::string(colors::fg16::gray) << "fix" << std::string(colors::reset)
              << ": "
              << "unable to retrieve fix information" << '\n';
}
}  // namespace error
