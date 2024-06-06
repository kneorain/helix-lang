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

template <AstParse T, TokenConcept sep>
std::expected<std::span<token::Token>, AstError>
AstSeparated<T, sep>::parse(std::span<token::Token> tokens) {

    // Implement parsing logic for AstSeparated
    static std::string_view sep_str = sep::MakeView();
    return std::unexpected(AstError::Unimplemented);
}

template <AstParse T, TokenConcept start, TokenConcept end>
std::expected<std::span<token::Token>, AstError>
AstDelimited<T, start, end>::parse(std::span<token::Token> tokens) {
    static std::string_view start_str = start::MakeView();
    static std::string_view end_str = end::MakeView();

    if (tokens[0].value != start_str)
        return std::unexpected(AstError::ExpectedToken);

    tokens = tokens.subspan(1);

    while (true) {

        T t;

        auto exp = t.parse(tokens);

        if (exp) {

            this->m_children.PushBack(tokens);

            if (tokens.first().GetSubTokensAsStr() == sep)
                tokens = tokens.subspan(1);
            else
                break;

        } else
            return exp;
    }
    // fn params can be empty
    /*if (this->m_children.IsEmpty()) {


    }*/
    if () {};

    if (tokens[0].value != end_str)
        return std::nullopt;

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
