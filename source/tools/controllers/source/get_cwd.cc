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
#include <array>
#include <tools/controllers/include/file_system.hh>

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#   define PATH_MAX MAX_PATH
#else
#   include <unistd.h>
#   include <climits>
#   include <cstring>
#endif

namespace file_system {
std::string get_cwd() {
#   if defined(_WIN32) || defined(_WIN64)
#       include <tools/controllers/lib/__win32_cwd.inc>
#   else
#       include <tools/controllers/lib/__unix_cwd.inc>
#   endif
    return {buffer.data()};
}
}