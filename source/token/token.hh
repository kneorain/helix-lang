#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "define.hh"
#include <cassert>
#include <string>
#include <utility>


namespace token {

union TokenType {
    keywords    keyword;
    primitives  primitive;
    operators   operator_;
    literals    literal;
    punctuation punct;
    delimiters  delim;
    identifiers ident;
};

struct Token {
    private:
    TokenType    type;   // type of the token
    discriminant kind;   // kind of the token

    public:
    u32          line;   // line number
    u32          column; // column number
    u16          length; // length of the token
    u64          offset; // offset from the beginning of the file
    string       value;  // value of the token

    Token(u32 line, u32 column, u16 length, u64 offset, std::string value) : line(line), column(column), length(length), offset(offset), value(std::move(value)) {
        if (keywords_map.at(value).has_value()) {
            type.keyword = keywords_map.at(value).value();
            this->kind = discriminant::KEYWORDS;
        } else if (primitives_map.at(value).has_value()) {
            type.primitive = primitives_map.at(value).value();
            this->kind = discriminant::PRIMITIVES;
        } else if (operators_map.at(value).has_value()) {
            type.operator_ = operators_map.at(value).value();
            this->kind = discriminant::OPERATORS;
        } else if (literals_map.at(value).has_value()) {
            type.literal = literals_map.at(value).value();
            this->kind = discriminant::LITERALS;
        } else if (punctuation_map.at(value).has_value()) {
            type.punct = punctuation_map.at(value).value();
            this->kind = discriminant::PUNCTUATION;
        } else if (delimiters_map.at(value).has_value()) {
            type.delim = delimiters_map.at(value).value();
            this->kind = discriminant::DELIMITERS;
        } else {
            type.ident = identifiers::IDENTIFIER;
            this->kind = discriminant::IDENTIFIERS;
        }
    }

    /// use of get_token():
    ///     auto tokenType = token.get_token(); // returns some token type such as keyword::IF
    ///     // can also use for comparison
    ///     if (token.get_kind() == discriminant::KEYWORDS) { // true if token is a keyword
    ///         if (token.get_token<discriminant::KEYWORDS>() == keyword::IF) { // true if token is a keyword and is IF
    ///             // do something
    ///         }
    ///     }
    
    discriminant get_kind() const {
        return kind;
    }

    template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
    T get_token() const {
        switch (kind) {
            case discriminant::KEYWORDS:
                return static_cast<T>(type.keyword);
            case discriminant::PRIMITIVES:
                return static_cast<T>(type.primitive);
            case discriminant::OPERATORS:
                return static_cast<T>(type.operator_);
            case discriminant::LITERALS:
                return static_cast<T>(type.literal);
            case discriminant::PUNCTUATION:
                return static_cast<T>(type.punct);
            case discriminant::DELIMITERS:
                return static_cast<T>(type.delim);
            case discriminant::IDENTIFIERS:
                return static_cast<T>(type.ident);
            default:
                throw std::runtime_error("Invalid token kind");
        }
    }
};

inline void test() {
    Token token(1, 1, 1, 1, "if");
    assert(token.get_kind() == discriminant::KEYWORDS);
    assert(token.get_token<keywords>() == keywords::IF);
}

}

#endif // __TOKEN_H__