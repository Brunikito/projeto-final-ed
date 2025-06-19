#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "rbt.h"
#include "utils/tree_utils.h"
#include "utils/bench_utils.h"

namespace RBT {

    // Declarações antecipadas das funções internas (forward declarations)
    void fixInsert(BinaryTree* tree, Node* k, InsertResult& stats);
    void leftRotate(BinaryTree* tree, Node* x, InsertResult& stats);
    void rightRotate(BinaryTree* tree, Node* x, InsertResult& stats);
    void destroyNode(Node* node, Node* NIL);

    // Cria uma nova Árvore Rubro-Negra com nó sentinela NIL
    BinaryTree* create() {
        BinaryTree* newtree = new BinaryTree;
        if (!newtree) return nullptr;

        Node* nil = new Node;
        if (!nil) {
            delete newtree;
            return nullptr;
        }
        
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        nil->isRed = false; // NIL é sempre preto
        nil->height = 0; // Pode manter por compatibilidade com getTreeStats, mas não é usado para balancear

        newtree->NIL = nil;
        newtree->root = newtree->NIL;
        
        return newtree; 
    }

    void leftRotate(BinaryTree* tree, Node* x, InsertResult& stats) {
        stats.numRotations.LL++;
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

    void rightRotate(BinaryTree* tree, Node* x, InsertResult& stats) {
        stats.numRotations.RR++;
        Node* y = x->left;
        x->left = y->right;

        if (y->right != tree->NIL) {
            y->right->parent = x;
        }
        
        y->parent = x->parent;

        if (x->parent == tree->NIL) {
            tree->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    // Corrige as propriedades da árvore após inserção (implementação padrão)
    void fixInsert(BinaryTree* tree, Node* k, InsertResult& stats) {
        Node* u; // uncle
        while (k->parent->isRed) {
            stats.numComparisons++; // Loop condition check
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right; // Tio
                if (u->isRed) { // CASO 1: Tio é vermelho
                    stats.numRecoloring++;
                    k->parent->isRed = false;
                    u->isRed = false;
                    k->parent->parent->isRed = true;
                    k = k->parent->parent;
                } else { // CASO 2 e 3: Tio é preto
                    if (k == k->parent->right) { // CASO 2: Triângulo
                        k = k->parent;
                        leftRotate(tree, k, stats);
                    }
                    // CASO 3: Linha
                    stats.numRecoloring++;
                    k->parent->isRed = false;
                    k->parent->parent->isRed = true;
                    rightRotate(tree, k->parent->parent, stats);
                }
            } else { // Caso simétrico: pai é filho direito
                u = k->parent->parent->left; // Tio
                if (u->isRed) { // CASO 1
                    stats.numRecoloring++;
                    k->parent->isRed = false;
                    u->isRed = false;
                    k->parent->parent->isRed = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) { // CASO 2
                        k = k->parent;
                        rightRotate(tree, k, stats);
                    }
                    // CASO 3
                    stats.numRecoloring++;
                    k->parent->isRed = false;
                    k->parent->parent->isRed = true;
                    leftRotate(tree, k->parent->parent, stats);
                }
            }
        }
        tree->root->isRed = false;
    }

    // Insere palavra ou adiciona documentId e balanceia a árvore
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto startTime = std::chrono::high_resolution_clock::now();
        InsertResult stats = InsertResult{0, 0.0, {0, 0, 0, 0}, 0, 0, 0};

        if (tree == nullptr || tree->NIL == nullptr) {
            std::cerr << "Erro: arvore ou NIL nao inicializado." << std::endl;
            return stats;
        }

        Node* y = tree->NIL;
        Node* x = tree->root;
        int currentDepth = 0;

        while (x != tree->NIL) {
            y = x;
            stats.numComparisons++;
            int comparison = word.compare(x->word);
            
            if (comparison == 0) {
                x->documentIds.push_back(documentId);
                stats.insertDepth = currentDepth;
                auto endTime = std::chrono::high_resolution_clock::now();
                stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                return stats; // Palavra já existe, não precisa balancear.
            }
            
            if (comparison < 0) {
                x = x->left;
            } else {
                x = x->right;
            }
            currentDepth++;
        }

        Node* z = new Node;
        z->word = word;
        z->documentIds.push_back(documentId);
        z->parent = y;
        z->left = tree->NIL;
        z->right = tree->NIL;
        z->isRed = true; // Novos nós são sempre vermelhos
        stats.insertDepth = currentDepth;

        if (y == tree->NIL) {
            tree->root = z;
        } else if (z->word < y->word) {
            y->left = z;
        } else {
            y->right = z;
        }

        fixInsert(tree, z, stats);
        
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    // Busca palavra e retorna documentos associados
    SearchResult search(BinaryTree* tree, const std::string& word) {
        auto startTime = std::chrono::high_resolution_clock::now();
        SearchResult stats = SearchResult{0, {}, 0.0, 0, 0};

        if (tree == nullptr || tree->NIL == nullptr) {
            return stats;
        }

        Node* actualNode = tree->root;
        int actualDepth = 0;
        while (actualNode != tree->NIL) {
            stats.numComparisons++;
            int comparison = word.compare(actualNode->word);

            if (comparison == 0) {
                stats.found = 1;
                stats.documentIds = actualNode->documentIds;
                stats.searchDepth = actualDepth;
                break; // Encontrou
            }
            
            actualDepth++;
            if (comparison < 0) {
                actualNode = actualNode->left;
            } else {
                actualNode = actualNode->right;
            }
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
        if (node == NIL || node == nullptr) return;
        destroyNode(node->left, NIL);
        destroyNode(node->right, NIL);
        delete node;
    }

    // Libera toda a memória alocada pela árvore
    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyNode(tree->root, tree->NIL);
        if (tree->NIL != nullptr) {
            delete tree->NIL;
        }
        delete tree;
    }

} // namespace RBT