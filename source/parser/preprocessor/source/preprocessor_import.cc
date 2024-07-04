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
#include "parser/preprocessor/include/preprocessor.hh"

#include <algorithm>
#include <string>
#include <vector>

#include "core/error/error.hh"
#include "token/include/generate.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

namespace parser {
void Preprocessor::handle_import_tokens(u32 &brace_level, bool &captured_import,
                                        bool &captured_specific,
                                        std::vector<TokenList> &explicit_imports,
                                        TokenList &import_path, TokenList &current_feature,
                                        TokenList &alias, u32 &import_end) {
    switch (current().token_kind()) {
        case token::IDENTIFIER:
        case token::OPERATOR_SCOPE:
            if (peek().has_value() && peek()->token_kind() == tokens::PUNCTUATION_OPEN_BRACE) {
                break;
            }
            import_path.push_back(current());
            break;

        case token::PUNCTUATION_OPEN_BRACE:
            ++brace_level;
            handle_open_brace_in_import(brace_level, captured_specific, explicit_imports,
                                        current_feature);
            break;

        case token::PUNCTUATION_CLOSE_BRACE:
            --brace_level;
            if (brace_level == 0) {
                captured_specific = true;
            }
            break;

        case token::KEYWORD_AS:
            parse_import_alias(alias, explicit_imports);
            break;

        case token::PUNCTUATION_SEMICOLON:
            import_end = current_pos;
            captured_import = true;
            break;

        default:
            error::Error(error::Line(
                current(), "unexpected token found in import statement `" + current().value() + "'",
                error::ERR, "perhaps forgot a semicolon?"));
            std::exit(1);
            break;
    }
}

void Preprocessor::handle_open_brace_in_import(u32 &brace_level, bool &captured_specific,
                                               std::vector<TokenList> &explicit_imports,
                                               TokenList &current_feature) {
    while (!captured_specific && not_end()) {
        advance();
        switch (current().token_kind()) {
            case token::IDENTIFIER:
            case token::OPERATOR_SCOPE:
                current_feature.push_back(current());
                break;

            case token::PUNCTUATION_COMMA:
                explicit_imports.push_back(current_feature);
                current_feature.clear();
                break;

            case token::PUNCTUATION_OPEN_BRACE:
                error::Error(error::Line(current(), "helix does not support nesting imports",
                                         error::ERR,
                                         "use valid helix import syntax. report this issue on "
                                         "github if it's not already reported."));
                break;

            case token::PUNCTUATION_CLOSE_BRACE:
                --brace_level;
                if (brace_level == 0) {
                    explicit_imports.push_back(current_feature);
                    current_feature.clear();
                    captured_specific = true;
                }
                break;

            default:
                error::Error(error::Line(current(),
                                         "unexpected token found in import statement `" +
                                             current().value() + "'",
                                         error::ERR, "perhaps forgot a semicolon?"));
                break;
        }
    }
}

void Preprocessor::parse_import_alias(TokenList &alias,
                                      const std::vector<TokenList> &explicit_imports) {
    bool captured_alias = false;

    if (peek_back()->token_kind() == token::PUNCTUATION_CLOSE_BRACE &&
        explicit_imports.size() > 1) {
        error::Error(error::Line(
            current(), "cannot alias explicit imports", error::FATAL,
            "only `import ... as ...` allowed, `import ...::{...} as ...` is disallowed."));
        return;
    }

    if (peek_back()->token_kind() != token::IDENTIFIER &&
        peek_back()->token_kind() != token::PUNCTUATION_CLOSE_BRACE) {
        error::Error(
            error::Line(peek_back().value(), "expected to import something to alias", error::ERR,
                        "add the object to import in the import statement before aliasing"));
        return;
    }

    while (!captured_alias && not_end()) {
        advance();
        switch (current().token_kind()) {
            case token::IDENTIFIER:
            case token::OPERATOR_SCOPE:
                alias.push_back(current());
                break;

            case token::PUNCTUATION_SEMICOLON:
                captured_alias = true;
                reverse();
                break;

            default:
                error::Error(error::Line(current(),
                                         "unexpected token found in import statement `" +
                                             current().value() + "'",
                                         error::ERR, "perhaps forgot a semicolon?"));
                break;
        }
    }
}

void Preprocessor::parse_using() {
    auto next_token = peek();
    if (next_token.has_value() && next_token->token_kind() == tokens::LITERAL_STRING &&
        std::find(allowed_abi.begin(), allowed_abi.end(), next_token->value()) !=
            allowed_abi.end()) {
        advance();
        handle_using_abi_imports();
    } else {
        handle_invalid_abi_option(next_token);
    }
}

void Preprocessor::handle_using_abi_imports() {
    if (peek().has_value() && (peek()->token_kind() == tokens::KEYWORD_IMPORT ||
                               peek()->token_kind() == tokens::PUNCTUATION_OPEN_BRACE)) {
        u32 brace_count = 0;
        if (peek()->token_kind() == tokens::PUNCTUATION_OPEN_BRACE) {
            ++brace_count;
        }

        advance();
        bool ended = false;
        while (!ended && not_end()) {
            advance();
            if (peek().has_value()) {
                switch (peek()->token_kind()) {
                    case tokens::PUNCTUATION_OPEN_BRACE:
                        ++brace_count;
                        break;
                    case tokens::PUNCTUATION_CLOSE_BRACE:
                        --brace_count;
                        if (brace_count == 0) {
                            ended = true;
                        }
                        break;
                    case tokens::KEYWORD_IMPORT:
                        if (brace_count == 0) {
                            parse_import_within_using();
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Preprocessor::parse_import_within_using() {
    bool end_of_import = false;
    while (!end_of_import && not_end()) {
        if (peek().has_value() && peek()->token_kind() == tokens::PUNCTUATION_SEMICOLON) {
            end_of_import = true;
        }
        advance();
    }
}

void Preprocessor::handle_invalid_abi_option(const std::optional<Token> &next_token) {
    std::string abi_options;
    for (const std::string &abi : allowed_abi) {
        abi_options += abi + ", ";
    }
    if (!allowed_abi.empty()) {
        abi_options = abi_options.substr(0, abi_options.size() - 2);
    }
    error::Error(error::Line(next_token.value(),
                             "disallowed abi option, abi should only be a string.", error::ERR,
                             "use one of allowed abi options [" + abi_options + "]"));
}
}  // namespace parser