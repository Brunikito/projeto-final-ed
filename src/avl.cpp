#include "avl.h"
#include "tree_utils.h"
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm> // Para std::max

namespace AVL {

// Declarações de funções auxiliares internas
Node* insertNode(Node* node, const std::string& word, int documentId, InsertResult& stats, Node* parent);
Node* rebalance(Node* node);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int height(Node* node);
int getBalance(Node* node);
void updateHeight(Node* node);

BinaryTree* create() {
    BinaryTree* newTree = new BinaryTree;
    if (newTree == nullptr) {
        std::cerr << "Erro na alocação de memoria para a AVL." << std::endl;
        return nullptr;
    }
    newTree->root = nullptr;
    newTree->NIL = nullptr; // Não usado na AVL, mas mantido por compatibilidade
    return newTree;
}

// --- Funções Auxiliares da AVL ---

// Retorna a altura de um nó (-1 para nulo)
int height(Node* node) {
    if (node == nullptr) return -1;
    return node->height;
}

// Atualiza a altura de um nó com base em seus filhos
void updateHeight(Node* node) {
    if (node != nullptr) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

// Calcula o fator de balanceamento de um nó
int getBalance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Rotação simples à direita
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;
    
    // Atualiza pais
    if (T2 != nullptr) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    // Atualiza alturas
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação simples à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza pais
    if (T2 != nullptr) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    // Atualiza alturas
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Rebalanceia a sub-árvore a partir do nó, se necessário
Node* rebalance(Node* node) {
    updateHeight(node);
    int balance = getBalance(node);

    // Caso 1: Desbalanceamento à Esquerda-Esquerda
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    // Caso 2: Desbalanceamento à Direita-Direita
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    // Caso 3: Desbalanceamento à Esquerda-Direita
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Desbalanceamento à Direita-Esquerda
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Nenhum rebalanceamento necessário
}

// --- Função de Inserção Principal ---

Node* insertNode(Node* node, const std::string& word, int documentId, InsertResult& stats, Node* parent) {
    // 1. Inserção padrão de BST
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->word = word;
        newNode->documentIds = {documentId};
        newNode->parent = parent;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 0;
        newNode->isRed = -1; // Não usado
        return newNode;
    }

    stats.numComparisons++;
    if (word < node->word) {
        node->left = insertNode(node->left, word, documentId, stats, node);
    } else if (word > node->word) {
        stats.numComparisons++;
        node->right = insertNode(node->right, word, documentId, stats, node);
    } else {
        stats.numComparisons++;
        node->documentIds.push_back(documentId);
        return node; // A palavra já existe, não precisa rebalancear
    }

    // 2. Rebalancear o nó ancestral
    return rebalance(node);
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto startTime = std::chrono::high_resolution_clock::now();
    InsertResult stats = {0, 0};

    if (tree == nullptr) {
        std::cerr << "Erro: arvore nao inicializada." << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return stats;
    }

    tree->root = insertNode(tree->root, word, documentId, stats, nullptr);
    
    // Atualiza a referência da raiz na árvore, caso tenha mudado após rotação
    if (tree->root != nullptr) {
        tree->root->parent = nullptr; 
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    return stats;
}


SearchResult search(BinaryTree* tree, const std::string& word){
    auto startTime = std::chrono::high_resolution_clock::now();
    SearchResult result;
    result.found = 0;
    result.documentIds = {};
    result.executionTime = 0;
    result.numComparisons = 0;
    
    if (tree == nullptr || tree->root == nullptr) {
        auto endTime = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        return result;
    }

    Node* actualNode = tree->root;
    while (actualNode != nullptr) {
        result.numComparisons++;
        if (word == actualNode->word) {
            result.found = 1;
            result.documentIds = actualNode->documentIds;
            break;
        }
        result.numComparisons++;
        if (word < actualNode->word) {
            actualNode = actualNode->left;
        } else {
            actualNode = actualNode->right;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    result.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    return result;
}


void destroyNode(Node* node) {
    if (node == nullptr) return;
    destroyNode(node->left);
    destroyNode(node->right);
    delete node;
}

void destroy(BinaryTree* tree) {
    if (tree == nullptr) return;
    destroyNode(tree->root);
    delete tree;
}

} // namespace AVL