#ifndef __AST_H__
#define __AST_H__

#include <expected>
#include <print>
#include <span>
#include <string_view>

#include "../../../token/include/token.hh"
// token::tokens::...
// token::token_map::at(token::tokens::...) // to get the string representation of the token type

namespace parser::ast {
template <typename T>
concept TokenConcept = requires(T token) {
    { token.make_view() } -> std::same_as<std::string_view>;
};

enum class AstNodeTag : int {};

enum class AstError : int {
    Unimplemented,
    ExpectedToken,
    ExpectedAstNode
};

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

template <AstParse T, TokenConcept sep>
class AstSeparated : public AstNode<T> {
  public:
    AstSeparated() {}
   ~AstSeparated() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

template <AstParse T>
using AstCommaSeparated = AstSeparated<T, token::token_classes::COMMA>;

template <AstParse T, TokenConcept start, TokenConcept end>
class AstDelimited : public AstNode<T> {
  public:
    AstDelimited() {}
   ~AstDelimited() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class AstVariable : public AstBase {
  public:
    AstVariable() {}
   ~AstVariable() {}
    
    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

/** (T,T,...) */
template <AstParse T>
using RoundCommaDelimited  = AstDelimited<AstCommaSeparated<T>, token::token_classes::OPEN_PAREN, token::token_classes::CLOSE_PAREN>;

/** < T,T,...>*/
template <AstParse T>
using AngleCommaDelimited  = AstDelimited<AstCommaSeparated<T>, token::token_classes::OPEN_ANGLE, token::token_classes::CLOSE_ANGLE>;

using CPPAstParameter      = RoundCommaDelimited<AstVariable>;
using CppTemplateArguments = AngleCommaDelimited<AstVariable>;

class AstLabel : public AstBase {
  public:
    AstLabel() {}
   ~AstLabel() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class AstType : public AstBase {
  public:
    AstType() {}
   ~AstType() {}

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class AstFunctionHeader : public AstBase {
  public:
    AstFunctionHeader() {}
   ~AstFunctionHeader() {}

    // AstParameter parameters;
    std::string_view ident;
    AstType    return_type;
    AstLabel    visibility;
    // TODO: templates

    std::expected<std::span<token::Token>, AstError> parse(std::span<token::Token> tokens) override;
};

class Ast {
    // Implementation
};

}  // namespace parser::ast
#endif  // __AST_H__