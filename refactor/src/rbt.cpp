#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "rbt.h"
#include "utils/tree_utils.h"
#include "utils/bench_utils.h"
#include "utils/value_utils.h"

namespace RBT {

    BinaryTree* create() {
        BinaryTree* newtree = new BinaryTree;
        if (!newtree) {
            std::cerr << "Erro na alocacao da arvore" << std::endl;
            return nullptr;
        }

        Node* nil = new Node;
        if (!nil) {
            std::cerr << "Erro na alocacao do NIL" << std::endl;
            return nullptr;
        }
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        nil->height = 0;
        nil->isRed = 0;
        newtree->root = nil;
        newtree->NIL = nil;
        return newtree;    
    }

    int height(Node* node, Node* NIL, InsertResult& stats){
        return node->height;
    }

    void updateHeight(Node* node, Node* NIL, InsertResult& stats){
        stats.numComparisons++;
        if(node != NIL) {
            stats.numComparisons++;
            node->height = ValueUtils::max(height(node->left, NIL, stats), height(node->right, NIL, stats)) + 1;
        }
    }

    void recursiveUpdateHeight(Node* node, Node* NIL, InsertResult& stats){
        stats.numComparisons++;
        if (node == NIL) return;
        updateHeight(node, NIL, stats);
        updateHeight(node->parent, NIL, stats);

    }

    Node* rightRotate(Node* y, Node* NIL, InsertResult& stats) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update parents
        x->parent = y->parent;
        y->parent = x;

        stats.numComparisons++;
        if (T2 != NIL) {
            T2->parent = y;
        }

        // Update heights
        updateHeight(y, NIL, stats);
        updateHeight(x, NIL, stats);
        recursiveUpdateHeight(x, NIL, stats);

