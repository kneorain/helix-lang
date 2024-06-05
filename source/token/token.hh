/// Part of the Helix Language Project
/// (c) 2024 The Helix Team
/// This code is licensed under the MIT License.

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <algorithm>
#include <cassert>
#include <string>
#include <string_view>
#include <variant>

#include "../include/inttypes.hh"
#include "./enums/delimiters.hh"
#include "./enums/keywords.hh"
#include "./enums/literals.hh"
#include "./enums/operators.hh"
#include "./enums/others.hh"
#include "./enums/primitives.hh"
#include "./enums/punctuation.hh"
#include "./include/define.hh"

namespace token {

/**
 * @brief Union representing the different possible types of a token.
 */
union TokenType {
    keywords keyword;      ///< Keyword token type
    primitives primitive;  ///< Primitive token type
    operators operator_;   ///< Operator token type
    literals literal;      ///< Literal token type
    punctuation punct;     ///< Punctuation token type
    delimiters delim;      ///< Delimiter token type
    other ident;           ///< Other token type (identifier)
};

/**
 * @brief Structure representing a token in the source code.
 */
struct Token {
  private:
    std::variant<keywords, primitives, operators, literals, punctuation, delimiters, other>
        type;           ///< Variant holding the specific type of the token
    discriminant kind;  ///< Discriminant indicating the kind of token

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
        : line(line), column(column), length(length), offset(offset), value(value) {
        auto check_and_set_kind = [this](const auto &map, std::string_view value, auto kind_value) -> bool {
            auto type_opt = map.at(value);
            if (type_opt.has_value()) {
                type = type_opt.value();
                this->kind = kind_value;
                return true;
            }
            return false;
        };

        if (check_and_set_kind(keywords_map, value, discriminant::KEYWORDS) ||
            check_and_set_kind(primitives_map, value, discriminant::PRIMITIVES) ||
            check_and_set_kind(operators_map, value, discriminant::OPERATORS) ||
            check_and_set_kind(punctuation_map, value, discriminant::PUNCTUATION) ||
            check_and_set_kind(delimiters_map, value, discriminant::DELIMITERS)) {
            return;
        }
    }

    /**
     * @brief Gets the specific token type.
     *
     * @tparam T The type to retrieve from the variant.
     * @return The specific type of the token.
     *
     * @note Example usage:
     * @code
     * auto tokenType = token.get_token(); // returns some token type such as keyword::IF
     * if (token.get_kind() == discriminant::KEYWORDS) { // true if token is a keyword
     *     if (token.get_token<discriminant::KEYWORDS>() == keyword::IF) { // true if token is
     *     a keyword and is IF
     *         // do something
     *     }
     * }
     * @endcode
     */
    template <typename T>
    [[nodiscard]] T get_token() const noexcept {
        return std::get<T>(type);
    }

    /**
     * @brief Gets the kind of the token.
     *
     * @return The discriminant indicating the kind of the token.
     */
    [[nodiscard]] discriminant get_kind() const noexcept { return kind; }
};
}  // namespace token

#endif  // __TOKEN_H__
