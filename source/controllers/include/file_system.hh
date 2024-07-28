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

#ifndef __FILE_SYSTEM_HH__
#define __FILE_SYSTEM_HH__

#include <cerrno>
#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/types/hx_ints"

namespace file_system {
std::string get_cwd();
std::optional<std::filesystem::path> resolve_path(const std::string &resolve);
std::optional<std::filesystem::path> resolve_path(const std::string &resolve,
                                                  const std::string &base);
std::string read_file(std::string &filename);
std::string read_file(const std::string &filename);

std::optional<std::string> get_line(const std::string &filename, u64 line);

class FileCache {
  public:
    static void add_file(const std::string &key, const std::string &value);
    static std::optional<std::string> get_file(const std::string &key);

  private:
    static std::unordered_map<std::string, std::string> cache_;
    static std::mutex mutex_;
};

class SourceTree {
  public:
    struct Node {
        std::string path;
        std::vector<Node> children;

        explicit Node(std::string path)
            : path(std::move(path)) {}
    };

    explicit SourceTree(const std::string &rootPath);

    void print() const;

  private:
    Node root;

    bool buildTree(const std::string &dirPath, Node &node);
    void printTree(const Node &node, const std::string &prefix = "") const;
};
}  // namespace file_system

#endif  // __FILE_SYSTEM_HH__