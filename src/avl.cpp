#include "avl.h"
#include "tree_utils.h"
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>

namespace AVL{
    BinaryTree* create() {
        BinaryTree* newtree = new BinaryTree;
        if (!newtree) {
            std::cerr << "Erro na alocacao" << std::endl;
            return nullptr;
        }
        newtree->root = nullptr;
        newtree->NIL = nullptr; // Não usado na AVL
        return newtree;    
    }

    int height(Node* node) { return node == nullptr ? 0 : node->height; }

    void updateHeight(Node* node) {
        if(node != nullptr) {
            node->height = std::max(height(node->left), height(node->right)) + 1;
        }
    }

    void recursiveUpdateHeight(Node* node, int& numComparisons) {
        if (node == nullptr) {
            numComparisons++;
            return;
        }
        updateHeight(node);
        updateHeight(node->parent);
        numComparisons += 3;
    }

    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return height(node->right) - height(node->left);
    }    /** 
     *           y                        x
     *        /     \                    / \
     *       x       z       =>         T1  y
     *      / \     / \                    / \
     *     T1 T2   T3 T4                  T2  z
     *                                       / \
     *                                      T3 T4
     */
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update parents
        x->parent = y->parent;
        y->parent = x;
        if (T2 != nullptr) {
            T2->parent = y;
        }

        // Update heights
        updateHeight(y);
        updateHeight(x);

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
    Node* leftRotate(Node* y) {
        Node* z = y->right;
        Node* T3 = z->left;

        // Perform rotation
        z->left = y;
        y->right = T3;

        // Update parents
        z->parent = y->parent;
        y->parent = z;
        if (T3 != nullptr) {
            T3->parent = y;
        }

        // Update heights
        updateHeight(y);
        updateHeight(z);

        return z;
    }    Node* rebalance(Node* node, int& numComparisons) {
        if (node == nullptr) return node;
        
        updateHeight(node);
        int balance = getBalance(node);

        // Rotação à direita
        if (balance < -1) {
            numComparisons++;
            if (getBalance(node->left) > 0) {
                // Rotação dupla esquerda-direita
                node->left = leftRotate(node->left);
                numComparisons++;
            }
            return rightRotate(node);
        }

        // Rotação à esquerda
        if (balance > 1) {
            numComparisons++;
            if (getBalance(node->right) < 0) {
                // Rotação dupla direita-esquerda
                node->right = rightRotate(node->right);
                numComparisons++;
            }
            return leftRotate(node);
        }

        return node;
    }Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats) {
        if (root == nullptr) {
            stats.numComparisons++;
            Node* newNode = new Node;
            if (!newNode) {
                std::cerr << "Erro na alocacao do novo no." << std::endl;
                stats.numComparisons++;
                return nullptr;
            }
            stats.numComparisons++;
            newNode->word = word;
            newNode->documentIds = std::vector<int> {documentId};
            newNode->parent = nullptr;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->isRed = -1;
            newNode->height = 1;
            return newNode;
        }

        if (word < root->word) {
            stats.numComparisons++;
            root->left = insertNode(root->left, word, documentId, stats);
            if (root->left != nullptr) {
                root->left->parent = root;
            }
        } else if (word > root->word) {
            stats.numComparisons++;
            root->right = insertNode(root->right, word, documentId, stats);
            if (root->right != nullptr) {
                root->right->parent = root;
            }
        } else {
            // Palavra já existe, adiciona o ID do documento
            if (std::find(root->documentIds.begin(), root->documentIds.end(), documentId) == root->documentIds.end()) {
                root->documentIds.push_back(documentId);
            }
            return root;
        }

        // Update height and balance
        updateHeight(root);
        return rebalance(root, stats.numComparisons);
    }    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto startTime = std::chrono::high_resolution_clock::now();
        InsertResult stats = InsertResult{0, 0};
        if (tree == nullptr) {
            std::cerr << "Erro: arvore nao inicializada." << std::endl;
            stats.numComparisons++;
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
        while (actualNode != nullptr) {
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

        auto endTime = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return result;
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