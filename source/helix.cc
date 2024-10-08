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

// #include "parser/ast/include/private/AST_nodes.hh"
#include <memory>

#include "clang/Basic/LangStandard.h"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"

// #include "parser/ast/include/types/AST_modifiers.hh"
#include "parser/ast/include/types/AST_types.hh"

#define _SILENCE_CXX23_ALIGNED_UNION_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifdef MSVC
#pragma comment(linker, "/STACK:2000000000")  // Set stack size to 2MB
#pragma comment(linker, "/HEAP:2000000000")   // Set heap size to 2MB
#endif

#include <llvm-18.1.9-src/clang/include/clang/Basic/Diagnostic.h>
#include <llvm-18.1.9-src/clang/include/clang/Basic/DiagnosticOptions.h>
#include <llvm-18.1.9-src/clang/include/clang/Basic/FileManager.h>
#include <llvm-18.1.9-src/clang/include/clang/Basic/TargetOptions.h>
#include <llvm-18.1.9-src/clang/include/clang/CodeGen/CodeGenAction.h>
#include <llvm-18.1.9-src/clang/include/clang/Frontend/CompilerInstance.h>
#include <llvm-18.1.9-src/clang/include/clang/Frontend/CompilerInvocation.h>
#include <llvm-18.1.9-src/clang/include/clang/Frontend/TextDiagnosticPrinter.h>
#include <llvm-18.1.9-src/clang/include/clang/Lex/PreprocessorOptions.h>
#include <llvm-18.1.9-src/llvm/include/llvm/ADT/IntrusiveRefCntPtr.h>
#include <llvm-18.1.9-src/llvm/include/llvm/Support/CommandLine.h>
#include <llvm-18.1.9-src/llvm/include/llvm/Support/InitLLVM.h>
#include <llvm-18.1.9-src/llvm/include/llvm/Support/MemoryBuffer.h>
#include <llvm-18.1.9-src/llvm/include/llvm/Support/Path.h>
#include <llvm-18.1.9-src/llvm/include/llvm/TargetParser/Host.h>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
// #include <memory>
// #include <system_error>
#include <vector>

#include "controller/include/Controller.hh"
#include "generator/include/CX-IR/CXIR.hh"
#include "lexer/include/lexer.hh"
// #include "llvm-18.1.9-src/llvm/include/llvm/AsmParser/Parser.h"
// #include "llvm-18.1.9-src/llvm/include/llvm/IR/IRBuilder.h"
// #include "llvm-18.1.9-src/llvm/include/llvm/IR/LLVMContext.h"
// #include "llvm-18.1.9-src/llvm/include/llvm/IR/LegacyPassManager.h"
// #include "llvm-18.1.9-src/llvm/include/llvm/IR/Module.h"
// #include "llvm-18.1.9-src/llvm/include/llvm/IR/Verifier.h"
// #include "llvm-18.1.9-src/llvm/include/llvm/MC/TargetRegistry.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/CodeGen.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/ErrorOr.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/FileSystem.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/SourceMgr.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/TargetSelect.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/raw_ostream.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Target/TargetMachine.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Target/TargetOptions.h"
#include "neo-panic/include/error.hh"
#include "neo-pprint/include/hxpprint.hh"
// #include "parser/ast/include/AST.hh"
// #include "parser/cpp/fn_signatures.hh"
#include "parser/preprocessor/include/preprocessor.hh"
// #include "token/include/Token.hh"

