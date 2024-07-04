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
#ifndef __PARSER_HH__
#define __PARSER_HH__

#include <iostream>
#include <memory>

#include "parser/cst/include/cst.hh"
#include "parser/cst/include/nodes.hh"
#include "token/include/token.hh"
#include "token/include/token_list.hh"

namespace parser {
class CSTParser {
    explicit CSTParser(token::TokenList tokens);
};
}  // namespace parser

#endif  // __PARSER_HH__