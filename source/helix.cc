//===------------------------------------------ C++ ------------------------------------------====//
//                                                                                                //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).       //
//  You are allowed to use, modify, redistribute, and create derivative works, even for           //
//  commercial purposes, provided that you give appropriate credit, and indicate if changes       //
//   were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/  //
//                                                                                                //
//  SPDX-License-Identifier: CC-BY-4.0                                                            //
//  Copyright (c) 2024 (CC BY 4.0)                                                                //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//

#include "parser/ast/include/private/AST_nodes.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_modifiers.hh"
#include "parser/ast/include/types/AST_types.hh"

#define _SILENCE_CXX23_ALIGNED_UNION_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifdef MSVC
#pragma comment(linker, "/STACK:2000000000")  // Set stack size to 2MB
#pragma comment(linker, "/HEAP:2000000000")   // Set heap size to 2MB
#endif

#include <chrono>
#include <cstdio>
#include <memory>
#include <vector>

#include "controller/include/Controller.hh"
#include "lexer/include/lexer.hh"
#include "neo-panic/include/error.hh"
#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/AST.hh"
#include "parser/cpp/fn_signatures.hh"
#include "parser/preprocessor/include/preprocessor.hh"
#include "token/include/Token.hh"

int compile(int argc, char **argv) {
    using namespace parser::lexer;
    using namespace parser::preprocessor;

    // relative to current working dir in POSIX shell (cmd/bash)
    __CONTROLLER_CLI_N::CLIArgs parsed_args(argc, argv, "0.0.1-alpha-0112");
    check_exit(parsed_args);

    if (parsed_args.verbose) {
        print(parsed_args.get_all_flags);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // read the file and tokenize its contents : stage 0
    print("tokenizing...", sysIO::endl('\r'));
    __TOKEN_N::TokenList tokens =
        Lexer(__CONTROLLER_FS_N::read_file(parsed_args.file), parsed_args.file).tokenize();

    std::vector<string> pkg_paths = {"/Volumes/Container/Projects/Helix/helix-lang/helix/pkgs"};

    // preprocess the tokens with optional module import paths : stage 1
    print("preprocessing...", sysIO::endl('\r'));
    Preprocessor(tokens, "main", pkg_paths).parse();

    // preprocessor::import_tree->print_tree(preprocessor::import_tree->get_root());

    // print the preprocessed tokens

    if (parsed_args.emit_tokens) {
        // print(tokens.to_json());
        print(tokens.to_json());
        print_tokens(tokens);
    }

    {  // remove all comments form `tokens`
        __TOKEN_N::TokenList new_tokens;

        for (auto &token : tokens) {
            if (token->token_kind() != __TOKEN_N::PUNCTUATION_SINGLE_LINE_COMMENT &&
                token->token_kind() != __TOKEN_N::PUNCTUATION_MULTI_LINE_COMMENT) {
                new_tokens.push_back(token.current().get());
            }
        }

        tokens = new_tokens;  // FIXME: integrate this into the parser
    }

    // generate ast from the given tokens : stage 2
    auto iter = tokens.begin();

    print("parsing...         ", sysIO::endl('\r'));

    parser::ast::NodeV<>       ast;
    parser::ast::ParseResult<> expr;

    while (iter.remaining_n() != 0) {
        print("parsing.. ", sysIO::endl('\r'));
        auto decl = parser::ast::node::Declaration(iter);
        expr      = decl.parse();

        print("parsing.  ", sysIO::endl('\r'));
        if (!expr.has_value()) {
            expr.error().panic();
            print(expr.error().what());

            break;
        }

        ast.emplace_back(expr.value());
        print("Parsing...", sysIO::endl('\r'));
    }

    if (!expr.has_value()) {
        print("aborting...", sysIO::endl('\r'));
    } else {
        print("parsed     ", sysIO::endl('\r'));
    }

    if (parsed_args.emit_ast) {
        std::vector<neo::json> node_json;

        for (auto &node : ast) {
            parser::ast::visitor::Jsonify json_visitor;
            node->accept(json_visitor);
            node_json.push_back(json_visitor.json);
        }

        print(neo::json("ast").add("Decls", node_json).to_string());
    }

    auto                          end  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    if (parsed_args.verbose) {
        // Print the time taken in nanoseconds and milliseconds
        print("time taken: ", diff.count() * 1e+9, " ns");
        print("            ", diff.count() * 1000, " ms");
    }

    return 0;
}

int main(int argc, char **argv) {
    try {
        compile(argc, argv);
    } catch (error::Panic &) {
        if (error::HAS_ERRORED) {
            for (const auto &err : error::ERRORS) {
                print(err.to_json());
            }
        }
    }
}

/*
proposed toolchain:

compile(
    string source,
    compiler_flags flags
)

*/
