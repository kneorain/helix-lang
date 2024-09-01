// -*- C++ -*-
//===------------------------------------------------------------------------------------------===//
//
// Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
// You are allowed to use, modify, redistribute, and create derivative works, even for commercial
// purposes, provided that you give appropriate credit, and indicate if changes were made.
// For more information, please visit: https://creativecommons.org/licenses/by/4.0/
//
// SPDX-License-Identifier: CC-BY-4.0
// Copyright (c) 2024 (CC BY 4.0)
//
//===------------------------------------------------------------------------------------------===//

#include <chrono>
#include <memory>
#include <vector>

#include "cli/include/cli.hh"
#include "controllers/include/file_system.hh"
#include "core/error/error.hh"
#include "core/utils/hx_print"
#include "lexer/include/lexer.hh"
#include "parser/preprocessor/include/preprocessor.hh"
#include "token/include/token_list.hh"
#include "parser/ast/include/AST.hh"
#include "parser/cpp/fn_signatures.hh"

int compile(int argc, char **argv) {
    using namespace token;
    using namespace parser::lexer;
    using namespace parser::preprocessor;

    // relative to current working dir in POSIX shell (cmd/bash)
    command_line::CLIArgs parsed_args(argc, argv, "0.0.1-alpha-0112");
    check_exit(parsed_args);

    auto start = std::chrono::high_resolution_clock::now();

    // read the file and tokenize its contents : stage 0
    TokenList tokens = Lexer(file_system::read_file(parsed_args.file), parsed_args.file).tokenize();

    std::vector<string> pkg_paths = {"/Volumes/Container/Projects/Helix/helix-lang/helix/pkgs"};

    // preprocess the tokens with optional module import paths : stage 1
    Preprocessor(tokens, "main", pkg_paths).parse();

    // preprocessor::import_tree->print_tree(preprocessor::import_tree->get_root());

    // print the preprocessed tokens
    auto end = std::chrono::high_resolution_clock::now();

    if (parsed_args.emit_ast) {
        // for testing only change to parse an entire program when done with ast
    
        end = std::chrono::high_resolution_clock::now();

    }

    if (parsed_args.emit_tokens) {
        // print(tokens.to_json());
        print(tokens.to_json());
        print_tokens(tokens);
    }

    std::chrono::duration<double> diff = end - start;

    // Print the time taken in nanoseconds and milliseconds
    print("time taken: ", diff.count() * 1e+9, " ns");
    print("            ", diff.count() * 1000, " ms");

    return 0;
}

int main(int argc, char **argv) {
    try {
        compile(argc, argv);
    } catch (error::Panic&) {
        // if (error::HAS_ERRORED) {
        // for (const auto& err : error::ERRORS) {
        //         print(err.to_json());
        //     }
        // }
    }
}

/*
proposed toolchain:

compile(
    string source,
    compiler_flags flags
)

*/