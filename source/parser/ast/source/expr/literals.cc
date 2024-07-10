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
#include <expected>
#include <string>
#include "core/utils/hx_print"
#include "core/utils/josnify.hh"
#include "parser/ast/include/ast.hh"
#include "parser/ast/include/expr_nodes.hh"
#include "token/include/generate.hh"

parser::ast::ParseResult parser::ast::node::Literals::parse() {
    // linearly parse out any literal
    for (auto &tok : *source_tokens) {
        switch (tok->token_kind()) {
            case tokens::LITERAL_FALSE:
            case tokens::LITERAL_TRUE:
                type = LiteralType::BOOL;
                break;
            
            case tokens::LITERAL_CHAR:
                type = LiteralType::CHAR;

                if ((tok->value().size() - 3) > 1) {
                    return std::unexpected(ParseError(tok.current().get(), 1.020));
                }
                break;

            case tokens::LITERAL_STRING:
                type = LiteralType::STRING;
                break;
            
            case tokens::LITERAL_NULL:
                type = LiteralType::NONE;
                break;

            case tokens::LITERAL_FLOATING_POINT:
                type = LiteralType::FLOAT;
                break;

                if ((tok->value().contains('e') || tok->value().contains('E')) && (tok->value().contains('-') || tok->value().contains('+'))) {
                    type = LiteralType::SCIENTIFIC;
                }
                break;

            case tokens::LITERAL_INTEGER:
                type = LiteralType::INTEGER;

                if ((tok->value().contains('e') || tok->value().contains('E')) && (tok->value().contains('-') || tok->value().contains('+'))) {
                    type = LiteralType::SCIENTIFIC;
                }
                break;

            default:
                print(tok.current().get().to_json());
                return std::unexpected(ParseError(tok.current().get(), 1.010));
        }

        if (type != LiteralType::INVALID) {
            value = tok.current().get();
            break;
        }
    }

    return 1; // since the size would never be greater then 1.
}

std::string parser::ast::node::Literals::to_json(u32 depth) const {
    // value
    // type
    std::string result = jsonify::indent(depth) + "\"Literals\" : {\n"
                       + jsonify::indent(depth+1) + "\"type\" : ";

    switch (this->type) {
        case LiteralType::INVALID:
            result += "\"invalid\",\n";
            break;
        case LiteralType::INTEGER:
            result += "\"integer\",\n";
            break;
        case LiteralType::SCIENTIFIC:
            result += "\"scientific\",\n";
            break;
        case LiteralType::FLOAT:
            result += "\"float\",\n";
            break;
        case LiteralType::STRING:
            result += "\"string\",\n";
            break;
        case LiteralType::BOOL:
            result += "\"bool\",\n";
            break;
        case LiteralType::CHAR:
            result += "\"char\",\n";
            break;
        case LiteralType::NONE:
            result += "\"none\",\n";
            break;
    }

    return result + jsonify::indent(depth+1) + "\"value\" : " + this->value.to_json(depth+1) + "\n" + jsonify::indent(depth) + "}";
}