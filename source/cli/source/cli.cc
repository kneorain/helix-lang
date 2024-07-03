/*
Helios - package manager / build system

Usage:
    helios create <project>               Create a new Helix project.
    helios build                          Build the current project.
    helios run [-r] -- <args>             Run the current project with optional arguments.
    helios test                           Run tests for the current project.
    helios clean                          Clean build artifacts.
    helios install <package>              Install a package.
    helios uninstall <package>            Uninstall a package.
    helios update                         Update all installed packages.
    helios search <package>               Search for a package.
    helios list                           List all installed packages.
    helios info <package>                 Show information about a specific package.
    helios help                           Show help information.
    helios version                        Show the version of Helios.
    helios license                        Show the license of Helios.
    helios doc-gen                        Generate documentation.
*/

/*
helix - command line interface

Usage:
    helix [options] <file> [options-2]
    helix (-h | --help)
    helix --version
    helix --license

options:
    -O1 --optimize1          Optimization level 1.
    -O2 --optimize2          Optimization level 2.
    -O3 --optimize3          Optimization level 3.
    -O4 --optimize4          Optimization level 4.
    -O5 --optimize5          Optimization level 5.

    -h --help                Show this screen.
    -v --version             Show version.
    -l --license             Show license information.

    --verbose                Show verbose output.
    --quiet                  Show no output.

    --emit-tokens            Show tokens.
    --emit-llvm              Show LLVM IR.
    --emit-asm               Show assembly.
    --emit-ast               Show AST in json format
    --emit-ir                Show intermediate representation. (C++)
    --emit-doc               Only extract doc-comments along with signatures in json format.

    --toolchain <options-3>  Set the toolchain to use

    --config <file>          Specify configuration file.
    -r --release             Build in release mode.
    -d --debug               Build in debug mode with symbols.

options-2:
    --lib [abi-options]      Compile as library.
    -o <file>                Output file.
    -I <dir>                 Include directory.
    -L <dir>                 Library directory.
    -l <lib>                 Link library.

options-3:
    --target <triple>        Target triple.
    --arch   <arch>          Target architecture.
    --os     <os>            Target operating system.


abi-options:
    -py  --python        Python stub files gen and pylib compile
    -rs  --rust          Rust source files gen and a rust compiler lib
    -cxx --cxx           C++ header files gen and linkable object file
    -hlx --helix         Helix ABI compatable libary
*/

#include <array>
#include <cstddef>
#include <iostream>
#include <string>

#include "cli/include/args.hh"

namespace command_line {
class CLIArgs {
    template <size_t arr_size>
    explicit CLIArgs(int argc, char **argv) {
        args::ArgumentParser parser(
            "This is a test program with a really long description that is probably going to have "
            "to be wrapped across multiple different lines.  This is a test to see how the line "
            "wrapping works",
            "This goes after the options.  This epilog is also long enough that it will have to be "
            "properly wrapped to display correctly on the screen");
        
        args::HelpFlag help(parser, "HELP", "Show this help menu.", {'h', "help"});
        
        args::ValueFlag<std::string> foo(parser, "FOO", "The foo flag.",
                                         {'a', 'b', 'c', "a", "b", "c", "the-foo-flag"});
        
        args::ValueFlag<std::string> bar(
            parser, "BAR",
            "The bar flag.  This one has a lot of options, and will need wrapping in the "
            "description, along with its long flag list.",
            {'d', 'e', 'f', "d", "e", "f"});
        
        args::ValueFlag<std::string> baz(
            parser, "FOO",
            "The baz flag.  This one has a lot of options, and will need wrapping in the "
            "description, even with its short flag list.",
            {"baz"});
    
        args::Positional<std::string>     pos1(parser, "POS1", "The pos1 argument.");
        args::PositionalList<std::string> poslist1(parser, "POSLIST1", "The poslist1 argument.");

        try {
            parser.ParseCLI(argc, argv);
        } catch (args::Help) {
            std::cout << parser;
            return;
        } catch (args::ParseError e) {
            std::cerr << e.what() << std::endl;
            std::cerr << parser;
            return;
        } catch (args::ValidationError e) {
            std::cerr << e.what() << std::endl;
            std::cerr << parser;
            return;
        }
    }
};

struct HelixArguments {
    // File and optional output file
    std::string file;
    std::optional<std::string> output_file;

    // Options
    bool optimize1 = false;
    bool optimize2 = false;
    bool optimize3 = false;
    bool optimize4 = false;

    bool help = false;
    bool version = false;
    bool license = false;

    bool verbose = false;
    bool quiet = false;

    bool show_ast = false;
    bool show_tokens = false;
    bool emit_llvm = false;
    bool emit_asm = false;
    bool emit_ir = false;
    bool emit_doc = false;

    std::optional<std::string> target_triple;
    std::optional<std::string> target_arch;
    std::optional<std::string> target_os;

    std::optional<std::string> config_file;
    bool release = false;
    bool debug = false;

    // Options-2
    bool compile_as_library = false;
    std::vector<std::string> include_dirs;
    std::vector<std::string> library_dirs;
    std::vector<std::string> link_libraries;
};
}  // end namespace command_line
