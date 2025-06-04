#include "bst.h"
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <chrono>

namespace BST{

BinaryTree* create() {
    BinaryTree* newTree = new BinaryTree;
    if (!newTree) {
        std::cerr << "Erro na alocação de memoria para a BST." << std::endl;
        return nullptr;
    }
    newTree->root = nullptr;
    newTree->NIL = nullptr;
    return newTree;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
    auto startTime = std::chrono::high_resolution_clock::now();
    InsertResult stats = InsertResult{0, 0};
    if (!tree) {
        std::cerr << "Erro: arvore nao inicializada." << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    if (!tree->root) {
        Node* newNode = new Node;
        if (!newNode) {
            std::cerr << "Erro na alocacao de memoria para o no." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        newNode->word = word;
        newNode->documentIds = std::vector<int>{documentId};
        newNode->parent = nullptr;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 0;
        newNode->isRed = -1;
        tree->root = newNode;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    // Actual function
    Node* actualNode = tree->root;
    while (actualNode->left != nullptr || actualNode->right != nullptr) {
        stats.numComparisons++;
        if (word == actualNode->word) {
            actualNode->documentIds.push_back(documentId);
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        stats.numComparisons++;
        if (word < actualNode->word) {
            actualNode = actualNode->left;
            continue;
        }
        actualNode = actualNode->right;
    }

    stats.numComparisons++;
    if (word == actualNode->word) {
        actualNode->documentIds.push_back(documentId);
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    Node* newNode = new Node;
    if (!newNode) {
        std::cerr << "Erro na alocacao de memoria para o no." << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    newNode->word = word;
    newNode->documentIds = std::vector<int>{documentId};
    newNode->parent = actualNode;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = actualNode->height + 1;
    newNode->isRed = -1;

    stats.numComparisons++;
    if (word < actualNode->word) {
        actualNode->left = newNode;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }
    actualNode->right = newNode;

    auto endTime = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    return stats;
}







}