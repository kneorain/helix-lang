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

#include <glaze-json/include/glaze/glaze.hpp>

#include "controller/include/config/Controller_config.def"
#include "controller/include/shared/file_system.hh"
#include "parser/ast/include/private/base/AST_base.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"
#include "token/include/private/Token_base.hh"

#define _SILENCE_CXX23_ALIGNED_UNION_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifdef MSVC
#pragma comment(linker, "/STACK:2000000000")  // Set stack size to 2MB
#pragma comment(linker, "/HEAP:2000000000")   // Set heap size to 2MB
#endif

#include <array>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <neo-panic/include/error.hh>
#include <neo-pprint/include/hxpprint.hh>
#include <string>
#include <vector>

#include "controller/include/Controller.hh"
#include "generator/include/CX-IR/CXIR.hh"
#include "lexer/include/lexer.hh"
#include "parser/preprocessor/include/preprocessor.hh"

enum class LogLevel { Debug, Info, Warning, Error };
inline bool NO_LOGS  = false;
inline bool LSP_MODE = false;

template <LogLevel l, typename... Args>
void log(Args &&...args) {
    if (NO_LOGS) {
        return;
    }

    if constexpr (l == LogLevel::Debug) {
        print(std::string(colors::fg16::gray),
              "debug: ",
              std::string(colors::reset),
              std::forward<Args>(args)...);
    } else if constexpr (l == LogLevel::Info) {
        print(std::string(colors::fg16::green),
              "info: ",
              std::string(colors::reset),
              std::forward<Args>(args)...);
    } else if constexpr (l == LogLevel::Warning) {
        print(std::string(colors::fg16::yellow),
              "warning: ",
              std::string(colors::reset),
              std::forward<Args>(args)...);
    } else if constexpr (l == LogLevel::Error) {
        print(std::string(colors::fg16::red),
              "error: ",
              std::string(colors::reset),
              std::forward<Args>(args)...);
    } else {
        print(std::forward<Args>(args)...);
    }
}

class CXIRCompiler {
  public:
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    template <typename T>
    struct ExecResult {
        T   output;
        int return_code{};
    };
    template <typename T>
    [[nodiscard]] ExecResult<T> exec(const std::string &cmd) const;
#else
    struct ExecResult {
        std::string output;
        int         return_code{};
    };
    [[nodiscard]] static ExecResult exec(const std::string &cmd) {
        std::array<char, 128> buffer;
        std::string           result;

        auto *pipe = popen(cmd.c_str(), "r");  // get rid of shared_ptr

        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }

        while (feof(pipe) == 0) {
            if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
                result += buffer.data();
            }
        }

        auto rc = pclose(pipe);

        if (rc == EXIT_SUCCESS) {
            return {result, 0};
        }

        return {result, 1};
    }
