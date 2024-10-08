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

#include <cstddef>
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/ManagedStatic.h"
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
// #include "parser/cpp/fn_signatures.hh"
#include <llvm-18.1.9-src/llvm/include/llvm/TargetParser/Host.h>

#include "llvm-18.1.9-src/clang/include/clang/CodeGen/CodeGenAction.h"
#include "llvm-18.1.9-src/clang/include/clang/Frontend/CompilerInstance.h"
#include "llvm-18.1.9-src/clang/include/clang/Frontend/FrontendActions.h"
#include "llvm-18.1.9-src/clang/include/clang/Lex/PreprocessorOptions.h"
#include "llvm-18.1.9-src/clang/include/clang/Tooling/CommonOptionsParser.h"
#include "llvm-18.1.9-src/clang/include/clang/Tooling/Tooling.h"
#include "llvm-18.1.9-src/llvm/include/llvm/IR/LLVMContext.h"
#include "llvm-18.1.9-src/llvm/include/llvm/IR/LegacyPassManager.h"
#include "llvm-18.1.9-src/llvm/include/llvm/IR/Module.h"
#include "llvm-18.1.9-src/llvm/include/llvm/MC/TargetRegistry.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/FileSystem.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/TargetSelect.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Support/raw_ostream.h"
#include "llvm-18.1.9-src/llvm/include/llvm/Target/TargetMachine.h"
#include "parser/preprocessor/include/preprocessor.hh"
#include "token/include/Token.hh"

// void compile_CXIR(generator::CXIR::CXIR &emitter,
//                   const std::string     &out,
//                   const std::string     &file,
//                   int                    argc,
//                   char                 **argv) {
//     print("starting");
//     llvm::InitLLVM X(argc, argv);
//     print("initialized llvm");

//     // Initialize LLVM components
//     llvm::InitializeAllTargets();
//     print("initialized targets");
//     llvm::InitializeAllTargetMCs();
//     print("initialized target MCs");
//     llvm::InitializeAllAsmParsers();
//     print("initialized asm parsers");
//     llvm::InitializeAllAsmPrinters();

//     clang::CompilerInstance compiler;
//     print("initialized compiler");

//     // Set language options
//     compiler.getLangOpts().CPlusPlus = true;
//     compiler.getLangOpts().LangStd = clang::LangStandard::lang_cxx23;
//     print("set C++ language standard to C++23");

//     // Create diagnostics
//     compiler.createDiagnostics();
//     print("created diagnostics");

//     // Set the target options
//     clang::TargetOptions targetOptions;
//     std::string targetTriple = llvm::sys::getDefaultTargetTriple();
//     print("Default target triple: ", targetTriple);

//     // Fallback if the default target triple is unknown
//     if (targetTriple == "unknown") {
//         targetTriple = "x86_64-pc-linux-gnu";  // Set a known target triple based on platform
//         print("Using fallback target triple: ", targetTriple);
//     }

//     targetOptions.Triple = targetTriple;
//     compiler.setTarget(clang::TargetInfo::CreateTargetInfo(
//         compiler.getDiagnostics(), std::make_shared<clang::TargetOptions>(targetOptions)));
//     print("set target");

//     // Create file manager and source manager
//     compiler.createFileManager();
//     print("created file manager");
//     compiler.createSourceManager(compiler.getFileManager());
//     print("created source manager");

//     // Create preprocessor
//     compiler.createPreprocessor(clang::TranslationUnitKind::TU_Complete);
//     print("created preprocessor");

//     // Set preprocessor and language options again (reaffirm settings)
//     clang::LangOptions &langOpts = compiler.getLangOpts();
//     langOpts.CPlusPlus = true;
//     langOpts.LangStd = clang::LangStandard::lang_cxx23;
//     print("set language options");

//     clang::PreprocessorOptions &ppOpts = compiler.getPreprocessorOpts();
//     ppOpts.RetainRemappedFileBuffers = true;
//     print("set preprocessor options");

//     clang::CodeGenOptions &cgOpts = compiler.getCodeGenOpts();
//     cgOpts.setDebugInfo(llvm::codegenoptions::DebugInfoKind::FullDebugInfo);
//     print("set code generation options");

