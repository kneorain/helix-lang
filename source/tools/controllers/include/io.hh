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
#ifndef __IO_H__
#define __IO_H__

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include "include/inttypes.hh"

namespace io {
std::string read_file(std::string &filename);
std::string read_file(const std::string &filename);

std::optional<std::string> get_line(const std::string &filename, u64 line);

class FileCache {
  public:
    static void add_file(const std::string &key, const std::string &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        cache_[key] = value;
    }

    static std::optional<std::string> get_file(const std::string &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto cache_it = cache_.find(key);
        if (cache_it != cache_.end()) {
            return cache_it->second;
        }
        return std::nullopt;
    }

  private:
    static std::unordered_map<std::string, std::string> cache_;
    static std::mutex mutex_;
};
}  // namespace io

#endif  // __IO_H__