#endif

    void compile_CXIR(generator::CXIR::CXIR &emitter,
                      const std::string     &out,
                      bool                   is_debug   = false,
                      bool                   is_verbose = false) const {
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        compile_CXIR_Windows(emitter, out, is_debug);
#else
        compile_CXIR_NonWindows(emitter, out, is_debug, is_verbose);
#endif
    }

  private:
    void compile_CXIR_Windows(generator::CXIR::CXIR &emitter,
                              const std::string     &out,
                              bool                   is_debug) const {
        std::string           cxx  = emitter.to_CXIR();
        std::filesystem::path path = __CONTROLLER_FS_N::get_cwd();
        std::error_code       ec;
        std::filesystem::path source_file =
            std::filesystem::temp_directory_path(ec) / "_H1HJA9ZLO_17.helix-compiler.cc";
        std::ofstream file(source_file);

        if (ec) {
            log<LogLevel::Error>("creating temporary file: ", ec.message());
            return;
        }

        if (!file) {
            log<LogLevel::Error>("creating ", source_file.string());
            return;
        }

        file << cxx;
        file.close();

        {
            std::string vswhere_cmd =
                R"("C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath)";
            auto vs_result = exec(vswhere_cmd);

            if (vs_result.return_code != 0 || vs_result.output.empty()) {
                log<LogLevel::Error>("visual studio not found or vswhere failed");
                goto cleanup;
            }

            std::string vs_path = vs_result.output;
            vs_path.erase(vs_path.find_last_not_of(" \n\r\t") + 1);

            if (!std::filesystem::exists(vs_path)) {
                log<LogLevel::Error>("visual studio path not found at " + vs_path);
                goto cleanup;
            }

            std::filesystem::path msvc_tools_path =
                std::filesystem::path(vs_path) / "VC" / "Auxiliary" / "Build" / "vcvars64.bat";

            if (!std::filesystem::exists(msvc_tools_path)) {
                log<LogLevel::Error>("msvc environment setup script not found at " +
                                     msvc_tools_path.string());
                goto cleanup;
            }

            std::string compile_cmd = "cmd.exe /c \"";
            compile_cmd += "call \"" + msvc_tools_path.string() + "\" >nul 2>&1 && ";
            compile_cmd += "cl /std:c++latest ";                  // Use C++23
            compile_cmd += is_debug ? "/Zi " : "/O2 ";            // Debug or Release
            compile_cmd += "/EHsc ";                              // Enable C++ exceptions
            compile_cmd += "/Fe:" + (path / out).string() + " ";  // Output file
            compile_cmd += "\"" + source_file.string() + "\"";    // Source file
            compile_cmd += "\"";

            ExecResult compile_result = exec(compile_cmd);

            if (compile_result.return_code != 0) {
                log<LogLevel::Error>("compilation failed with return code " +
                                     std::to_string(compile_result.return_code));
                log<LogLevel::Error>("compiler output:\n" + compile_result.output);
                goto cleanup;
            }

            log<LogLevel::Info>("compiled cxir from " + source_file.string());
            log<LogLevel::Info>("compiled successfully to " + (path / out).string());
        }

    cleanup:
        std::filesystem::remove(source_file);
        std::filesystem::path obj_file = source_file;
        obj_file.replace_extension(".obj");

        if (std::filesystem::exists(obj_file)) {
            std::error_code ec_remove;
            std::filesystem::remove(obj_file, ec_remove);

            if (ec_remove) {
                log<LogLevel::Warning>("failed to delete object file " + obj_file.string() + ": " +
                                       ec_remove.message());
            } else {
                log<LogLevel::Info>("deleted object file " + obj_file.string());
            }
            return;
        }

        obj_file = path / source_file.filename();
        obj_file.replace_extension(".obj");

        if (std::filesystem::exists(obj_file)) {
            std::error_code ec_remove;
            std::filesystem::remove(obj_file, ec_remove);

            if (ec_remove) {
                log<LogLevel::Warning>("failed to delete object file " + obj_file.string() + ": " +
                                       ec_remove.message());
            } else {
                log<LogLevel::Info>("deleted object file " + obj_file.string());
            }
        }
    }

    std::tuple<token::Token, std::string, std::string>
    parse_clang_err(std::string clang_out) const {
        std::string filePath;
        int         lineNumber   = 0;
        int         columnNumber = 0;
        std::string message;

        std::istringstream stream(clang_out);
        std::getline(stream, filePath, ':');  // Extract file path
        stream >> lineNumber;                 // Extract line number
        stream.ignore();                      // Ignore the next colon
        stream >> columnNumber;               // Extract column number
        stream.ignore();                      // Ignore the next colon
        std::getline(stream, message);        // Extract the message

        auto pof = token::Token(lineNumber, 0, 1, columnNumber, "/*error*/", filePath, "<other>");

        return {pof, message, filePath};
    }

    void compile_CXIR_NonWindows(generator::CXIR::CXIR &emitter,
                                 const std::string     &out,
                                 bool                   is_debug,
                                 bool                   is_verbose = false) const {
        std::string cxx = emitter.to_CXIR();

        std::filesystem::path path        = __CONTROLLER_FS_N::get_cwd();
        std::filesystem::path source_file = path / "_H1HJA9ZLO_17.helix-compiler.cc";
        std::ofstream         file(source_file);

        if (!file) {
            log<LogLevel::Error>("error creating " + source_file.string() + " file");
            return;
        }

        file << cxx;
        file.close();

        std::string compiler        = "c++";
        auto        compiler_result = exec(compiler + " --version");
        std::string compile_flags   = "-std=c++23 ";
        compile_flags += is_debug ? "-g " : "-O2 ";

        if ((compiler_result.output.find("clang") != std::string::npos) ||
            (compiler_result.output.find("gcc") != std::string::npos)) {
            log<LogLevel::Info>(
                "using system's '" +
                std::string((compiler_result.output.find("clang") != std::string::npos) ? "clang"
                                                                                        : "gcc") +
                "' compiler, with the '" +
                ((compiler_result.output.find("clang") != std::string::npos) ? "lld" : "ld") +
                "' linker");

            // -fdiagnostics-format=json << gcc
            /// -fdiagnostics-show-hotness -fdiagnostics-print-source-range-info  << clang
            compile_flags += " -fcaret-diagnostics-max-lines=0 -fno-diagnostics-fixit-info "
                             "-fno-elide-type -fno-diagnostics-show-line-numbers "
                             "-fno-color-diagnostics -fno-diagnostics-show-option ";

        } else {
            log<LogLevel::Error>("aborting. unknown compiler: " + compiler_result.output);
            return;
        }

        compile_flags += "-fno-omit-frame-pointer -Wl,-w,-rpath,/usr/local/lib ";
        compile_flags += "\"" + source_file.string() + "\" -o \"" + (path / out).string() + "\"";

        auto compile_result = exec("c++ " + compile_flags + " 2>&1");

        if (compile_result.return_code != 0) {
            std::vector<std::string> lines;
            std::istringstream       stream(compile_result.output);

            for (std::string line; std::getline(stream, line);) {
                if (line.starts_with('/')) {
                    lines.push_back(line);
                }
            }

            for (auto &line : lines) {
                auto err = parse_clang_err(line);

                if (!std::filesystem::exists(std::get<2>(err))) {
                    error::Panic(error::CompilerError{
                        .err_code     = 0.8245,
                        .err_fmt_args = {"error at: " + std::get<2>(err) + std::get<1>(err)},
                    });

                    continue;
                }

                std::pair<size_t, size_t> err_t = {std::get<1>(err).find_first_not_of(' '),
                                                   std::get<1>(err).find(':') -
                                                       std::get<1>(err).find_first_not_of(' ')};

                error::Level level = std::map<string, error::Level>{
                    {"error", error::Level::ERR},                       //
                    {"warning", error::Level::WARN},                    //
                    {"note", error::Level::NOTE}                        //
                }[std::get<1>(err).substr(err_t.first, err_t.second)];  //

                std::string msg = std::get<1>(err).substr(err_t.first + err_t.second + 1);

                msg = msg.substr(msg.find_first_not_of(' '));

                error::Panic(error::CodeError{
                    .pof          = &std::get<0>(err),
                    .err_code     = 0.8245,
                    .err_fmt_args = {msg},
                    .mark_pof     = false,
                    .level        = level,
                    .indent       = static_cast<size_t>((level == error::NOTE) ? 1 : 0),
                });
            }

            if (is_verbose || !error::HAS_ERRORED) {
                log<LogLevel::Info>("compilation passed");
                log<LogLevel::Error>((is_verbose ? "compiler output:\n" : "linker failed. ") +
                                     compile_result.output);
            } else {
                log<LogLevel::Error>("compilation failed");
            }

            log<LogLevel::Error>("aborting...");
            goto cleanup;
        }

        log<LogLevel::Info>("lowered " +
                            (emitter.get_file_name().has_value() ? emitter.get_file_name().value()
                                                                 : source_file.string()) +
                            " and compiled cxir");
        log<LogLevel::Info>("compiled successfully to " + (path / out).string());

    cleanup:
        std::filesystem::remove(source_file);
    }
};

