#include "tree_utils.h"
#include <vector>
#include <string>
#include <iostream>

void recursivePrintIndex(Node* node, int& counter){
    if (node == nullptr) return;
    recursivePrintIndex(node->left, counter);
    std::cout << ++counter << ". " << node->word << ": ";
    for (size_t i = 0; i < node->documentIds.size(); ++i) {
        std::cout << node->documentIds[i];
        if (i != node->documentIds.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    recursivePrintIndex(node->right, counter);
}
void recursivePrintTree(Node* node, const std::string& prefix, bool isLeft){
    if (node == nullptr) return;
    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    std::cout << node->word << std::endl;

    bool hasLeft = node->left != nullptr;
    bool hasRight = node->right != nullptr;

    if (hasLeft || hasRight) {
        std::string newPrefix = prefix + (isLeft ? "│   " : "    ");
        if (node->left) recursivePrintTree(node->left, newPrefix, true);
        if (node->right) recursivePrintTree(node->right, newPrefix, false);
    }
}
void printIndex(BinaryTree* tree){
    int counter = 0;
    if (tree && tree->root)
        recursivePrintIndex(tree->root, counter);
}
void printTree(BinaryTree* tree){
    if (tree && tree->root)
        std::cout << tree->root->word << std::endl;
    if (tree && tree->root) {
        if (tree->root->left) recursivePrintTree(tree->root->left, "", true);
        if (tree->root->right) recursivePrintTree(tree->root->right, "", false);
    }
}
void printSearchResult(const SearchResult& result, const std::string& word){
    if (result.found < 0) {
        std::cerr << "Error: Found cannot be negative." << std::endl;
        return;
    }
    if (word.empty()) {
        std::cerr << "Error: Word cannot be empty." << std::endl;
        return;
    }
    if (result.found == 0) {
        std::cout << "Search Result: Not Found" << std::endl;
        return;
    }
    if (result.documentIds.empty()) {
        std::cout << "Search Result: Found but no document IDs" << std::endl;
        return;
    } // Espero que não aconteça, mas é bom verificar
    if (result.executionTime < 0) {
        std::cerr << "Error: Execution time cannot be negative." << std::endl;
        return;
    }
    if (result.numComparisons < 0) {
        std::cerr << "Error: Number of comparisons cannot be negative." << std::endl;
        return;
    }
    std::cout << "Search Result: Found in " << result.executionTime << " us." << std::endl;
    std::cout << word << ": ";
    for (const auto& id : result.documentIds) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}
void printSearchStats(const SearchResult& result){
    if (result.found < 0) {
        std::cerr << "Error: Found cannot be negative." << std::endl;
        return;
    }
    if (result.executionTime < 0) {
        std::cerr << "Error: Execution time cannot be negative." << std::endl;
        return;
    }
    if (result.numComparisons < 0) {
        std::cerr << "Error: Number of comparisons cannot be negative." << std::endl;
        return;
    }
    std::cout << "Search Result:" << std::endl;
    if (result.found == 1) {
        std::cout << "Found" << std::endl;
        if (result.documentIds.empty()) {
            std::cout << "No document IDs" << std::endl;
        } // Espero que não aconteça, mas é bom verificar
        else {
            std::cout << "Document IDs: ";
            for (const auto& id : result.documentIds) {
                std::cout << id << " ";
        }
    }
    } else {
        std::cout << "Not Found" << std::endl;
    }
    std::cout << "Execution Time: " << result.executionTime << " us." << std::endl;
    std::cout << "Number of Comparisons: " << result.numComparisons << std::endl;
}