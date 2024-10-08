#ifndef __HELIX_TOOLING_HH__
#define __HELIX_TOOLING_HH__

#include "controller/include/config/Controller_config.def"

__CONTROLLER_TOOL_BEGIN {
    class CompilerInvocation;

    class CompilerInstance {
        CompilerInstance() = default;
        ~CompilerInstance() = default;

        CompilerInstance(const CompilerInstance &) = delete;
        CompilerInstance(CompilerInstance &&) = delete;

        CompilerInstance &operator=(const CompilerInstance &) = delete;
        CompilerInstance &operator=(CompilerInstance &&) = delete;

        explicit CompilerInstance(CompilerInvocation &invocation);
        CompilerInstance(int argc, const char **argv);

        void createDiagnostics();
        void createDiagnostics(int argc, const char **argv);
    };
}

#endif // __HELIX_TOOLING_HH__