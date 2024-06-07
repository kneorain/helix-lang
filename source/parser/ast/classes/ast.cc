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

#include "ast.hh"
#include <optional>

using namespace token;

namespace parser::ast {
/*
void AstBase::parse(std::span<token::Token> tokens) {

    int depth = 0;  // Initialized depth

    for (const Token& token : tokens) {
        using enum Token_e;

        switch (token.GetType()) {
            case OpenCurlyBracket:
            case OpenRoundBracket:
            case OpenAngleBracket:
            case OpenSquareBracket: {

                }
                // Handle other cases if needed
            default: {
                    break;
                }
        }
    }

    return *this;  // Return the current object or adjust based on your actual parsing logic
}
*/

// def

template <AstParse T>
std::expected<std::span<token::Token>, AstError> AstNode<T>::parse(std::span<token::Token> tokens) {
    // Implement parsing logic for AstNode
    return std::unexpected(AstError::Unimplemented);
}

std::expected<std::span<token::Token>, AstError>
AstVariable::parse(std::span<token::Token> tokens) {

    // Implement parsing logic for AstVariable
    return std::unexpected(AstError::Unimplemented);
}

template <AstParse T, AstSegment sep, Separation Type >
std::expected<std::span<token::Token>, AstError>
AstSeparated<T, sep, Type>::parse(std::span<token::Token> tokens) {

    // Implement parsing logic for AstSeparated
    constexpr std::string_view sep_str = sep::make_view();



    if constexpr (Separation::OptionalTrailing == Type) {}

    if constexpr (Separation::Trailing == Type){}
    
    if constexpr (Separation::NoTrailing == Type){}





    
    return std::unexpected(AstError::Unimplemented);
}



template <AstParse T, AstSegment start, AstSegment end>
std::expected<std::span<token::Token>, AstError> AstDelimited<T, start, end>::parse(std::span<token::Token> tokens) {
    // Remove the start
    if (tokens[0].value != start::make_view())
        return std::unexpected(AstError::ExpectedToken);
    
    tokens = tokens.subspan(1);

    T astNode;
    // TODO: need methods to add row and column to the astNode
    std::expected<std::span<token::Token>, AstError> expect = astNode.parse(tokens);
    
    if (expect.has_value()) {
        this->m_children.push_back(astNode);
    } else {
        return expect; 
    }

    // Remove the end
    if (tokens[0].value != end::make_view())
        return std::unexpected(AstError::ExpectedToken);

    
    // Return the remaining tokens
    return tokens.subspan(1);
}

std::expected<std::span<token::Token>, AstError> AstLabel::parse(std::span<token::Token> tokens) {
    // Implement parsing logic for AstLabel
    return std::unexpected(AstError::Unimplemented);
}

std::expected<std::span<token::Token>, AstError>
AstFunctionHeader::parse(std::span<token::Token> tokens) {
    // Implement parsing logic for AstFunctionHeader
    return std::unexpected(AstError::Unimplemented);
}

std::expected<std::span<token::Token>, AstError> AstType::parse(std::span<token::Token> tokens) {
    return std::unexpected(AstError::Unimplemented);
};
}  // namespace parser::ast
