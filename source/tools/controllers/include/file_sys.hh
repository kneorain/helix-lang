#ifndef __FILE_SYS_H__
#define __FILE_SYS_H__

#include <filesystem>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace file_system {

class SourceTree {
  public:
    struct Node {
        std::string path;
        std::vector<Node> children;

        explicit Node(std::string path)
            : path(std::move(path)) {}
    };

    explicit SourceTree(const std::string &rootPath)
        : root(Node(rootPath)) {
        buildTree(rootPath, root);
    }

    void printTree(const Node &node, const std::string &prefix = "") const {
        std::cout << prefix << node.path << "\n";
        for (const auto &child : node.children) {
            printTree(child, prefix + "  ");
        }
    }

    void print() const { printTree(root); }

  private:
    Node root;

    bool buildTree(const std::string &dirPath, Node &node) {
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
};

}  // namespace file_system

#endif  // __FILE_SYS_H__
