#include "tree_utils.h"
#include <vector>
#include <string>
#include <iostream>

void recursivePrintIndex(Node* node, int level){
    if (node == nullptr) return;
    recursivePrintIndex(node->left, level + 1);
    std::cout << std::string(level * 2, ' ') << node->word << " (" << node->documentIds.size() << " docs)" << std::endl;
    recursivePrintIndex(node->right, level + 1);
}
void recursivePrintTree(Node* node, int level){

}
void printIndex(BinaryTree* tree){

}
void printTree(BinaryTree* tree){

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