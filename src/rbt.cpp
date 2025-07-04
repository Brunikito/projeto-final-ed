#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "rbt.h"
#include "utils/tree_utils.h"
#include "utils/bench_utils.h"
#include "utils/value_utils.h"

namespace RBT {
    // cria uma nova Árvore Rubro-Negra com nó sentinela NIL
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
         if (!tree) {
            std::cerr << "Erro na alocacao da arvore" << std::endl;
            return nullptr;
        }
        tree->NIL = new Node;
        if (!tree->NIL) {
            std::cerr << "Erro na alocacao do NIL" << std::endl;
            return nullptr;
        }
        tree->NIL->isRed = false; // O nó sentinela é sempre preto.
        tree->NIL->word = "";     // Inicialização opcional para clareza.
        tree->NIL->documentIds = {};  // Inicialização opcional.
        
        // CORREÇÃO CRÍTICA: O sentinela deve apontar para si mesmo.
        tree->NIL->left = tree->NIL;
        tree->NIL->right = tree->NIL;
        tree->NIL->parent = tree->NIL;
		tree->NIL->height = 0;

        // A raiz inicialmente aponta para o sentinela.
        tree->root = tree->NIL;
        tree->root->parent = tree->NIL; // Garante que a raiz também aponta para o NIL como pai.

        return tree;
    }
    // retorna a altura de um nó
    int height(Node* node, Node* NIL, InsertResult& stats){
		if (node == NIL) return 0;
        return node->height;
    }

    // atualiza a altura de um nó com base em seus filhos
    void updateHeight(Node* node, Node* NIL, InsertResult& stats){
        stats.numComparisons++;
        if(node != NIL) {
            stats.numComparisons++;
            node->height = ValueUtils::max(height(node->left, NIL, stats), height(node->right, NIL, stats)) + 1;
        }
    }

    // atualiza recursivamente a altura de um nó e seu pai
    void recursiveUpdateHeight(Node* node, Node* NIL, InsertResult& stats){
        stats.numComparisons++;
        if (node == NIL) return;
        updateHeight(node, NIL, stats);
        updateHeight(node->parent, NIL, stats);

    }    
    Node* rightRotate(Node* y, Node* NIL, InsertResult& stats) {
        Node* x = y->left;
        Node* T2 = x->right;

        // performa rotatacao
        x->right = y;
        y->left = T2;

        // atualiza parents
        x->parent = y->parent;
        y->parent = x;

        stats.numComparisons++;
        if (T2 != NIL) {
            T2->parent = y;
        }

        // Update parent's pointer to x (the new root of this subtree)
        stats.numComparisons++;
        if (x->parent != NIL) {
            stats.numComparisons++;
            if (x->parent->left == y) {
                x->parent->left = x;
            } else {
                x->parent->right = x;
            }
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

        // performa rotacao
        z->left = y;
        y->right = T3;

        // atualiza parents
        z->parent = y->parent;
        y->parent = z;
        stats.numComparisons++;
        if (T3 != NIL) {
            T3->parent = y;
        }

        // Update parent's pointer to z (the new root of this subtree)
        stats.numComparisons++;
        if (z->parent != NIL) {
            stats.numComparisons++;
            if (z->parent->left == y) {
                z->parent->left = z;
            } else {
                z->parent->right = z;
            }
        }

        // Update heights
        updateHeight(y, NIL, stats);
        updateHeight(z, NIL, stats);
        recursiveUpdateHeight(z, NIL, stats);

        return z;
    }

    // Insere um novo nó com palavra e documentId
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
    
    // corrige as propriedades da árvore após inserção
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
                uncle = grandparent->right;
                stats.numComparisons++;
                if (uncle->isRed == 1) {
                    parent->isRed = 0;
                    uncle->isRed = 0;
                    grandparent->isRed = 1;
                    actualNode = grandparent;
                    continue;
                }                stats.numComparisons++;
                if (actualNode == parent->right) {
                        Node* newParent = leftRotate(parent, tree->NIL, stats);
                        if (newParent->parent == tree->NIL) {
                            tree->root = newParent;
                        }
                        actualNode = parent;
                        parent = actualNode->parent;
                        grandparent = parent->parent;
                }
                parent->isRed = 0;
                grandparent->isRed = 1;
                Node* newGrandparent = rightRotate(grandparent, tree->NIL, stats);
                if (newGrandparent->parent == tree->NIL) {
                    tree->root = newGrandparent;
                }
                return;
            }
            uncle = grandparent->left;
            stats.numComparisons++;
            if (uncle->isRed == 1) {
                parent->isRed = 0;
                uncle->isRed = 0;
                grandparent->isRed = 1;
                actualNode = grandparent;
                continue;
            }            stats.numComparisons++;
            if (actualNode == parent->left) {
                    Node* newParent = rightRotate(parent, tree->NIL, stats);
                    if (newParent->parent == tree->NIL) {
                        tree->root = newParent;
                    }
                    actualNode = parent;
                    parent = actualNode->parent;
                    grandparent = parent->parent;
            }
            parent->isRed = 0;
            grandparent->isRed = 1;
            Node* newGrandparent = leftRotate(grandparent, tree->NIL, stats);
            if (newGrandparent->parent == tree->NIL) {
                tree->root = newGrandparent;
            }
            return;
        }
    }
    
    // insere palavra ou adiciona documentId e balanceia a árvore
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
			recursiveUpdateHeight(newNode, tree->NIL, stats);
            tree->root->isRed = 0;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    // Busca palavra e retorna documentos associados
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