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
#include <functional>
#include <iostream>
#include <stdexcept>

#include "core/utils/colors_ansi.hh"
#include "core/utils/josnify.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

namespace token {
TokenList::TokenList(std::string filename)
    : filename(std::move(filename))
    , it(this->cbegin()) {}

TokenList::TokenList(const std::string &filename, std::vector<Token>::const_iterator start,
                     std::vector<Token>::const_iterator end)
    : std::vector<Token>(start, end)
    , filename(filename) {}

void TokenList::remove_left() {
    this->erase(this->cbegin(), it);
    it = this->cbegin();
}

void TokenList::reset() { it = this->cbegin(); }

const std::string &TokenList::file_name() const { return filename; }

TokenList TokenList::slice(u64 start, i64 end) {
    if (end < 0) {
        end = i64(this->size()) - (-end);
    }

    if (end > i64(this->size())) {
        end = i64(this->size());
    }

    auto start_index = static_cast<std::vector<Token>::difference_type>(start);
    auto end_index = static_cast<std::vector<Token>::difference_type>(end);

    return {this->filename, this->cbegin() + start_index, this->cbegin() + end_index};
}

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
void TokenList::insert_remove(TokenList &tokens, u64 start, u64 end) {
    if (start > end || end > this->size()) {
        throw std::out_of_range("Invalid start or end index");
    }

    auto start_it = this->cbegin() + static_cast<std::vector<Token>::difference_type>(start);
    auto end_it = this->cbegin() + static_cast<std::vector<Token>::difference_type>(end);

    this->erase(start_it, end_it);
    this->insert(start_it, tokens.cbegin(), tokens.cend());
}

void print_tokens(token::TokenList &tokens) {
    u16 indent = 0;

    for (auto &tok : tokens) {
        if (tok->value() == "{") {
            indent++;
        } else if (tok->value() == "}") {
            indent--;
        }
        if (tok->token_kind() == token::tokens::PUNCTUATION_SEMICOLON ||
            tok->token_kind() == token::tokens::PUNCTUATION_OPEN_BRACE ||
            tok->token_kind() == token::tokens::PUNCTUATION_CLOSE_BRACE ||
            tok->token_kind() == token::tokens::PUNCTUATION_SINGLE_LINE_COMMENT) {
            if (tok->token_kind() != token::tokens::PUNCTUATION_CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red
                          << token::tokens_map.at(tok->token_kind()).value() << colors::reset
                          << ", " << colors::fg16::green << tok->value() << colors::reset << ") ";
            }

            std::cout << "\n";
            std::cout << std::string(static_cast<u16>(indent * 4), ' ');

            if (tok->token_kind() == token::tokens::PUNCTUATION_CLOSE_BRACE) {
                std::cout << "(" << colors::fg16::red
                          << token::tokens_map.at(tok->token_kind()).value() << colors::reset
                          << ", " << colors::fg16::green << tok->value() << colors::reset << ") ";
            }

            continue;
        }
        std::cout << "(" << colors::fg16::red << token::tokens_map.at(tok->token_kind()).value()
                  << colors::reset << ", " << colors::fg16::green << tok->value() << colors::reset
                  << ") ";
    }

    std::cout << "\n";
}

bool TokenList::operator==(const TokenList &rhs) const {
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

bool TokenList::TokenListIter::operator!=(const TokenListIter &other) const {
    return cursor_position != other.cursor_position;
}

bool TokenList::TokenListIter::operator==(const TokenListIter &other) const {
    return cursor_position == other.cursor_position;
}

// FIXME : This is a temporary fix, need to change this to a a reference
Token *TokenList::TokenListIter::operator->() {
    return &tokens.get()[cursor_position];
}  // TODO: change if a shared ptr is needed

TokenList::TokenListIter &TokenList::TokenListIter::operator*() { return *this; }

std::reference_wrapper<TokenList::TokenListIter> TokenList::TokenListIter::operator--() {
    if ((cursor_position - 1) >= 0) {
        --cursor_position;
        return *this;
    }

    throw std::out_of_range("access to token in token list is out of bounds");
}

std::reference_wrapper<TokenList::TokenListIter> TokenList::TokenListIter::operator++() {
    if ((cursor_position + 1) <= end) {
        ++cursor_position;
        return *this;
    }

    throw std::out_of_range("access to token in token list is out of bounds");
}

std::reference_wrapper<Token> TokenList::TokenListIter::advance(int n) {
    if ((cursor_position + n) <= end) {
        ++cursor_position;
    }

    if (n > 1) {
        return advance(n - 1);
    }

    return tokens.get()[cursor_position];
}

std::reference_wrapper<Token> TokenList::TokenListIter::reverse(int n) {
    if ((cursor_position - n) >= 0) {
        --cursor_position;
    }

    if (n > 1) {
        return advance(n - 1);
    }

    return tokens.get()[cursor_position];
}

std::optional<std::reference_wrapper<Token>> TokenList::TokenListIter::peek(int n) {
    if ((cursor_position + n) <= end) {
        return tokens.get()[cursor_position + n];
    }

    return std::nullopt;
}

std::optional<std::reference_wrapper<Token>> TokenList::TokenListIter::peek_back(int n) {
    if ((cursor_position - n) >= 0) {
        return tokens.get()[cursor_position - n];
    }

    return std::nullopt;
}

std::reference_wrapper<Token> TokenList::TokenListIter::current() {
    return tokens.get()[cursor_position];
}

TO_JSON_SIGNATURE_EXTEND(TokenList) {
    std::string result = "{\n"
    + jsonify::indent(depth+1) + "\"tokens\" : [\n";

    for (auto &tok : *this) {
        result += tok.to_json(depth+2, true) + ",\n";
    }

    if (!this->empty()) {
        result.erase(result.size() - 2, 2);
    }

    result += "\n";

    return result + jsonify::indent(depth+1) + "]\n" + jsonify::indent(depth) + "}\n";
}

}  // namespace token