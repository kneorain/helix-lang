#include <catch2/catch_test_macros.hpp>
#include <string>
#include <string_view>
#include <chrono>

#include "../source/token/token.hh"

using std::string;

#define REQUIRE_DURATION_UNDER_500NS(start, end) \
    REQUIRE_THROWS_AS(std::chrono::duration_cast<std::chrono::nanoseconds>((end) - (start)).count() < 500, std::overflow_error);

inline void check_token(u32 line, u32 column, u16 length, u64 offset, std::string_view value, token::discriminant kind, auto expected,
                 const char *token_str) {
    auto start = std::chrono::high_resolution_clock::now();
    token::Token token(line, column, length, offset, value);
    auto end = std::chrono::high_resolution_clock::now();
    REQUIRE(token.get_kind() == kind);
    REQUIRE(token.get_token<decltype(expected)>() == expected);
    
    REQUIRE_DURATION_UNDER_500NS(start, end);
}

#include <string_view>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include "../source/token/token.hh"

using std::string;

#define REQUIRE_DURATION_UNDER_500NS(start, end) \
    REQUIRE(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < 500);

void check_token(int line, int col, int start, int end, std::string_view text, 
                 token::discriminant kind, auto expected, const char* token_str) {
    auto start_time = std::chrono::high_resolution_clock::now();
    token::Token token(line, col, start, end, text);
    auto end_time = std::chrono::high_resolution_clock::now();
    REQUIRE(token.get_kind() == kind);
    REQUIRE(token.get_token<decltype(expected)>() == expected);
    REQUIRE_DURATION_UNDER_500NS(start_time, end_time);
}

TEST_CASE("Test token::Token constructor", "[token::Token]") {
    SECTION("testing keyword 'if'") {
        check_token(1, 1, 1, 1, std::string_view("if"), token::discriminant::KEYWORDS,
                    token::keywords::IF, "if");
    }
    SECTION("testing keyword 'else'") {
        check_token(1, 1, 1, 1, std::string_view("else"), token::discriminant::KEYWORDS,
                    token::keywords::ELSE, "else");
    }
    SECTION("testing primitive 'int'") {
        check_token(1, 1, 1, 1, std::string_view("int"), token::discriminant::PRIMITIVES,
                    token::primitives::INT, "int");
    }
    SECTION("testing operator '+'") {
        check_token(1, 1, 1, 1, std::string_view("+"), token::discriminant::OPERATORS,
                    token::operators::ADD, "+");
    }
    SECTION("testing identifier 'identifier'") {
        check_token(1, 1, 1, 1, std::string_view("identifier"),
                    token::discriminant::OTHER, token::other::IDENTIFIER, "identifier");
    }
    SECTION("testing operator '=='") {
        check_token(1, 1, 1, 1, std::string_view("=="), token::discriminant::OPERATORS,
                    token::operators::EQUAL, "==");
    }
    SECTION("testing operator '!='") {
        check_token(1, 1, 1, 1, std::string_view("!="), token::discriminant::OPERATORS,
                    token::operators::NOT_EQUAL, "!=");
    }
    SECTION("testing operator '&&'") {
        check_token(1, 1, 1, 1, std::string_view("&&"), token::discriminant::OPERATORS,
                    token::operators::LOGICAL_AND, "&&");
    }
    SECTION("testing identifier '1L'") {
        check_token(1, 1, 1, 1, std::string_view("1L"), token::discriminant::OTHER,
                    token::other::IDENTIFIER, "1L");
    }
    SECTION("testing identifier '1.0F'") {
        check_token(1, 1, 1, 1, std::string_view("1.0F"), token::discriminant::OTHER,
                    token::other::IDENTIFIER, "1.0F");
    }
}