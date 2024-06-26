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

#ifndef __TOKEN_HH__
#define __TOKEN_HH__
#include <include/inttypes.hh>
#include <iostream>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <token/include/generate.hh>
#include <vector>

namespace token {

/**
 * @brief Structure representing a token in the source code.
 */
struct Token {
  private:
    u32 line{};                     ///< Line number where the token is located
    u32 column{};                   ///< Column number where the token starts
    u32 len{};                      ///< Length of the token
    u32 _offset{};                  ///< Offset from the beginning of the file
    tokens kind{};                  ///< Kind of the token
    std::string val;                ///< String value of the token
    std::string filename;           ///< Name of the file
    mutable std::shared_mutex mtx;  ///< Mutex for thread safety

  public:
    /**
     * @brief Constructs a Token with the specified attributes.
     *
     * @param line Line number where the token is located.
     * @param column Column number where the token starts.
     * @param length Length of the token.
     * @param offset Offset from the beginning of the file.
     * @param value String value of the token.
     * @param token_kind Optional kind of the token as a string view.
     */
    Token(u64 line, u64 column, u64 length, u64 offset, std::string_view value,
          const std::string &filename, std::string_view token_kind = "");

    /**
     * @brief Copy constructor.
     *
     * @param other Token to copy from.
     */
    Token(const Token &other);

    /**
     * @brief Copy assignment operator.
     *
     * @param other Token to copy from.
     * @return Reference to the current object.
     */
    Token &operator=(const Token &other);

    /**
     * @brief Move constructor.
     *
     * @param other Token to move from.
     */
    Token(Token &&other) noexcept;

    /**
     * @brief Move assignment operator.
     *
     * @param other Token to move from.
     * @return Reference to the current object.
     */
    Token &operator=(Token &&other) noexcept;

    /**
     * @brief Default constructor that initializes the token to whitespace.
     */
    Token();

    explicit Token(tokens token_type, const std::string &filename, std::string value = "");

    /**
     * @brief Destructor.
     */
    ~Token();

    /* ====-------------------------- getters ---------------------------==== */

    /**
     * @brief Gets the line number where the token is located.
     *
     * @return Line number.
     */
    u64 line_number() const;

    /**
     * @brief Gets the column number where the token starts.
     *
     * @return Column number.
     */
    u64 column_number() const;

    /**
     * @brief Gets the length of the token.
     *
     * @return Length of the token.
     */
    u64 length() const;

    /**
     * @brief Gets the offset from the beginning of the file.
     *
     * @return Offset from the beginning of the file.
     */
    u64 offset() const;

    /**
     * @brief Gets the kind of the token.
     *
     * @return Kind of the token.
     */
    tokens token_kind() const;

    /**
     * @brief Gets the string value of the token.
     *
     * @return String value of the token.
     */
    std::string value() const;

    /**
     * @brief Gets the kind of the token as a string view.
     *
     * @return Kind of the token as a string view.
     */
    std::string_view token_kind_repr() const;

    /**
     * @brief Gets the filename of the token.
     *
     * @return Filename.
     */
    std::string_view file_name() const;

    // as string and ostream

    std::string to_string() const {
        return std::string("Token(") + std::string("line: ") + std::to_string(line) +
               std::string(", column: ") + std::to_string(column) + std::string(", len: ") +
               std::to_string(len) + std::string(", offset: ") + std::to_string(_offset) +
               std::string(", kind: ") + std::string(token_kind_repr()) + std::string(", val: ") +
               std::string(val) + ")";
    }

    std::ostream &operator<<(std::ostream &os) const { return os << to_string(); }

    /* ====-------------------------- setters ---------------------------==== */

    /**
     * @brief Sets the filename of where the token belongs.
     *
     * @param value String file name.
     */
    void set_file_name(const std::string &file_name);

    bool operator==(const Token &rhs) const {
        return (line == rhs.line && column == rhs.column && len == rhs.len &&
                _offset == rhs._offset && kind == rhs.kind && val == rhs.val &&
                filename == rhs.filename);
    }
};

/**
 * @brief Class representing a list of tokens.
 */
class TokenList : public std::vector<Token> {
  private:
    std::string filename;
    TokenList(std::string filename, std::vector<Token>::const_iterator start,
              std::vector<Token>::const_iterator end);

  public:
    using std::vector<Token>::vector;  // Inherit constructors
    using const_iterator = std::vector<Token>::const_iterator;

    mutable const_iterator it;

    TokenList() = default;

    /**
     * @brief Constructs a TokenList with the specified filename.
     *
     * @param filename Name of the file.
     */
    explicit TokenList(std::string filename);

    /**
     * @brief Gets the next token in the list.
     *
     * @return Next token.
     */
    Token next(u32 n = 1) const;

    /**
     * @brief Peeks at the current token in the list without advancing the iterator.
     *
     * @return Current token.
     */
    [[nodiscard]] Token peek(u32 n = 1) const;

    /**
     * @brief Gets the current token in the list.
     *
     * @return Current token.
     */
    [[nodiscard]] Token current() const;

    /**
     * @brief Gets a constant iterator to the beginning of the token list.
     *
     * @return Constant iterator to the beginning.
     */
    [[nodiscard]] std::vector<Token>::const_iterator begin() const {
        return std::vector<Token>::begin();
    }

    /**
     * @brief Gets a constant iterator to the end of the token list.
     *
     * @return Constant iterator to the end.
     */
    [[nodiscard]] std::vector<Token>::const_iterator end() const {
        return std::vector<Token>::end();
    }

    /**
     * @brief Gets the previous token in the list.
     *
     * @return Previous token.
     */
    [[nodiscard]] Token previous(u32 n = 1) const;

    /**
     * @brief Removes tokens from the beginning of the list up to the current iterator position.
     */
    void remove_left();

    /**
     * @brief Resets the iterator to the beginning of the token list.
     */
    void reset();

    /**
     * @brief Appends a token to the end of the token list.
     *
     * @param token Token to append.
     */
    void append(const Token &token);

    /**
     * @brief Slices the token list from the start index to the end index.
     *
     * @param start Start index.
     * @param end End index.
     * @return Sliced token list.
     */
    TokenList slice(u64 start, u64 end);

    [[nodiscard]] bool reached_end() const;

    /**
     * @brief Gets the filename of the token list.
     *
     * @return Filename.
     */
    [[nodiscard]] std::string file_name() const;

    /**
     * @brief Replaces tokens in the list from start to end with the provided tokens.
     *
     * This function removes tokens from the specified start index up to, but not including,
     * the end index, and then inserts the tokens from the provided TokenList at the start index.
     *
     * @param tokens TokenList to insert.
     * @param start Start index of the range to remove.
     * @param end End index of the range to remove.
     */
    void insert_remove(TokenList &tokens, u64 start, u64 end);

    bool operator==(const TokenList &rhs) const {
        // First, compare sizes
        if (size() != rhs.size()) {
            return false;
        }

        // Then, compare each element
        for (size_t i = 0; i < size(); ++i) {
            if (at(i) != rhs.at(i)) {  // Assuming Token has operator==
                return false;
            }
        }

        return true;
    }
};

/**
 * @brief Prints the tokens in the provided token list.
 *
 * @param tokens Token list to be printed.
 */
void print_tokens(token::TokenList &tokens);

}  // namespace token

#endif  // __TOKEN_HH__