//     clang::DiagnosticOptions &diagOpts = compiler.getDiagnosticOpts();
//     diagOpts.ShowColors = true;
//     print("set diagnostic options");

//     // Set the input CXIR code and output file
//     std::string cxir_code = emitter.to_CXIR();
//     llvm::StringRef buff_ref(cxir_code);
//     print("set memory buffer");

//     auto buffer = llvm::MemoryBuffer::getMemBuffer(buff_ref, "CXIR");
//     print("created memory buffer");

//     compiler.getSourceManager().setMainFileID(
//         compiler.getSourceManager().createFileID(std::move(buffer)));
//     print("set main file ID");

//     clang::FrontendOptions &frontendOpts = compiler.getFrontendOpts();
//     frontendOpts.OutputFile = out;
//     print("set output file");

//     // Create LLVM context and action
//     llvm::LLVMContext context;

//     print("creating EmitObj action");
//     auto action = std::make_unique<clang::EmitObjAction>(&context);

//     // Set up target machine
//     std::string error;
//     const llvm::Target *target = llvm::TargetRegistry::lookupTarget(targetOptions.Triple, error);

//     if (target == nullptr) {
//         print("Error finding target: ", error);
//         return;
//     }

//     llvm::TargetMachine *targetMachine = target->createTargetMachine(
//         targetOptions.Triple, "", "", llvm::TargetOptions(), llvm::Reloc::PIC_,
//         llvm::CodeModel::Large);

//     if (targetMachine == nullptr) {
//         print("Failed to create target machine");
//         return;
//     }

//     compiler.getCodeGenOpts().PrepareForLTO = true;
//     compiler.setTarget(clang::TargetInfo::CreateTargetInfo(
//         compiler.getDiagnostics(), std::make_shared<clang::TargetOptions>(targetOptions)));
//     print("set target machine");

//     // Execute the compilation action
//     print("invoking compiler");
//     if (!compiler.ExecuteAction(*action)) {
//         print("failed to execute action");
//         return;
//     }

//     print("object file '", out, "' generated successfully!");

//     // Clean up LLVM
//     llvm::llvm_shutdown();
//     print("shut down llvm");
// }

void compile_CXIR(generator::CXIR::CXIR &emitter, const std::string &out, char **argv, size_t argc) {
    /// compile the c++ using an in-memory buffer and invoke clang++
    std::string cxx = emitter.to_CXIR();

    // make a call to system: clang++
    std::string cmd            = std::string("clang++ -x c++ - -c -g -o \"") + out + '"';
    const char *compileCommand = cmd.c_str();

    // Use popen to execute the command and pipe the in-memory C++ code to clang++
    FILE *clangProcess = popen(compileCommand, "w");
    if (clangProcess == nullptr) {
        std::cerr << "failed to run clang++!" << std::endl;
        return;
    }

    // Write the in-memory C++ code to the clang process (as input)
    fputs(cxx.c_str(), clangProcess);
    fflush(clangProcess);  // Ensure all data is flushed

    // Close the process to complete the compilation
    int result = pclose(clangProcess);
    if (result != 0) {
        std::cerr << "compilation failed!" << std::endl;
        return;
    }

    std::cout << "object file '" << out << "' generated successfully!" << std::endl;
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
    print("tokenizing...", sysIO::endl('\n'));
    __TOKEN_N::TokenList tokens =
        parser::lexer::Lexer(__CONTROLLER_FS_N::read_file(in_file_path), in_file_path).tokenize();

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
                   : std::filesystem::path(in_file_path).stem().string();

    #ifdef WIN32
    out_file += ".exe";
    #endif

    std::array<const char *, 5> f_argv{};

    if (parsed_args.build_mode == __CONTROLLER_CLI_N::CLIArgs::MODE::DEBUG_) {
        f_argv = {
        "-std=c++23", "-g", "-O0", "-fno-omit-frame-pointer", "-Wl,-rpath,/usr/local/lib"};
    } else {
        f_argv = {
        "-std=c++23", "-O3", "-fomit-frame-pointer", "-Wl,-rpath,/usr/local/lib"};
    }
    

    compile_CXIR(emitter, out_file, const_cast<char **>(f_argv.data()), f_argv.size());

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
