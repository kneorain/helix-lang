#ifndef __HELIX_TOOLING_HH__
#define __HELIX_TOOLING_HH__

#include <memory>
#include <string>

#include "controller/include/config/Controller_config.def"

/* The Vial file format is as described:
- The file is a binary file
- the file starts with a magic number and a version number
- the file is divided into 3 main sections: the manifest, the data, and the symbol table
- the manifest is a list of key-value pairs that describe the data
- the data contains all the files that are part of the compilation unit
- the symbol table contains all the symbols that are part of the compilation unit
- having the data and the symbol table separate allows for caching and incremental compilation
    @brief having a separate symbol table allows for the following:
           each compile with an import to a vile would be parsed and instead of recompiling the vile
           only the symbol table would be updated and after the first compile of the vile each
           subsequent compile would only need to update the symbol table


| offset | size(B) | field                   | description                                         |
|--------|---------|-------------------------|-----------------------------------------------------|
| 0x00   | 8       | Magic Number            | `0x68656C69782D7669616C` ("helix-vial" in ASCII)    |
| 0x08   | 2       | Vial Version            | Version of the Vial format                          |
| 0x0A   | 2       | Compiler Version        | Version of the Helix compiler used to generate      |
| 0x0C   | 4       | Manifest Offset         | Start of the manifest section (metadata in JSON)    |
| 0x10   | 4       | Data Section Offset     | Start of the data (source code and compiled objects)|
| 0x14   | 4       | Symbol Table Offset     | Start of the symbol table (functions, symbols)      |
| 0x18   | 16      | Compilation Timestamp   | Unicode timestamp of the compilation                |
| 0x28   | 4       | Document Section Offset | Start of the document section (user docs)           |
| 0x2C   | 4       | Resource Section Offset | Start of the resources section (images, etc.)       |
| 0x30   | 4       | Signature Offset?       | digital signature for verifying file integrity      |
| 0x34   | 4       | Checksum                | Checksum (e.g., CRC32) of the entire file           |
| 0x38   | 4       | Total File Size         | Total size of the Vial file in bytes                |
| 0x3C   | 4       | Padding                 | padding for 8-byte alignment                        |
*/

__CONTROLLER_TOOL_BEGIN {

    // base classes
    class DiagnosticHandler;
    class InvocationManager;
    class CompilationUnit;
    class FileManager;
    class FrontendProcessor;
    class BackendProcessor;

    // diagnostic handlers
    class PrettyDiagnosticHandler;
    class SimpleDiagnosticHandler;
    class JsonDiagnosticHandler;

    // frontend processors
    class LexicalProcessor;
    class PreProcessor;
    class ASTProcessor;  // generates AST and SymbolTable
    class CXXProcessor;  // converts a clang C++ SymbolTable to a Helix by-directional SymbolTable
    class SemanticProcessor;
    class VialProcessor;  // generates a Vial file from a Helix file

    // backend processors
    class CXIRGenerator;
    class LLVMGenerator;
    class ExecutableGenerator;
    class ObjectGenerator;

    class CompilationUnit {
      public:
        /**
         * @brief the main constructor for a compilation unit. takes the command-line
         *        arguments and gets the whole thing going.
         * @param argc number of command-line arguments
         * @param argv array of argument strings
         */
        CompilationUnit(int argc, const char **argv);

        explicit CompilationUnit(InvocationManager &invocation);

        template <std::size_t N>
        explicit CompilationUnit(std::array<const char *, N> &argv)
            : CompilationUnit(argv.size(), argv.data()) {}

        template <std::size_t N>
        explicit CompilationUnit(std::array<std::string, N> &argv)
            : CompilationUnit(argv.size(), argv.data()) {}

        ~CompilationUnit();

        CompilationUnit(const CompilationUnit &)            = delete;
        CompilationUnit &operator=(const CompilationUnit &) = delete;

        CompilationUnit(CompilationUnit &&) noexcept            = default;
        CompilationUnit &operator=(CompilationUnit &&) noexcept = default;

        [[nodiscard]] bool initialize();
        [[nodiscard]] bool process();
        void               finalize();

        void set_frontend_processor(std::unique_ptr<FrontendProcessor> frontend);
        void set_backend_processor(std::unique_ptr<BackendProcessor> backend);

        void set_diagnostic_handler(std::unique_ptr<DiagnosticHandler> handler);
        void report_diagnostics() const;

        [[nodiscard]] FileManager       &get_file_manager_ref();
        [[nodiscard]] InvocationManager &get_invocation_manager_ref();

        [[nodiscard]] bool has_errors() const;
        void               clear_errors();
        void               log_status() const;
        void               emit_errors() const;

      private:
        [[nodiscard]] bool validate_inputs() const;
        void               setup_environment();

        void release_resources();

        std::unique_ptr<InvocationManager> invocation;
        std::unique_ptr<DiagnosticHandler> diagnostic_handler;
        std::unique_ptr<FileManager>       file_manager;
        std::unique_ptr<FrontendProcessor> frontend_processor;
        std::unique_ptr<BackendProcessor>  backend_processor;

        bool hasErrors_;
    };
}

#endif  // __HELIX_TOOLING_HH__