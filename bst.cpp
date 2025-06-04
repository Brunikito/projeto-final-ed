#include "bst.h"
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <chrono>

namespace BST{

BinaryTree* create() {
    BinaryTree* newTree = new BinaryTree;
    if (newTree == nullptr) {
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
    if (tree == nullptr) {
        std::cerr << "Erro: arvore nao inicializada." << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    if (tree->root == nullptr) {
        Node* newNode = new Node;
        if (newNode == nullptr) {
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

    // Last Node
    stats.numComparisons++;
    if (word == actualNode->word) {
        actualNode->documentIds.push_back(documentId);
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    Node* newNode = new Node;
    if (newNode == nullptr) {
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

SearchResult search(BinaryTree* tree, const std::string& word){
    auto startTime = std::chrono::high_resolution_clock::now();
    SearchResult result;
    result.found = 0;
    result.documentIds = std::vector<int>{};
    result.executionTime = 0;
    result.numComparisons = 0;
    if (tree == nullptr) {
        std::cerr << "Erro: arvore nao inicializada." << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return result;
    }

    if (tree->root == nullptr) {
        std::cerr << "Erro: arvore vazia." << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return result;
    }

    // Actual function
    Node* actualNode = tree->root;
    while (actualNode->left != nullptr || actualNode->right != nullptr) {
        result.numComparisons++;
        if (word == actualNode->word) {
            result.found = 1;
            result.documentIds = actualNode->documentIds;
            auto endTime = std::chrono::high_resolution_clock::now();
            result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return result;
        }
        result.numComparisons++;
        if (word < actualNode->word) {
            actualNode = actualNode->left;
            continue;
        }
        actualNode = actualNode->right;
    }

    // Last Node
    result.numComparisons++;
    if (word == actualNode->word) {
        result.found = 1;
        result.documentIds = actualNode->documentIds;
        auto endTime = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return result;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    return result;
}

void destroy(BinaryTree* tree){
    if (tree == nullptr) return;
    if (tree->NIL) delete tree->NIL;
    if (tree->root == nullptr){
        delete tree;
        return;
    }

    // Deleta todos os nós da árvore exceto a raiz
    Node* actualNode = tree->root;
    while (actualNode->left != nullptr || actualNode->right != nullptr || actualNode->parent != nullptr){
        if (actualNode->left == nullptr && actualNode->right == nullptr) {
            Node* parentNode = actualNode->parent;
            if (parentNode->left == actualNode) {
                parentNode->left = nullptr;
            } else {
                parentNode->right = nullptr;
            }
            delete actualNode;
            actualNode = parentNode;
        }
        else if (actualNode->left) {
            actualNode = actualNode->left;
        } else {
            actualNode = actualNode->right;
        }
    }

    // Deleta a raiz
    delete actualNode;
    tree->root = nullptr;
    return;

}