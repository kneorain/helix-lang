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

#include "tools/controllers/include/io.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include "include/error/error.hh"

namespace io {
std::unordered_map<std::string, std::string> FileCache::cache_;
std::mutex FileCache::mutex_;

std::optional<std::string> get_line(const std::string &filename, u64 line) {
    std::string source = io::read_file(filename);

    u64 current_line = 1;
    u64 start = 0;
    u64 end = 0;

    for (u64 i = 0; i < source.size(); ++i) {
        if (source[i] == '\n') {
            ++current_line;
            if (current_line == line) {
                start = i + 1;
            } else if (current_line == line + 1) {
                end = i;
                break;
            }
        }

        if (i == source.size() - 1) {
            end = source.size();
        }
    }

    if (line > current_line) {
        return std::nullopt;
    }

    return source.substr(start, end - start);
}

std::string _internal_read_file(const std::string &filename) {
    auto cached_file = FileCache::get_file(filename);
    if (cached_file.has_value()) {
        return cached_file.value();
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file) {
        error::Error(error::Compiler{filename, "file not found."});
        return "";
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string source(size, '\0');
    if (!file.read(source.data(), size)) {
        error::Error(error::Compiler{filename, "failed to read file."});
        return "";
    }

    FileCache::add_file(filename, source);

    return source;
}

std::string read_file(std::string &filename) {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path abs_path = std::filesystem::absolute(cwd / filename);
    filename = abs_path.string();

    return _internal_read_file(filename);
}

// TODO: make all readfiles after the first one be relative to the first one
/// Example: readfile("file1.hlx") -> /path/to/file1.hlx
///          readfile("test/file2.hlx") -> /path/to/test/file2.hlx
///          readfile("../file3.hlx") -> /path/to/file3.hlx

std::string read_file(const std::string &filename) {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path abs_path = std::filesystem::absolute(cwd / filename);

    return _internal_read_file(abs_path.string());
}
}  // namespace io