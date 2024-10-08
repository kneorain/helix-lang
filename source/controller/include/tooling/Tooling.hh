#ifndef __HELIX_TOOLING_HH__
#define __HELIX_TOOLING_HH__

#include "controller/include/config/Controller_config.def"

__CONTROLLER_TOOL_BEGIN {
    // base classes
    class DiagnosticHandler;
    class InvocationManager;
    class CompilationUnit;
    class FileManager;
    class FrontendProcessor;
    class BackendProcessor;

    // derived classes
    class PrettyDiagnosticHandler;

    class CompilationUnit {
        CompilationUnit() = default;
        ~CompilationUnit() = default;

        CompilationUnit(const CompilationUnit &) = delete;
        CompilationUnit(CompilationUnit &&) = delete;

        CompilationUnit &operator=(const CompilationUnit &) = delete;
        CompilationUnit &operator=(CompilationUnit &&) = delete;

        explicit CompilationUnit(InvocationManager &invocation);
        CompilationUnit(int argc, const char **argv);

        void createDiagnostics();
        void createDiagnostics(DiagnosticHandler &diag);
    };
}

#endif // __HELIX_TOOLING_HH__