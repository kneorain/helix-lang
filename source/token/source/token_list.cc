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
#include "token/include/token_list.hh"
#include "core/types/hx_ints"
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <type_traits>
#include <print>
#include <utility>
#include "core/utils/colors_ansi.hh"
#include "core/utils/josnify.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"
#include <optional>

namespace token {
TokenList::TokenList(std::string filename)
    : filename(std::move(filename))
    , it(this->cbegin()) {}

TokenList::TokenList(const std::string &filename, TokenVec::const_iterator start,
                     TokenVec::const_iterator end)
    : TokenVec(start, end)
    , filename(filename) {}

void TokenList::remove_left() {
    this->erase(this->cbegin(), it);
    it = this->cbegin();
}

void TokenList::reset() { it = this->cbegin(); }

const std::string &TokenList::file_name() const { return filename; }

TokenList TokenList::slice(const std::uint64_t start, std::int64_t end) {
    if (end < 0) {
        end = static_cast<
        std::int64_t
        >(this->size());// - (-end);
    }
    if (end > static_cast<std::int64_t>(this->size())) {
        end = static_cast<std::int64_t>(this->size());
    }

    if (start > end ) {
        throw std::out_of_range("Start of slice is greater than range.");
    }

    difference_type start_index = start;
    difference_type end_index =end;

    return {this->filename, this->cbegin() + start_index, this->cbegin() + end_index };
}

TokenList TokenList::raw_slice(const std::uint64_t start, const std::int64_t end) const {

    auto start_index = static_cast<TokenVec::difference_type>(start);
    auto end_index = static_cast<TokenVec::difference_type>(end);

    return {this->filename, this->cbegin() + start_index, this->cbegin() + end_index};
}

/// @brief 
/// @param i Inclusive split
/// @return first is the left side of the split and the second is the right
std::pair<TokenList,TokenList> TokenList::split_at(const std::uint64_t i) const {
    auto start_idx = static_cast<TokenVec::difference_type>(i);
    TokenList first {this->filename, this ->cbegin(), cbegin() + start_idx};
    TokenList second {
        this->filename, this->cbegin() + start_idx,  this->cend()
    }
    ;
    return {first,second};
    }

    TokenList TokenList::pop( const std::uint64_t offset) {

        auto diff = static_cast<TokenVec::difference_type>(offset);
        *this = {this->filename, this->cbegin() + diff + 1, this->cend()};

        // TODO: Bounds Checks
       return{this->filename, this->cbegin(),this->cbegin() + diff};

}       

   const Token &TokenList::pop_front() {
    if (this->empty()) {
        throw std::out_of_range("Token is not in range");
    }
    const Token& tok = this->front();

    *this = {this->filename,this->cbegin()+1,this->cend()};
    
    return tok;
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

    auto start_it = this->cbegin() + static_cast<TokenVec::difference_type>(start);
    auto end_it = this->cbegin() + static_cast<TokenVec::difference_type>(end);

    this->erase(start_it, end_it);
    this->insert(start_it, tokens.cbegin(), tokens.cend());
}

void print_tokens(token::TokenList &tokens) {
    std::uint16_t indent = 0;

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

// FIXME : This is a temporary fix, need to change this to a  reference
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
    if ((cursor_position) <= end + 1) {
        ++cursor_position;
        return *this;
    }

    throw std::out_of_range("access to token in token list is out of bounds");
}

std::reference_wrapper<Token> TokenList::TokenListIter::advance(const std::int32_t n) {
    if ((cursor_position + n) <= end + 1) {
        ++cursor_position;
    }

    if (n > 1) {
        return advance(n - 1);
    }

    return tokens.get()[cursor_position];
}

std::reference_wrapper<Token> TokenList::TokenListIter::reverse(const std::int32_t n) {
    if ((cursor_position - n) >= 0) {
        --cursor_position;
    }

    if (n > 1) {
        return advance(n - 1);
    }

    return tokens.get()[cursor_position];
}

std::optional<std::reference_wrapper<Token>> TokenList::TokenListIter::peek(const std::int32_t n) const {
    if ((cursor_position + n) <= end) {
        return tokens.get()[cursor_position + n];
    }

    return std::nullopt;
}

std::optional<std::reference_wrapper<Token>> TokenList::TokenListIter::peek_back(const std::int32_t n) const {
    if ((cursor_position - n) >= 0) {
        return tokens.get()[cursor_position - n];
    }

    return std::nullopt;
}

std::reference_wrapper<Token> TokenList::TokenListIter::current() const {
    return tokens.get()[cursor_position];
}

TO_JSON_SIGNATURE_EXTEND(TokenList) {
    std::string result = "{\n" + jsonify::indent(depth + 1) + "\"tokens\" : [\n";

    for (auto &tok : *this) {
        result += tok.to_json(depth + 2, true) + ",\n";
    }

    if (!this->empty()) {
        result.erase(result.size() - 2, 2);
    }

    result += "\n";

    return result + jsonify::indent(depth + 1) + "]\n" + jsonify::indent(depth) + "}\n";
}

}  // namespace token