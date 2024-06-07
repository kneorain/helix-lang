#ifndef __AST_H__
#define __AST_H__

#include <expected>
#include <print>
#include <span>
#include <string_view>

#include "../../../token/include/token.hh"
using namespace token;
// token::tokens::...
// token::token_map::at(token::tokens::...) // to get the string representation of the token type

namespace parser::ast {
template <typename T>
concept AstSegment = requires(T token) {
    { token.make_view() } -> std::same_as<std::string_view>;
};

enum class AstNodeTag : int {};

enum class AstError : int { Unimplemented, ExpectedToken, ExpectedAstNode };

class AstBase {
  public:
    // AstNodeTag m_tag;

    AstBase() {};
    virtual ~AstBase() {}

    virtual std::expected<std::span<token::Token>, AstError>
    parse(std::span<token::Token> tokens) = 0;
};

template <class T>
concept AstParse = requires(T t, std::span<token::Token> tokens) {
    { t.parse(tokens) } -> std::same_as<std::expected<std::span<token::Token>, AstError>>;
};

template <AstParse T>
class AstNode : public AstBase {
  public:
    AstNode() {}
    ~AstNode() {}

    virtual std::expected<std::span<token::Token>, AstError>
    parse(std::span<token::Token> tokens) override = 0;

    inline T get_children() const { return this->m_children; }

  protected:
    std::vector<T> m_children{};
};

// ---------------------------------------------- Seperated

enum Separation { Trailing, OptionalTrailing, NoTrailing };

/**
 *
 * @tparam T
 * @tparam sep
 * @tparam Type This can either be SeparationType::Trailing, SeparationType::OptionalTrailing or
 * SeparationType::NoTrailing
 */
template <AstParse T, AstSegment sep, Separation Type>
class AstSeparated : public AstNode<T> {
  public:
    AstSeparated() = default;
    ~AstSeparated() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

// make concept that does same as for seperation type enum that does or

template <AstParse T>
using AstCommaSeparated = AstSeparated<T, classes::COMMA, Separation::OptionalTrailing>;

template <AstParse T>
using AstSemiColonSeparated = AstSeparated<T, classes::SEMICOLON, Separation::NoTrailing>;

// ---------------------------------------------- Delimited

template <AstParse T, AstSegment start, AstSegment end>
class AstDelimited : public AstNode<T> {
  public:
    AstDelimited() = default;
    ~AstDelimited() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

/** (T) **/
template <AstParse T>
using ParenDelimited = AstDelimited<T, classes::OPEN_PAREN, classes::CLOSE_PAREN>;

/** <T> **/
template <AstParse T>
using AngleDelimited = AstDelimited<T, classes::OPEN_ANGLE, classes::CLOSE_ANGLE>;

/** [T] **/
template <AstParse T>
using BracketDelimited = AstDelimited<T, classes::OPEN_BRACKET, classes::CLOSE_BRACKET>;

/** {T} **/
template <AstParse T>
using BraceDelimited = AstDelimited<T, classes::OPEN_BRACE, classes::CLOSE_BRACE>;

/** <T, T, ...> **/
template <AstParse T>
using CommaSeparatedAngleDelimited = AngleDelimited<AstCommaSeparated<T>>;

/** (T, T, ...) **/
template <AstParse T>
using CommaSeparatedParenDelimited = ParenDelimited<AstCommaSeparated<T>>;

/** [T, T, ...] **/
template <AstParse T>
using CommaSeparatedBracketDelimited = BracketDelimited<AstCommaSeparated<T>>;

/** {T, T, ...} **/
template <AstParse T>
using CommaSeparatedBraceDelimited = BraceDelimited<AstCommaSeparated<T>>;

//using CPPAstParameter = RoundCommaDelimited<AstVariable>;
//using CppTemplateArguments = AngleCommaDelimited<AstVariable>;

class AstVariable : public AstBase {
  public:
    AstVariable() = default;
    ~AstVariable() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class AstLabel : public AstBase {
  public:
    AstLabel() = default;
    ~AstLabel() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class AstType : public AstBase {
  public:
    AstType() = default;
    ~AstType() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class AstFunctionHeader : public AstBase {
  public:
    AstFunctionHeader() = default;
    ~AstFunctionHeader() {}

    // AstParameter parameters;
    std::string_view ident;
    AstType return_type;
    AstLabel visibility;
    // TODO: templates

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class Ast {
    // Implementation
};

}  // namespace parser::ast
#endif  // __AST_H__