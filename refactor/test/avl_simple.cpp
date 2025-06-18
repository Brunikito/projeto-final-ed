// Versão simplificada para testes AVL
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>

#include "avl_simple.h"
#include "tree_utils_simple.h"

namespace AVL{
    BinaryTree* create() {
        BinaryTree* newtree = new BinaryTree;
        if (!newtree) {
            std::cerr << "Erro na alocacao" << std::endl;
            return nullptr;
        }
        newtree->root = nullptr;
        newtree->NIL = nullptr;
        return newtree;    
    }

    int height(Node* node, InsertResult& stats){
        stats.numComparisons++;
        return node == nullptr ? 0 : node->height;
    }

    void updateHeight(Node* node, InsertResult& stats){
        stats.numComparisons++;
        if(node != nullptr) {
            stats.numComparisons++;
            node->height = std::max(height(node->left, stats), height(node->right, stats)) + 1;
        }
    }

    void recursiveUpdateHeight(Node* node, InsertResult& stats){
        stats.numComparisons++;
        if (node == nullptr) return;
        updateHeight(node, stats);
        updateHeight(node->parent, stats);

    }

    int getBalance(Node* node, InsertResult& stats){
        stats.numComparisons++;
        if (node == nullptr) return 0;
        return height(node->right, stats) - height(node->left, stats);
    }

    
    /** 
     *           y                        x
     *        /     \                    / \
     *       x       z       =>         T1  y
     *      / \     / \                    / \
     *     T1 T2   T3 T4                  T2  z
     *                                       / \
     *                                      T3 T4
     */
    Node* rightRotate(Node* y, InsertResult& stats) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update parents
        x->parent = y->parent;
        y->parent = x;

        stats.numComparisons++;
        if (T2 != nullptr) {
            T2->parent = y;
        }

        // Update heights
        updateHeight(y, stats);
        updateHeight(x, stats);

        return x;
    }

    /** 
     *           y                        z
     *        /     \                    / \
     *       x       z       =>         y  T4
     *      / \     / \                / \
     *     T1 T2   T3 T4              x  T3
     *                               / \
     *                              T1 T2
     */
    Node* leftRotate(Node* y, InsertResult& stats) {
        Node* z = y->right;
        Node* T3 = z->left;

        // Perform rotation
        z->left = y;
        y->right = T3;

        // Update parents
        z->parent = y->parent;
        y->parent = z;
        stats.numComparisons++;
        if (T3 != nullptr) {
            T3->parent = y;
        }

        // Update heights
        updateHeight(y, stats);
        updateHeight(z, stats);

        return z;
    }    
      Node* rebalance(Node* node, InsertResult& stats) {
        if (node == nullptr) return node;
        
        updateHeight(node, stats);
        int balance = getBalance(node, stats);

        // Rotação à direita (caso esquerda-esquerda ou esquerda-direita)
        if (balance < -1) {
            if (getBalance(node->left, stats) > 0) {
                // Rotação dupla esquerda-direita
                node->left = leftRotate(node->left, stats);
                stats.numRotations.LR++;
            } else {
                stats.numRotations.RR++;
            }
            return rightRotate(node, stats);
        }

        // Rotação à esquerda (caso direita-direita ou direita-esquerda)
        if (balance > 1) {
            if (getBalance(node->right, stats) < 0) {
                // Rotação dupla direita-esquerda
                node->right = rightRotate(node->right, stats);
                stats.numRotations.RL++;
            } else {
                stats.numRotations.LL++;
            }
            return leftRotate(node, stats);
        }
        
        return node;
    }

    Node* insertNode(Node* node, const std::string& word, int documentId, InsertResult& stats) {
        Node* parent = node != nullptr? node->parent : nullptr;
        stats.numComparisons++;
        if (node == nullptr) {
            Node* newNode = new Node;
            stats.numComparisons++;
            if (!newNode) {
                std::cerr << "Erro na alocacao do novo no." << std::endl;
                return nullptr;
            }
            newNode->word = word;
            newNode->documentIds = std::vector<int> {documentId};
            newNode->parent = parent;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->isRed = -1;
            newNode->height = 1;
            return newNode;
        }
        
        stats.numComparisons++;
        if (word < node->word) {
            node->left = insertNode(node->left, word, documentId, stats);
            stats.numComparisons++;
            if (node->left != nullptr) {
                node->left->parent = node;
            }
        } else if (word > node->word) {
            stats.numComparisons++;
            node->right = insertNode(node->right, word, documentId, stats);
            stats.numComparisons++;
            if (node->right != nullptr) {
                node->right->parent = node;
            }        
        } else {
            // Palavra já existe, adiciona o ID do documento
            stats.numComparisons++;
            node->documentIds.push_back(documentId);
            return node;
        }

        // Update height and balance
        updateHeight(node, stats);
        return rebalance(node, stats);
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
        tree->root = insertNode(tree->root, word, documentId, stats); // Insere o nó e atualiza a raiz
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
        if (tree->root == nullptr) {
            std::cerr << "Erro: arvore vazia." << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }

        // Actual function
        Node* actualNode = tree->root;
        stats.numComparisons++;
        int actualDepth = 0;
        while (actualNode != nullptr) {
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
    void destroyNode(Node* node) {
        if (node == nullptr) return;
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
        node = nullptr;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        if (tree->NIL != nullptr) {
            delete tree->NIL;
        }
        // Inicia a recursão
        destroyNode(tree->root);
        delete tree;
        tree = nullptr;
    }

} // Namespace AVL
