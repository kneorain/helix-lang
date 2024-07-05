/**
 * @author Ojas Talgaonkar
 * @copyright Copyright (c) 2024 (CC BY 4.0)
 *
 * @note This code is part of the Helix Language Project and is licensed under the Attribution 4.0
 * International license (CC BY 4.0). You are allowed to use, modify, redistribute, and create
 * derivative works, even for commercial purposes, provided that you give appropriate credit,
 * provide a link to the license, and indicate if changes were made. For more information, please
 * visit: https://creativecommons.org/licenses/by/4.0/ SPDX-License-Identifier: CC-BY-4.0
 *
 * @note This code is provided by the creators of Helix. Visit our website at:
 * https://helix-lang.com/ for more information.
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
    -m <mod>                 Helix Modules directory.

options-3:
    --target <triple>        Target triple.
    --arch   <arch>          Target architecture.
    --os     <os>            Target operating system.
    --sdk    <sdk-path>      Optional Path to a sdk.

abi-options:
    -py  --python        Python stub files gen and pylib compile
    -rs  --rust          Rust source files gen and a rust compiler lib
    -cxx --cxx           C++ header files gen and linkable object file
    -hlx --helix         Helix ABI compatable libary
*/

#include "cli/include/cli.hh"

#include <array>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>

#include "cli/include/args.hh"
#include "core/types/hx_ints"

namespace command_line {
CLIArgs::CLIArgs(int argc, char **argv) {
    // Parse command line arguments
    args::ArgumentParser parser("helix parser");
    args::Group commands(parser, "commands");
    args::Command version(commands, {"-v", "--version"}, "displays version");
    args::Command lisence(commands, "--lisence", "displays lisence");

    try {
        parser.ParseCLI(argc, argv);
        if (version) {
            std::cout << "current_version";
        } else if (lisence) {
            std::cout << "lisence";
        }

    } catch (args::Help) { std::cout << parser; } catch (args::Error &e) {
        std::cerr << e.what() << std::endl << parser;
        return;
    }
}
}  // end namespace command_line
