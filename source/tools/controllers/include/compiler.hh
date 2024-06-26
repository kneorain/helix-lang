/**
 * @author Dhruvan Kartik
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
#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <vector>

namespace clang {
using namespace std;

struct Arguments {
    vector<string> args; //> additional arguments to pass
    vector<string> libs; //> lib dirs, such as for libcxx
    vector<string> incs; //> include dirs
    vector<string> link; //> link dirs
};

class Compiler {
    private:
        Arguments args;

    public:
        Compiler() = default;
        explicit Compiler(Arguments args);
};
}


#endif // __COMPILER_H__