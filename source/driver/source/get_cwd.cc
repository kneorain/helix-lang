// -*- C++ -*-
//===------------------------------------------------------------------------------------------===//
//
// Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).
// You are allowed to use, modify, redistribute, and create derivative works, even for commercial
// purposes, provided that you give appropriate credit, and indicate if changes were made.
// For more information, please visit: https://creativecommons.org/licenses/by/4.0/
//
// SPDX-License-Identifier: CC-BY-4.0
// Copyright (c) 2024 (CC BY 4.0)
//
//===------------------------------------------------------------------------------------------===//

#include <array>

#include "driver/include/file_system.hh"

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
#       include "driver/lib/__win32_cwd.inc"
#   else
#       include "driver/lib/__unix_cwd.inc"
#   endif
    return {buffer.data()};
}
}  // namespace file_system