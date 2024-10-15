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
#include "parser/ast/include/private/base/AST_base.hh"
#include "parser/ast/include/types/AST_jsonify_visitor.hh"
#include "parser/ast/include/types/AST_types.hh"

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
#include <string>
#include <vector>

#include "controller/include/Controller.hh"
#include "generator/include/CX-IR/CXIR.hh"
#include "lexer/include/lexer.hh"
#include "neo-panic/include/error.hh"
#include "neo-pprint/include/hxpprint.hh"
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
    template <typename T>
    struct ExecResult {
        T   output;
        int return_code{};
    };

    template <typename T>
    [[nodiscard]] ExecResult<T> exec(const std::string &cmd) const {
        ExecResult<T>         result;
        std::array<char, 128> buffer{};
        std::string           data;

        // Use platform-specific popen and pclose
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
#else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
#endif
        if (!pipe) {
            result.return_code = -1;
            return result;
        }

        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            data += buffer.data();
        }

        int rc = 0;
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        rc = _pclose(pipe.release());
#else
        rc = pclose(pipe.release());
#endif
        result.output      = static_cast<T>(data);
        result.return_code = rc;

        return result;
    }

    void compile_CXIR(generator::CXIR::CXIR &emitter,
                      const std::string     &out,
                      bool                   is_debug = false) const {
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        compile_CXIR_Windows(emitter, out, is_debug);
#else
        compile_CXIR_NonWindows(emitter, out, is_debug);
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
            auto vs_result = exec<std::string>(vswhere_cmd);

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

            ExecResult<std::string> compile_result = exec<std::string>(compile_cmd);

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

    void compile_CXIR_NonWindows(generator::CXIR::CXIR &emitter,
                                 const std::string     &out,
                                 bool                   is_debug) const {
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

        std::string compile_flags = "-std=c++23 ";
        compile_flags += is_debug ? "-g " : "-O2 ";
        compile_flags += "-fno-omit-frame-pointer -Wl,-w,-rpath,/usr/local/lib ";
        compile_flags += "\"" + source_file.string() + "\" -o \"" + (path / out).string() + "\"";

        ExecResult<std::string> compile_result = exec<std::string>("c++ " + compile_flags);

        if (compile_result.return_code != 0) {
            log<LogLevel::Error>("compilation failed");
            log<LogLevel::Error>("compiler output:\n" + compile_result.output);
            goto cleanup;
        }

        log<LogLevel::Info>("compiled cxir from " + source_file.string());
        log<LogLevel::Info>("compiled successfully to " + (path / out).string());

    cleanup:
        std::filesystem::remove(source_file);
    }
};

class CompilationUnit {
  public:
    int compile(int argc, char **argv) {
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        parser::ast::NodeT<parser::ast::node::Program>     ast;
        std::filesystem::path                              in_file_path;
        generator::CXIR::CXIR                              emitter;
        parser::lexer::Lexer                               lexer;
        __TOKEN_N::TokenList                               tokens;

        __CONTROLLER_CLI_N::CLIArgs parsed_args(argc, argv, "0.0.1-alpha-2012");
        check_exit(parsed_args);

        if (parsed_args.quiet || parsed_args.lsp_mode) {
            NO_LOGS = true;
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

        compiler.compile_CXIR(
            emitter, out_file, parsed_args.build_mode == __CONTROLLER_CLI_N::CLIArgs::MODE::DEBUG_);

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
            log<LogLevel::Info>("\n", colors::fg16::yellow, emitter.to_readable_CXIR(), colors::reset);
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
    int  result = 1;

    try {
        result = compiler.compile(argc, argv);
    } catch (error::Panic &) { // hard error
        return 69;             // nice
    }

    if (LSP_MODE && error::HAS_ERRORED) {
        for (const auto &err : error::ERRORS) {
            print(err.to_json());
        }

        return 1; // soft error
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
