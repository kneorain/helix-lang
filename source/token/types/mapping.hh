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

#ifndef __MAPPING_H__
#define __MAPPING_H__

#include <array>
#include <optional>
#include <string>
#include <utility>

using std::string;

namespace token {
template <typename Enum, int N>
struct Mapping {
    std::array<std::pair<Enum, std::string_view>, N> data;

    constexpr Mapping(std::array<std::pair<Enum, std::string_view>, N> init_data) : data(init_data) {}

    [[nodiscard]] constexpr std::optional<Enum> at(std::string_view x) const noexcept {
        for (const auto &[key, value] : data) {
            if (value == x) {
                return key;
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr std::optional<std::string_view> at(Enum x) const noexcept {
        for (const auto &[key, value] : data) {
            if (key == x) {
                return value;
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr auto begin() const noexcept {
        return data.begin();
    }

    [[nodiscard]] constexpr auto end() const noexcept {
        return data.end();
    }
};
}  // namespace token

#endif // __MAPPING_H__