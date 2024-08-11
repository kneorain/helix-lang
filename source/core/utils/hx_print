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
#ifndef __PRINT_V2_HH__
#define __PRINT_V2_HH__

#include <iostream>

namespace sysIO {
using endl = struct endl {
    std::string end_l = "\n";
    endl() = default;
    explicit endl(std::string end)
        : end_l(std::move(end)) {}
    explicit endl(const char *end)
        : end_l(end) {}
    explicit endl(const char end)
        : end_l(std::string(1, end)) {}
    endl(const endl &end) = default;
    endl(endl &&) = default;                  // Add move constructor
    endl &operator=(const endl &) = default;  // Add copy assignment operator
    endl &operator=(endl &&) = default;       // Add move assignment operator
    ~endl() = default;                        // Add destructor
    friend std::ostream &operator<<(std::ostream &oss, const endl &end) {
        oss << end.end_l;
        return oss;
    }
};
}  // namespace sysIO

template <typename... Args>
inline constexpr void print(Args &&...args) {
    if constexpr (sizeof...(args) == 0) {
        std::cout << sysIO::endl('\n');
        return;
    };
    (std::cout << ... << args);
    if constexpr (sizeof...(args) > 0) {
        if constexpr (!std::is_same_v<std::remove_cv_t<std::remove_reference_t<
                                          decltype(std::get<sizeof...(args) - 1>(
                                              std::tuple<Args...>(args...)))>>,
                                      sysIO::endl>) {
            std::cout << sysIO::endl('\n');
        }
    }
}

#endif  // __PRINT_V2_HH__