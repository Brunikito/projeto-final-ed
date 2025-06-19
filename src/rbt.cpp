#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "rbt.h"
#include "utils/tree_utils.h" // Apenas para os structs de resultado
#include "utils/value_utils.h" // Apenas para ValueUtils::max se precisar

namespace RBT {

    // Função auxiliar para rotação à esquerda
    void leftRotate(BinaryTree* tree, Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != tree->NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == tree->NIL) {
            tree->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Função auxiliar para rotação à direita
    void rightRotate(BinaryTree* tree, Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != tree->NIL) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == tree->NIL) {
            tree->root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }
    
    // Corrige as propriedades da árvore após a inserção
    void fixInsert(BinaryTree* tree, Node* k) {
        Node* u; // uncle
        while (k->parent->isRed) {
            if (k->parent == k->parent->parent->right) { // pai é filho direito
                u = k->parent->parent->left; // tio é o filho esquerdo
                if (u->isRed) {
                    // Caso 1: Tio é vermelho
                    u->isRed = false;
                    k->parent->isRed = false;
                    k->parent->parent->isRed = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // Caso 2: Tio é preto, k é filho esquerdo (triângulo)
                        k = k->parent;
                        rightRotate(tree, k);
                    }
                    // Caso 3: Tio é preto, k é filho direito (linha)
                    k->parent->isRed = false;
                    k->parent->parent->isRed = true;
                    leftRotate(tree, k->parent->parent);
                }
            } else { // pai é filho esquerdo
                u = k->parent->parent->right; // tio é o filho direito
                if (u->isRed) {
                    // Caso 1: Tio é vermelho
                    u->isRed = false;
                    k->parent->isRed = false;
                    k->parent->parent->isRed = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // Caso 2: Tio é preto, k é filho direito (triângulo)
                        k = k->parent;
                        leftRotate(tree, k);
                    }
                    // Caso 3: Tio é preto, k é filho esquerdo (linha)
                    k->parent->isRed = false;
                    k->parent->parent->isRed = true;
                    rightRotate(tree, k->parent->parent);
                }
            }
            if (k == tree->root) {
                break;
            }
        }
        tree->root->isRed = false;
    }

    // Cria uma nova Árvore Rubro-Negra com nó sentinela NIL
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->NIL = new Node;
        tree->NIL->isRed = false;
        tree->NIL->word = ""; 
        tree->NIL->documentIds = {};
        
        tree->NIL->left = tree->NIL;
        tree->NIL->right = tree->NIL;
        tree->NIL->parent = tree->NIL;

        tree->root = tree->NIL;
        
        std::cout << "Arvore criada" << std::endl; // Debug
        return tree;
    }

    // Insere palavra ou adiciona documentId e balanceia a árvore
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto startTime = std::chrono::high_resolution_clock::now();
        InsertResult stats = {};
        
        Node* y = tree->NIL;
        Node* x = tree->root;
        int currentDepth = 0;

        while (x != tree->NIL) {
            y = x;
            stats.numComparisons++;
            if (word == x->word) {
                x->documentIds.push_back(documentId);
                stats.insertDepth = currentDepth;
                auto endTime = std::chrono::high_resolution_clock::now();
                stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                return stats; // Palavra já existe, apenas adiciona ID.
            }

            stats.numComparisons++;
            if (word < x->word) {
                x = x->left;
            } else {
                x = x->right;
            }
            currentDepth++;
        }

        Node* z = new Node;
        z->parent = y;
        z->word = word;
        z->documentIds.push_back(documentId);
        z->left = tree->NIL;
        z->right = tree->NIL;
        z->isRed = true;

        stats.insertDepth = currentDepth;
        
        if (y == tree->NIL) {
            tree->root = z;
        } else if (z->word < y->word) {
            y->left = z;
        } else {
            y->right = z;
        }

        if (z->parent == tree->NIL) {
            z->isRed = false; // Raiz é sempre preta
        } else if (z->parent->parent != tree->NIL) {
            fixInsert(tree, z);
        }
        
        tree->root->isRed = false; // Garante que a raiz é sempre preta

        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    // Busca palavra e retorna documentos associados
    SearchResult search(BinaryTree* tree, const std::string& word) {
        auto startTime = std::chrono::high_resolution_clock::now();
        SearchResult stats = {};

        Node* actualNode = tree->root;
        int actualDepth = 0;
        while (actualNode != tree->NIL) {
            stats.numComparisons++;
            if (word == actualNode->word) {
                stats.found = true;
                stats.documentIds = actualNode->documentIds;
                stats.searchDepth = actualDepth;
                break;
            }
            stats.numComparisons++;
            if (word < actualNode->word) {
                actualNode = actualNode->left;
            } else {
                actualNode = actualNode->right;
            }
            actualDepth++;
        }
        
        if (!stats.found) {
            stats.searchDepth = actualDepth;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    // Função auxiliar para destruir nós recursivamente
    void destroyNode(Node* node, Node* NIL) {
        if (node == NIL) return;
        destroyNode(node->left, NIL);
        destroyNode(node->right, NIL);
        delete node;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyNode(tree->root, tree->NIL);
        delete tree->NIL;
        delete tree;
    }

} // namespace RBT
