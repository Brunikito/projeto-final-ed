#define AVL_H
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "tree_utils.h"

namespace AVL {
    Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats, Node* parent) ;
    Node* rebalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int height(Node* node);
    int getBalance(Node* node);
    void updateHeight(Node* node);
    BinaryTree* create();
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroy(BinaryTree* tree);
}