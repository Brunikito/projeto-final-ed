#include "avl.h"
#include "tree_utils.h"
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>


Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats, Node* parent) ;
Node* rebalance(Node* node);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int height(Node* node);
int getBalance(Node* node);
void updateHeight(Node* node);



BinaryTree* Create() {
    BinaryTree* newtree = new BinaryTree;
    if (!newtree) {
        std::cerr << "Erro na alocação" << std::endl;
        return nullptr;
    }
    newtree->root = nullptr;
    newtree->NIL = nullptr; // Não usado na AVL
    return newtree;    

}

int Height(Node* node) {
if (node == nullptr) {
    return -1; 
}
    return node->height;
}

void updateHeight(Node* node) {
    if(node != nullptr) {
        node->height = std::max(Height(node->left), Height(node->right)) + 1;
    }
}

int getBalance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->right) - height(node->left);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* rebalance(Node* node) {
    updateHeight(node);
    int balance = getBalance(node);

    if (balance < -1) {
        if (getBalance(node->left) > 0) {
            node->left = rightRotate(node->left);
        }
        return rightRotate(node);
    }

    if (balance > 1) {
        if (getBalance(node->right) < 0) {
            node->right = leftRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats, Node* parent) {
    if (root == nullptr) {
        Node* newNode = new Node;
        if (!newNode) {
            std::cerr << "Erro na alocação donovo nó." << std::endl;
            return nullptr;
        }
        newNode->word = word;
        newNode->documentIds.push_back(documentId);
        newNode->parent = parent;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 0; // Novo nó tem altura 0
        stats.numComparisons++;
        return newNode;
    }

    if (word < root->word) {
        stats.numComparisons++;
        root->left = insertNode(root->left, word, documentId, stats, root);
    } else if (word > root->word) {
        stats.numComparisons++;
        root->right = insertNode(root->right, word, documentId, stats, root);
    } else {
        // Palavra já existe, adiciona o ID do documento
        if (std::find(root->documentIds.begin(), root->documentIds.end(), documentId) == root->documentIds.end()) {
            root->documentIds.push_back(documentId);
        }
    }

    return rebalance(root);
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
    Node* parent = nullptr;
    while (actualNode != nullptr) {
        stats.numComparisons++;
        if (word == actualNode->word) {
            actualNode->documentIds.push_back(documentId);
            auto endTime = std::chrono::high_resolution_clock::now();
            stats.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            return stats;
        }
        stats.numComparisons++;
        parent = actualNode;
        if (word < actualNode->word) {
            actualNode = actualNode->left;
            continue;
        }
        actualNode = actualNode->right;
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
    newNode->parent = parent;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 0;
    newNode->isRed = -1;

    stats.numComparisons++;
    if (word < parent->word) {
        parent->left = newNode;
        }
    else parent->right = newNode;

    while (parent != nullptr) {
        if (parent->left == nullptr || parent->right == nullptr) {
            parent->height++;
        } else {
            parent->height = std::max(parent->left->height, parent->right->height) + 1;
        }
        parent = parent->parent;
    }

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