        return x;
    }

    Node* leftRotate(Node* y, Node* NIL, InsertResult& stats) {
        Node* z = y->right;
        Node* T3 = z->left;

        // Perform rotation
        z->left = y;
        y->right = T3;

        // Update parents
        z->parent = y->parent;
        y->parent = z;
        stats.numComparisons++;
        if (T3 != NIL) {
            T3->parent = y;
        }

        // Update heights
        updateHeight(y, NIL, stats);
        updateHeight(z, NIL, stats);
        recursiveUpdateHeight(z, NIL, stats);

        return z;
    }

    Node* insertNode(BinaryTree* tree, const std::string& word, int documentId, InsertResult& stats){
        stats.numComparisons++;
        if (tree == nullptr) {
            std::cerr << "Erro: arvore nao inicializada." << std::endl;
            return nullptr;
        }
        stats.numComparisons++;
        if (tree->NIL == nullptr) {
            std::cerr << "Erro: NIL não inicializado." << std::endl;
            return nullptr;
        }

        Node* parent = tree->NIL;
        Node* actualNode = tree->root;
        int currentDepth = 0;
        stats.numComparisons++;
        while (actualNode != tree->NIL) {
            parent = actualNode;
            stats.numComparisons += 2;
            if (word == actualNode->word) {
                stats.insertDepth = currentDepth;
                actualNode->documentIds.push_back(documentId);
                return nullptr;
            }
            stats.numComparisons++;
            currentDepth++;
            if (word < actualNode->word) {
                actualNode = actualNode->left;
                continue;
            }
            actualNode = actualNode->right;
        }
        Node* newNode = new Node;
        if (newNode == nullptr) {
            std::cerr << "Erro: novo no não inicializado." << std::endl;
            return nullptr;
        }
        newNode->word = word;
        newNode->documentIds = std::vector<int>{documentId};
        newNode->parent = parent;
        newNode->left = tree->NIL;
        newNode->right = tree->NIL;
        newNode->isRed = true;

        stats.numComparisons++;
        if (parent == tree->NIL) {
            tree->root = newNode;
            return newNode;
        }
        stats.numComparisons++;
        if (word < parent->word) {
            parent->left = newNode;
            return newNode;
        }
        parent->right = newNode;
        return newNode;
    }
    
    void fixInsert(BinaryTree* tree, Node* insertedNode, InsertResult& stats) {
        stats.numComparisons++;
        if (tree == nullptr) {
            std::cerr << "Erro: arvore nao inicializada." << std::endl;
            return;
        }
        stats.numComparisons++;
        if (tree->NIL == nullptr) {
            std::cerr << "Erro: NIL não inicializado." << std::endl;
            return;
        }
        Node *parent, *grandparent, *uncle;
        stats.numComparisons++;
        if (insertedNode->parent->isRed == 0) return;
        Node* actualNode = insertedNode;
        stats.numComparisons++;
        while (actualNode->parent->isRed == 1){ // o nil é preto, então basta isso
            parent = actualNode->parent;
            grandparent = parent->parent;
            stats.numComparisons++;
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                stats.numComparisons++;
                if (uncle->isRed == 1) {
                    parent->isRed = 0;
                    uncle->isRed = 0;
                    grandparent->isRed = 1;
                    actualNode = grandparent;
                    continue;
                } 
                stats.numComparisons++;
                if (actualNode == parent->right) {
                        leftRotate(parent, tree->NIL, stats);
                        actualNode = parent;
                        parent = actualNode->parent;
                        grandparent = parent->parent;
                }
                parent->isRed = 0;
                grandparent->isRed = 1;
                rightRotate(grandparent, tree->NIL, stats);
                return;
            }
            Node* uncle = grandparent->left;
            stats.numComparisons++;
            if (uncle->isRed == 1) {
                parent->isRed = 0;
                uncle->isRed = 0;
                grandparent->isRed = 1;
                actualNode = grandparent;
                continue;
            } 
            stats.numComparisons++;
            if (actualNode == parent->left) {
                    rightRotate(actualNode, tree->NIL, stats);
                    actualNode = parent;
                    parent = actualNode->parent;
                    grandparent = parent->parent;
            }
            parent->isRed = 0;
            grandparent->isRed = 1;
            leftRotate(grandparent, tree->NIL, stats);
            return;
        }
    }
    
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto startTime = std::chrono::high_resolution_clock::now();
        InsertResult stats = InsertResult{0, 0.0, {0, 0, 0, 0}, 0, 0, 0}; // tree_utils v>=3.0.0
        stats.numComparisons++;
        if (tree == nullptr) {
            std::cerr << "Erro: arvore nao inicializada." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        stats.numComparisons++;
        if (tree->NIL == nullptr) {
            std::cerr << "Erro: NIL não inicializado." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        Node* newNode = insertNode(tree, word, documentId, stats);
        stats.numComparisons++;
        if (newNode != nullptr) {
            fixInsert(tree, newNode, stats);
            tree->root->isRed = 0;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    SearchResult search(BinaryTree* tree, const std::string& word) {
        auto startTime = std::chrono::high_resolution_clock::now();
        SearchResult stats = SearchResult{0, {}, 0.0, 0, 0};
        stats.numComparisons++;
        if (tree == nullptr) {
            std::cerr << "Erro: arvore nao inicializada." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        stats.numComparisons++;
        if (tree->NIL == nullptr) {
            std::cerr << "Erro: NIL não inicializado." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        stats.numComparisons++;
        if (tree->root == tree->NIL) {
            std::cerr << "Erro: arvore vazia." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }

        // Actual function
        Node* actualNode = tree->root;
        stats.numComparisons++;
        int actualDepth = 0;
        while (actualNode != tree->NIL) {
            stats.numComparisons+=2; // 1 do while e 1 do próximo for
            if (word == actualNode->word) {
                stats.found = 1;
                stats.documentIds = actualNode->documentIds;
                stats.searchDepth = actualDepth;
                auto endTime = std::chrono::high_resolution_clock::now();
                stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                return stats;
            }
            actualDepth++;
            stats.numComparisons++;
            if (word < actualNode->word) {
                actualNode = actualNode->left;
                continue;
            }
            actualNode = actualNode->right;
        }

        stats.searchDepth = actualDepth;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    // Função auxiliar para recursão
    void destroyNode(Node* node, Node* NIL) {
        if (node == NIL) return;
        destroyNode(node->left, NIL);
        destroyNode(node->right, NIL);
        delete node;
        node = nullptr;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;

        // Inicia a recursão
        destroyNode(tree->root, tree->NIL);
        if (tree->NIL != nullptr) {
            delete tree->NIL;
            tree->NIL = nullptr;
        }
        delete tree;
        tree = nullptr;
    }

} // namespace RBT