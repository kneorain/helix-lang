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

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <cassert>
#include <string>
#include <string_view>

#include "../../include/inttypes.hh"
#include "./generate.hh"


namespace token {
/**
 * @brief Structure representing a token in the source code.
 */
struct Token {
  private:
    
  public:
    u32 line;           ///< Line number where the token is located
    u32 column;         ///< Column number where the token starts
    u16 length;         ///< Length of the token
    u64 offset;         ///< Offset from the beginning of the file
    std::string value;  ///< String value of the token

    /**
     * @brief Constructs a Token with the specified attributes.
     *
     * @param line Line number where the token is located.
     * @param column Column number where the token starts.
     * @param length Length of the token.
     * @param offset Offset from the beginning of the file.
     * @param value String value of the token.
     */
    Token(u32 line, u32 column, u16 length, u64 offset, std::string_view value)
        : line(line)
        , column(column)
        , length(length)
        , offset(offset)
        , value(value) {
        
    }
};
}  // namespace token

#endif  // __TOKEN_H__
