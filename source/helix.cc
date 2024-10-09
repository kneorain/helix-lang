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

#include "controller/include/config/Controller_config.def"
#include "controller/include/shared/file_system.hh"
#include "llvm/Support/CodeGen.h"
#define _SILENCE_CXX23_ALIGNED_UNION_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifdef MSVC
#pragma comment(linker, "/STACK:2000000000")  // Set stack size to 2MB
#pragma comment(linker, "/HEAP:2000000000")   // Set heap size to 2MB
#endif
#include <chrono>
#include <cstdlib>
#include <vector>

#include "controller/include/Controller.hh"
#include "generator/include/CX-IR/CXIR.hh"
#include "lexer/include/lexer.hh"
#include "neo-panic/include/error.hh"
#include "neo-pprint/include/hxpprint.hh"
#include "parser/ast/include/AST.hh"
#include "parser/cpp/fn_signatures.hh"
#include "parser/preprocessor/include/preprocessor.hh"
#include "token/include/Token.hh"

void compile_CXIR(generator::CXIR::CXIR &emitter, const std::string &out, bool is_debug = false) {
    /// compile the c++ using an in-memory buffer and invoke clang++
    std::string cxx = emitter.to_CXIR();

    std::filesystem::path path = __CONTROLLER_FS_N::get_cwd();
    std::ofstream file(path / "_H1HJA9ZLO_17.helix-compiler.cc");

    if (!file) {
        print("error creating _H1HJA9ZLO_17.helix-compiler.cc file");
        goto cleanup;
    }

    {
        file << cxx;
        file.close();

        std::string cmd = std::string("c++ -std=c++23 ") + (is_debug ? "-g" : "") +
                          " -O0 -fno-omit-frame-pointer -Wl,-w,-rpath,/usr/local/lib " +
                          (path / "_H1HJA9ZLO_17.helix-compiler.cc").string() + " -o " + (path / out).string();

        const char *compileCommand = cmd.c_str();

        if (system(compileCommand) != 0) {
            print("compilation failed");
            goto cleanup;
        }

        std::cout << "compiled to " << path / out << std::endl;
    }

cleanup:
    std::filesystem::remove(path / "_H1HJA9ZLO_17.helix-compiler.cc");
}

int compile(int argc, char **argv) {
    // relative to current working dir in POSIX shell (cmd/bash)
    __CONTROLLER_CLI_N::CLIArgs parsed_args(argc, argv, "0.0.1-alpha-2012");
    check_exit(parsed_args);

    if (parsed_args.verbose) {
        print(parsed_args.get_all_flags);
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto in_file_path = __CONTROLLER_FS_N::normalize_path(parsed_args.file);

    // read the file and tokenize its contents : stage 0
    print("tokenizing...", sysIO::endl('\r'));
    __TOKEN_N::TokenList tokens =
        parser::lexer::Lexer(__CONTROLLER_FS_N::read_file(in_file_path), in_file_path).tokenize();

    std::vector<string> pkg_paths = {"/Volumes/Container/Projects/Helix/helix-lang/helix/pkgs"};

    // preprocess the tokens with optional module import paths : stage 1
    print("preprocessing...", sysIO::endl('\r'));
    parser::preprocessor::Preprocessor(tokens, "main", pkg_paths).parse();

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

    generator::CXIR::CXIR emitter;

    for (auto &node : ast) {
        node->accept(emitter);
    }

    if (parsed_args.emit_ir) {
        print("emitting CX-IR...", sysIO::endl('\r'));

        if (parsed_args.verbose) {
            print(colors::fg16::green, emitter.to_CXIR(), colors::reset);
        } else {
            print(emitter.to_readable_CXIR());
        }
    }

    std::string out_file;

    out_file = (parsed_args.output_file.has_value())
                   ? parsed_args.output_file.value()
                   : std::filesystem::path(in_file_path).stem().string();

    compile_CXIR(
        emitter, out_file, parsed_args.build_mode == __CONTROLLER_CLI_N::CLIArgs::MODE::DEBUG_);

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
