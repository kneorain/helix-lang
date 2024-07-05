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

#include <chrono>
#include <memory>
#include <vector>

#include "cli/include/cli.hh"
#include "controllers/include/file_system.hh"
#include "core/utils/hx_print"
#include "lexer/include/lexer.hh"
#include "parser/cst/include/cst.hh"
#include "parser/cst/include/nodes.hh"
#include "parser/preprocessor/include/preprocessor.hh"

int main(int argc, char **argv) {
    using namespace token;
    using namespace parser;
    using namespace lexer;

    auto start = std::chrono::high_resolution_clock::now();

    // "D:\projects\helix-lang\tests\main.hlx"
    // std::string file_name = "/Volumes/Container/Projects/Helix/helix-lang/tests/main.hlx"; //
    // relative to current working dir in POSIX shell (cmd/bash)
    command_line::CLIArgs(argc, argv);

    std::string file_name =
        "tests/main.hlx";  // relative to current working dir in Windows shell (cmd/powershell)
    // read the file and tokenize its contents : stage 0
    TokenList tokens = Lexer(file_system::read_file(file_name), file_name).tokenize();

    // preprocess the tokens : stage 1
    Preprocessor(tokens, "main").parse();

    // end the timer and calculate the duration

    // preprocessor::import_tree->print_tree(preprocessor::import_tree->get_root());

    // print the preprocessed tokens
    // print_tokens(tokens);

    auto node =
        std::make_shared<cst::Parentheses<cst::StringLiteral>>(std::make_shared<TokenList>(tokens));

    auto tmp = node->parse();

    cst::CSTNodeList<> list;

    list.push_back(node);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    print(node->to_json());
    print(tokens.to_json());

    // Print the time taken in nanoseconds and milliseconds
    print("time taken: ", diff.count() * 1e+9, " ns");
    print("            ", diff.count() * 1000, " ms");

    return 0;
}