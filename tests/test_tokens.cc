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

#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <string>
#include <string_view>

#include <../source/token/include/lexer.hh>

using std::string;

TEST_CASE("Test token::Token constructor", "[token::Token]") {
    SECTION("testing keyword 'if'") {
        token::Token token = token::Token(1, 1, 2, 0, "if");

        REQUIRE(token.line_number()   == 1);
        REQUIRE(token.column_number() == 1);
        REQUIRE(token.length()        == 2);
        REQUIRE(token.offset()        == 0);
        REQUIRE(token.token_kind()    == token::tokens::KEYWORD_IF);
        REQUIRE(token.value()         == "if");
    }
}