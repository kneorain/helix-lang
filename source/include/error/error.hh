/**
 * @file error.h
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

#ifndef __ERROR_H__
#define __ERROR_H__

#include <print>
#include <string>
#include <vector>

#include "../inttypes.hh"

namespace error {

/**
 * @enum Level
 * @brief Enumeration representing the level of an error.
 */
enum Level {
    NOTE,   ///< Informational note.
    WARN,   ///< Warning level.
    ERR,    ///< Error level.
    FATAL,  ///< Fatal error level.
};

/**
 * @struct Line
 * @brief Represents an error occurring at a specific line in a file.
 */
struct Line {
    std::string file_name;  ///< Name of the file where the error occurred.
    u32 line_number;        ///< Line number of the error.
    u32 column;             ///< Column number of the error.
    u32 offset;             ///< Offset within the line.
    std::string message;    ///< Error message.

    Level level = ERR;  ///< Error level.
    std::string fix;    ///< Suggested fix message.
};

/**
 * @struct Compiler
 * @brief Represents a compiler error.
 */
struct Compiler {
    std::string file_name;  ///< Name of the file where the error occurred.
    std::string message;    ///< Error message.
    Level level = ERR;      ///< Error level.
    std::string fix;        ///< Suggested fix message.
};

/**
 * @class Error
 * @brief Class for handling and printing errors.
 */
class Error {
  public:
    /**
     * @brief Default constructor.
     */
    Error() = default;

    /**
     * @brief Constructor for a Line error.
     * @param error The Line error to handle.
     */
    explicit Error(const Line &error);

    /**
     * @brief Constructor for a message with a specified level.
     * @param message The error message.
     * @param level The level of the error.
     */
    Error(const std::string &message, const Level &level);

    /**
     * @brief Constructor for a Compiler error.
     * @param compiler The Compiler error to handle.
     */
    explicit Error(const Compiler &compiler);

  private:
    /**
     * @brief Prints the start of the error message.
     * @param message The error message.
     * @param level The level of the error.
     * @param file_name (Optional) The name of the file where the error occurred.
     */
    static void print_start(std::string_view message, const Level &level,
                            std::string_view file_name = "");

    /**
     * @brief Prints information about the error.
     * @param message The error message.
     * @param file_name The name of the file where the error occurred.
     * @param line The line number of the error.
     * @param col The column number of the error.
     * @param offset The offset within the line.
     */
    static void print_info(std::string_view message, std::string_view file_name, const u32 &line,
                           const u32 &col, const u32 &offset);

    /**
     * @brief Prints the lines surrounding the error.
     * @param lines The lines of code.
     * @param line The line number of the error.
     * @param col The column number of the error.
     * @param offset The offset within the line.
     */
    static void print_lines(const std::vector<std::string> &lines, const u32 &line, const u32 &col,
                            const u32 &offset);

    /**
     * @brief Prints the suggested fix for the error.
     * @param fix_message The fix message.
     * @param col The column number of the error.
     * @param offset The offset within the line.
     */
    static void print_fix(std::string_view fix_message, const u32 &col, const u32 &offset);

    /**
     * @brief Prints a message indicating no fix information is available.
     */
    static void print_no_fix();
};

}  // namespace error

#endif  // __ERROR_H__