class CompilationUnit {
  public:
    int compile(int argc, char **argv) {
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        parser::ast::NodeT<parser::ast::node::Program>              ast;
        std::filesystem::path                                       in_file_path;
        generator::CXIR::CXIR                                       emitter;
        parser::lexer::Lexer                                        lexer;
        __TOKEN_N::TokenList                                        tokens;

        __CONTROLLER_CLI_N::CLIArgs parsed_args(argc, argv, "0.0.1-alpha-2012");
        check_exit(parsed_args);

        if (parsed_args.quiet || parsed_args.lsp_mode) {
            NO_LOGS           = true;
            error::SHOW_ERROR = false;
        }

        if (parsed_args.verbose) {
            log<LogLevel::Debug>(parsed_args.get_all_flags);
        }

        start        = std::chrono::high_resolution_clock::now();
        in_file_path = __CONTROLLER_FS_N::normalize_path(parsed_args.file);
        lexer        = {__CONTROLLER_FS_N::read_file(in_file_path.string()), in_file_path.string()};
        tokens       = lexer.tokenize();

        log<LogLevel::Info>("tokenized");

        // preprocessor - missing for now
        log<LogLevel::Info>("preprocessed");

        if (parsed_args.emit_tokens) {
            log<LogLevel::Debug>(tokens.to_json());
            print_tokens(tokens);
        }

        remove_comments(tokens);
        ast = parser::ast::make_node<parser::ast::node::Program>(tokens);

        if (!ast) {
            log<LogLevel::Error>("aborting...");
            return 1;
        }

        ast->parse();
        log<LogLevel::Info>("parsed");

        if (parsed_args.emit_ast) {
            parser::ast::visitor::Jsonify json_visitor;
            ast->accept(json_visitor);

            if (parsed_args.lsp_mode) {
                print(json_visitor.json.to_string());
                return 0;
            }

            log<LogLevel::Debug>(json_visitor.json.to_string());
        }

        if (error::HAS_ERRORED || parsed_args.lsp_mode) {
            LSP_MODE = parsed_args.lsp_mode;
            return 0;
        }

        ast->accept(emitter);
        log<LogLevel::Info>("emitted cx-ir");

        if (parsed_args.emit_ir) {
            emit_cxir(emitter, parsed_args.verbose);
        }

        std::string out_file = determine_output_file(parsed_args, in_file_path);
        log<LogLevel::Info>("output file: " + out_file);

        if (error::HAS_ERRORED) {
            log<LogLevel::Error>("aborting... due to previous errors");
            return 1;
        }

        compiler.compile_CXIR(emitter,
                              out_file,
                              parsed_args.build_mode == __CONTROLLER_CLI_N::CLIArgs::MODE::DEBUG_,
                              parsed_args.verbose);

        log_time(start, parsed_args.verbose, std::chrono::high_resolution_clock::now());
        return 0;
    }

