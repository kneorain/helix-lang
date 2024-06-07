#include "ast.hh"
#include <optional>


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

template <AstParse T, TokenConcept sep, SeparationTypeConcept Type >
std::expected<std::span<token::Token>, AstError>
AstSeparated<T, sep, Type>::parse(std::span<token::Token> tokens) {

    // Implement parsing logic for AstSeparated
    constexpr std::string_view sep_str = sep::make_view();

    
    return std::unexpected(AstError::Unimplemented);
}

template <AstParse T, TokenConcept start, TokenConcept end>
std::expected<std::span<token::Token>, AstError>
AstDelimited<T, start, end>::parse(std::span<token::Token> tokens) {
    static std::string_view start_str = start::make_view();
    static std::string_view end_str = end::make_view();

    if (tokens[0].value != start_str)
        return std::unexpected(AstError::ExpectedToken);

    tokens = tokens.subspan(1);

    T t;

    auto exp = t.parse(tokens);

    // fn params can be empty
    // todo make an enum for empty or non empty requirements 
   /* if (this->m_children.IsEmpty()) {


    }
    if () {};

    if (tokens[0].value != end_str)
        return std::nullopt;*/

    return std::unexpected(AstError::Unimplemented);
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
