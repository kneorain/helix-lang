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
};
}  // namespace token

#endif // __MAPPING_H__