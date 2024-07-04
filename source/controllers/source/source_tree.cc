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
#include <iostream>

#include "controllers/include/file_system.hh"

namespace file_system {
SourceTree::SourceTree(const std::string &rootPath)
    : root(Node(rootPath)) {
    buildTree(rootPath, root);
}

void SourceTree::print() const { printTree(root); }

bool SourceTree::buildTree(const std::string &dirPath, Node &node) {
    bool containsHelixFiles = false;
    for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
        if (entry.is_directory()) {
            Node dirNode(entry.path().string());
            if (buildTree(entry.path().string(), dirNode)) {
                node.children.push_back(std::move(dirNode));
                containsHelixFiles = true;
            }
        } else if (entry.path().extension() == ".hlx") {
            node.children.emplace_back(entry.path().string());
            containsHelixFiles = true;
        }
    }
    return containsHelixFiles;
}

void SourceTree::printTree(const Node &node, const std::string &prefix) const {
    std::cout << prefix << node.path << "\n";
    for (const auto &child : node.children) {
        printTree(child, prefix + "  ");
    }
}

}  // namespace file_system