void compile_CXIR(generator::CXIR::CXIR &emitter,
                  const std::string     &out,
                  const std::string     &file,
                  int                    argc,
                  char                 **argv) {
    print("starting");
    llvm::InitLLVM X(argc, argv);
    print("initialized llvm");
    llvm::InitializeAllTargets();
    print("initialized targets");
    llvm::InitializeAllTargetMCs();
    print("initialized target MCs");
    llvm::InitializeAllAsmParsers();
    print("initialized asm parsers");
    llvm::InitializeAllAsmPrinters();

    clang::CompilerInstance compiler;
    print("initialized compiler");
    clang::CompilerInvocation::CreateFromArgs(
        compiler.getInvocation(),
        {"-std=c++23", "-g", "-O0", "-fno-omit-frame-pointer", "-Wl,-rpath,/usr/local/lib"},
        compiler.getDiagnostics());

    // Set the input file and output file by using a MemoryBufferRef
    print("setting input file");
    std::unique_ptr<llvm::MemoryBuffer> buffer =
        llvm::MemoryBuffer::getMemBuffer(emitter.to_CXIR());

    if (!buffer) {
        print("failed to create memory buffer!");
        return;
    }

    print("created memory buffer");
    llvm::MemoryBufferRef buff_ref = llvm::MemoryBufferRef(buffer->getBuffer(), file);

    print("set memory buffer");
    compiler.getFrontendOpts().Inputs.push_back(clang::FrontendInputFile(
        buff_ref, clang::InputKind(Language::CXX, clang::InputKind::Source)));

    print("set input file");
    compiler.getFrontendOpts().OutputFile = out;

    // Invoke the compiler (action depends on what you want, e.g. EmitObj)
    std::unique_ptr<clang::FrontendAction> action = std::make_unique<clang::EmitObjAction>();
 
    print("set output file");
    // Execute the action
    compiler.ExecuteAction(*action);
}

// void compile_CXIR(generator::CXIR::CXIR &emitter, const std::string &out) {
//     /// compile the c++ using an in-memory buffer and invoke clang++
//     std::string cxx = emitter.to_CXIR();

//     // make a call to system: clang++
//     std::string cmd = std::string("clang++ -x c++ - -c -g -o \"") + out + '"';
//     const char* compileCommand = cmd.c_str();

//     // Use popen to execute the command and pipe the in-memory C++ code to clang++
//     FILE* clangProcess = popen(compileCommand, "w");
//     if (clangProcess == nullptr) {
//         std::cerr << "failed to run clang++!" << std::endl;
//         return;
//     }

//     // Write the in-memory C++ code to the clang process (as input)
//     fputs(cxx.c_str(), clangProcess);
//     fflush(clangProcess); // Ensure all data is flushed

//     // Close the process to complete the compilation
//     int result = pclose(clangProcess);
//     if (result != 0) {
//         std::cerr << "compilation failed!" << std::endl;
//         return;
//     }

//     std::cout << "object file '" << out << "' generated successfully!" << std::endl;
// }

int compile(int argc, char **argv) {
    // relative to current working dir in POSIX shell (cmd/bash)
    __CONTROLLER_CLI_N::CLIArgs parsed_args(argc, argv, "0.0.1-alpha-2012");
    check_exit(parsed_args);

    if (parsed_args.verbose) {
        print(parsed_args.get_all_flags);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // read the file and tokenize its contents : stage 0
    print("tokenizing...", sysIO::endl('\n'));
    __TOKEN_N::TokenList tokens =
        parser::lexer::Lexer(__CONTROLLER_FS_N::read_file(parsed_args.file), parsed_args.file)
            .tokenize();

    std::vector<string> pkg_paths = {"/Volumes/Container/Projects/Helix/helix-lang/helix/pkgs"};

    // preprocess the tokens with optional module import paths : stage 1
    print("preprocessing...", sysIO::endl('\n'));
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

    print("parsing...         ", sysIO::endl('\n'));

    parser::ast::NodeV<>       ast;
    parser::ast::ParseResult<> expr;

    while (iter.remaining_n() != 0) {
        print("parsing.. ", sysIO::endl('\n'));
        auto decl = parser::ast::node::Declaration(iter);
        expr      = decl.parse();

        print("parsing.  ", sysIO::endl('\n'));
        if (!expr.has_value()) {
            expr.error().panic();
            print(expr.error().what());

            break;
        }

        ast.emplace_back(expr.value());
        print("Parsing...", sysIO::endl('\n'));
    }

    if (!expr.has_value()) {
        print("aborting...", sysIO::endl('\n'));
    } else {
        print("parsed     ", sysIO::endl('\n'));
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
        print("emitting CX-IR...", sysIO::endl('\n'));

        print(emitter.to_readable_CXIR());
    }

    std::string out_file;

    out_file = (parsed_args.output_file.has_value())
                   ? parsed_args.output_file.value()
                   : std::filesystem::path(parsed_args.file).stem().string();
    const std::array<const char*, 5> f_argv = {"-std=c++23", "-g", "-O0", "-fno-omit-frame-pointer", "-Wl,-rpath,/usr/local/lib"};
    compile_CXIR(emitter, out_file, parsed_args.file, f_argv.size(), const_cast<char**>(f_argv.data()));

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