  private:
    CXIRCompiler compiler;

    static void remove_comments(__TOKEN_N::TokenList &tokens) {
        __TOKEN_N::TokenList new_tokens;

        for (auto &token : tokens) {
            if (token->token_kind() != __TOKEN_N::PUNCTUATION_SINGLE_LINE_COMMENT &&
                token->token_kind() != __TOKEN_N::PUNCTUATION_MULTI_LINE_COMMENT) {
                new_tokens.push_back(token.current().get());
            }
        }

        tokens = new_tokens;
    }

    static void emit_cxir(const generator::CXIR::CXIR &emitter, bool verbose) {
        log<LogLevel::Info>("emitting cx-ir...");

        if (verbose) {
            log<LogLevel::Debug>("\n", colors::fg16::yellow, emitter.to_CXIR(), colors::reset);
        } else {
            log<LogLevel::Info>(
                "\n", colors::fg16::yellow, emitter.to_readable_CXIR(), colors::reset);
        }
    }

    static std::string determine_output_file(const __CONTROLLER_CLI_N::CLIArgs &parsed_args,
                                             const std::filesystem::path       &in_file_path) {

        std::string out_file = (parsed_args.output_file.has_value())
                                   ? parsed_args.output_file.value()
                                   : std::filesystem::path(in_file_path).stem().string();

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        out_file += ".exe";
#endif

        return out_file;
    }

    static void log_time(const std::chrono::high_resolution_clock::time_point &start,
                         bool                                                  verbose,
                         const std::chrono::high_resolution_clock::time_point &end) {

        std::chrono::duration<double> diff = end - start;

        if (verbose) {
            log<LogLevel::Debug>("time taken: " + std::to_string(diff.count() * 1e+9) + " ns");
            log<LogLevel::Debug>("            " + std::to_string(diff.count() * 1000) + " ms");
        }
    }
};

int main(int argc, char **argv) {
    auto compiler = CompilationUnit();
    int  result   = 1;

    try {
        result = compiler.compile(argc, argv);
    } catch (error::Panic &) {  // hard error
        return 69;              // nice
    }

    if (LSP_MODE && error::HAS_ERRORED) {
        for (const auto &err : error::ERRORS) {
            print(err.to_json());
        }

        return 1;  // soft error
    }

    return result;
}

/*
using the new toolchain the entire process can happen like this:

template <std::size_t N>
int helix_compiler(std::array<std::string, N> args) {
    InvocationManager       invoke      = InvocationManager(args, true);
    CompilationUnit         compile     = CompilationUnit(invoke);
    PrettyDiagnosticHandler diag_handle = PrettyDiagnosticHandler();

    // frontend processors
    compile.add_frontend_processor(LexicalProcessor());
    compile.add_frontend_processor(PreProcessor());
    compile.add_frontend_processor(ASTProcessor());

    // backend processors
    compile.add_backend_processor(CXIRGenerator());
    compile.add_backend_processor(ExecutableGenerator<OutputFormat::Executable>());

    // set diagnostics
    compile.set_diagnostic_handler(diag_handle);

    if (compile.execute() != InvocationManager::Success) {
        switch (compile.exit_state) {
            case InvocationManager::CompilerError:
                log(
                    "compiler internal error: ",
                    diag_handle
                        .get<InvocationManager::CompilerError>()
                        .format()
                        .to_string()
                ); break;

            case InvocationManager::CodeError:
                log(
                    "user code error: ",
                    diag_handle
                        .get<InvocationManager::CodeError>()
                        .format()
                        .to_string()
                ); break;

            case InvocationManager::UnrecoverableError:
                log(
                    "fatal error: ",
                    diag_handle
                        .get<InvocationManager::UnrecoverableError>()
                        .format()
                        .to_string()
                ); break;

            case InvocationManager::SystemError:
                log(
                    "sys call error: ",
                    diag_handle
                        .get<InvocationManager::SystemError>()
                        .format()
                        .to_string()
                ); break;
        };

        diag_handle.panic(PrettyDiagnosticHandler::ColorMode::ON);
    }

    return 0;
}

*/
