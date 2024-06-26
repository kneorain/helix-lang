/*
helix - command line interface

Usage:
    helix [options] <file> [options-2]
    helix (-h | --help)
    helix --version
    helix --license

Options:
    -O1 --optimize1      Optimization level 1.
    -O2 --optimize2      Optimization level 2.
    -O3 --optimize3      Optimization level 3.
    -O4 --optimize4      Optimization level 4.

    -h --help            Show this screen.
    --version            Show version.
    --license            Show license information.

    --verbose            Show verbose output.
    --quiet              Show no output.

    --ast                Show abstract syntax tree.
    --tokens             Show tokens.
    --emit-llvm          Show LLVM IR.
    --emit-asm           Show assembly.
    --emit-ir            Show intermediate representation. (C | C++)
    --emit-doc           Only extract doc-comments along with signatures.

    --target <triple>    Target triple.
    --arch <arch>        Target architecture.
    --os <os>            Target operating system.

    --config <file>              Specify configuration file.
    --release                    Build in release mode.
    --debug                      Build in debug mode.

Options-2:
    -o <file>            Output file.
    --lib                Compile as library.
    -I<dir>              Include directory.
    -L<dir>              Library directory.
    -l<lib>              Link library.
*/

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

#include <cli/include/args.hh>

void parse() {}
